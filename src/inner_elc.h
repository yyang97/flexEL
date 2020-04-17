/**
 * @file InnerELC.h
 * 
 * @brief Inner optimization routine for empirial likelihood problems under right-censoring.
 */

#ifndef INNERELC_h
#define INNERELC_h

#include <Rcpp.h>
#include <RcppEigen.h>
#include <math.h>
#include <Rmath.h> // for random number 
#include <cmath>  // for abs on scalars
#include "sort_order.h"
#include "ind_smooth.h" // for smoothed indicator function
#include "block_outer.h"
#include "adj_G.h" // for support correction
// #include "MwgAdapt.h" // for adaptive mcmc

// [[Rcpp::depends(RcppEigen)]]

using namespace Rcpp;
using namespace Eigen;

/* --------------------------------------------------------------------------- */

/**
 * @brief EL namespace
 * 
 * Wrap the exported library components into a namespace called \b el to avoid potential naming conflicts with other libraries or user-defined headers.
 */
namespace flexEL {
  
  /**
   * @file       InnerELC.h
   *
   * @class      InnerELC
   *
   * @brief      A template class for empirical likelihood inner optimization calculation with right-censored responses.
   */
  class InnerELC { 
  private:
    
    // dim of G_ matrix
    int n_obs_; // number of columns
    int n_eqs_; // number of rows
    
    // placeholders for EM algorithm
    VectorXd deltas_; // censoring indicators
    VectorXd weights_; // weights in weighted maximum log EL
    VectorXd omegas_; // empirical distribution
    VectorXd omegas_init_; // initial value for omegas, in case of reset
    VectorXd omegasps_; // partial sum of omegas
    VectorXd epsilons_; // residuals used for ordering in EM
    VectorXi eps_ord_; // order of epsilons
    VectorXd psots_; // partial sum of omegatildas
    VectorXd psoss_; // partial sum of omegas (another s just to distinguish with the name of another double variable)
    ArrayXd logels_; // logel values
  
    // placeholders for LambdaNR
    MatrixXd G_; // G matrix for the estimating equations
    MatrixXd G_used_;
    VectorXd lambda0_;
    VectorXd lambda_old_;
    VectorXd lambda_new_;
    MatrixXd GGt_;
    MatrixXd GGt_used_;
    VectorXd Glambda_;
    ArrayXd Gl11_;
    VectorXd lGq_;
    VectorXd Q1_;
    MatrixXd Q2_;
    LDLT<MatrixXd> Q2ldlt_;
    VectorXd rho_;
    VectorXd rel_err_; // relative difference between two vectors (element-wise absolute difference divided by sum)
    double abs_err_; // absolute difference between two scalars

    // for support modification
    int n_obs1_; // n_obs1_ = n_obs_+1: for initial space allocation
    int n_obs2_; // n_obs2_ = n_obs_+support: used n_obs_ in calculation
    
    // tolerance values for LambdaNR and EM
    double rel_tol_;
    double abs_tol_;
    int max_iter_;
    bool supp_;
    double supp_a_; // tuning parameter for support currection
    
    // maximum relative error in lambda: same for cens / non-cens
    double MaxRelErr();
    
    // LogSharp and its derivatives for the EL dual problem
    double LogSharp(double x, double q); // A support-refined log function
    double LogSharp1(double x, double q); // First derivative of LogSharp
    double LogSharp2(double x, double q); // Second derivative of LogSharp
    
    // Helper function for EvalWeights: calculate partial sum of omegas.
    double EvalPSO(const int ii); // Partial sum of omegas_jj s.t. eps_jj >= eps_ii
    double EvalPSOSmooth(const int ii, const double s); // smoothed version
    
  public:
    
    // constructors
    InnerELC();
    InnerELC(int n_obs);
    InnerELC(int n_obs, int n_eqs);
    
    // set options functions
    void set_opts(const int& max_iter, const double& rel_tol, 
                 const double& abs_tol, const bool& supp, const double& supp_a, 
                 const Ref<const VectorXd>& lambda0);
    void set_opts(const int& max_iter, const double& rel_tol, 
                 const double& abs_tol, const bool& supp, 
                 const Ref<const VectorXd>& lambda0);
    void set_opts(const int& max_iter, const double& rel_tol, 
                 const double& abs_tol, const bool& supp, const double& supp_a);
    void set_opts(const int& max_iter, const double& rel_tol, 
                 const double& abs_tol, const bool& supp);
    void set_opts(const int& max_iter, const double& rel_tol, 
                 const bool& supp, const double& supp_a);
    void set_opts(const int& max_iter, const double& rel_tol, 
                 const bool& supp);
    void set_opts(const bool& supp);
    // void setTol(const int& max_iter, const double& rel_tol, const double& abs_tol);
    // void setTol(const int& max_iter, const double& rel_tol);
    
    // core calculations
    void LambdaNR(int& n_iter, double& max_err); // dual solution by Newton-Raphson algorithm
    void EvalWeights(); // calculate weights according to epsilons
    void EvalOmegas(); // empirical distribution
    double LogEL(); // log empirical likelihood
    void EvalWeightsSmooth(const double s);
    void EvalOmegasSmooth(const double s);
    double LogELSmooth(const double s);
    
    // set and get functions 
    void set_deltas(const Ref<const VectorXd>& deltas);
    void set_lambda(const Ref<const VectorXd>& lambda); // assigned to lambdaNew
    void set_weights(const Ref<const VectorXd>& weights); 
    void set_omegas(const Ref<const VectorXd>& omegas);
    void set_epsilons(const Ref<const VectorXd>& epsilons);
    void set_G(const Ref<const MatrixXd>& G);
    VectorXd get_lambda(); 
    VectorXd get_weights(); 
    VectorXd get_omegas(); 
    VectorXd get_epsilons();
    MatrixXd get_G();
    Ref<MatrixXd> get_ref_G();

    // // posterior sampler
    // MatrixXd postSample(int nsamples,int nburn, VectorXd betaInit, 
    //                     const Ref<const VectorXd>& sigs, 
    //                     VectorXd &RvDoMcmc,VectorXd &paccept);
    // void mwgStep(VectorXd &thetaCur, const int &idx, const double &mwgsd,
    //              bool &accept, double &LogELCur);
    // MatrixXd postSampleAdapt(int nsamples, int nburn, VectorXd thetaInit,
    //                          double *mwgSd, VectorXd &rvDoMcmc, bool *doAdapt, 
    //                          VectorXd &paccept);
  };
}

/* --------------------------------------------------------------------------- */

// private functions 

// maximum relative error in lambda
inline double flexEL::InnerELC::MaxRelErr() {
  // TODO: added for numerical stability, what is a good tolerance to use ?
  if ((lambda_new_ - lambda_old_).array().abs().maxCoeff() < 1e-10) return(0);
  rel_err_ = ((lambda_new_ - lambda_old_).array() / (lambda_new_ + lambda_old_).array()).abs();
  return(rel_err_.maxCoeff());
}

// LogSharp
inline double flexEL::InnerELC::LogSharp(double x, double q) {
  double xq;
  if(x >= q) {
    return(log(x));
  } else {
    xq = x/q;
    return(-0.5*xq*xq + 2.0*xq - 1.5 + log(q));
  }
}

// d LogSharp(x)/dx
inline double flexEL::InnerELC::LogSharp1(double x, double q) {
  if(x >= q) {
    return(1.0/x);
  } else {
    return(-1.0/(q*q)*x + 2.0/q);
  }
}

// d^2 LogSharp(x)/dx^2
inline double flexEL::InnerELC::LogSharp2(double x, double q) {
  if(x >= q) {
    return(-1.0/(x*x));
  } else {
    return(-1.0/(q*q));
  }
}

inline double flexEL::InnerELC::EvalPSO(const int ii) {
  double psos = 0;
  int kk;
  for (int jj=n_obs2_-1; jj>=0; jj--) {
    // Note: epsOrd corresponds to epsilons acesndingly 
    kk = eps_ord_(jj); // kk is the index of the jj-th largest epsilon
    psos += omegas_(kk);
    if (kk == ii) break; // until (backwardsly) reaching ii-th largest epsilon 
  }
  return psos;
}

inline double flexEL::InnerELC::EvalPSOSmooth(const int ii, const double s) {
  double psos_smooth = 0;
  if (supp_ && ii == (n_obs2_-1)) {
    psos_smooth = omegas_.head(n_obs2_-1).sum() + 0.5*omegas_(n_obs2_-1);
  }
  else {
    for (int jj=0; jj<n_obs2_; jj++) {
      psos_smooth += ind_smooth(epsilons_(ii)-epsilons_(jj),s)*omegas_(jj);
    }
  }
  return(psos_smooth);
  // VectorXd ss = ArrayXd::Zero(omegas.size()) + s;
  // return (ind_smooth(epsilons[ii]-epsilons.array(),ss).array()*omegas.array()).sum();
}

/* --------------------------------------------------------------------------- */

// public functions

// constructors
/**
 * @brief Default constructor for InnerELC.
 */
inline flexEL::InnerELC::InnerELC() {}

// ctor with dimensions as input
/**
 * @brief Constructor for InnerELC with number of observations only as input for memory allocation.
 * 
 * @param n_obs    Number of observations.
 */
inline flexEL::InnerELC::InnerELC(int n_obs) {
  n_obs_ = n_obs;
  // support correction
  supp_ = false;
  n_obs1_ = n_obs_+1;
  n_obs2_ = n_obs_+supp_;
  omegas_ = VectorXd::Zero(n_obs1_).array() + 1.0/(double)n_obs1_; // Initialize omegas to 1/n_obs?
}

// ctor with dimensions as input
/**
 * @brief Constructor for InnerELC with dimensions of G matrix as inputs for memory allocation.
 * 
 * @param n_obs    Number of observations.
 * @param n_eqs    Number of estimating equations.
 */
inline flexEL::InnerELC::InnerELC(int n_obs, int n_eqs) {
  // set internal values
  n_obs_ = n_obs;
  n_eqs_ = n_eqs;
  // support correction
  supp_ = false;
  n_obs1_ = n_obs_+1;
  n_obs2_ = n_obs_+supp_;
  // space allocation
  omegas_init_ = VectorXd::Zero(n_obs1_).array() + 1.0/(double)n_obs1_; 
  omegas_ = VectorXd::Zero(n_obs1_).array() + 1.0/(double)n_obs1_; 
  G_ = MatrixXd::Zero(n_eqs_,n_obs1_); // NEW: JAN 1
  GGt_ = MatrixXd::Zero(n_eqs_,n_obs1_*n_eqs_);
  lambda0_ = VectorXd::Zero(n_eqs_); 
  lambda_old_ = VectorXd::Zero(n_eqs_); // Initialize to all 0's
  lambda_new_ = VectorXd::Zero(n_eqs_);
  Q1_ = VectorXd::Zero(n_eqs_);
  Q2_ = MatrixXd::Zero(n_eqs_,n_eqs_);
  Glambda_ = VectorXd::Zero(n_obs1_);
  Gl11_ = ArrayXd::Zero(n_obs1_);
  rho_ = VectorXd::Zero(n_obs1_);
  rel_err_ = VectorXd::Zero(n_eqs_);
  Q2ldlt_.compute(MatrixXd::Identity(n_eqs_,n_eqs_));
  deltas_ = VectorXd::Zero(n_obs1_);
  weights_ = VectorXd::Zero(n_obs1_);
  epsilons_ = VectorXd::Zero(n_obs1_);
  eps_ord_ = VectorXi::Zero(n_obs1_);
  psoss_ = VectorXd::Zero(n_obs1_);
  logels_ = ArrayXd::Zero(n_obs1_);
  lGq_ = VectorXd::Zero(n_obs1_);
}

// set options
/**
 * @brief Set tolerance values for NR, support correction option and tuning parameter, and initial value of lambda.
 * 
 * @param max_iter    Maximum number of iterations.
 * @param rel_tol     Relative tolerance (for Newton-Raphson algorithm).
 * @param abs_tol     Absolute tolerance (for EM algorithm).
 * @param supp        Whether to have support correction.
 * @param supp_a      Tuning parameter for support correction (referred as "a" in chen-et-al08).
 * @param lambda0     Initial value for lambda.
 */
inline void flexEL::InnerELC::set_opts(const int& max_iter, 
                                  const double& rel_tol, const double& abs_tol, 
                                  const bool& supp, const double& supp_a,
                                  const Ref<const VectorXd>& lambda0) {
  max_iter_ = max_iter;
  rel_tol_ = rel_tol;
  abs_tol_ = abs_tol;
  supp_ = supp;
  supp_a_ = supp_a;
  n_obs2_ = n_obs_+supp_;
  lambda0_ = lambda0;
  if (supp_) {
    epsilons_.tail(1)(0) = -INFINITY;
    deltas_.tail(1)(0) = 0;
  }
}

/**
 * @brief Set tolerance values for NR, support correction option and tuning parameter, and initial value of lambda.
 * 
 * @param max_iter    Maximum number of iterations.
 * @param rel_tol     Relative tolerance (for Newton-Raphson algorithm).
 * @param abs_tol     Absolute tolerance (for EM algorithm).
 * @param supp        Whether to have support correction.
 * @param lambda0     Initial value for lambda.
 */
inline void flexEL::InnerELC::set_opts(const int& max_iter, 
                                  const double& rel_tol, const double& abs_tol, 
                                  const bool& supp, 
                                  const Ref<const VectorXd>& lambda0) {
  max_iter_ = max_iter;
  rel_tol_ = rel_tol;
  abs_tol_ = abs_tol;
  supp_ = supp;
  supp_a_ = std::max(1.0,0.5*log(n_obs_));
  n_obs2_ = n_obs_+supp_;
  lambda0_ = lambda0;
  if (supp_) {
    epsilons_.tail(1)(0) = -INFINITY;
    deltas_.tail(1)(0) = 0;
  }
}

/**
 * @brief Set tolerance values for NR, support correction option and tuning parameter, and initial value of lambda.
 * 
 * @param max_iter    Maximum number of iterations.
 * @param rel_tol     Relative tolerance (for Newton-Raphson algorithm).
 * @param abs_tol     Absolute tolerance (for EM algorithm).
 * @param supp        Whether to have support correction.
 * @param supp_a      Tuning parameter for support correction (referred as "a" in chen-et-al08).
 */
inline void flexEL::InnerELC::set_opts(const int& max_iter, 
                                  const double& rel_tol, const double& abs_tol, 
                                  const bool& supp, const double& supp_a) {
  max_iter_ = max_iter;
  rel_tol_ = rel_tol;
  abs_tol_ = abs_tol;
  supp_ = supp;
  supp_a_ = supp_a;
  n_obs2_ = n_obs_+supp_;
  if (supp_) {
    epsilons_.tail(1)(0) = -INFINITY;
    deltas_.tail(1)(0) = 0;
  }
}

/**
 * @brief Set tolerance values for NR, support correction option and tuning parameter, and initial value of lambda.
 * 
 * @param max_iter    Maximum number of iterations.
 * @param rel_tol     Relative tolerance (for Newton-Raphson algorithm).
 * @param abs_tol     Absolute tolerance (for EM algorithm).
 * @param supp    Whether to have support correction.
 */
inline void flexEL::InnerELC::set_opts(const int& max_iter, 
                                  const double& rel_tol, const double& abs_tol, 
                                  const bool& supp) {
  max_iter_ = max_iter;
  rel_tol_ = rel_tol;
  abs_tol_ = abs_tol;
  supp_ = supp;
  supp_a_ = std::min((double)n_obs_,0.5*log(n_obs_));
  n_obs2_ = n_obs_+supp_;
  if (supp_) {
    epsilons_.tail(1)(0) = -INFINITY;
    deltas_.tail(1)(0) = 0;
  }
}

/**
 * @brief Set tolerance values for NR, supp correction option and tuning parameter, and initial value of lambda.
 * 
 * @param max_iter    Maximum number of iterations.
 * @param rel_tol     Relative tolerance (for Newton-Raphson algorithm).
 * @param supp        Whether to have support correction.
 * @param supp_a      Tuning parameter for support correction (referred as "a" in chen-et-al08).
 */
inline void flexEL::InnerELC::set_opts(const int& max_iter, const double& rel_tol,
                                  const bool& supp, const double& supp_a) {
  max_iter_ = max_iter;
  rel_tol_ = rel_tol;
  supp_ = supp;
  supp_a_ = supp_a;
  n_obs2_ = n_obs_+supp_;
  if (supp_) {
    epsilons_.tail(1)(0) = -INFINITY;
    deltas_.tail(1)(0) = 0;
  }
}

/**
 * @brief Set tolerance values for NR, support correction option and tuning parameter, and initial value of lambda.
 * 
 * @param max_iter    Maximum number of iterations.
 * @param rel_tol     Relative tolerance (for Newton-Raphson algorithm).
 * @param supp    Whether to have support correction.
 */
inline void flexEL::InnerELC::set_opts(const int& max_iter, const double& rel_tol,
                                  const bool& supp) {
  max_iter_ = max_iter;
  rel_tol_ = rel_tol;
  supp_ = supp;
  supp_a_ = std::min((double)n_obs_,0.5*log(n_obs_));
  n_obs2_ = n_obs_+supp_;
  if (supp_) {
    epsilons_.tail(1)(0) = -INFINITY;
    deltas_.tail(1)(0) = 0;
  }
}

/**
 * @brief Set tolerance values for NR, support correction option and tuning parameter, and initial value of lambda.
 * 
 * @param supp    Whether to have support correction.
 */
inline void flexEL::InnerELC::set_opts(const bool& supp) {
  supp_ = supp;
  supp_a_ = std::min((double)n_obs_,0.5*log(n_obs_));
  n_obs2_ = n_obs_+supp_;
  if (supp_) {
    epsilons_.tail(1)(0) = -INFINITY;
    deltas_.tail(1)(0) = 0;
  }
}

/**
 * @brief Find the optimal lambda by a Newton-Raphson algorithm (with right-censored EL).
 * 
 * @param[out] n_iter    Number of iterations to achieve convergence.
 * @param[out] max_err   Maximum relative error among entires in lambda at the last step.
 */
inline void flexEL::InnerELC::LambdaNR(int& n_iter, double& max_err) {

  lambda_old_ = lambda0_;
  lambda_new_.fill(0.0);
  
  // Note: these two cannot be preallocate untill `supp` is set
  // but has to do it this way since .block does not return a MatrixXd (TODO: alternative way?)
  GGt_used_ = GGt_.block(0,0,n_eqs_,n_obs2_*n_eqs_);
  G_used_ = G_.block(0,0,n_eqs_,n_obs2_);
  
  block_outer(GGt_used_,G_used_);
  
  // To avoid numerical problem (TODO: test this again and see if it is ok without it?)
  VectorXd weights_save = weights_;
  for (int ll=0;ll<n_obs2_; ll++) {
    if (weights_save(ll) < rel_tol_*n_obs_) weights_save(ll) = 0;
  }
  
  // newton-raphson loop
  int ii;
  for(ii=0; ii<max_iter_; ii++) {
    // Q1 and Q2
    Glambda_.noalias() = lambda_old_.transpose() * G_used_;
    Glambda_ = weights_.head(n_obs2_).sum() + Glambda_.array();
    Q2_.fill(0.0); 
    for(int jj=0; jj<n_obs2_; jj++) {
      rho_(jj) = LogSharp1(Glambda_(jj), weights_(jj));
      
      // To avoid numerical problem
      if (weights_(jj) > rel_tol_*n_obs_) {
        Q2_ += weights_(jj) * LogSharp2(Glambda_(jj), weights_(jj)) * GGt_used_.block(0,jj*n_eqs_,n_eqs_,n_eqs_);
      }
    }
    // To avoid numerical problem
    for (int kk=0; kk<n_obs2_; kk++) {
      if (isinf(rho_(kk)) && weights_save(kk) == 0) rho_(kk) = 0;
    }
    // update lambda
    Q1_ = G_used_ * (rho_.array()*weights_save.head(n_obs2_).array()).matrix();
    Q2ldlt_.compute(Q2_);
    lambda_new_.noalias() = lambda_old_ - Q2ldlt_.solve(Q1_);
    max_err = MaxRelErr();
    if (max_err < rel_tol_) {
      break;
    }
    lambda_old_ = lambda_new_; // complete cycle
  }
  n_iter = ii; // output lambda and also n_iter and max_err
  return;
}


/**
 * @brief Calculate weights for weighted log EL in EM according to epsilons.
 */
inline void flexEL::InnerELC::EvalWeights() {
  // find the indices for increasing order of epsilons 
  psots_.fill(0.0);
  int kk;
  double psos;
  for (int ii=0; ii<n_obs2_; ii++) {
    for (int jj=0; jj<n_obs2_; jj++) {
      kk = eps_ord_(jj);
      if (deltas_(kk) == 0) {
        psos = EvalPSO(kk);
        // to prevent dividing by 0
        if (abs(psos) >= 1e-10) psots_(ii) += omegas_(ii)/psos;
        else if (omegas_(ii) >= 1e-10 && EvalPSO(kk) < 1e-10) {
          // TODO: this means a problem
          std::cout << "EvalWeights: dividing by 0 problem." << std::endl;
        }
      }
      if (kk == ii) break;
    }
  }
  weights_.array() = deltas_.array() + psots_.array();
}


/**
* @brief Evaluate omegas using an EM algorithm.
*/
inline void flexEL::InnerELC::EvalOmegas() {
  // Need to have a valid starting value if the last one is not valid in MCMC
  if (omegas_ != omegas_) {
    // std::cout << "EvalOmegas: resetting omegas_." << std::endl;
    omegas_ = omegas_init_;
  }
  int n_iter;
  double max_err;
  // lGq_(n_obs2_);
  double logelOld = LogEL();
  double logel = logelOld;
  int ii;
  for(ii=0; ii<max_iter_; ii++) {
    // E-step:
    EvalWeights(); // assigns weights according to epsilons
    // M-step:
    LambdaNR(n_iter, max_err);
    lGq_.head(n_obs2_) = ((lambda_new_.transpose() * G_.block(0,0,n_eqs_,n_obs2_)).array() + weights_.head(n_obs2_).sum()).transpose();
    omegas_.head(n_obs2_).array() = weights_.head(n_obs2_).array() / lGq_.head(n_obs2_).array();
    omegas_.head(n_obs2_).array() = omegas_.head(n_obs2_).array() / (omegas_.head(n_obs2_).array().sum()); // normalize
    logel = LogEL();
    max_err = abs(logel-logelOld); // absolute error in log EL
    if (max_err < abs_tol_) break;
    logelOld = logel;
  }
  n_iter = ii;
  if (n_iter == max_iter_ && max_err > abs_tol_) {
    // TODO: maybe should assign nan elsewhere
    for (int ii=0; ii<n_obs2_; ii++) {
      omegas_(ii) = std::numeric_limits<double>::quiet_NaN();
    }
  }
  return;
}

/**
* @brief Calculate logEL using omegas and deltas.
*/
inline double flexEL::InnerELC::LogEL() {
  // EvalOmegas(max_iter,rel_tol); 
  if (omegas_ != omegas_) return -INFINITY; // (NaN is not equal to themselves)
  else if ((omegas_.head(n_obs_).array() < -1e-10/n_obs2_).any()) return -INFINITY;
  else {
    omegas_ = omegas_.array().abs();
    for (int ii=0; ii<n_obs2_; ii++) {
      psoss_(ii) = EvalPSO(ii);
    }
    for (int jj=0; jj<n_obs2_; jj++) {
      if (deltas_(jj) == 1) logels_(jj) = log(omegas_(jj));
      else  logels_(jj) = log(psoss_(jj));
    }
    return(logels_.head(n_obs2_).sum());
  }
}

/**
 * @brief Calculate weights for weighted log EL in EM according to epsilons.
 * 
 * @param s        Tuning parameter for smoothing.
 */
inline void flexEL::InnerELC::EvalWeightsSmooth(const double s) {
  psots_.fill(0.0); // TODO initialize psots somewhere else???
  for (int ii=0; ii<n_obs2_; ii++) {
    psoss_(ii) = EvalPSOSmooth(ii,s);
  }
  if (supp_) {
    for (int jj=0; jj<n_obs2_; jj++) {
      for (int kk=0; kk<n_obs2_; kk++) {
        if (jj == n_obs2_-1 && kk == n_obs2_-1) {
          psots_(jj) += (1-deltas_(kk))*ind_smooth(0.0,s)*omegas_(jj)/psoss_(kk);
        }
        else psots_(jj) += (1-deltas_(kk))*ind_smooth(epsilons_(kk)-epsilons_(jj),s)*omegas_(jj)/psoss_(kk);
      }
    }
  }
  else {
    for (int jj=0; jj<n_obs2_; jj++) {
      for (int kk=0; kk<n_obs2_; kk++) {
        psots_(jj) += (1-deltas_(kk))*ind_smooth(epsilons_(kk)-epsilons_(jj),s)*omegas_(jj)/psoss_(kk);
      }
    }
  }
  weights_ = deltas_.array()+psots_.array();
}

/**
 * @brief Evaluate omegas using an EM algorithm with continuity correction.
 * 
 * @param s        Tuning parameter for smoothing.
 */
inline void flexEL::InnerELC::EvalOmegasSmooth(const double s) {
  if (omegas_ != omegas_) {
    // std::cout << "EvalOmegas: resetting omegas." << std::endl;
    omegas_ = omegas_init_;
  }
  int n_iter;
  double max_err;
  double logelOld = LogELSmooth(s);
  double logel = logelOld;
  int ii;
  for(ii=0; ii<max_iter_; ii++) {
    // E-step:
    EvalWeightsSmooth(s); // assigns weights according to epsilons
    // M-step:
    LambdaNR(n_iter, max_err);
    lGq_.head(n_obs2_) = ((lambda_new_.transpose() * G_.block(0,0,n_eqs_,n_obs2_)).array() + weights_.head(n_obs2_).sum()).transpose();
    omegas_.head(n_obs2_).array() = weights_.head(n_obs2_).array() / lGq_.head(n_obs2_).array();
    omegas_.head(n_obs2_).array() = omegas_.head(n_obs2_).array() / (omegas_.head(n_obs2_).array().sum()); // normalize
    logel = LogELSmooth(s);
    abs_err_ = abs(logel-logelOld);
    if (abs_err_ < abs_tol_) break;
    logelOld = logel;
  }
  n_iter = ii; 
  if (n_iter == max_iter_ && abs_err_ > abs_tol_) {
    // TODO: maybe should assign nan elsewhere 
    for (int ii=0; ii<n_obs2_; ii++) {
      omegas_(ii) = std::numeric_limits<double>::quiet_NaN();
    }
  }
  return;
}

/**
 * @brief Calculate logEL using omegas and deltas.
 * 
 * @param s        Tuning parameter for smoothing.
 */
inline double flexEL::InnerELC::LogELSmooth(const double s) {
  if (omegas_ != omegas_) return -INFINITY; // (NaN is not equal to themselves)
  else if ((omegas_.array() < -1e-10/omegas_.size()).any()) return -INFINITY;
  else {
    omegas_ = omegas_.array().abs();
    // psoss_ = VectorXd::Zero(n_obs2_);
    for (int ii=0; ii<n_obs2_; ii++) {
      psoss_(ii) = EvalPSOSmooth(ii,s);
    }
    // logels_ = ArrayXd::Zero(n_obs2_);
    for (int jj=0; jj<n_obs2_; jj++) {
      if (deltas_(jj) == 1) logels_(jj) = log(omegas_(jj));
      else  logels_(jj) = log(psoss_(jj));
    }
    return(logels_.head(n_obs2_).sum());
  }
}

// setters

/**
 * @brief Set the value of epsilons.
 */
inline void flexEL::InnerELC::set_epsilons(const Ref<const VectorXd>& epsilons) {
  epsilons_.head(n_obs_) = epsilons;
  eps_ord_.head(n_obs2_) = sort_inds(epsilons_.head(n_obs2_)); 
}

/**
 * @brief Set the value of lambda.
 */
inline void flexEL::InnerELC::set_lambda(const Ref<const VectorXd>& lambda) {
  lambda_new_ = lambda;
}

/**
 * @brief Set the value of weights.
 */
inline void flexEL::InnerELC::set_weights(const Ref<const VectorXd>& weights) {
  weights_.head(n_obs_) = weights; 
}

/**
 * @brief Set the value of omegas.
 */
inline void flexEL::InnerELC::set_omegas(const Ref<const VectorXd>& omegas) {
  // n_obs = _omegas.size(); // TODO: where to set n_obs
  omegas_init_.head(n_obs2_) = omegas; // new
  omegas_.head(n_obs2_) = omegas; 
}

/**
 * @brief Set the value of deltas.
 */
inline void flexEL::InnerELC::set_deltas(const Ref<const VectorXd>& deltas) {
  psots_ = VectorXd::Zero(n_obs2_); // TODO: initialization maybe should be done at better places
  deltas_.head(n_obs_) = deltas;
}

/**
 * @brief Set the value of G.
 */
inline void flexEL::InnerELC::set_G(const Ref<const MatrixXd>& G) {
  G_.block(0,0,n_eqs_,n_obs_) = G;
  if (supp_) adj_G(G_,supp_a_);
}

// getters

/**
 * @brief Get the value of lambda.
 */
inline VectorXd flexEL::InnerELC::get_lambda() {
  return(lambda_new_);
}

/**
 * @brief Get the value of weights.
 */
inline VectorXd flexEL::InnerELC::get_weights() {
  return(weights_.head(n_obs2_));
}

/**
 * @brief Get the value of omegas.
 */
inline VectorXd flexEL::InnerELC::get_omegas() {
  return(omegas_.head(n_obs2_));
}

/**
 * @brief Get the value of epsilons.
 */
inline VectorXd flexEL::InnerELC::get_epsilons() {
  return(epsilons_.head(n_obs2_));
}

/**
 * @brief Get the value of G.
 */
inline MatrixXd flexEL::InnerELC::get_G() {
  return(G_.block(0,0,n_eqs_,n_obs2_));
}

/**
 * @brief Get the reference of G.
 */
inline Ref<MatrixXd> flexEL::InnerELC::get_ref_G() {
  return Ref<MatrixXd>(G_.block(0,0,n_eqs_,n_obs2_));
}

/* TAKE OUT ALL MCMC SAMPLERS FOR NOW:
// posterior sampler: location model, single quantile case
// Note: omegasInit needed as the starting value for EM?
template<typename ELModel>
inline MatrixXd InnerELC<ELModel>::postSample(int nsamples, int nburn,
                                              VectorXd betaInit, 
                                              const Ref<const VectorXd>& sigs,
                                              VectorXd &RvDoMcmc, VectorXd &paccept) {
  std::cout << "--------------------------- ELC postSample ----------------------------" << std::endl;
  VectorXd betaOld = betaInit;
  VectorXd betaNew = betaInit;
  VectorXd betaProp = betaInit;
  int betalen = betaInit.size();
  MatrixXd beta_chain(betalen,nsamples); 
  // beta_chain.fill(0.0); // debug
  ELModel::evalG(betaInit);
  evalEpsilons(betaInit);
  EvalOmegas(); // omegasInit should have been assigned
  double logELOld = LogEL();
  // std::cout << "after calling LogEL()." << std::endl;
  double logELProp;
  bool satisfy;
  double u;
  double a;
  double ratio;
  int n_iter;
  double max_err;
  // paccept.fill(0.0);
  paccept = VectorXd::Zero(betalen);
  // std::cout << "sigs = " << sigs.transpose() << std::endl;
  // std::cout << "paccept = " << paccept.transpose() << std::endl;
  // std::cout << "RvDoMcmc = " << RvDoMcmc.transpose() << std::endl;

  for (int ii=-nburn; ii<nsamples; ii++) {
    if (ii % 200 == 0) {
      std::cout << "ii = " << ii << std::endl;
    }
    for (int jj=0; jj<betalen; jj++) {
      if (RvDoMcmc(jj)) {
        betaProp = betaOld;
        betaProp(jj) += sigs(jj)*R::norm_rand();
        // std::cout << "betaProp = " << betaProp.transpose() << std::endl;
        // check if proposed beta satisfies the constraint
        satisfy = false;
        ELModel::EvalG(betaProp);
        EvalEpsilons(betaProp);
        EvalWeights();
        // std::cout << "weights = " << weights.transpose() << std::endl;
        // check whether the constrains are satisfied or not
        // std::cout << "old lambdaNew = " << lambdaNew.transpose() << std::endl;
        LambdaNR(n_iter, max_err);
        // std::cout << "new lambdaNew = " << lambdaNew << std::endl;
        if (n_iter < max_iter) satisfy = true;
        // if does not satisfy, keep the old beta
        if (satisfy == false) break;
        // if does satisfy, decide whether to accept
        u = R::unif_rand();
        // use the lambda calculate just now to get the logEL for Prop
        // to avoid an extra call of LambdaNR
        // VectorXd logomegahat = log(weights.array() /
        //   (weights.transpose() + lambdaNew.transpose() * G).array().sum());
        // logELProp = (weights.array()*logomegahat.array()).sum();
        EvalOmegas(); // LambdaNR is in here as well
        // std::cout << "omegas = " << omegas.transpose() << std::endl;
        logELProp = LogEL();
        // std::cout << "logELOld = " << logELOld << std::endl;
        // std::cout << "logELProp = " << logELProp << std::endl;
        ratio = exp(logELProp-logELOld);
        // std::cout << "ratio = " << ratio << std::endl;
        a = std::min(1.0,ratio);
        if (u < a) { // accepted
          paccept(jj) += 1;
          betaNew = betaProp;
          betaOld = betaNew;
          // betaOld = betaProp;
          logELOld = logELProp; // store the new one
        }
      }
    }
    if (ii >= 0) {
      beta_chain.col(ii) = betaNew;
      // beta_chain.col(ii) = betaProp;
    }
  }
  paccept /= (nsamples+nburn);
  return(beta_chain);
}

template<typename ELModel>
inline void InnerELC<ELModel>::mwgStep(VectorXd &thetaCur,
                                       const int &idx,
                                       const double &mwgsd,
                                       bool &accept, 
                                       double &logELCur) {
  // std::cout << "in mwgStep: logELCur = " << logELCur << std::endl;
  int nTheta = thetaCur.size();
  accept = false;
  VectorXd thetaProp = thetaCur;
  thetaProp(idx) += mwgsd*R::norm_rand();
  // sig2 has to be positive
  if (idx == nBet+nGam && thetaProp(idx) < 0) {
    // std::cout << "negative sig2 = " << thetaProp(idx) << std::endl;
    return;
  }
  
  if (nTheta == nBet) {
    ELModel::EvalG(thetaProp);
    EvalEpsilons(thetaProp);
  }
  else {
    if (nTheta == nBet + nGam + 1){
      ELModel::EvalG(thetaProp.head(nBet), 
                     thetaProp.segment(nBet,nGam), 
                     thetaProp.tail(1)(0),
                     VectorXd::Zero(0));
    }
    else {
      ELModel::EvalG(thetaProp.head(nBet), 
                     thetaProp.segment(nBet,nGam), 
                     thetaProp.segment(nBet+nGam,1)(0),
                     thetaProp.tail(nQts));
    }
    EvalEpsilons(thetaProp.head(nBet),
                 thetaProp.segment(nBet,nGam),
                 thetaProp.segment(nBet+nGam,1)(0));
  }
  int n_iter;
  double max_err;
  EvalWeights();
  LambdaNR(n_iter, max_err);
  bool satisfy = false;
  if (n_iter < max_iter || max_err <= rel_tol) satisfy = true;
  // if does not satisfy, keep the old theta
  if (satisfy == false) {
    // std::cout << "LambdaNR not converged so keep the old one."<< std::endl;
    // std::cout << "n_iter = " << n_iter << std::endl;
    // std::cout << "max_err = " << max_err << std::endl;
    return;
  }
  // if does satisfy, flip a coin
  double u = R::unif_rand();
  // std::cout << "before EvalOmegas" << std::endl;
  EvalOmegas();
  // std::cout << "omegas = " << omegas.transpose() << std::endl;
  double logELProp = LogEL();
  // std::cout << "logELProp = " << logELProp << std::endl;
  double ratio = exp(logELProp-logELCur);
  double a = std::min(1.0,ratio);
  if (u < a) { // accepted
    accept = true;
    thetaCur = thetaProp;
    logELCur = logELProp;
  }
}

// template<typename ELModel>
// inline MatrixXd InnerELC<ELModel>::postSampleAdapt(int nsamples, int nburn, 
//                                                    VectorXd thetaInit,
//                                                    double *mwgSd, bool *rvDoMcmc, 
//                                                    VectorXd &paccept) {
template<typename ELModel>
inline MatrixXd InnerELC<ELModel>::postSampleAdapt(int nsamples, int nburn, 
                                                   VectorXd thetaInit,
                                                   double *mwgSd,
                                                   VectorXd &rvDoMcmc,
                                                   bool *doAdapt, 
                                                   VectorXd &paccept) {
  int nTheta = thetaInit.size();
  MatrixXd theta_chain(nTheta,nsamples);
  paccept = VectorXd::Zero(nTheta);
  // theta_chain.fill(0.0); // debug
  // paccept.fill(0.0);
  MwgAdapt tuneMCMC(nTheta, doAdapt);
  bool *isAccepted = new bool[nTheta];
  for (int ii=0; ii<nTheta; ii++) {
    isAccepted[ii] = false;
  }
  VectorXd thetaCur = thetaInit;
  if (nTheta == nBet) {
    std::cout << "location model." << std::endl;
    ELModel::EvalG(thetaCur);
    EvalEpsilons(thetaCur);
  }
  else {
    if (nTheta == nBet + nGam + 1) {
      std::cout << "location-scale model for mean regression." << std::endl;
      ELModel::EvalG(thetaCur.head(nBet),
                     thetaCur.segment(nBet,nGam),
                     thetaCur.tail(1)(0),
                     VectorXd::Zero(0));
    }
    else {
      std::cout << "location-scale model for quantile regression." << std::endl;
      ELModel::EvalG(thetaCur.head(nBet),
                     thetaCur.segment(nBet,nGam),
                     thetaCur.segment(nBet+nGam,1)(0),
                     thetaCur.tail(nQts));
    }
    EvalEpsilons(thetaCur.head(nBet),
                 thetaCur.segment(nBet,nGam),
                 thetaCur.segment(nBet+nGam,1)(0)); // Note: have to take the element here
  }
  EvalOmegas();
  // std::cout << "initial omegas = " << omegas.transpose() << std::endl;
  double logELCur = LogEL();
  // MCMC loop
  for(int ii=-nburn; ii<nsamples; ii++) {
    // if (ii % 200 == 0) {
    //   std::cout << "ii = " << ii << std::endl;
    //   
    //   // DEBUG begins
    //   std::cout << "mwgSd = ";
    //   for (int ll=0; ll<nTheta; ll++) {
    //     std::cout << mwgSd[ll] << ' ';
    //   }
    //   std::cout << std::endl;
    // 
    //   std::cout << "isAccepted = ";
    //   for (int ll=0; ll<nTheta; ll++) {
    //     std::cout << isAccepted[ll] << ' ';
    //   }
    //   std::cout << std::endl;
    //   // DEBUG ends
    // }
    for(int jj=0; jj<nTheta; jj++) {
      if(rvDoMcmc[jj]) {
        // modifies thetaCur's jj-th entry
        mwgStep(thetaCur,jj,mwgSd[jj],isAccepted[jj],logELCur);
        // std::cout << "in sampler loop: thetaCur = " << thetaCur.transpose() << std::endl;
        // std::cout << "mwgSd[jj] = " << mwgSd[jj] << std::endl;
        if (isAccepted[jj]) paccept(jj) += 1; // add 1 to paccept if accepted
      }
    }
    if (ii >= 0) {
      theta_chain.col(ii) = thetaCur;
    }
    tuneMCMC.adapt(mwgSd, isAccepted);
    // TODO: temp to check if the chain is converging..
    if (ii > 0 && ii % 1000 == 0) {
      int noconv = 0;
      VectorXd pacctemp = paccept.array() / (nburn+ii);
      std::cout << "pactemp = "; 
      for (int kk=0; kk<nTheta; kk++) {
        std::cout << pacctemp(kk) << ' ';
        if (pacctemp(kk) < 0.4) noconv += 1;
      }
      std::cout << std::endl;
      if (noconv == nTheta) {
        theta_chain.fill(0.0);
        break;
      }
    }
  }
  paccept /= (nsamples+nburn);
  delete[] isAccepted; // deallocate memory
  return(theta_chain);
}
*/

#endif