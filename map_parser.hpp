#pragma once
#include<fstream>
#include"matlib/matrix.hpp"

class BSPVertex{
  // TBD
};

class Map;

class TesselatedBezier {
private:

  face_t* face;

  std::vector<uint32_t>       indexes;

public:
  std::vector<vertex_t>       vertex; 
  std::vector<vertex_t> controls ;
  std::vector<int32_t>        trianglesPerRow;
  std::vector<uint32_t*>      rowIndexes;
  void tessellate(int level);


  TesselatedBezier();

  ~TesselatedBezier(){};


};




class Map{

public:
  Map(char* filename);
  ~Map();

  char* get_tex_name(int tex_id){
    return textures[tex_id].texname;
  }

private:
  std::ifstream map_file;
  dheader_t map_header;

  unsigned int numplanes;
  unsigned int numnodes;
  unsigned int numtexinfo;
  unsigned int numfaces;
  unsigned int numleaves;
  unsigned int nummeshverts;
  unsigned int nummodels;
  unsigned int numlightmaps;
  unsigned int numvisdata;
  unsigned int numleaffaces;

  plane_t*    planes;
  entities_t* entities;
  node_t*     nodes;
  texinfo_t*  textures;
  dleaf_t*    leaves;
  model_t*    models;
  face_t*     faces;
  meshvert_t* meshverts;
  lightmap_t* lightmaps;
  visdata_t*  visdata;
  leafface_t* leaffaces;

  void convertF3(float field[3]){
    float temp;
    temp = field[1];
    field[1] = field[2];
    field[2] = -temp;
  }

  void convertV3(vertex_t* t){
    float temp;
    temp = t->y;
    t->y = t->z;
    t->z = -temp;
  }


  void convertI3(int32_t field[3]){
    int32_t temp;
    temp = field[1];
    field[1] = field[2];
    field[2] = -temp;
  }

public:
  vertex_t*   vertices;
  unsigned int numvertices;

  void convert();

  std::vector<face_t*> polygons;
  std::vector<TesselatedBezier*> patches;
  std::vector<face_t*> meshes;
  std::vector<face_t*> billboards;
  int tesselation_level = 6;
};

