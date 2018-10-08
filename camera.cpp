#include"camera.hpp"
#include"matlib/util.hpp"
#define degreesToRadians(angleDegrees) (angleDegrees * PI / 180.0)



void Camera::forward(float len){
  Matrix cnt = center_pos.toRowMatrix(false);
  Matrix eye_mat = eye_pos.toRowMatrix(false);
  Vector h = (center_pos -= eye_pos).copyPart(3).normalize();

  Matrix trans = MatrixUtil::transMatrix(len*h[0], len*h[1], len*h[2]);

  cnt = cnt * trans;
  eye_mat = eye_mat * trans;

  this->center_pos[0] = cnt(0,0);
  this->center_pos[1] = cnt(0,1);
  this->center_pos[2] = cnt(0,2);

  this->eye_pos[0] = eye_mat(0,0);
  this->eye_pos[1] = eye_mat(0,1);
  this->eye_pos[2] = eye_mat(0,2);
}

void Camera::backward(float len){
  Matrix cnt = center_pos.toRowMatrix(false);
  Matrix eye_mat = eye_pos.toRowMatrix(false);
  Vector h = (center_pos -= eye_pos).copyPart(3).normalize();

  Matrix trans = MatrixUtil::transMatrix(-len*h[0], -len*h[1], -len*h[2]);

  cnt = cnt * trans;
  eye_mat = eye_mat * trans;

  this->center_pos[0] = cnt(0,0);
  this->center_pos[1] = cnt(0,1);
  this->center_pos[2] = cnt(0,2);

  this->eye_pos[0] = eye_mat(0,0);
  this->eye_pos[1] = eye_mat(0,1);
  this->eye_pos[2] = eye_mat(0,2);
}

void Camera::handle_mouse(int xrel, int yrel){
  Matrix result;

  

  if(xrel != 0 ){
    result = center_pos.toRowMatrix(false);
    double yrot_angle = atan(xrel*0.01);

      Matrix rot_mat = MatrixUtil::yRotMatrix(yrot_angle);
      Matrix inv_translate = MatrixUtil::transMatrix(-this->eye_pos[0], -this->eye_pos[1], -this->eye_pos[2]);
      Matrix trans = MatrixUtil::transMatrix(this->eye_pos[0], this->eye_pos[1], this->eye_pos[2]);

      result = result * (inv_translate*rot_mat*trans);
      this->center_pos[0] = result(0,0);
      this->center_pos[1] = result(0,1);
      this->center_pos[2] = result(0,2);
  }

  if(yrel != 0){
    result = center_pos.toRowMatrix(false);
    double xrot_angle = yrel*0.01;
    double tmp = (atan(xrot_angle)  * 180 / PI ) + total_pitch;
    Vector h = (center_pos -= eye_pos).copyPart(3);
    Vector u = h.nVectorProduct(v_up.copyPart(3)).normalize();
  

     if(tmp>-88.0f && tmp<88.0f){
      total_pitch = tmp;
      printf("%lf\n", total_pitch);
      Matrix rot_mat = MatrixUtil::axisAngleRotMatrix(u, xrot_angle);

      result = result * rot_mat;
      this->center_pos[0] = result(0,0);
      this->center_pos[1] = result(0,1);
      this->center_pos[2] = result(0,2);
    
       }
  }
}

void Camera::strafe(float len){
  Matrix cnt = center_pos.toRowMatrix(false);
  Matrix eye_mat = eye_pos.toRowMatrix(false);
  Vector h = (center_pos -= eye_pos).copyPart(3).normalize();
  Vector u = (h.nVectorProduct(v_up.copyPart(3))).normalize();

  Matrix trans = MatrixUtil::transMatrix(len*u[0], len*u[1], len*u[2]);

  cnt = cnt * trans;
  eye_mat = eye_mat * trans;

  this->center_pos[0] = cnt(0,0);
  this->center_pos[1] = cnt(0,1);
  this->center_pos[2] = cnt(0,2);

  this->eye_pos[0] = eye_mat(0,0);
  this->eye_pos[1] = eye_mat(0,1);
  this->eye_pos[2] = eye_mat(0,2);
}
