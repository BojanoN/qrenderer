#pragma once
#include "vector.hpp"

class Matrix{

 public:
  // Konstruktori
 Matrix(std::vector<std::vector<double> > values):elements(values), rows(elements.size()), cols(elements[0].size()){};

  Matrix(){
    
  };

  // Vraća broj redaka
  virtual int getRowsCount(){return this->rows;};
  // Vraća broj stupaca
  virtual int getColsCount(){return this->cols;};

  // Vraća element matrice na indeksu (i, j)
 virtual double& operator()(int i, int j){
   if(i<this->rows && j<this->cols)
      return this->elements[i][j];
    else
      throw std::invalid_argument("Index out of bounds!");
  };

  // Vraća polje svih elemenata matrice
  virtual std::vector<std::vector<double> > toArray(){
    return this->elements;
  };

  // Zbraja dvije matrice i rezultat pohranjuje u trenutnoj
  Matrix& operator+(Matrix& matrix){
    if(this->getRowsCount()==matrix.getRowsCount() && this->getColsCount()==matrix.getColsCount()){
      for(int i=0; i<this->getRowsCount(); i++){
        for(int j=0; j<this->getColsCount(); j++){
          (*this)(i,j)+=matrix(i,j);
        }
      }
      return *this;
    }else
      throw std::invalid_argument("Matrix dimensions are not equal!");
  };

  // Zbraja dvije matrice i vraća novi objekt sa pohranjenim rezultatom
  Matrix operator+=(Matrix& matrix){
    std::vector<std::vector<double> > tmp(this->toArray());
    if(this->getRowsCount()==matrix.getRowsCount() && this->getColsCount()==matrix.getColsCount()){
      for(int i=0; i<this->getRowsCount(); i++){
        for(int j=0; j<this->getColsCount(); j++){
          tmp[i][j]+=matrix(i,j);
        }
      }
      return Matrix(tmp);
    }else
      throw std::invalid_argument("Matrix dimensions are not equal!");
  };

  // Oduzima dvije matrice i rezultat pohranjuje u trenutnoj
  Matrix& operator-(Matrix& matrix){
    if(this->getRowsCount()==matrix.getRowsCount() && this->getColsCount()==matrix.getColsCount()){
      for(int i=0; i<this->getRowsCount(); i++){
        for(int j=0; j<this->getColsCount(); j++){
          (*this)(i,j)-=matrix(i,j); 
        }
      }
      return *this;
    }else
      throw std::invalid_argument("Matrix dimensions are not equal!");
  };

  // Unarni minus, invertira elemente matrice
   Matrix operator-(){
    std::vector<std::vector<double> > tmp(this->toArray());
      for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->cols; j++){
          tmp[i][j]=-tmp[i][j];
        }
      }
      return Matrix(tmp);
    };

  // Oduzima dvije matrice i vraća novi objekt sa pohranjenim rezultatom
  Matrix operator-=(Matrix& matrix){
    std::vector<std::vector<double> > tmp(this->toArray());
    if(this->getRowsCount()==matrix.getRowsCount() && this->getColsCount()==matrix.getColsCount()){
      for(int i=0; i<this->getRowsCount(); i++){
        for(int j=0; j<this->getColsCount(); j++){
          tmp[i][j]-=matrix(i,j);
        }
      }
      return Matrix(tmp);
    }else
      throw std::invalid_argument("Matrix dimensions are not equal!");
  };

  // Množi dvije matrice i rezultat vraća u novom objektu
  Matrix operator*(Matrix matrix){
    std::vector<std::vector<double> > newMatrix;
    if(this->getColsCount()==matrix.getRowsCount()){
      for(int i=0; i<this->getRowsCount(); i++){
        std::vector<double> tmp;
        for(int j=0; j<matrix.getColsCount(); j++){
          double sum=0;
        
          for(int k=0; k<this->getColsCount(); k++){
            sum+=((*this)(i,k)*matrix(k,j));
          }
          tmp.push_back(sum);
        }
        newMatrix.push_back(tmp); 
      }
      return Matrix(newMatrix);
    }else
      throw std::invalid_argument("Matrix dimensions are not compatible!");
  };


  // Transponira matricu
  Matrix nTranspose(bool live);

  // Vraća dio matrice određen indeksima
  Matrix subMatrix(std::vector<int> rows, std::vector<int> cols, bool live);

  // Računa determinantu trenutne matrice
  double determinant(){
    if(this->getColsCount()==this->getRowsCount()){
      /*if(this->getColsCount()==2){
        return((*this)(0,0)*(*this)(1,1) - (*this)(0,1)*(*this)(1,0));
      }else if(this->getColsCount()==3){
        double det=0;
        for(int i=0; i<3; i++)
          det += ((*this)(0,i) * ((*this)(1,(i+1)%3) * (*this)(2,(i+2)%3) - (*this)(1,(i+2)%3) * (*this)(2,(i+1)%3)));
        return det;
      }else
      throw std::invalid_argument("Matrix dimension must be <=3"); */
      double tmp[N][N];
      
      for(int i=0; i<this->elements.size(); i++){
        for(int j=0; j<this->elements.size(); j++){
          tmp[i][j]=this->elements[i][j];
        }
      }
      return this->determinant(tmp, elements.size());
    }else
      throw std::invalid_argument("Matrix must be square!");
  
  };

  // Operator ~. Računa inverz matrice i vraća novi objekt sa rezultatom
  Matrix operator~(){
    if(this->getColsCount()==this->getRowsCount()){
      /*std::vector<std::vector<double> > newMatrix; 
      double det = this->determinant();
      if(this->getColsCount()==2){
        std::vector<double> tmp1;
        std::vector<double> tmp2;
        
        tmp1.push_back((*this)(1,1)/det);
        tmp1.push_back(-(*this)(0,1)/det);

        tmp2.push_back(-(*this)(1,0)/det);
        tmp2.push_back((*this)(0,0)/det);

        newMatrix.push_back(tmp1);
        newMatrix.push_back(tmp2);

        return Matrix(newMatrix);
      }else if(this->getColsCount()==3){
        for(int i=0; i<3; i++){
          std::vector<double> tmp;
          double val;
          for(int j=0; j<3; j++){
            val=(*this)((j+1)%3,(i+1)%3) * (*this)((j+2)%3,(i+2)%3) - ((*this)((j+1)%3,(i+2)%3) * (*this)((j+2)%3,(i+1)%3));
            tmp.push_back(val/ det);
        }
          newMatrix.push_back(tmp);
        }
        return Matrix(newMatrix);
      }else
      throw std::invalid_argument("Matrix dimension must be <=3");*/
      double tmp[N][N];
      double inv[N][N];
      std::vector<std::vector<double>> res;
      for(int i=0; i<this->elements.size(); i++){
        for(int j=0; j<this->elements.size(); j++){
          tmp[i][j]=this->elements[i][j];
        }
      }
      bool succ = this->inverse(tmp, inv, this->elements.size());
      if(succ){
        for(int i=0; i<this->elements.size(); i++){
          std::vector<double> r;
          for(int j=0; j<this->elements.size(); j++){
            r.push_back(inv[i][j]);
          }
          res.push_back(r);
        }
        return Matrix(res);
      }else
        throw std::invalid_argument("Singular matrix");
      
    }else
      throw std::invalid_argument("Matrix must be square!");
      };

  static std::regex parseRegex;

  // Kreira novu matricu iz ulaznog niza znakova
  static Matrix parseSimple(std::string str){

      if(std::regex_match(str, Matrix::parseRegex)){
        std::vector<std::vector<double> > ret;
        std::vector<double> tmp;
        ret.push_back(tmp);

        for(int i=0,j=0; i<str.size(); i++){
            if(str[i]!=' '){
              if(str[i]!='|'){
                int k=i;
                while((isdigit(str[i]) || str[i]=='-') && i<str.size())
                  i++;
                

                ret[j].push_back(atof(str.substr(k,i).c_str()));
              }
              else{
                j++;
                std::vector<double> newVect;
                ret.push_back(newVect);
              }
            }
            
        }
        return Matrix(ret);
      }else
        throw std::invalid_argument("Invalid input string!");
    
    };

  // Odgovarajuće matrice (jednostupčane ili jednoretčane) pretvara u vektor
  Vector* toVector(bool live);

 private:
  std::vector<std::vector<double> > elements;
  
  int rows;
  int cols;
  

void getCofactor(double A[N][N], double temp[N][N], int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
double determinant(double A[N][N], int n)
{
    double D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];
 
    double temp[N][N]; // To store cofactors
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}


// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(double A[N][N],double adj[N][N], int n)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    int sign = 1;
      double temp[N][N];
 
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, n);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, n-1));
        }
    }
}
 
// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(double A[N][N], double inverse[N][N], int n)
{
    // Find determinant of A[][]
    double det = determinant(A, n);
    if (det == 0)
    {
      std::cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    // Find adjoint
    double adj[N][N];
    adjoint(A, adj, n);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            inverse[i][j] = adj[i][j]/(det);
 
    return true;
}

};


// Razred koji modelira pogled na transponiranu matricu, izmjene u transponiranoj matrici su vidljive u originalnoj

class MatrixTransposeView: public Matrix{

 public:

  // Konstruktori
 MatrixTransposeView(Matrix* values){
   matrix=values;
 };

  // Vraća broj stupaca
 int getColsCount(){return matrix->getRowsCount();};
  // Vraća broj redaka
 int getRowsCount(){return matrix->getColsCount();};

   std::vector<std::vector<double> > toArray(){
     std::vector<std::vector<double> > ret;
     for(int i=0; i<matrix->getRowsCount(); i++){
       std::vector<double> tmp;
       for(int j=0; j<matrix->getColsCount(); j++){
         tmp.push_back((*matrix)(j,i));
       }
       ret.push_back(tmp);
      }
     return ret;
  };
   

   double& operator()(int i, int j){
     return (*matrix)(j,i);
   };

  std::unique_ptr<Vector> toVector(bool live);


 private:
  Matrix* matrix;

};


// Razred koji modelira pogled na dio matrice, izmjene u tom dijelu mijenjaju i originalu matricu

class MatrixSubMatrixView: public Matrix{

 public:
  MatrixSubMatrixView(std::vector<int> rows, std::vector<int> cols, Matrix* values): rowsIndices(rows), colsIndices(cols), matrix(values){};


  int getColsCount(){return colsIndices.size();};
  int getRowsCount(){return rowsIndices.size();};

  double& operator()(int i, int j){
    if(i<rowsIndices.size() && j<colsIndices.size()){
      return (*matrix)(rowsIndices[i], colsIndices[j]);
    }else
      throw std::invalid_argument("Index out of bounds!");
  };

  std::vector<std::vector<double> > toArray(){
    std::vector<std::vector<double> > ret;
    for(int i=0; i<rowsIndices.size(); i++){
      std::vector<double> tmp;
      for(int j=0; j<colsIndices.size(); j++){
        tmp.push_back((*matrix)(rowsIndices[i],colsIndices[j]));
      }
      ret.push_back(tmp);
    }
    return ret;
  };



 private:
  std::vector<int> rowsIndices;
  std::vector<int> colsIndices;
  Matrix* matrix;

};


inline std::ostream & operator<<(std::ostream & Str, Matrix& matrix) { 
  for(int i=0; i<matrix.getRowsCount(); i++){
    for(int j=0; j<matrix.getColsCount(); j++){
      if(j+1 == matrix.getColsCount())
        Str<<matrix(i,j);
      else
        Str<<matrix(i,j)<<" ";
    }
    Str<<"\n";
  }
  return Str;
};


inline std::ostream & operator<<(std::ostream & Str, std::unique_ptr<Matrix> matrix) { 
  for(int i=0; i<matrix->getRowsCount(); i++){
    for(int j=0; j<matrix->getColsCount(); j++){
      if(j+1 == matrix->getColsCount())
        Str<<(*matrix)(i,j);
      else
        Str<<(*matrix)(i,j)<<" ";
    }
    Str<<"\n";
  }
  return Str;
};


// Razred koji modelira prikaz vektora kao matricu

class MatrixVectorView: public Matrix{

public:

  MatrixVectorView(Vector* vect, bool row): vector(vect), asRowMatrix(row){
    
  };

  int getColsCount(){
    if(asRowMatrix)
      return 1;
    else
      return this->vector->getDimension();
  };
  int getRowsCount(){
    if(asRowMatrix)
      return this->vector->getDimension();
    else
      return 1;
  };

  double& operator()(int i, int j){
    if(asRowMatrix){
      if(i==0 && j<this->vector->getDimension())
        return (*vector)[j];
      else
        throw std::invalid_argument("Index out of bounds!");
    }else{
      if(j==0 && i<this->vector->getDimension())
        return (*vector)[i];
      else
        throw std::invalid_argument("Index out of bounds!");
    }

  };

 std::vector<std::vector<double> > toArray(){
    std::vector<std::vector<double> > ret;
    if(asRowMatrix){
      ret.push_back(this->vector->toArray());
    }else{
      for(int i=0; i<this->vector->getDimension(); i++){
        std::vector<double> tmp;
        tmp.push_back((*vector)[i]); 
        ret.push_back(tmp);
      }
    }
    return ret;
    };



private:
  Vector* vector;
  bool asRowMatrix;
  
};


// Razred koji modelira prikaz matrice kao vektora

class VectorMatrixView: public Vector{
public:

  VectorMatrixView(Matrix* mat, bool asRow):matrix(mat), rowMatrix(asRow){
    if(!(mat->getColsCount()==1 && mat->getRowsCount()!=1) && !(mat->getRowsCount()==1 && mat->getColsCount()!=1))
      throw std::invalid_argument("Matrix must be a row or column matrix!");
    else{
      if(asRow)
        dimension=mat->getColsCount();
      else
        dimension=mat->getRowsCount();
    }
  }

  

  double& operator[](unsigned int index){
    if(rowMatrix){
      return(*matrix)(0,index);
    }else
      return(*matrix)(index,0);
  };


 
  int getDimension() const{return this->dimension;};

private:
  int dimension;
  bool rowMatrix;
  Matrix* matrix;
};

