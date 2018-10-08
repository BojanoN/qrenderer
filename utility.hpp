#include "texture.hpp"
#include <iostream>
#include "zip_archive.hpp"
#include <map>

#pragma once

class TextureManager{

public:

  static  std::map<std::string, Texture*>  texture_cache;
  static  std::vector<std::string> texture_types;

  // TODO: zamotat uvjet za loadanje iz zipa il diska u zasbenu klasu tipa Source da izbjegnemo derpy rješenja
  static Texture* get_texture(std::string tex_name, bool from_archive, Zip* archive){


    std::map<std::string, Texture* >::iterator i = texture_cache.find(tex_name);

    if ( i != texture_cache.end()){
        return i->second;
      }else if (from_archive){
        return TextureManager::load_texture_from_archive(archive, tex_name);
      }else{
        return TextureManager::load_texture_from_disk(tex_name);
      }
    
  };


  static Texture* load_texture_from_archive(Zip* archive, std::string tex_name){

    zip_file_t* tex_data=nullptr;
    std::string tmp;
    // Zip entry stats
    for(int i=0; i<3; i++){
      try{
        tmp = tex_name+texture_types[i];
         tex_data = archive->get_entry_by_name(tmp);
         break;
      }catch (std::runtime_error){
        continue;
      }
    }

    if(!tex_data)
      return nullptr;

    struct zip_stat stat;
    zip_stat(archive->zip_file, tmp.c_str(), 0, &stat);

    std::cout << "Loading texture: "<<tex_name<<"\n";

    int w, h, channels;

    zip_uint64_t size = stat.size;
    unsigned char* buff = new unsigned char[size];
    zip_fread(tex_data, buff, size);
    unsigned char* img_buff = SOIL_load_image_from_memory(buff, size, &w, &h, &channels, 0);

    GLuint tex_id;

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img_buff);
    
    

    delete[] buff;
    delete[] img_buff;

    Texture* ret = new Texture(tex_id, 1, w, h);

    texture_cache[tex_name] = ret;

    return ret;
  }

  static Texture* load_texture_from_disk(std::string path){

    return nullptr;

  }

  static Texture* load_texture_from_memory(unsigned char* buffer, int buff_size, int w, int h, int bpp){
    
 

    GLuint tex_id;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, buffer);
    

    return new Texture(tex_id, bpp, w, h );
  }

};

