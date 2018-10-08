#include"map_parser.hpp"

Map::~Map(){
  std::cout<<"benis\n";
  delete[] nodes;

  std::cout<<"beni\n";
  delete[] planes;
  std::cout<<"ben\n";
   delete[] entities->data;
  std::cout<<"be\n";
  delete entities;
  std::cout<<"b\n";
  delete[] textures;
  std::cout<<"enis\n";
  delete[] leaves;

  std::cout<<"nis\n";
  delete[] models;
  std::cout<<"is\n";
  delete[] vertices;
  std::cout<<"s\n";
  delete[] lightmaps;
  std::cout<<"sa\n";
  delete[] visdata;
  delete[] meshverts;
  delete[] faces;
  for(TesselatedBezier* t : patches){
    delete t;
    }
};

Map::Map(char* filename):map_file(filename){

  map_file.read(reinterpret_cast<char*>(&(this->map_header)), sizeof(dheader_t));
  //TODO: forsirat provjeru version polja, dodat entrye koji potencijalno fale
  //IDEJA: ispis ovisno o log levelu
  //STRUKTURNI DIO: stvorit sučelje Map kojeg će onda implementirat mape za Q1,Q2,Q3, etc...

  printf("%.*s\nVersion: %x\n", 4, map_header.str, map_header.version);

  numplanes    = map_header.entries[PLANES].size / sizeof(plane_t);
  numvertices  = map_header.entries[VERTICES].size / sizeof(vertex_t);
  numnodes     = map_header.entries[NODES].size / sizeof(node_t);
  numtexinfo   = map_header.entries[TEXTURES].size / sizeof(texinfo_t);
  numfaces     = map_header.entries[FACES].size / sizeof(face_t);
  numleaves    = map_header.entries[LEAVES].size / sizeof(dleaf_t);
  numleaffaces = map_header.entries[LEAFFACES].size / sizeof(leafface_t);
  nummodels    = map_header.entries[MODELS].size / sizeof(model_t);
  nummeshverts = map_header.entries[MESHVERTS].size / sizeof(meshvert_t);
  numlightmaps = map_header.entries[LIGHTMAPS].size / sizeof(lightmap_t);
  numvisdata   = map_header.entries[VISDATA].size / sizeof(visdata_t);
  
  planes         = new plane_t[numplanes+1];
  entities       = new entities_t;
  entities->data = new char[map_header.entries[ENTITIES].size+1];
  
  nodes          = new node_t[numnodes+1];
  textures       = new texinfo_t[numtexinfo+1];
  leaves         = new dleaf_t[numleaves+1];
  models         = new model_t[nummodels+1]; 
  vertices       = new vertex_t[numvertices];
  faces          = new face_t[numfaces+1];
  meshverts      = new meshvert_t[nummeshverts];
  lightmaps      = new lightmap_t[numlightmaps];
  visdata        = new visdata_t[numvisdata];
  leaffaces      = new leafface_t[numleaffaces];


  printf("NUMPLANES: %d\nNUMMODELS: %d\n", numplanes, nummodels);

  map_file.seekg(map_header.entries[PLANES].offset);
  map_file.read(reinterpret_cast<char*>(planes), map_header.entries[PLANES].size);
  
  map_file.seekg(map_header.entries[ENTITIES].offset);
  map_file.read(reinterpret_cast<char*>(entities->data), map_header.entries[ENTITIES].size);

  map_file.seekg(map_header.entries[NODES].offset);
  map_file.read(reinterpret_cast<char*>(nodes), map_header.entries[NODES].size);

  map_file.seekg(map_header.entries[TEXTURES].offset);
  map_file.read(reinterpret_cast<char*>(textures), map_header.entries[TEXTURES].size);

  map_file.seekg(map_header.entries[LEAVES].offset);
  map_file.read(reinterpret_cast<char*>(leaves), map_header.entries[LEAVES].size);

  map_file.seekg(map_header.entries[MODELS].offset);
  map_file.read(reinterpret_cast<char*>(models), map_header.entries[MODELS].size);

  map_file.seekg(map_header.entries[VERTICES].offset);
  map_file.read(reinterpret_cast<char*>(vertices), map_header.entries[VERTICES].size);

  map_file.seekg(map_header.entries[FACES].offset);
  map_file.read(reinterpret_cast<char*>(faces), map_header.entries[FACES].size);

  map_file.seekg(map_header.entries[MESHVERTS].offset);
  map_file.read(reinterpret_cast<char*>(meshverts), map_header.entries[MESHVERTS].size);

  map_file.seekg(map_header.entries[LIGHTMAPS].offset);
  map_file.read(reinterpret_cast<char*>(lightmaps), map_header.entries[LIGHTMAPS].size);

  map_file.seekg(map_header.entries[VISDATA].offset);
  map_file.read(reinterpret_cast<char*>(visdata), map_header.entries[VISDATA].size);

  map_file.seekg(map_header.entries[LEAFFACES].offset);
  map_file.read(reinterpret_cast<char*>(leaffaces), map_header.entries[LEAFFACES].size);

  map_file.close();

  convert();

  int32_t width ;
  int32_t height ;
  std::vector<TesselatedBezier*> patch_vertices;
  std::cout<<"benis\n";

  for(unsigned int i=0; i<numfaces; i++){
    switch(faces[i].type){
    case(POLYGON):
      polygons.push_back(&faces[i]);
      break;
    case(PATCH):
      //for(int i )
      width = (faces[i].size[0] - 1) / 2;
      height = (faces[i].size[1] - 1) / 2;

      patch_vertices.clear();
      patch_vertices.resize(width*height);
      for(int i=0; i<width*height; i++)
        patch_vertices[i] =  new TesselatedBezier();

      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
              patch_vertices[y *width + x]->controls[row * 3 + col] =
                 vertices[faces[i].vertex + (y * 2 * width + x * 2) + row * width + col];
            }
          }
          patch_vertices[y * width + x]->tessellate(tesselation_level);
        }
      }
      for(TesselatedBezier* p : patch_vertices)
        patches.push_back(p);
      break;
    case(MESH):
      meshes.push_back(&faces[i]);
      break;
    case(BILLBOARD):
      billboards.push_back(&faces[i]);
      break;
    }
  }
  std::cout<<"benis\n";


};

void TesselatedBezier::tessellate(int level){
    int L = level;
    
    // The number of vertices along a side is 1 + num edges
    const int L1 = L + 1;

    vertex.resize(L1 * L1);

    // Compute the vertices
    int i;

    for (i = 0; i <= L; ++i) {
        double a = (double)i / L;
        double b = 1 - a;

        vertex[i] =
            controls[0] * (b * b) + 
            controls[3] * (2 * b * a) +
            controls[6] * (a * a);
    }

    for (i = 1; i <= L; ++i) {
        double a = (double)i / L;
        double b = 1.0 - a;

        std::vector<vertex_t> temp(3);

        int j;
        for (j = 0; j < 3; ++j) {
            int k = 3 * j;
            temp[j] =
                controls[k + 0] * (b * b) +
                controls[k + 1] * (2 * b * a) +
                controls[k + 2] * (a * a);
        }

        for(j = 0; j <= L; ++j) {
            double a = (double)j / L;
            double b = 1.0 - a;

            vertex[i * L1 + j]=
                temp[0] * (b * b) +  
                temp[1] * (2 * b * a) +
                temp[2] * (a * a);
        }
    }


    // Compute the indices
    int row;
    indexes.resize(L * (L + 1) * 2);

    for (row = 0; row < L; ++row) {
        for(int col = 0; col <= L; ++col)	{
            indexes[(row * (L + 1) + col) * 2 + 1] = row       * L1 + col;
            indexes[(row * (L + 1) + col) * 2]     = (row + 1) * L1 + col;
        }
    }

    trianglesPerRow.resize(L);
    rowIndexes.resize(L);
    for (row = 0; row < L; ++row) {
        trianglesPerRow[row] = 2 * L1;
        rowIndexes[row]      = &indexes[row * 2 * L1];
        }
}

TesselatedBezier::TesselatedBezier():controls(9) {


};

void Map::convert(){

  for (int i=0; i < numvertices; i++)
    {
      convertV3((&vertices[i]));
      convertF3(vertices[i].normal);
    }

  /* for (int i=0; i < numleaves; i++)
    {
      swizzleInt3(leaves[i].maxs);
      swizzleInt3(leaves[i].mins);
      }*/

  /*for (int i=0; i < m_iNumFaces; i++)
    {
      swizzleFloat3(m_pFaces[i].normal);
      }*/


}
