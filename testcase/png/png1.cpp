#include "png/png.hpp"
#include <algorithm>
#include <cstdlib>

int main(){
  {
    using namespace vastina::png;
    ::system("mkdir -p test");
    ::system("rm -f test/black.png");
    ::system("rm -f test/blue.png");
    {
      auto p { png("test/black.png", 256, 256) };
      std::fill(p.data.begin(), p.data.end(), (unsigned char)0);
      p.write();
    }
    {
      auto p { png("test/blue.png", 256, 256) };
      unsigned index = 0;
      for(unsigned y = 0; y < p.height; y++){
        p.data[index++] = p.config.filter_method;
        for(unsigned x = 0; x < p.width; x++){
          p.data[index++] = 0;
          p.data[index++] = 0;
          p.data[index++] = 0xff;
        }
      }
      p.write();
    }
  }
}