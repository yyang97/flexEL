#ifndef MEANREGMODEL_h
#define MEANREGMODEL_h

// #include <math.h>
// #include <Rmath.h>

class MeanRegModel {
private:
  RowVectorXd yXb;
  RowVectorXd eZg;
  RowVectorXd yXbeZg;
  RowVectorXd yXbeZg2; 
  MatrixXd tG;
protected:
  VectorXd y;
  MatrixXd X;
  MatrixXd Z;
  int nObs, nEqs, nBet, nGam, nQts; // TODO: nQts is not used in mean reg
  MatrixXd G;
public:
  // MeanRegModel(const Ref<const VectorXd>& _y, const Ref<const MatrixXd>& _X,
  //              void* params); // old ctor 
  // MeanRegModel(); // default ctor -- it shouldn't have one actually
  void initData(int _nObs, int _nEqs);
  void setData(const Ref<const VectorXd>& _y, 
               const Ref<const MatrixXd>& _X,
               void* params); // set data with default ctor
  void setData(const Ref<const VectorXd>& _y, 
               const Ref<const MatrixXd>& _X,
               const Ref<const MatrixXd>& _Z,
               void* params); // set data with default ctor
  // for location linear regression models
  void evalG(const Ref<const VectorXd>& beta); 
  // for location-scale linear regression models
  void evalG(const Ref<const VectorXd>& beta, 
             const Ref<const VectorXd>& gamma, 
             const double& sig2,
             const Ref<const VectorXd>& dummy);
  void setG(const Ref<const MatrixXd>& _G); 
  MatrixXd getG();
};

/*
// constructor: old
inline MeanRegModel::MeanRegModel(const Ref<const VectorXd>& _y,
                                  const Ref<const MatrixXd>& _X,
                                  void* params) {
    y = _y;
    X = _X;
    nObs = y.size();
    nBet = X.rows(); // X gets passed as p x nObs matrix
    G = MatrixXd::Zero(nBet,nObs);
    tG = MatrixXd::Zero(nObs, nBet);
    yXb = RowVectorXd::Zero(nObs);
}
*/

// // default ctor
// inline MeanRegModel::MeanRegModel() {}

// pre-allocate space with given dimensions
inline void MeanRegModel::initData(int _nObs, int _nEqs) {
  nObs = _nObs;
  nEqs = _nEqs; // X gets passed as nBet x nObs matrix
  G = MatrixXd::Zero(nEqs,nObs);
}

// setData location model (with default ctor)
inline void MeanRegModel::setData(const Ref<const VectorXd>& _y,
                                  const Ref<const MatrixXd>& _X,
                                  void* params) {
  y = _y;
  X = _X;
  nObs = y.size();
  nBet = X.rows(); // X gets passed as nBet x nObs matrix
  nGam = 0; 
  nEqs = nBet; 
  G = MatrixXd::Zero(nBet,nObs);
  tG = MatrixXd::Zero(nObs, nBet);
  yXb = RowVectorXd::Zero(nObs);
}

// setData location-scale model (with default ctor)
inline void MeanRegModel::setData(const Ref<const VectorXd>& _y,
                                  const Ref<const MatrixXd>& _X,
                                  const Ref<const MatrixXd>& _Z,
                                  void* params) {
  y = _y;
  X = _X;
  Z = _Z;
  nObs = y.size();
  nBet = X.rows(); // X gets passed as nBet x nObs matrix
  nGam = Z.rows(); // Z gets passed as nGam x nObs matrix
  nEqs = nBet+nGam+1; 
  G = MatrixXd::Zero(nEqs,nObs);
  tG = MatrixXd::Zero(nObs, nEqs);
  eZg = RowVectorXd::Zero(nObs);
  yXbeZg = RowVectorXd::Zero(nObs);
  yXbeZg2 = RowVectorXd::Zero(nObs);
}

// form the G matrix for location linear regression model 
inline void MeanRegModel::evalG(const Ref<const VectorXd>& beta) {
  // std::cout << "evalG: beta = " << beta.transpose() << std::endl;
  yXb.noalias() = y.transpose() - beta.transpose() * X;
  tG = X.transpose();
  tG.array().colwise() *= yXb.transpose().array();
  G = tG.transpose();
}

// form the G matrix for location-scale linear regression model 
inline void MeanRegModel::evalG(const Ref<const VectorXd>& beta, 
                                const Ref<const VectorXd>& gamma,
                                const double &sig2,
                                const Ref<const VectorXd>& dummy) {
  eZg.array() = (-gamma.transpose()*Z).array().exp();
  yXbeZg.array() = (y.transpose()-beta.transpose()*X).array() * eZg.array();
  yXbeZg2.array() = yXbeZg.array()*yXbeZg.array();
  tG.block(0,0,nObs,nBet) = X.transpose();
  tG.block(0,0,nObs,nBet).array().colwise() *= yXbeZg.transpose().array() * eZg.transpose().array();
  tG.block(0,nBet,nObs,nGam) = Z.transpose();
  // tG.block(0,nBet,nObs,nGam).array().colwise() *= yXbeZg2.transpose().array();
  tG.block(0,nBet,nObs,nGam).array().colwise() *= (1.0-yXbeZg2.transpose().array());
  tG.rightCols(1).array() = 1/sig2*yXbeZg2.transpose().array()-1;
  G = tG.transpose();
}

// set function for G matrix
inline void MeanRegModel::setG(const Ref<const MatrixXd>& _G) {
    G = _G; 
}

// get function for G matrix
inline MatrixXd MeanRegModel::getG() {
    return(G);
}

#endif
