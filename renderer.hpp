#include"map_parser.hpp"
#include"camera.hpp"
#include <map>
#include <utility>
#include "utility.hpp"
#include"texture.hpp"
#include"screen.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#pragma once


class Renderer{
public:
  virtual void renderFrame() =0;

  void renderText(const char* text, int x, int y ){

    switchTo2D();
    int w,h;

    glEnable(GL_TEXTURE_2D);

    for(const char* p=text; *p; p++){

      Texture* tx = texture_cache[*p];

      w = tx->width;
      h = tx->height;
    
      glBindTexture(GL_TEXTURE_2D, tx->id);

      glBegin(GL_QUADS);
      {
        glTexCoord2f(0,0); glVertex2i(x, y);
        glTexCoord2f(1,0); glVertex2i(x + w, y);
        glTexCoord2f(1,1); glVertex2i(x + w, y - h);
        glTexCoord2f(0,1); glVertex2i(x, y - h);
      }
      glEnd();

      x+=w;
    }
    glDisable(GL_TEXTURE_2D);



  }

  void init_fontlib(){
    TTF_Init();
    atexit(TTF_Quit);

    font =  TTF_OpenFont("fonts/DejaVuSans-Bold.ttf", 20);
    cache_font_textures();
  }



  virtual void switchTo3D(){
     glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glDisable(GL_BLEND);
    //glPolygonMode(GL_FRONT, GL_FILL);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(53.13f, Screen::width/(float)Screen::height, 1.0f, 1024.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera->eye_pos[0], camera->eye_pos[1], camera->eye_pos[2],
              camera->center_pos[0], camera->center_pos[1], camera->center_pos[2],
              camera->v_up[0], camera->v_up[1], camera->v_up[2]);

    glViewport(0, 0, Screen::width, Screen::height);

  }

  virtual void switchTo2D(){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT, GL_FILL);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, Screen::width, 0, Screen::height );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  }

  virtual ~Renderer(){
    for(std::pair<int, Texture*> p : texture_cache){
      Texture *t = p.second;
      delete t;
    }
    TTF_CloseFont(font);
  }


protected:

  void cache_font_textures(){

    for(const char* p = all_chars; *p; p++){
      SDL_Surface* txt = TTF_RenderGlyph_Blended(font, *p, color);
      uint8_t bpp = txt->format->BytesPerPixel;
      int width = txt->w;
      int height = txt->h;

      Texture* texture = TextureManager::load_texture_from_memory((unsigned char*)txt->pixels, width*height ,width, height,  bpp ); 
      texture_cache[*p] = texture;
      SDL_FreeSurface(txt);
    }

  };

  Map* map;
  Camera* camera;
  const char* all_chars =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";


  TTF_Font* font;
  SDL_Color color ={0,255,0,0};
  std::map<char, Texture*> texture_cache;

};
