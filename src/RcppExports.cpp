// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

// CensEL_ctor
SEXP CensEL_ctor(int n_obs, int n_eqs);
RcppExport SEXP _flexEL_CensEL_ctor(SEXP n_obsSEXP, SEXP n_eqsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n_obs(n_obsSEXP);
    Rcpp::traits::input_parameter< int >::type n_eqs(n_eqsSEXP);
    rcpp_result_gen = Rcpp::wrap(CensEL_ctor(n_obs, n_eqs));
    return rcpp_result_gen;
END_RCPP
}
// CensEL_set_max_iter_nr
void CensEL_set_max_iter_nr(SEXP pCEL, int max_iter);
RcppExport SEXP _flexEL_CensEL_set_max_iter_nr(SEXP pCELSEXP, SEXP max_iterSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< int >::type max_iter(max_iterSEXP);
    CensEL_set_max_iter_nr(pCEL, max_iter);
    return R_NilValue;
END_RCPP
}
// CensEL_set_max_iter_em
void CensEL_set_max_iter_em(SEXP pCEL, int max_iter);
RcppExport SEXP _flexEL_CensEL_set_max_iter_em(SEXP pCELSEXP, SEXP max_iterSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< int >::type max_iter(max_iterSEXP);
    CensEL_set_max_iter_em(pCEL, max_iter);
    return R_NilValue;
END_RCPP
}
// CensEL_set_rel_tol
void CensEL_set_rel_tol(SEXP pCEL, int rel_tol);
RcppExport SEXP _flexEL_CensEL_set_rel_tol(SEXP pCELSEXP, SEXP rel_tolSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< int >::type rel_tol(rel_tolSEXP);
    CensEL_set_rel_tol(pCEL, rel_tol);
    return R_NilValue;
END_RCPP
}
// CensEL_set_abs_tol
void CensEL_set_abs_tol(SEXP pCEL, int abs_tol);
RcppExport SEXP _flexEL_CensEL_set_abs_tol(SEXP pCELSEXP, SEXP abs_tolSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< int >::type abs_tol(abs_tolSEXP);
    CensEL_set_abs_tol(pCEL, abs_tol);
    return R_NilValue;
END_RCPP
}
// CensEL_set_lambda0
void CensEL_set_lambda0(SEXP pCEL, Eigen::VectorXd lambda0);
RcppExport SEXP _flexEL_CensEL_set_lambda0(SEXP pCELSEXP, SEXP lambda0SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda0(lambda0SEXP);
    CensEL_set_lambda0(pCEL, lambda0);
    return R_NilValue;
END_RCPP
}
// CensEL_get_n_obs
int CensEL_get_n_obs(SEXP pGEL);
RcppExport SEXP _flexEL_CensEL_get_n_obs(SEXP pGELSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    rcpp_result_gen = Rcpp::wrap(CensEL_get_n_obs(pGEL));
    return rcpp_result_gen;
END_RCPP
}
// CensEL_get_n_eqs
int CensEL_get_n_eqs(SEXP pGEL);
RcppExport SEXP _flexEL_CensEL_get_n_eqs(SEXP pGELSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    rcpp_result_gen = Rcpp::wrap(CensEL_get_n_eqs(pGEL));
    return rcpp_result_gen;
END_RCPP
}
// CensEL_get_supp_adj
bool CensEL_get_supp_adj(SEXP pGEL);
RcppExport SEXP _flexEL_CensEL_get_supp_adj(SEXP pGELSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    rcpp_result_gen = Rcpp::wrap(CensEL_get_supp_adj(pGEL));
    return rcpp_result_gen;
END_RCPP
}
// CensEL_set_supp_adj
void CensEL_set_supp_adj(SEXP pCEL, bool supp_adj, Rcpp::Nullable<Rcpp::NumericVector> a_);
RcppExport SEXP _flexEL_CensEL_set_supp_adj(SEXP pCELSEXP, SEXP supp_adjSEXP, SEXP a_SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< bool >::type supp_adj(supp_adjSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::NumericVector> >::type a_(a_SEXP);
    CensEL_set_supp_adj(pCEL, supp_adj, a_);
    return R_NilValue;
END_RCPP
}
// CensEL_set_smooth
void CensEL_set_smooth(SEXP pCEL, bool smooth, Rcpp::Nullable<Rcpp::NumericVector> s_);
RcppExport SEXP _flexEL_CensEL_set_smooth(SEXP pCELSEXP, SEXP smoothSEXP, SEXP s_SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< bool >::type smooth(smoothSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::NumericVector> >::type s_(s_SEXP);
    CensEL_set_smooth(pCEL, smooth, s_);
    return R_NilValue;
END_RCPP
}
// CensEL_eval_weights
Eigen::VectorXd CensEL_eval_weights(SEXP pCEL, Eigen::VectorXd delta, Eigen::VectorXd epsilon, Eigen::VectorXd omega);
RcppExport SEXP _flexEL_CensEL_eval_weights(SEXP pCELSEXP, SEXP deltaSEXP, SEXP epsilonSEXP, SEXP omegaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type delta(deltaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type omega(omegaSEXP);
    rcpp_result_gen = Rcpp::wrap(CensEL_eval_weights(pCEL, delta, epsilon, omega));
    return rcpp_result_gen;
END_RCPP
}
// CensEL_omega_hat
Eigen::VectorXd CensEL_omega_hat(SEXP pCEL, Eigen::MatrixXd G, Eigen::VectorXd delta, Eigen::VectorXd epsilon);
RcppExport SEXP _flexEL_CensEL_omega_hat(SEXP pCELSEXP, SEXP GSEXP, SEXP deltaSEXP, SEXP epsilonSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type delta(deltaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type epsilon(epsilonSEXP);
    rcpp_result_gen = Rcpp::wrap(CensEL_omega_hat(pCEL, G, delta, epsilon));
    return rcpp_result_gen;
END_RCPP
}
// CensEL_logel
double CensEL_logel(SEXP pCEL, Eigen::MatrixXd G, Eigen::VectorXd delta, Eigen::VectorXd epsilon);
RcppExport SEXP _flexEL_CensEL_logel(SEXP pCELSEXP, SEXP GSEXP, SEXP deltaSEXP, SEXP epsilonSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pCEL(pCELSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type delta(deltaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type epsilon(epsilonSEXP);
    rcpp_result_gen = Rcpp::wrap(CensEL_logel(pCEL, G, delta, epsilon));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_ctor
SEXP GenEL_ctor(int n_obs, int n_eqs);
RcppExport SEXP _flexEL_GenEL_ctor(SEXP n_obsSEXP, SEXP n_eqsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n_obs(n_obsSEXP);
    Rcpp::traits::input_parameter< int >::type n_eqs(n_eqsSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_ctor(n_obs, n_eqs));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_set_max_iter
void GenEL_set_max_iter(SEXP pGEL, int max_iter);
RcppExport SEXP _flexEL_GenEL_set_max_iter(SEXP pGELSEXP, SEXP max_iterSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< int >::type max_iter(max_iterSEXP);
    GenEL_set_max_iter(pGEL, max_iter);
    return R_NilValue;
END_RCPP
}
// GenEL_set_rel_tol
void GenEL_set_rel_tol(SEXP pGEL, double rel_tol);
RcppExport SEXP _flexEL_GenEL_set_rel_tol(SEXP pGELSEXP, SEXP rel_tolSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< double >::type rel_tol(rel_tolSEXP);
    GenEL_set_rel_tol(pGEL, rel_tol);
    return R_NilValue;
END_RCPP
}
// GenEL_set_supp_adj
void GenEL_set_supp_adj(SEXP pGEL, bool supp_adj, Rcpp::Nullable<Rcpp::NumericVector> a_, Rcpp::Nullable<Rcpp::NumericVector> weight_adj_);
RcppExport SEXP _flexEL_GenEL_set_supp_adj(SEXP pGELSEXP, SEXP supp_adjSEXP, SEXP a_SEXP, SEXP weight_adj_SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< bool >::type supp_adj(supp_adjSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::NumericVector> >::type a_(a_SEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::NumericVector> >::type weight_adj_(weight_adj_SEXP);
    GenEL_set_supp_adj(pGEL, supp_adj, a_, weight_adj_);
    return R_NilValue;
END_RCPP
}
// GenEL_set_lambda0
void GenEL_set_lambda0(SEXP pGEL, Eigen::VectorXd lambda0);
RcppExport SEXP _flexEL_GenEL_set_lambda0(SEXP pGELSEXP, SEXP lambda0SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda0(lambda0SEXP);
    GenEL_set_lambda0(pGEL, lambda0);
    return R_NilValue;
END_RCPP
}
// GenEL_get_n_obs
int GenEL_get_n_obs(SEXP pGEL);
RcppExport SEXP _flexEL_GenEL_get_n_obs(SEXP pGELSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_get_n_obs(pGEL));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_get_n_eqs
int GenEL_get_n_eqs(SEXP pGEL);
RcppExport SEXP _flexEL_GenEL_get_n_eqs(SEXP pGELSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_get_n_eqs(pGEL));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_get_supp_adj
bool GenEL_get_supp_adj(SEXP pGEL);
RcppExport SEXP _flexEL_GenEL_get_supp_adj(SEXP pGELSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_get_supp_adj(pGEL));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_lambda_nr
Eigen::VectorXd GenEL_lambda_nr(SEXP pGEL, Eigen::MatrixXd G, Eigen::VectorXd weights, bool verbose);
RcppExport SEXP _flexEL_GenEL_lambda_nr(SEXP pGELSEXP, SEXP GSEXP, SEXP weightsSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_lambda_nr(pGEL, G, weights, verbose));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_omega_hat
Eigen::VectorXd GenEL_omega_hat(SEXP pGEL, Eigen::VectorXd lambda, Eigen::MatrixXd G, Eigen::VectorXd weights);
RcppExport SEXP _flexEL_GenEL_omega_hat(SEXP pGELSEXP, SEXP lambdaSEXP, SEXP GSEXP, SEXP weightsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type weights(weightsSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_omega_hat(pGEL, lambda, G, weights));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_logel
double GenEL_logel(SEXP pGEL, Eigen::MatrixXd G, bool verbose);
RcppExport SEXP _flexEL_GenEL_logel(SEXP pGELSEXP, SEXP GSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_logel(pGEL, G, verbose));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_weighted_logel
double GenEL_weighted_logel(SEXP pGEL, Eigen::MatrixXd G, Eigen::VectorXd weights, bool verbose);
RcppExport SEXP _flexEL_GenEL_weighted_logel(SEXP pGELSEXP, SEXP GSEXP, SEXP weightsSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_weighted_logel(pGEL, G, weights, verbose));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_logel_grad
Rcpp::List GenEL_logel_grad(SEXP pGEL, Eigen::MatrixXd G, bool verbose);
RcppExport SEXP _flexEL_GenEL_logel_grad(SEXP pGELSEXP, SEXP GSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_logel_grad(pGEL, G, verbose));
    return rcpp_result_gen;
END_RCPP
}
// GenEL_weighted_logel_grad
Rcpp::List GenEL_weighted_logel_grad(SEXP pGEL, Eigen::MatrixXd G, Eigen::VectorXd weights, bool verbose);
RcppExport SEXP _flexEL_GenEL_weighted_logel_grad(SEXP pGELSEXP, SEXP GSEXP, SEXP weightsSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type pGEL(pGELSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(GenEL_weighted_logel_grad(pGEL, G, weights, verbose));
    return rcpp_result_gen;
END_RCPP
}
// MeanReg_evalG
Eigen::MatrixXd MeanReg_evalG(Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd beta);
RcppExport SEXP _flexEL_MeanReg_evalG(SEXP ySEXP, SEXP XSEXP, SEXP betaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type beta(betaSEXP);
    rcpp_result_gen = Rcpp::wrap(MeanReg_evalG(y, X, beta));
    return rcpp_result_gen;
END_RCPP
}
// MeanRegLS_EvalG
Eigen::MatrixXd MeanRegLS_EvalG(Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::MatrixXd Z, Eigen::VectorXd beta, Eigen::VectorXd gamma, double sig2);
RcppExport SEXP _flexEL_MeanRegLS_EvalG(SEXP ySEXP, SEXP XSEXP, SEXP ZSEXP, SEXP betaSEXP, SEXP gammaSEXP, SEXP sig2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type Z(ZSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type gamma(gammaSEXP);
    Rcpp::traits::input_parameter< double >::type sig2(sig2SEXP);
    rcpp_result_gen = Rcpp::wrap(MeanRegLS_EvalG(y, X, Z, beta, gamma, sig2));
    return rcpp_result_gen;
END_RCPP
}
// QuantRegEvalG
Eigen::MatrixXd QuantRegEvalG(Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd tauArr, Eigen::MatrixXd Beta);
RcppExport SEXP _flexEL_QuantRegEvalG(SEXP ySEXP, SEXP XSEXP, SEXP tauArrSEXP, SEXP BetaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type tauArr(tauArrSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type Beta(BetaSEXP);
    rcpp_result_gen = Rcpp::wrap(QuantRegEvalG(y, X, tauArr, Beta));
    return rcpp_result_gen;
END_RCPP
}
// QuantRegLSEvalG
Eigen::MatrixXd QuantRegLSEvalG(Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::MatrixXd Z, Eigen::VectorXd tauArr, Eigen::VectorXd beta, Eigen::VectorXd gamma, double sig2, Eigen::VectorXd nu);
RcppExport SEXP _flexEL_QuantRegLSEvalG(SEXP ySEXP, SEXP XSEXP, SEXP ZSEXP, SEXP tauArrSEXP, SEXP betaSEXP, SEXP gammaSEXP, SEXP sig2SEXP, SEXP nuSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type Z(ZSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type tauArr(tauArrSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type gamma(gammaSEXP);
    Rcpp::traits::input_parameter< double >::type sig2(sig2SEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type nu(nuSEXP);
    rcpp_result_gen = Rcpp::wrap(QuantRegLSEvalG(y, X, Z, tauArr, beta, gamma, sig2, nu));
    return rcpp_result_gen;
END_RCPP
}
// QuantRegEvalGSmooth
Eigen::MatrixXd QuantRegEvalGSmooth(Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::VectorXd tauArr, Eigen::MatrixXd Beta, double s);
RcppExport SEXP _flexEL_QuantRegEvalGSmooth(SEXP ySEXP, SEXP XSEXP, SEXP tauArrSEXP, SEXP BetaSEXP, SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type tauArr(tauArrSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type Beta(BetaSEXP);
    Rcpp::traits::input_parameter< double >::type s(sSEXP);
    rcpp_result_gen = Rcpp::wrap(QuantRegEvalGSmooth(y, X, tauArr, Beta, s));
    return rcpp_result_gen;
END_RCPP
}
// QuantRegLSEvalGSmooth
Eigen::MatrixXd QuantRegLSEvalGSmooth(Eigen::VectorXd y, Eigen::MatrixXd X, Eigen::MatrixXd Z, Eigen::VectorXd tauArr, Eigen::VectorXd beta, Eigen::VectorXd gamma, double sig2, Eigen::VectorXd nu, double s);
RcppExport SEXP _flexEL_QuantRegLSEvalGSmooth(SEXP ySEXP, SEXP XSEXP, SEXP ZSEXP, SEXP tauArrSEXP, SEXP betaSEXP, SEXP gammaSEXP, SEXP sig2SEXP, SEXP nuSEXP, SEXP sSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type Z(ZSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type tauArr(tauArrSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type gamma(gammaSEXP);
    Rcpp::traits::input_parameter< double >::type sig2(sig2SEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type nu(nuSEXP);
    Rcpp::traits::input_parameter< double >::type s(sSEXP);
    rcpp_result_gen = Rcpp::wrap(QuantRegLSEvalGSmooth(y, X, Z, tauArr, beta, gamma, sig2, nu, s));
    return rcpp_result_gen;
END_RCPP
}
// adjG
Eigen::MatrixXd adjG(Eigen::MatrixXd G, double a);
RcppExport SEXP _flexEL_adjG(SEXP GSEXP, SEXP aSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type G(GSEXP);
    Rcpp::traits::input_parameter< double >::type a(aSEXP);
    rcpp_result_gen = Rcpp::wrap(adjG(G, a));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_flexEL_CensEL_ctor", (DL_FUNC) &_flexEL_CensEL_ctor, 2},
    {"_flexEL_CensEL_set_max_iter_nr", (DL_FUNC) &_flexEL_CensEL_set_max_iter_nr, 2},
    {"_flexEL_CensEL_set_max_iter_em", (DL_FUNC) &_flexEL_CensEL_set_max_iter_em, 2},
    {"_flexEL_CensEL_set_rel_tol", (DL_FUNC) &_flexEL_CensEL_set_rel_tol, 2},
    {"_flexEL_CensEL_set_abs_tol", (DL_FUNC) &_flexEL_CensEL_set_abs_tol, 2},
    {"_flexEL_CensEL_set_lambda0", (DL_FUNC) &_flexEL_CensEL_set_lambda0, 2},
    {"_flexEL_CensEL_get_n_obs", (DL_FUNC) &_flexEL_CensEL_get_n_obs, 1},
    {"_flexEL_CensEL_get_n_eqs", (DL_FUNC) &_flexEL_CensEL_get_n_eqs, 1},
    {"_flexEL_CensEL_get_supp_adj", (DL_FUNC) &_flexEL_CensEL_get_supp_adj, 1},
    {"_flexEL_CensEL_set_supp_adj", (DL_FUNC) &_flexEL_CensEL_set_supp_adj, 3},
    {"_flexEL_CensEL_set_smooth", (DL_FUNC) &_flexEL_CensEL_set_smooth, 3},
    {"_flexEL_CensEL_eval_weights", (DL_FUNC) &_flexEL_CensEL_eval_weights, 4},
    {"_flexEL_CensEL_omega_hat", (DL_FUNC) &_flexEL_CensEL_omega_hat, 4},
    {"_flexEL_CensEL_logel", (DL_FUNC) &_flexEL_CensEL_logel, 4},
    {"_flexEL_GenEL_ctor", (DL_FUNC) &_flexEL_GenEL_ctor, 2},
    {"_flexEL_GenEL_set_max_iter", (DL_FUNC) &_flexEL_GenEL_set_max_iter, 2},
    {"_flexEL_GenEL_set_rel_tol", (DL_FUNC) &_flexEL_GenEL_set_rel_tol, 2},
    {"_flexEL_GenEL_set_supp_adj", (DL_FUNC) &_flexEL_GenEL_set_supp_adj, 4},
    {"_flexEL_GenEL_set_lambda0", (DL_FUNC) &_flexEL_GenEL_set_lambda0, 2},
    {"_flexEL_GenEL_get_n_obs", (DL_FUNC) &_flexEL_GenEL_get_n_obs, 1},
    {"_flexEL_GenEL_get_n_eqs", (DL_FUNC) &_flexEL_GenEL_get_n_eqs, 1},
    {"_flexEL_GenEL_get_supp_adj", (DL_FUNC) &_flexEL_GenEL_get_supp_adj, 1},
    {"_flexEL_GenEL_lambda_nr", (DL_FUNC) &_flexEL_GenEL_lambda_nr, 4},
    {"_flexEL_GenEL_omega_hat", (DL_FUNC) &_flexEL_GenEL_omega_hat, 4},
    {"_flexEL_GenEL_logel", (DL_FUNC) &_flexEL_GenEL_logel, 3},
    {"_flexEL_GenEL_weighted_logel", (DL_FUNC) &_flexEL_GenEL_weighted_logel, 4},
    {"_flexEL_GenEL_logel_grad", (DL_FUNC) &_flexEL_GenEL_logel_grad, 3},
    {"_flexEL_GenEL_weighted_logel_grad", (DL_FUNC) &_flexEL_GenEL_weighted_logel_grad, 4},
    {"_flexEL_MeanReg_evalG", (DL_FUNC) &_flexEL_MeanReg_evalG, 3},
    {"_flexEL_MeanRegLS_EvalG", (DL_FUNC) &_flexEL_MeanRegLS_EvalG, 6},
    {"_flexEL_QuantRegEvalG", (DL_FUNC) &_flexEL_QuantRegEvalG, 4},
    {"_flexEL_QuantRegLSEvalG", (DL_FUNC) &_flexEL_QuantRegLSEvalG, 8},
    {"_flexEL_QuantRegEvalGSmooth", (DL_FUNC) &_flexEL_QuantRegEvalGSmooth, 5},
    {"_flexEL_QuantRegLSEvalGSmooth", (DL_FUNC) &_flexEL_QuantRegLSEvalGSmooth, 9},
    {"_flexEL_adjG", (DL_FUNC) &_flexEL_adjG, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_flexEL(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
