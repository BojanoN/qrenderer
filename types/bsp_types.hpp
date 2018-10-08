#pragma once

#include<cstdint>

typedef struct
{
  uint32_t  offset;
  uint32_t  size;
} dentry_t;

typedef struct                 // The BSP file header
{
  char str[4];
  int32_t  version;               // Model version, must be 0x17 (23).
  dentry_t entries[17];

} dheader_t;

enum HeaderEntries{
                   ENTITIES,
                   TEXTURES,
                   PLANES,
                   NODES,
                   LEAVES,
                   LEAFFACES,
                   MODELS=7,
                   VERTICES=10,
                   MESHVERTS,
                   FACES=13,
                   LIGHTMAPS,
                   VISDATA=16
};

enum FaceTypes{
               POLYGON=1,
               PATCH,
               MESH,
               BILLBOARD
};

typedef float scalar_t;        // Scalar value,

typedef struct{
  char* data;
} entities_t;

typedef struct                 // Vector or Position
{ scalar_t x;                  // horizontal
  scalar_t y;                  // horizontal
  scalar_t z;                  // vertical
} vec3_t;

typedef struct                 // Vector or Position
{ int16_t x;                  // horizontal
  int16_t y;                  // horizontal
  int16_t z;                  // vertical
} vec3s_t;


typedef struct                 // Bounding Box, Float values
{ vec3_t   min;                // minimum values of X,Y,Z
  vec3_t   max;                // maximum values of X,Y,Z
} boundbox_t;

typedef struct                 // Bounding Box, Short values
{
  vec3s_t min;                 // minimum values of X,Y,Z
  vec3s_t   max;                 // maximum values of X,Y,Z
} bboxshort_t;

typedef struct
{ boundbox_t bound;            // The bounding box of the Model
  uint32_t face_id;                // index of Faces
  uint32_t face_num;               // number of Faces
  uint32_t brush;
  uint32_t num_brushes;
} model_t;

class vertex_t
{
public:
  float x;                    // X,Y,Z coordinates of the vertex
  float y;                    // usually some integer value
  float z; // but coded in floating point
  float texcoord[2];
  float lmcoord[2];
  float normal[3];
  uint8_t color[4];

  vertex_t operator+(const vertex_t &v) const {
    vertex_t res;

    res.x = v.x+ x;
    res.y = v.y+ y;
    res.z = v.z+ z;

    return res;
  }

  vertex_t operator*(const double &v) const {
    vertex_t res;

    res.x =  v* x;
    res.y = v* y;
    res.z = v* z;

    return res;
  }


}; 

typedef struct
{ uint16_t vertex0;             // index of the start vertex
                               //  must be in [0,numvertices[
  uint16_t vertex1;             // index of the end vertex
                               //  must be in [0,numvertices[
} edge_t;

typedef struct
{ vec3_t   vectorS;            // S vector, horizontal in texture space)
  scalar_t distS;              // horizontal offset in texture space
  vec3_t   vectorT;            // T vector, vertical in texture space
  scalar_t distT;              // vertical offset in texture space
  uint32_t   texture_id;         // Index of Mip Texture
                               //           must be in [0,numtex[ 
  uint32_t   animated;           // 0 for ordinary textures, 1 for water
} surface_t;

typedef struct
{
  int32_t texture;
  int32_t effect;
  int32_t type;
  int32_t vertex;
  int32_t n_vertexes;
  int32_t meshvert;
  int32_t n_meshverts;
  int32_t lm_index;
  int32_t lm_start[2];
  int32_t lm_size[2];
  float lm_origin[3];
  float lm_vecs[2][3];
  float normal[3];
  int32_t size[2];
}face_t;

typedef struct{
  int32_t face;
} leafface_t;

typedef struct                 // Mip texture list header
{
  uint32_t numtex;                 // Number of textures in Mip Texture list
  uint32_t offset;         // Offset to each of the individual texture
} mipheader_t;                 //  from the beginning of mipheader_t

typedef struct                 // Mip Texture
{ char   name[16];             // Name of the texture.
  uint32_t width;                // width of picture, must be a multiple of 8
  uint32_t height;               // height of picture, must be a multiple of 8
  uint32_t offset1;              // offset to u_char Pix[width   * height]
  uint32_t offset2;              // offset to u_char Pix[width/2 * height/2]
  uint32_t offset4;              // offset to u_char Pix[width/4 * height/4]
  uint32_t offset8;              // offset to u_char Pix[width/8 * height/8]
} miptex_t;

typedef struct
{ uint32_t    plane_id;            // The plane that splits the node
                               //           must be in [0,numplanes[
  uint16_t front;               // If bit15==0, index of Front child node
                               // If bit15==1, ~front = index of child leaf
  uint16_t back;                // If bit15==0, id of Back child node
                               // If bit15==1, ~back =  id of child leaf
  bboxshort_t box;             // Bounding box of node and all childs
} node_t;

typedef struct
{ uint32_t type;                   // Special type of leaf
  uint32_t vislist;                // Beginning of visibility lists
                               //     must be -1 or in [0,numvislist[
  bboxshort_t bound;           // Bounding box of the leaf
  uint16_t lface_id;            // First item of the list of faces
                               //     must be in [0,numlfaces[
  uint16_t lface_num;           // Number of faces in the leaf
  uint8_t sndwater;             // level of the four ambient sounds:
  uint8_t sndsky;               //   0    is no sound
  uint8_t sndslime;             //   0xFF is maximum volume
  uint8_t sndlava;              //
} dleaf_t;

typedef struct
{ vec3_t normal;               // Vector orthogonal to plane (Nx,Ny,Nz)
                               // with Nx2+Ny2+Nz2 = 1
  scalar_t dist;               // Offset to plane, auint32_t the normal vector.
                               // Distance from (0,0,0) to the plane
} plane_t;


typedef struct{
  char texname[64];
  int32_t         flags;                  // miptex flags + overrides
	int32_t         texdata;                // Pointer to texture name, size, etc.
} texinfo_t;

typedef struct {
  int32_t num_vecs;
  int32_t size_vecs;
  unsigned char *vecs; // [num_vecs*size_vecs]
} visdata_t;


typedef struct {
  unsigned char map[128][128][3];
} lightmap_t;

typedef struct{
  uint32_t offset;
} meshvert_t;
