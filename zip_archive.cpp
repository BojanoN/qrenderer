#include "zip_archive.hpp"




void Zip::list_contents(){
  int n = zip_get_num_entries(zip_file, 0);
  for(int i=0; i<n; i++){
    if(zip_stat_index(zip_file, i, 0, &st) == 0){

      printf("File: %s\n", st.name);

    }
  }
}


zip_file_t* Zip::get_entry_by_name(std::string& name){

  zip_file_t* ret;

  ret = zip_fopen(this->zip_file, name.c_str(), 0);
  if(ret == nullptr){
    throw std::runtime_error(zip_strerror(this->zip_file));
  }

  this->open_entries.push_back(ret);

  return ret;
}
