#include "map_parser.hpp"
#include "camera.hpp"
#include "GLrenderer.cpp"
#include "soft_renderer.cpp"
#include "utility.hpp"
#include <SDL2/SDL_opengl.h>
#include<unistd.h>
#include "zip_archive.hpp"


/*
SDL_Window* SDLGlinit(){

  SDL_Init( SDL_INIT_EVERYTHING );

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  
  SDL_Window* ret = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,Screen::width, Screen::height, SDL_WINDOW_OPENGL |   SDL_WINDOW_SHOWN);

  if(ret == 0){
    throw std::runtime_error(SDL_GetError());
  }
  return ret;
}


void GLinit(){
  


}*/

int main(int argc, char** argv){
  
  
  bool active = true;
  SDL_Window* screen = nullptr;
  SDL_GLContext context;
  SDL_Event e;
  Map* map;
  Camera camera(50,50,50,-10,-10,-10,0,1,0, 53);
  Renderer* gl;


  /*try{
    screen = SDLinit();
    context = SDL_GL_CreateContext(screen);
    GLinit();
    SDL_GL_SetSwapInterval(0);
    SDL_SetRelativeMouseMode(SDL_TRUE);
  }catch (std::exception& e){
    std::cout<<"An exception occured during initialization: "<<e.what()<<"\n";
    exit(2);
  }
  SDL_GL_MakeCurrent(screen, context);*/
  atexit(SDL_Quit);


  map = new Map("data/mpq3ctf1.bsp");

  //gl = new GLRenderer(map, &camera);
  gl = new SoftRenderer(map, &camera);

  screen = gl->getScreen();

  unsigned int ref_time =  0;
  unsigned int cur_time;
  int no_frames = 0;
  int fps = 0;
  std::cout<<sizeof(float)<<"\n";

  while(active){
    while( SDL_PollEvent( &e ) != 0 ) { //User requests quit
      if( e.type == SDL_QUIT ){
        active = false;
      } else if( e.type == SDL_KEYDOWN ) { //Select surfaces based on key press
        switch( e.key.keysym.sym ) {
        case SDLK_UP:
          camera.forward(2);
          break;
        case SDLK_DOWN:
          camera.backward(2);
          break;
        case SDLK_LEFT:
          camera.strafe(-2);
          break;
        case SDLK_RIGHT:
          camera.strafe(2);
          break;
        case SDLK_w:
          camera.handle_mouse(0, 5);
        default:
          break;
        }
      }else if(e.type == SDL_MOUSEMOTION){
        SDL_MouseMotionEvent* tmp = (SDL_MouseMotionEvent *) &e;
        camera.handle_mouse(tmp->xrel, tmp->yrel);
      }
    }
    gl->renderFrame();
    no_frames++;
    cur_time = SDL_GetTicks();
    if(cur_time -ref_time >= 1000){
      fps =no_frames;
      no_frames = 0;
      ref_time = cur_time;
    }
    //gl->renderText(std::to_string(fps).c_str(), 970, 750);
   

    SDL_GL_SwapWindow(screen );
   }

  SDL_DestroyWindow(screen);
  delete map;
  delete gl;

  return 0;
}
