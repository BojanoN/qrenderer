#include "matrix.hpp"
#include <cmath>
#include <ctgmath>
#define PI 3.14159265

class MatrixUtil{
public:
  static Matrix yRotMatrix(float angle){
    double sine = sin(angle);
    double cosine = cos(angle);

    Matrix ret = identity4;
    ret(0,0) = cosine;
    ret(0,2) = sine;
    ret(2,0) = -sine;
    ret(2,2) = cosine;

    return ret;
  };

  
  static Matrix xRotMatrix(float angle){

    double sine = sin(angle );
    double cosine = cos(angle);

    Matrix ret = identity4;
    ret(1,1) = cosine;
    ret(1,2) = sine;
    ret(2,1) = -sine;
    ret(2,2) = cosine;

    return ret;
  };

  

  static Matrix transMatrix(float x, float y, float z){
    Matrix ret = identity4;

    ret(3,0) = x;
    ret(3,1) = y;
    ret(3,2) = z;

    return ret;
  }

  static Matrix axisAngleRotMatrix(Vector axis, float angle){
    Matrix ret = identity4;
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

  static Matrix perspectiveProjection(float fovy, float aspect, float zNear, float zFar){
    Matrix ret = identity4;

    float f = 1. / tan(fovy / 2.);
    float tmpDiff = zNear - zFar;

    ret(0, 0) = f / aspect;
    ret(1, 1) = f;
    ret(2, 2) = (zFar + zNear) / (tmpDiff);
    ret(2, 3) = (zFar * zNear * 2) / tmpDiff;
    ret(3, 2) = -1;

    return ret;
  }

  static Matrix viewMatrix(Vector eye, Vector center, Vector up){
    
      Matrix tmp = identity4;

      std::vector<double> elems;
      elems.push_back(eye[0] - center[0]);
      elems.push_back(eye[1] - center[1]);
      elems.push_back(eye[2] - center[2]);

      Vector F(elems);

      F.normalize();
      up.normalize();

      Vector s = up.nVectorProduct(F);

      tmp(0, 0) = s[0];
      tmp(1, 0) = s[1];
      tmp(2, 0) = s[2];

      s.normalize();
      Vector u = F.nVectorProduct(s);


      tmp(0, 1) = u[0];
      tmp(1, 1) = u[1];
      tmp(2, 1) = u[2];

      tmp(0, 2) = F[0];
      tmp(1, 2) = F[1];
      tmp(2, 2) = F[2];

      tmp(3, 0) = -(s.scalarProduct(eye));
      tmp(3, 1) = -(u.scalarProduct(eye));
      tmp(3, 2) = -(F.scalarProduct(eye));

      return  Matrix(tmp);
  }

  static Matrix viewportMatrix(int x, int y, int width, int height){
    Matrix tmp = identity4;

    tmp(0, 0) = width / 2.;
    tmp(1, 1) = height / 2.;
    tmp(2, 2) = 255 / 2.;

    tmp(0, 3) = x + width / 2.;
    tmp(1, 3) = y + height / 2.;
    tmp(2, 3) = 255 / 2.;


    return tmp;
  }

  private:
  static const Matrix identity4;
};
