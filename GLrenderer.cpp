#include"renderer.hpp"
#include<GL/gl.h>
#include<GL/glu.h>

#include "utility.hpp"
#include "zip_archive.hpp"



class GLRenderer: public Renderer{

private:
  void renderFace(face_t* face){
    int32_t first_vertex = face->vertex ;

    Texture* tex = TextureManager::get_texture(map->get_tex_name(face->texture), true, z);
    if(!tex){
      return;
    }
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D ,tex->id);

    glBegin(GL_POLYGON);
    
    for(int32_t i=0; i<face->n_vertexes; i++){
      vertex_t* tmp = &(map->vertices[first_vertex+i]);
      glTexCoord2f(tmp->texcoord[0], tmp->texcoord[1]); 
      glVertex3f(tmp->x, tmp->y,tmp->z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
  
  }

  void renderMesh(face_t* face){
    glBegin(GL_TRIANGLES);
    int32_t first_meshvert = face->meshvert + face->vertex;
    
    for(int32_t i=0; i<face->n_meshverts; i++){
      vertex_t* tmp = &(map->vertices[first_meshvert+i]);
      glVertex3f(tmp->x, tmp->y, tmp->z);
    }
    glEnd();
    }

  void renderPatch(TesselatedBezier* bez){
    glBegin(GL_TRIANGLES);
      
    for(unsigned int i=0; i<bez->vertex.size(); i++){
      vertex_t* tmp = &(bez->vertex[i]);
      glVertex3f(tmp->x, tmp->y, tmp->z);
    }
    glEnd();
    
  }

  
public:
  Zip* z;
  GLRenderer(Map* m, Camera* c){
    this->map = m;
    this->camera = c;
    z = new Zip("textures.pk3", 0);

    init_fontlib();

  }
  virtual ~GLRenderer(){};
  void renderFrame(){
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.5f, 0.5f);
    
    switchTo3D();
     
    glColor3f(0.0f, 0.5f, 0.5f);
 


    for(unsigned int i=0; i<map->polygons.size(); i++){
      renderFace(map->polygons[i]);
    }

    for(unsigned int i=0; i<map->meshes.size(); i++){
      //renderMesh(map->meshes[i]);
    }
    glColor3f(1.0f, 0.5f, 0.5f);

    for(unsigned int i=0; i<map->patches.size(); i++){
      renderPatch(map->patches[i]);
    }

   

    glFlush();
  }

};

