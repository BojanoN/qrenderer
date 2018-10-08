#include <vector>
#include <SOIL/SOIL.h>
#include "zip_archive.hpp"
#include <GL/gl.h>

#pragma once

class Texture{
public:
 
  Texture(unsigned int i, int bpp ,int w, int h): id(i),
                                                                    width(w), height(h), bytes_per_pixel(bpp){};


  ~Texture(){

    glDeleteTextures(1, &this->id);
    
  };




  unsigned int id;

  int bytes_per_pixel;
  int width;
  int height;



};
