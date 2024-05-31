#include "vasdef.hpp"

namespace vastina {
namespace png {

extern "C++" void write_uint32( std::ofstream& file, uint32_t value );
extern "C++" void write_chunk( std::ofstream& file, const string_view& type, const std::vector<uint8_t>& data );

struct pngConfig{
  u8 bit_depth {8};           GSetter(bit_depth)
  u8 color_type {2};          GSetter(color_type)
  u8 compression_method {0};  GSetter(compression_method)
  u8 filter_method {0};       GSetter(filter_method)
  u8 interlace_method {0};    GSetter(interlace_method)
};

struct png {
  string filename;
  u32 width;
  u32 height;
  vector<u8> data;
  pngConfig config {};

  png(const string&path, u32 w, u32 h, pngConfig cfig = {}) :
      filename(path)
    , width(w)
    , height(h)
    , data(w*h*3+h)
    , config(cfig)
  {}
  void resize( u32, u32, u8 );
  void GenRandomPNG( bool );
  void write();
  void read( const string_view& path );
  inline void setIndex(u32 x, u32 y, u8 offset, u8 val){
    data[(y+1)+y*width+x+offset] = val;
  }

  GSetter(filename)
  GSetter(width)
  GSetter(height)
  GSetter(config)
};

}; // namespace png
}; // namespace vastina