#ifndef INNEREL_h
#define INNEREL_h

// class for computing inner optimization of EL likelihood
#include <Rcpp.h>
using namespace Rcpp;
#include <RcppEigen.h>
using namespace Eigen;
// [[Rcpp::depends(RcppEigen)]]

template <typename ELModel>
class InnerEL : public ELModel { 
private:
    using ELModel::nObs;
    using ELModel::nEqs;
    using ELModel::G;
    // constants for logstar calculations
    double trunc, aa, bb, cc; 
    VectorXd lambdaOld;
    VectorXd lambdaNew;
    VectorXd omegas; // store the empirical distribution 
    // temporary storage for Newton-Raphson
    MatrixXd GGt;
    VectorXd Glambda;
    ArrayXd Gl11;
    VectorXd Q1;
    MatrixXd Q2;
    LDLT<MatrixXd> Q2ldlt;
    VectorXd rho;
    VectorXd relErr;
    // columnwise outer product (see below)
    void blockOuter(void);
    // maximum relative error in lambda: same for cens / non-cens
    double maxRelErr(const Ref<const VectorXd>& lambdaNew,
                     const Ref<const VectorXd>& lambdaOld);
public:
    // constructor for regression-like problems: old 
    // InnerEL(const Ref<const VectorXd>& y, const Ref<const MatrixXd>& X, 
    //       void* params);
    InnerEL(); // default ctor
    void setData(const Ref<const VectorXd>& _y, const Ref<const MatrixXd>& _X, 
                 void* _params);
    // logstar and its derivatives
    double logstar(double x);
    double logstar1(double x);
    double logstar2(double x);
    // Newton-Raphson algorithm
    void lambdaNR(int& nIter, double& maxErr,
                  int maxIter, double relTol);
    VectorXd getLambda(); // get function for lambdaNew
    // log empirical likelihood calculation with given omega and G
    double logEL(); 
    // find the best omegas given G 
    void evalOmegas(int maxIter, double relTol); 
    // set and get functions 
    void setOmegas(const Ref<const VectorXd>& _omegas); 
    VectorXd getOmegas(); // returns omegas
    // posterior sampler: removed for now
    // MatrixXd PostSample(int nsamples, int nburn, VectorXd betaInit,
    //                     const Ref<const VectorXd>& sigs,
    //                     int maxIter, double relTol);
};

// // constructor for mean regression: old 
// template<typename ELModel>
// inline InnerEL<ELModel>::InnerEL(const Ref<const VectorXd>& y,
// 				 const Ref<const MatrixXd>& X,
// 				 void* params) : ELModel(y, X, params) {
//     // std::cout << nObs << std::endl;
//     // std::cout << nEqs << std::endl;
//     // logstar constants
//     omegas = VectorXd::Zero(nObs).array() + 1.0/(double)nObs; // Initialize to 1/nObs
//     trunc = 1.0 / nObs;
//     aa = -.5 * nObs*nObs;
//     bb = 2.0 * nObs;
//     cc = -1.5 - log(nObs);
//     // Newton-Raphson initialization
//     GGt = MatrixXd::Zero(nEqs,nObs*nEqs);
//     lambdaOld = VectorXd::Zero(nEqs); // Initialize to all 0's
//     lambdaNew = VectorXd::Zero(nEqs);
//     Q1 = VectorXd::Zero(nEqs);
//     Q2 = MatrixXd::Zero(nEqs,nEqs);
//     Glambda = VectorXd::Zero(nObs);
//     Gl11 = ArrayXd::Zero(nObs);
//     rho = VectorXd::Zero(nObs);
//     relErr = VectorXd::Zero(nEqs);
//     Q2ldlt.compute(MatrixXd::Identity(nEqs,nEqs));
// }

// default ctor 
template<typename ELModel>
inline InnerEL<ELModel>::InnerEL(){}

// set data with default ctor
template<typename ELModel>
inline void InnerEL<ELModel>::setData(const Ref<const VectorXd>& _y,
                                      const Ref<const MatrixXd>& _X,
                                      void* _params) {
    // std::cout << nObs << std::endl;
    // std::cout << nEqs << std::endl;
    ELModel::setData(_y,_X,_params); // set base class data 
    // logstar constants
    omegas = VectorXd::Zero(nObs).array() + 1.0/(double)nObs; // Initialize to 1/nObs
    trunc = 1.0 / nObs;
    aa = -.5 * nObs*nObs;
    bb = 2.0 * nObs;
    cc = -1.5 - log(nObs);
    // Newton-Raphson initialization
    GGt = MatrixXd::Zero(nEqs,nObs*nEqs);
    lambdaOld = VectorXd::Zero(nEqs); // Initialize to all 0's
    lambdaNew = VectorXd::Zero(nEqs);
    Q1 = VectorXd::Zero(nEqs);
    Q2 = MatrixXd::Zero(nEqs,nEqs);
    Glambda = VectorXd::Zero(nObs);
    Gl11 = ArrayXd::Zero(nObs);
    rho = VectorXd::Zero(nObs);
    relErr = VectorXd::Zero(nEqs);
    Q2ldlt.compute(MatrixXd::Identity(nEqs,nEqs));
}

// logstar
template<typename ELModel>
inline double InnerEL<ELModel>::logstar(double x) {
    if(x >= trunc) {
    return(log(x));
    } else {
    return((aa*x + bb)*x + cc);
    }
}

// d logstar(x)/dx
template<typename ELModel>
inline double InnerEL<ELModel>::logstar1(double x) {
    if(x >= trunc) {
    return(1.0/x);
    } else {
    // return(aa*x + bb);
    return(2.0*aa*x + bb); // TODO: should be (2*aa*x + bb) ?
    }
}

// d^2 logstar(x)/dx^2
template<typename ELModel>
inline double InnerEL<ELModel>::logstar2(double x) {
    if(x >= trunc) {
    return(-1.0/(x*x));
    } else {
    // return(aa);
    return(2.0*aa); // TODO: should be 2aa ?
    }
}

// for an (m x N) matrix G = [g1 ... gN], returns the (m x mN) matrix
// GGt = [g1 g1' ... gN gN']
template<typename ELModel>
inline void InnerEL<ELModel>::blockOuter(void) {
    // for each row of G, compute outer product and store as block
    for(int ii=0; ii<nObs; ii++) {
    GGt.block(0,ii*nEqs,nEqs,nEqs).noalias() = G.col(ii) * G.col(ii).transpose();
    }
    return;
}

// maximum relative error in lambda
template<typename ELModel>
inline double InnerEL<ELModel>::maxRelErr(const Ref<const VectorXd>& lambdaNew,
                                 const Ref<const VectorXd>& lambdaOld) {
    relErr = ((lambdaNew - lambdaOld).array() / (lambdaNew + lambdaOld).array()).abs();
    return(relErr.maxCoeff());
}

// Newton-Raphson algorithm
template<typename ELModel>
inline void InnerEL<ELModel>::lambdaNR(int& nIter, double& maxErr,
                              int maxIter, double relTol) {
    int ii, jj;
    blockOuter(); // initialize GGt
    //lambdaOld = lambdaIn; // initialize lambda
    // newton-raphson loop
    for(ii=0; ii<maxIter; ii++) {
        // Q1 and Q2
        Glambda.noalias() = lambdaOld.transpose() * G;
        Glambda = 1.0 - Glambda.array();
        Q2.fill(0.0);
        for(jj=0; jj<this->nObs; jj++) {
            rho(jj) = logstar1(Glambda(jj));
            Q2 += logstar2(Glambda(jj)) * GGt.block(0,jj*nEqs,nEqs,nEqs);
        }
        Q1 = -G * rho;
        // update lambda
        Q2ldlt.compute(Q2);
        lambdaNew.noalias() = lambdaOld - Q2ldlt.solve(Q1);
        maxErr = maxRelErr(lambdaNew, lambdaOld); // maximum relative error
        if (maxErr < relTol) {
            break;
        }
        lambdaOld = lambdaNew; // complete cycle
    }
    nIter = ii; // output lambda and also nIter and maxErr
    return;
}

template<typename ELModel>
inline VectorXd InnerEL<ELModel>::getLambda() {
    return(lambdaNew);
}

// TODO: now G must have been assigned before calling this function 
// const Ref<const VectorXd>& theta
// template<typename ELModel>
// inline void InnerEL<ELModel>::evalOmegas(int& nIter, double& maxErr, 
//                                          int maxIter, double relTol) {
template<typename ELModel>
inline void InnerEL<ELModel>::evalOmegas(int maxIter, double relTol) {
    // G must have been assigned
    int nIter;
    double maxErr; 
    // std::cout << "evalOmegas: before lambdaNew = " << lambdaNew << std::endl;
    lambdaNR(nIter, maxErr, maxIter, relTol);
    // std::cout << "evalOmegas: after lambdaNew = " << lambdaNew << std::endl;
    // check convergence 
    if (nIter == maxIter && maxErr > relTol) {
        omegas = VectorXd::Zero(nObs);
    }
    else {
        Glambda.noalias() = lambdaNew.transpose() * G;
        Gl11 = 1.0/(1.0-Glambda.array());
        omegas.array() = Gl11.array() / Gl11.sum();
    }
}

template<typename ELModel>
inline void InnerEL<ELModel>::setOmegas(const Ref<const VectorXd>& _omegas) {
    omegas = _omegas; 
}

template<typename ELModel>
inline VectorXd InnerEL<ELModel>::getOmegas() {
    return(omegas);
}

template<typename ELModel>
inline double InnerEL<ELModel>::logEL() {
    // check if omega is not a feasible solution with G return -Inf
    VectorXd rhs = G * omegas; // if feasible, should be approx a vector of 0s
    std::cout << "rhs = " << rhs.transpose() << std::endl; 
    // TODO: what tolarance?  
    if (rhs.array().sum() > 0.01) return -INFINITY;
    else return(omegas.array().log().sum());
}

// This version finds the maximized loglikelihood, 
//      or -Inf if no feasible omegas satisfies G.
// template<typename ELModel>
// inline double InnerEL<ELModel>::logEL(int maxIter, double relTol) {
//     evalOmegas(maxIter, relTol); // evaluate weights and assign them
//     // Maybe add a flag for lambdaNR's convergence..?
//     // if lambdaNR did not converge, return -Inf
//     if (omegas.sum() == 0) return -INFINITY;
//     else return(omegas.array().log().sum());
// }

// Old code: 
// log empirical likelihood for linear regression Y = X'beta + eps
// beta is ncol(X) x 1 = p x 1 vector
// REMOVED: const Ref<const VectorXd>& theta
// template<typename ELModel>
// inline double InnerEL<ELModel>::logEL(int maxIter, double relTol) {
//     int nIter;
//     double maxErr;
//     // ELModel::evalG(theta); // REMOVED here, evalG or assign G in export 
//     lambdaNR(nIter, maxErr, maxIter, relTol);
//     if (nIter == maxIter && maxErr > relTol) {
//         // std::cout << "lambdaNR did not coverge" << std::endl;
//         return(-INFINITY);
//     }
//     else {
//         // std::cout << "lambdaNR coverged" << std::endl;
//         Glambda.noalias() = lambdaNew.transpose() * G;
//         Gl11 = 1.0/(1.0-Glambda.array());
//         // std::cout << "Gl11 = " << Gl11 << std::endl;
//         return((log(Gl11) - log(Gl11.sum())).sum());
//     }
// }

// posterior sampler: removed for now
/*
template<typename ELModel>
inline MatrixXd InnerEL<ELModel>::PostSample(int nsamples, int nburn,
					     VectorXd betaInit, const Ref<const VectorXd>& sigs,
					     int maxIter, double relTol) {
  VectorXd betaOld = betaInit;
  VectorXd betaNew = betaOld;
  VectorXd betaProp = betaOld;
  int betalen = betaInit.size();
  MatrixXd beta_chain(betaInit.size(),nsamples);
  int nIter;
  double maxErr;
  double logELOld = logEL(nIter, maxErr, maxIter, relTol); // NEW: chache old
  double logELProp;
  bool satisfy;
  double u;
  double a;
  double ratio;

  for (int ii=-nburn; ii<nsamples; ii++) {
    for (int jj=0; jj<betalen; jj++) {
      betaProp = betaOld;
      // betaProp(jj) = betaOld(jj) + sigs(jj)*R::norm_rand();
      betaProp(jj) += sigs(jj)*R::norm_rand();
      // check if proposed beta satisfies the constraint
      satisfy = false;
      // int nIter = 0;
      // double maxErr;
      // had a BUG here?! Didn't change G!!!
      ELModel::evalG(betaProp); // NEW: change G with betaProp
      lambdaNR(nIter, maxErr, maxIter, relTol);
      if (nIter < maxIter) satisfy = true;
      // if does not satisfy, keep the old beta
      if (satisfy == false) break;
      // if does satisfy, flip a coin
      u = R::unif_rand();
      // use the lambda calculate just now to get the logEL for Prop
      // to avoid an extra call of lambdaNR
      // VectorXd rlg = 1/(1-(lambdaNew.transpose()*ELModel::G).array());
      VectorXd logomegahat = log(1/(1-(lambdaNew.transpose()*ELModel::G).array())) -
        log((1/(1-(lambdaNew.transpose()*ELModel::G).array())).sum());
      logELProp = logomegahat.sum();
      ratio = exp(logELProp-logELOld);
      // std::cout << "ratio = " << ratio << std::endl;
      // double ratio = exp(logEL(y, X, betaProp, maxIter, relTol) -
      //                    logEL(y, X, betaOld, maxIter, relTol));
      a = std::min(1.0,ratio);
      if (u < a) { // accepted
        betaNew = betaProp;
        betaOld = betaNew;
        logELOld = logELProp; // NEW: store the new one
      }
    }
    if (ii >= 0) {
      beta_chain.col(ii) = betaNew;
    }
  }
  return(beta_chain);
}
*/

#endif
