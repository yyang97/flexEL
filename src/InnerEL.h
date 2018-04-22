#ifndef INNEREL_h
#define INNEREL_h

// class for computing inner optimization of EL likelihood
#include <Rcpp.h>
using namespace Rcpp;
#include <RcppEigen.h>
using namespace Eigen;
#include "MwgAdapt.h" // for adaptive mcmc
// [[Rcpp::depends(RcppEigen)]]

template <typename ELModel>
class InnerEL : public ELModel { 
private:
    using ELModel::nObs;
    using ELModel::nEqs;
    using ELModel::nBet;
    using ELModel::nGam;
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
    // tolerance for Newton-Raphson lambdaNR (New)
    int maxIter;
    double relTol;
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
    void setData(const Ref<const VectorXd>& _y, 
                 const Ref<const MatrixXd>& _X, 
                 void* _params);
    void setData(const Ref<const VectorXd>& _y, 
                 const Ref<const MatrixXd>& _X, 
                 const Ref<const MatrixXd>& _Z, 
                 void* _params);
    // logstar and its derivatives
    double logstar(double x);
    double logstar1(double x);
    double logstar2(double x);
    // Newton-Raphson algorithm
    void setTol(const int& _maxIter, const double& _relTol);
    void lambdaNR(int& nIter, double& maxErr);
    // void lambdaNR(int& nIter, double& maxErr,
    //               int maxIter, double relTol);
    // calculate omegas given G and lambda (New)
    void evalOmegas();
    // calculate logEL given omegas
    double logEL();
    // set and get functions 
    void setLambda(const Ref<const VectorXd>& _lambda); // assigned to lambdaNew
    void setOmegas(const Ref<const VectorXd>& _omegas); 
    VectorXd getLambda(); // get function for lambdaNew
    VectorXd getOmegas(); // returns omegas
    // posterior samplers:
    void mwgStep(VectorXd &thetaCur, const int &idx, const double &mwgsd,
                 bool &accept, double &logELCur);
    MatrixXd postSampleAdapt(int nsamples, int nburn, VectorXd thetaInit,
                             double *mwgSd, bool *rvDoMcmc, VectorXd &paccept);
    // void mwgStep(MatrixXd &ThetaCur, const int &idxx, const int &idxy, 
    //              const double &mwgsd, bool &accept,double &logELCur);
    // MatrixXd postSampleAdapt(int nsamples, int nburn, MatrixXd ThetaInit,
    //                          double *mwgSd, bool *rvDoMcmc, MatrixXd &paccept);
    MatrixXd postSample(int nsamples, int nburn, MatrixXd ThetaInit,
                        const Ref<const MatrixXd>& Sigs, MatrixXd &paccept);
    // MatrixXd postSample(int nsamples, int nburn, VectorXd thetaInit,
    //                     const Ref<const VectorXd>& sigs, 
    //                     VectorXd &paccept, int betalen);
};

/*
// constructor for mean regression: old
template<typename ELModel>
inline InnerEL<ELModel>::InnerEL(const Ref<const VectorXd>& y,
				 const Ref<const MatrixXd>& X,
				 void* params) : ELModel(y, X, params) {
    // std::cout << nObs << std::endl;
    // std::cout << nEqs << std::endl;
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
 */

// default ctor 
template<typename ELModel>
inline InnerEL<ELModel>::InnerEL(){}

// set data with default ctor (location model)
template<typename ELModel>
inline void InnerEL<ELModel>::setData(const Ref<const VectorXd>& _y,
                                      const Ref<const MatrixXd>& _X,
                                      void* _params) {
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

// set data with default ctor (location-scale model)
template<typename ELModel>
inline void InnerEL<ELModel>::setData(const Ref<const VectorXd>& _y,
                                      const Ref<const MatrixXd>& _X,
                                      const Ref<const MatrixXd>& _Z,
                                      void* _params) {
  ELModel::setData(_y,_X,_Z,_params); // set base class data 
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

template<typename ELModel>
inline void InnerEL<ELModel>::setTol(const int& _maxIter,
                                     const double& _relTol) {
  maxIter = _maxIter;
  relTol = _relTol;
}

// Note: maxIter and relTol must have been assigned 
// Newton-Raphson algorithm
template<typename ELModel>
inline void InnerEL<ELModel>::lambdaNR(int& nIter, double& maxErr) {
// inline void InnerEL<ELModel>::lambdaNR(int& nIter, double& maxErr,
//                               int maxIter, double relTol) {
    int ii, jj;
    blockOuter(); // initialize GGt
    //lambdaOld = lambdaIn; // initialize lambda
    // newton-raphson loop
    for(ii=0; ii<maxIter; ii++) {
        // Q1 and Q2
        // std::cout << "lambdaOld = " << lambdaOld.transpose() << std::endl;
        Glambda.noalias() = lambdaOld.transpose() * G;
        Glambda = 1.0 - Glambda.array();
        // std::cout << "Glambda = " << Glambda.transpose() << std::endl;
        // if (Glambda.maxCoeff() > 1000) {
        // std::cout << "G = \n" << G.transpose() << std::endl;
        // }
        Q2.fill(0.0);
        for(jj=0; jj<nObs; jj++) {
            rho(jj) = logstar1(Glambda(jj));
            Q2 += logstar2(Glambda(jj)) * GGt.block(0,jj*nEqs,nEqs,nEqs);
        }
        Q1 = -G * rho;
        // std::cout << "rho = " << rho.transpose() << std::endl;
        // if (ii == 0) {
        //   std::cout << "Q2 = \n" << Q2 << std::endl;
        // }
        // std::cout << "Q1 = " << Q1.transpose() << std::endl;
        // update lambda
        Q2ldlt.compute(Q2);
        // std::cout << "Q2ldlt.solve(Q1) = " << Q2ldlt.solve(Q1).transpose() << std::endl;
        lambdaNew.noalias() = lambdaOld - Q2ldlt.solve(Q1);
        // std::cout << "lambdaNew ="  << lambdaNew.transpose() << std::endl;
        // std::cout << "lambdaOld ="  << lambdaOld.transpose() << std::endl;
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
inline void InnerEL<ELModel>::setLambda(const Ref<const VectorXd>& _lambda) {
  lambdaNew = _lambda;
}

template<typename ELModel>
inline VectorXd InnerEL<ELModel>::getLambda() {
    return(lambdaNew);
}

// Note: G must have been assigned before calling this function 
/* Old code
template<typename ELModel>
inline void InnerEL<ELModel>::evalOmegas(int maxIter, double relTol) {
    // G must have been assigned
    int nIter;
    double maxErr; 
    lambdaNR(nIter, maxErr, maxIter, relTol);
    // check convergence 
    if (nIter == maxIter && maxErr > relTol) {
        // omegas = NumericVector::create(NA_REAL); // does not work
        for (int ii=0; ii<nObs; ii++) {
          omegas(ii) = std::numeric_limits<double>::quiet_NaN();
        }
    }
    else {
        Glambda.noalias() = lambdaNew.transpose() * G;
        Gl11 = 1.0/(1.0-Glambda.array());
        omegas.array() = Gl11.array() / Gl11.sum();
    }
}
*/ 

// Note: G and lambdaNew must have been assigned before calling
// i.e., in InnerElExports.cpp, assign lambdaNew first 
template<typename ELModel>
inline void InnerEL<ELModel>::evalOmegas() {
  // G and lambdaNew must have been assigned
  if (lambdaNew != lambdaNew) { // if lambdaNew is NaN 
    for (int ii=0; ii<nObs; ii++) {
      omegas(ii) = std::numeric_limits<double>::quiet_NaN();
    }
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

// Note: omegas must have been assigned before calling 
// i.e., in InnerElExports.cpp, evaluate & assign omegas first 
template<typename ELModel>
inline double InnerEL<ELModel>::logEL() {
  // if omegas are NaN, return -Inf
  if (omegas != omegas) return -INFINITY;
  else return(omegas.array().log().sum());
}

// Note: each column of ThetaInit/Sigs is one theta vector; 
//       ThetaInit and Sig should have the same dimensions
template<typename ELModel>
inline MatrixXd InnerEL<ELModel>::postSample(int nsamples, int nburn,
                MatrixXd ThetaInit, const Ref<const MatrixXd>& Sigs,
                MatrixXd &paccept) {
  int nTheta = ThetaInit.rows(); // dimension of theta
  int numTheta = ThetaInit.cols(); // numer of thetas
  MatrixXd Theta_chain(nTheta*numTheta,nsamples);
  MatrixXd ThetaOld = ThetaInit;
  MatrixXd ThetaNew = ThetaOld;
  MatrixXd ThetaProp = ThetaOld;
  if (nTheta == nBet) { // location regs
    ELModel::evalG(ThetaOld);
  }
  else if (nTheta == nBet + nGam){ // LS mean reg
    ELModel::evalG(ThetaOld.topRows(nBet),
                   ThetaOld.bottomRows(nGam), 
                   VectorXd::Zero(0));
    // std::cout << "G = \n" << G << std::endl;
  }
  else { // LS quant reg
    ELModel::evalG(ThetaOld.topRows(nBet), 
                   ThetaOld.block(nBet,0,nGam,numTheta), 
                   ThetaOld.bottomRows(1));
    // std::cout << "ThetaOld.topRows(nBet) = " << ThetaOld.topRows(nBet) << std::endl;
    // std::cout << "ThetaOld.block(nBet,0,nGam,numTheta) = " << ThetaOld.block(nBet,0,nGam,numTheta) << std::endl;
    // std::cout << "ThetaOld.bottomRows(1) = " << ThetaOld.bottomRows(1) << std::endl;
    // std::cout << "G = \n" << G.transpose() << std::endl;
  }
  int nIter;
  double maxErr;
  // lambdaNR(nIter, maxErr, maxIter, relTol); 
  lambdaNR(nIter, maxErr);
  // std::cout << "first lambdaNEW = " << lambdaNew.transpose() << std::endl;
  // TODO: what if not converged ?
  if (nIter == maxIter && maxErr > relTol) {
    // TODO: throw an error ??
    std::cout << "ThetaInit not valid." << std::endl;
    // return NULL;
  }
  evalOmegas();
  // std::cout << "first omegas = " << omegas.transpose() << std::endl;
  double logELOld = logEL(); 
  // std::cout << "first logEL = " << logELOld << std::endl;
  double logELProp;
  bool satisfy;
  double u;
  double a;
  double ratio;
  paccept = MatrixXd::Zero(ThetaInit.rows(),ThetaInit.cols()); // TODO: need to initialize to 0 ?
  
  bool go_next;
  for (int ii=-nburn; ii<nsamples; ii++) {
    go_next = false;
    for (int kk=0; kk<numTheta; kk++) {  
      if (go_next == true) break;
      for (int jj=0; jj<nTheta; jj++) {
        ThetaProp = ThetaOld;
        ThetaProp(jj,kk) += Sigs(jj,kk)*R::norm_rand();
        // ThetaProp(jj,kk) += Sigs(jj,kk)*1.5; // DEBUG
        // std::cout << "ThetaProp = \n" << ThetaProp.transpose() << std::endl;
        // check if proposed theta satisfies the constraint
        satisfy = false;
        // ELModel::evalG(thetaProp); // NEW: change G with thetaProp
        if (nTheta == nBet) { // location models
          ELModel::evalG(ThetaProp);
          // std::cout << "G = \n" << G << std::endl;
        }
        else if (nTheta == nBet + nGam){
          ELModel::evalG(ThetaProp.topRows(nBet), 
                         ThetaProp.bottomRows(nTheta-nBet), 
                         VectorXd::Zero(0));
          // std::cout << "G = \n" << G << std::endl;
        }
        else {
          // std::cout << "calling LS quant evalG" << std::endl;
          ELModel::evalG(ThetaProp.topRows(nBet), 
                         ThetaProp.block(nBet,0,nGam,numTheta), 
                         ThetaProp.bottomRows(1));
        }
        // lambdaNR(nIter, maxErr, maxIter, relTol);
        // std::cout << "lambdaOld = " << lambdaOld.transpose() << std::endl;
        // std::cout << "lambdaNew = " << lambdaNew.transpose() << std::endl;
        lambdaNR(nIter, maxErr);
        // std::cout << "nIter = " << nIter << std::endl;
        // std::cout << "maxErr = " << maxErr << std::endl;
        // std::cout << "lambdaNew = " << lambdaNew.transpose() << std::endl;
        if (nIter < maxIter) satisfy = true;
        // if does not satisfy, keep the old theta
        if (satisfy == false) {
          // std::cout << "go out 2 loops" << std::endl;
          go_next = true; // break out two loops
          break;
        }
        // if does satisfy, flip a coin
        u = R::unif_rand();
        // use the lambda calculate just now to get the logEL for Prop
        // to avoid an extra call of lambdaNR
        VectorXd logomegahat = log(1/(1-(lambdaNew.transpose()*ELModel::G).array())) -
          log((1/(1-(lambdaNew.transpose()*ELModel::G).array())).sum());
        logELProp = logomegahat.sum();
        ratio = exp(logELProp-logELOld);
        // std::cout << "logELProp = " << logELProp << std::endl; 
        // std::cout << "ratio = " << ratio << std::endl;
        a = std::min(1.0,ratio);
        if (u < a) { // accepted
          paccept(jj,kk) += 1; 
          ThetaNew = ThetaProp;
          ThetaOld = ThetaNew;
          logELOld = logELProp; // NEW: store the new one
        }
      }
    }
    if (ii >= 0) {
      // Theta_chain.col(ii) = ThetaNew;
      Theta_chain.col(ii) = Map<VectorXd>(ThetaNew.data(), ThetaNew.size());
    }
  }
  paccept /= (nsamples+nburn); 
  return(Theta_chain);
}

// mwgStep updates the idx entry of thetaCur
template<typename ELModel>
inline void InnerEL<ELModel>::mwgStep(VectorXd &thetaCur,
                                      const int &idx,
                                      const double &mwgsd,
                                      bool &accept, 
                                      double &logELCur) {
  accept = false;
  VectorXd thetaProp = thetaCur;
  thetaProp(idx) += mwgsd*R::norm_rand();
  ELModel::evalG(thetaProp);
  int nIter;
  double maxErr;
  // lambdaNR(nIter, maxErr, maxIter, relTol);
  lambdaNR(nIter, maxErr);
  bool satisfy = false;
  if (nIter < maxIter || maxErr <= relTol) satisfy = true;
  // if does not satisfy, keep the old theta
  if (satisfy == false) return;
  // if does satisfy, flip a coin
  double u = R::unif_rand();
  VectorXd logomegahat = log(1/(1-(lambdaNew.transpose()*ELModel::G).array())) -
    log((1/(1-(lambdaNew.transpose()*ELModel::G).array())).sum());
  double logELProp = logomegahat.sum();
  double ratio = exp(logELProp-logELCur);
  double a = std::min(1.0,ratio);
  if (u < a) { // accepted
    accept = true;
    thetaCur = thetaProp;
    logELCur = logELProp;
  }
}

// only works for single quantile (vector theta)
// Note: maxIter and relTol must have been assigned 
// Note: the logical vector rvDoMcmc is for debuging -- true entries are updated 
template<typename ELModel>
inline MatrixXd InnerEL<ELModel>::postSampleAdapt(int nsamples, int nburn,
                                                  VectorXd thetaInit,
                                                  double *mwgSd, bool *rvDoMcmc,
                                                  VectorXd &paccept) {
  
  int thetalen = thetaInit.size();
  MwgAdapt tuneMCMC(thetalen, rvDoMcmc);
  bool *isAccepted = new bool[thetalen];
  for (int ii=0; ii<thetalen; ii++) {
    isAccepted[ii] = false;
  }
  MatrixXd theta_chain(thetalen,nsamples);
  paccept = VectorXd::Zero(thetalen);
  VectorXd thetaCur = thetaInit;
  ELModel::evalG(thetaCur);
  int nIter;
  double maxErr;
  lambdaNR(nIter, maxErr);
  // TODO: throw an error ??
  if (nIter == maxIter && maxErr > relTol) {
    std::cout << "thetaInit not valid." << std::endl;
  }
  evalOmegas();
  double logELCur = logEL();
  // MCMC loop
  for(int ii=-nburn; ii<nsamples; ii++) {
    for(int jj=0; jj<thetalen; jj++) {
      if(rvDoMcmc[jj]) {
        // std::cout << "isAccepted[" << jj << "] = " << isAccepted[jj] << std::endl;
        // modifies thetaCur's jj-th entry
        mwgStep(thetaCur,jj,mwgSd[jj],isAccepted[jj],logELCur);
        if (isAccepted[jj]) paccept(jj) += 1; // add 1 to paccept if accepted
      }
    }
    if (ii >= 0) {
      theta_chain.col(ii) = thetaCur;
    }
    tuneMCMC.adapt(mwgSd, isAccepted);
  }
  paccept /= (nsamples+nburn);
  delete[] isAccepted; // deallocate memory
  return(theta_chain);
}

/* only works for single quantile (vector theta)
// posterior sampler: depend on evalG
// Note: maxIter and relTol must have been assigned 
//       paccept should be a vector of length(thetaInit)
//       if betalen == thetaInit.size(), then use location model only 
template<typename ELModel>
inline MatrixXd InnerEL<ELModel>::postSample(int nsamples, int nburn,
                VectorXd thetaInit, const Ref<const VectorXd>& sigs,
                VectorXd &paccept, int betalen) {
  int thetalen = thetaInit.size();
  MatrixXd theta_chain(thetalen,nsamples);
  VectorXd thetaOld = thetaInit;
  VectorXd thetaNew = thetaOld;
  VectorXd thetaProp = thetaOld;
  if (thetalen == betalen) {
    ELModel::evalG(thetaOld);
  }
  else {
    ELModel::evalG(thetaOld.head(betalen), thetaOld.tail(thetalen-betalen));
  }
  int nIter;
  double maxErr;
  // lambdaNR(nIter, maxErr, maxIter, relTol); 
  lambdaNR(nIter, maxErr);
  // TODO: what if not converged ?
  if (nIter == maxIter && maxErr > relTol) {
    // TODO: throw an error ??
    std::cout << "thetaInit not valid." << std::endl;
    // return NULL;
  }
  evalOmegas();
  double logELOld = logEL(); 
  double logELProp;
  bool satisfy;
  double u;
  double a;
  double ratio;
  paccept = VectorXd::Zero(thetaInit.size()); // TODO: need to initialize to 0 ?
  
  for (int ii=-nburn; ii<nsamples; ii++) {
    for (int jj=0; jj<thetalen; jj++) {
      thetaProp = thetaOld;
      thetaProp(jj) += sigs(jj)*R::norm_rand();
      // check if proposed theta satisfies the constraint
      satisfy = false;
      // ELModel::evalG(thetaProp); // NEW: change G with thetaProp
      if (thetalen == betalen) {
        ELModel::evalG(thetaProp);
      }
      else {
        ELModel::evalG(thetaProp.head(betalen), thetaProp.tail(thetalen-betalen));
      }
      // lambdaNR(nIter, maxErr, maxIter, relTol);
      lambdaNR(nIter, maxErr);
      if (nIter < maxIter) satisfy = true;
      // if does not satisfy, keep the old theta
      if (satisfy == false) break;
      // if does satisfy, flip a coin
      u = R::unif_rand();
      // use the lambda calculate just now to get the logEL for Prop
      // to avoid an extra call of lambdaNR
      VectorXd logomegahat = log(1/(1-(lambdaNew.transpose()*ELModel::G).array())) -
        log((1/(1-(lambdaNew.transpose()*ELModel::G).array())).sum());
      logELProp = logomegahat.sum();
      ratio = exp(logELProp-logELOld);
      a = std::min(1.0,ratio);
      if (u < a) { // accepted
        paccept(jj) += 1; 
        thetaNew = thetaProp;
        thetaOld = thetaNew;
        logELOld = logELProp; // NEW: store the new one
      }
    }
    if (ii >= 0) {
      theta_chain.col(ii) = thetaNew;
    }
  }
  paccept /= (nsamples+nburn); 
  return(theta_chain);
}
*/


/* only works for location model
template<typename ELModel>
inline MatrixXd InnerEL<ELModel>::postSample(int nsamples, int nburn,
					     VectorXd thetaInit, const Ref<const VectorXd>& sigs,
					     VectorXd &paccept) {
  VectorXd thetaOld = thetaInit;
  VectorXd thetaNew = thetaOld;
  VectorXd thetaProp = thetaOld;
  int thetalen = thetaInit.size();
  MatrixXd theta_chain(thetalen,nsamples);
  ELModel::evalG(thetaOld);
  int nIter;
  double maxErr;
  // lambdaNR(nIter, maxErr, maxIter, relTol); 
  lambdaNR(nIter, maxErr);
  // TODO: what if not converged ?
  if (nIter == maxIter && maxErr > relTol) {
    // TODO: throw an error ??
    std::cout << "thetaInit not valid." << std::endl;
    // return NULL;
  }
  evalOmegas();
  double logELOld = logEL(); 
  double logELProp;
  bool satisfy;
  double u;
  double a;
  double ratio;
  paccept = VectorXd::Zero(thetaInit.size()); // TODO: need to initialize to 0 ?

  for (int ii=-nburn; ii<nsamples; ii++) {
    for (int jj=0; jj<thetalen; jj++) {
      thetaProp = thetaOld;
      thetaProp(jj) += sigs(jj)*R::norm_rand();
      // check if proposed theta satisfies the constraint
      satisfy = false;
      ELModel::evalG(thetaProp); // NEW: change G with thetaProp
      // lambdaNR(nIter, maxErr, maxIter, relTol);
      lambdaNR(nIter, maxErr);
      if (nIter < maxIter) satisfy = true;
      // if does not satisfy, keep the old theta
      if (satisfy == false) break;
      // if does satisfy, flip a coin
      u = R::unif_rand();
      // use the lambda calculate just now to get the logEL for Prop
      // to avoid an extra call of lambdaNR
      VectorXd logomegahat = log(1/(1-(lambdaNew.transpose()*ELModel::G).array())) -
        log((1/(1-(lambdaNew.transpose()*ELModel::G).array())).sum());
      logELProp = logomegahat.sum();
      ratio = exp(logELProp-logELOld);
      a = std::min(1.0,ratio);
      if (u < a) { // accepted
        paccept(jj) += 1; 
        thetaNew = thetaProp;
        thetaOld = thetaNew;
        logELOld = logELProp; // NEW: store the new one
      }
    }
    if (ii >= 0) {
      theta_chain.col(ii) = thetaNew;
    }
  }
  paccept /= (nsamples+nburn); 
  return(theta_chain);
}
*/

#endif
