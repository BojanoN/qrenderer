#include"matrix.hpp"
#include <cmath>
#include <ctgmath>
#define PI 3.14159265

class MatrixUtil{
public:
  static Matrix yRotMatrix(float angle){
    double sine = sin(angle);
    double cosine = cos(angle);

    Matrix ret = identity;
    ret(0,0) = cosine;
    ret(0,2) = sine;
    ret(2,0) = -sine;
    ret(2,2) = cosine;

    return ret;
  };

  
  static Matrix xRotMatrix(float angle){

    double sine = sin(angle );
    double cosine = cos(angle);

    Matrix ret = identity;
    ret(1,1) = cosine;
    ret(1,2) = sine;
    ret(2,1) = -sine;
    ret(2,2) = cosine;

    return ret;
  };

  

  static Matrix transMatrix(float x, float y, float z){
    Matrix ret = identity;

    ret(3,0) = x;
    ret(3,1) = y;
    ret(3,2) = z;

    return ret;
  }

  static Matrix axisAngleRotMatrix(Vector axis, float angle){
    Matrix ret = identity;
    double sine = sin(angle );
    double cosine = cos(angle);

    ret(0,0) = cosine+axis[0]*axis[0]*(1-cosine);
    ret(0,1) = axis[0]*axis[1]*(1-cosine)-axis[2]*sine;
    ret(0,2) = axis[0]*axis[2]*(1-cosine)+axis[1]*sine;

    ret(1,0) =  axis[0]*axis[1]*(1-cosine)+axis[2]*sine;
    ret(1,1) = cosine+axis[1]*axis[1]*(1-cosine);
    ret(1,2) = axis[1]*axis[2]*(1-cosine)-axis[0]*sine;

    ret(2,0) = axis[2]*axis[0]*(1-cosine)-axis[1]*sine;
    ret(2,1) = axis[2]*axis[1]*(1-cosine)+axis[0]*sine;
    ret(2,2) =  cosine+axis[2]*axis[2]*(1-cosine);

    return ret;
  }

private:
  static const Matrix identity;
};
