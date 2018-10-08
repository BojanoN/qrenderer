#pragma once
#include"matlib/matrix.hpp"
#define PI 3.14159265


class Camera{
public:
  bool isVisible(bboxshort_t& box){return false;};

  Vector eye_pos;
  Vector center_pos;
  Vector v_up;

  Camera(double e_x, double e_y, double e_z,
         double c_x, double c_y, double c_z,
         double v_x, double v_y, double v_z,
         double f):eye_pos(e_x, e_y, e_z, 1),
                   center_pos(c_x, c_y, c_z, 1),
                   v_up(v_x, v_y, v_z, 1),
                   fov(f),
                   total_pitch(0)
  {
    Vector h = (center_pos -= eye_pos).copyPart(3);
    Vector u = h.nVectorProduct(v_up.copyPart(3));
    Vector v = u.nVectorProduct(h);

    x = u.normalize();
    y = v.normalize();
    z = h.normalize();
  };
  double fov;
  double total_pitch;

  Vector x;
  Vector y;
  Vector z;

  void forward(float len);
  void backward(float len);
  void handle_mouse(int xrel, int yrel);
  void strafe(float len);
};
