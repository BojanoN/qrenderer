#include <zip.h>
#include <vector>
#include <stdexcept>
#pragma once




class Zip{

public:
  Zip(const char* filename, int flags){
    zip_file = zip_open(filename, flags, &err);
    if(zip_file == NULL){
      zip_error_init_with_code(&e, err);
      throw std::runtime_error(zip_error_strerror(&e));
    }
  }

  ~Zip(){

    for(zip_file_t* entry : open_entries){
      zip_fclose(entry);
    }

    zip_close(zip_file);
  }


  void list_contents();


  zip_file_t* get_entry_by_name(std::string& name);

  zip* zip_file;
  

private:
  zip_error_t e;
  struct zip_stat st;
  int err = 0;

  std::vector<zip_file_t*> open_entries;

};
