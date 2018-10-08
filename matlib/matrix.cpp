#include"matrix.hpp"

Matrix Vector::toRowMatrix(bool live){
    std::vector<std::vector<double> > newMatrix; 
    newMatrix.push_back(this->toArray());
    return (Matrix(newMatrix));
};

Matrix* Vector::toColumnMatrix(bool live){
  std::vector<std::vector<double> > newMatrix;
  if(live){
    return (new MatrixVectorView(this, false));
  }else{
    for(int i=0; i<this->getDimension(); i++){
      std::vector<double> tmp;
      tmp.push_back((*this)[i]);
      newMatrix.push_back(tmp);
    }
    return new Matrix(newMatrix);
  }
};

Vector*  Matrix::toVector(bool live){
  
  if(live){

    if(this->getRowsCount()==1)
      return new VectorMatrixView(this, true);
    else
      return new VectorMatrixView(this, false);
  }else{
    if(this->getRowsCount()==1)
      return new Vector(this->toArray()[0]);
    else{
      std::vector<double> tmp;
      for(int i=0; i<this->getRowsCount(); i++)
        tmp.push_back((*this)(i,0));
      return new Vector(tmp);
    }
  }
};


Matrix Matrix::nTranspose(bool live){
  if(live){
    return MatrixTransposeView(this);
  }else{
    MatrixTransposeView ret(this);
    return Matrix(ret.toArray());
  }
};


Matrix Matrix::subMatrix(std::vector<int> rows, std::vector<int> cols, bool live){
  if(live){
    return MatrixSubMatrixView(rows, cols, this);
  }else
    return Matrix(MatrixSubMatrixView(rows, cols, this).toArray());
};

std::regex Matrix:: parseRegex("(-)*[[:digit:]]+( (-)*[[:digit:]]+)*( \\| (-)*[[:digit:]]+( (-)*[[:digit:]]+)*)*");

