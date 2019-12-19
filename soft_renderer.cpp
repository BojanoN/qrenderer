#include"renderer.hpp"
#include<GL/gl.h>
#include<GL/glu.h>
#include "matlib/util.hpp"

#include "utility.hpp"
#include "zip_archive.hpp"
#include <chrono> 
using namespace std::chrono; 
class SoftRenderer: public Renderer{

private:
  void renderFace(face_t* face){
    int32_t first_vertex = face->vertex;

    for(int32_t i=0; i+1<face->n_vertexes; i++){
      vertex_t* tmp = &(map->vertices[first_vertex+i]);
      vertex_t* tmp2 = &(map->vertices[first_vertex+i+1]);
      
      draw3DLine(tmp->x, tmp->y, tmp->z, tmp2->x, tmp2->y, tmp2->z);
    }
    vertex_t* tmp = &(map->vertices[first_vertex]);
    vertex_t* tmp2 = &(map->vertices[first_vertex+ face->n_vertexes-1]);

    draw3DLine(tmp->x, tmp->y, tmp->z, tmp2->x, tmp2->y, tmp2->z);
  }

  void renderMesh(face_t* face){


  }

  
public:
  Zip* z;
  SoftRenderer(Map* m, Camera* c): vec_buf(0, 0, 0, 1), norm_buf(0, 0, 0){
    this->map = m;
    this->camera = c;
    z = new Zip("textures.pk3", 0);

    init_fontlib();

    projection = MatrixUtil::perspectiveProjection(53.13f, Screen::width/(float)Screen::height, 1.0f, 1024.0f);
    view = MatrixUtil::viewMatrix(c->eye_pos3, c->center_pos3, c->v_up3);
    viewport = MatrixUtil::viewportMatrix(0, 0, Screen::width, Screen::height);

    try{
      this->screen = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Screen::width, Screen::height, SDL_WINDOW_OPENGL |   SDL_WINDOW_SHOWN);
      this->sdl_rend = SDL_CreateRenderer(this->screen, -1, SDL_RENDERER_SOFTWARE);
      SDL_SetRelativeMouseMode(SDL_TRUE);
    }catch (std::exception& e){
      std::cout<<"An exception occured during initialization: "<<e.what()<<"\n";
      exit(2);
    }


    lookAt = projection * view;
  }
  virtual ~SoftRenderer(){
    SDL_DestroyRenderer(sdl_rend);
    SDL_DestroyWindow(screen);
  };

  void renderFrame(){
    SDL_SetRenderDrawColor(sdl_rend, 0, 0, 0, 0);
    SDL_RenderClear(sdl_rend);
    SDL_SetRenderDrawColor(sdl_rend, 255, 255, 255, 255);

    std::cout<<"RENDERING FRAME\n";
    SDL_RenderDrawPoint(sdl_rend, 501, 501);
    SDL_RenderDrawPoint(sdl_rend, 500, 500);
  
    for(unsigned int i=0; i<2; i++){
      auto start = high_resolution_clock::now(); 
      renderFace(map->polygons[i]);
      auto end = high_resolution_clock::now();
      auto duration = duration_cast<milliseconds>(end - start);
      std::cout << duration.count() << "\n"; 
    }
    std::cout<<"DONE\n\n";
    SDL_RenderPresent(sdl_rend);
  }

  void setProjectionMatrix(Matrix& m){
    this->projection = m;
    this->lookAt = this->view * this->projection;
  }

  void setViewMatrix(Matrix& m){
    this->view = m;
    this->lookAt = this->view * this->projection;
  }

  private:

  Matrix viewport;
  Matrix projection;
  Matrix view;

  Matrix lookAt;

  Vector vec_buf;
  Vector norm_buf;

  SDL_Renderer* sdl_rend;

  void drawVertex3(float x, float y, float z){
    vec_buf[0] = x;
    vec_buf[1] = y;
    vec_buf[2] = z;

    
    norm_buf.normalize();
  
    vec_buf[0] = norm_buf[0];
    vec_buf[1] = norm_buf[1];
    vec_buf[2] = norm_buf[2];

    Vector transformed = (viewport * lookAt * (*vec_buf.toColumnMatrix(false))).toVector(false)->nFromHomogenous();
    std::cout<<transformed<<"\n";
    SDL_RenderDrawPoint(sdl_rend, transformed[0], transformed[1]);
  }

  void draw3DLine(float x1, float y1, float z1, float x2, float y2, float z2){
    // Bresenham's algorithm
    int xs;
    int ys;
    int zs;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int dz = abs(z2 - z1);

    float p1, p2;

    int pdx = dx << 1;
    int pdy = dy << 1;
    int pdz = dz << 1;

    xs = (x2 > x1) ? 1 : -1;
    ys = (y2 > y1) ? 1 : -1;
    zs = (z2 > z1) ? 1 : -1;


    if (dx >= dy && dx >=dz){
      p1 = (dy - dx) << 1;
      p2 = (dz - dx) << 1;

      for(int i=0; i<=dx; i++){
        drawVertex3(x1, y1, z1);


        if(p1 >= 0){
          y1 += ys;
          p1 -= pdx;
        }
        if(p2 >= 0){
          z1 += zs;
          p2 -= pdx;
        }
        p1 += pdy;
        p2 += pdz;

        x1 += xs;
      }
    }else if(dy >= dx && dy >= dz){
      p1 = (dx - dy) << 1;
      p2 = (dz - dy) << 1;

      for(int i=0; i<=dy; i++){
        drawVertex3(x1, y1, z1);

        if(p1 >= 0){
          x1 += xs;
          p1 -= pdy;
        }
        if(p2 >= 0){
          z1 += zs;
          p2 -= pdy;
        }
        p1 += pdx;
        p2 += pdz;

        y1 += ys;
      }
    }else{
      p1 = (dy - dz) << 1;
      p2 = (dx - dz) << 1;

      for(int i=0; i<=dz; i++){

        drawVertex3(x1, y1, z1);

        if(p1 >= 0){
          y1 += ys;
          p1 -= pdz;
        }
        if(p2 >= 0){
          x1 += xs;
          p2 -= pdz;
        }

        p1 += pdy;
        p2 += pdx;

        z1 += zs;
      }
    }
    glFlush();
  }
};

