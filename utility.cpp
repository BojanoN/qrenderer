#include "utility.hpp"


std::map<std::string, Texture*> TextureManager::texture_cache={ };
std::vector<std::string> TextureManager::texture_types = {".jpg", ".png", ".tga"};
