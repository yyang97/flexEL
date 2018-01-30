// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

// lambdaNR
Rcpp::List lambdaNR(Eigen::MatrixXd G, int maxIter, double eps, bool verbose);
RcppExport SEXP _bayesELnew_lambdaNR(SEXP GSEXP, SEXP maxIterSEXP, SEXP epsSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< int >::type maxIter(maxIterSEXP);
    Rcpp::traits::input_parameter< double >::type eps(epsSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(lambdaNR(G, maxIter, eps, verbose));
    return rcpp_result_gen;
END_RCPP
}
// MeanReg_loglik
double MeanReg_loglik(Eigen::VectorXd y, Eigen::MatrixXd X, int nObs, int nEqs, Eigen::VectorXd beta, Eigen::VectorXd lambda0, int maxIter, double eps);
RcppExport SEXP _bayesELnew_MeanReg_loglik(SEXP ySEXP, SEXP XSEXP, SEXP nObsSEXP, SEXP nEqsSEXP, SEXP betaSEXP, SEXP lambda0SEXP, SEXP maxIterSEXP, SEXP epsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< int >::type nObs(nObsSEXP);
    Rcpp::traits::input_parameter< int >::type nEqs(nEqsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda0(lambda0SEXP);
    Rcpp::traits::input_parameter< int >::type maxIter(maxIterSEXP);
    Rcpp::traits::input_parameter< double >::type eps(epsSEXP);
    rcpp_result_gen = Rcpp::wrap(MeanReg_loglik(y, X, nObs, nEqs, beta, lambda0, maxIter, eps));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_bayesELnew_lambdaNR", (DL_FUNC) &_bayesELnew_lambdaNR, 4},
    {"_bayesELnew_MeanReg_loglik", (DL_FUNC) &_bayesELnew_MeanReg_loglik, 8},
    {NULL, NULL, 0}
};

RcppExport void R_init_bayesELnew(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
