#include "bmp/bmp.hpp"

#include <algorithm>
#include <cstdint>
#include <fcntl.h>
#include <fstream>
#include <functional>
#include <random>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

namespace vastina {
namespace bmp {

static std::random_device rd {};
static std::mt19937 mt( rd() );
static std::uniform_int_distribution<int> dist( 0, 1000000 );
static auto rnd { std::bind( dist, mt ) };

static inline std::string_view GenRandomStr()
{
  constexpr static std::string_view const nicestr {
    "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()-_=+{}[]:;\"'\\?/,.<>" };
  constexpr u32 nicestrlen = nicestr.size();
  static std::array<char, BUFSIZ / 64> buf;
  for ( auto& ch : buf )
    ch = nicestr[rnd() % nicestrlen];

  int start = rnd() % ( buf.size() - 1 );
  unsigned long len = std::max( rnd() % ( buf.size() - start ), 1UL );
  return { buf.begin() + start, len };
}

void bmp::resize( u32 ln, u32 col )
{
  line = ln;
  column = col;
  bgrdata.resize( ln * col * 3 );
}

void bmp::write()
{
  if ( !filename.ends_with( ".bmp" ) )
    filename.append( ".bmp" );

  char buf[57] { 'B', 'M' };
  {
    u32 column_len = column * 3;
    if ( column_len & 3 )
      column_len = ( ( column_len >> 2 ) + 1 ) << 2;
    u32 file_len = 56 /*head*/ + ( line * column_len );
    // file head
    *( (u32*)( buf + 2 ) ) = file_len;
    *( (u32*)( buf + 6 ) ) = 0;
    *( (u32*)( buf + 10 ) ) = 56; // after 56 bit lies color data, for align, take 56
    *( (u32*)( buf + 14 ) ) = 40; // filehead length
    *( (i32*)( buf + 18 ) ) = column;
    *( (i32*)( buf + 22 ) ) = line;
    *( (u16*)( buf + 26 ) ) = 1;
    *( (u16*)( buf + 28 ) ) = 24; // 8*3, rgb length
    *( (u64*)( buf + 30 ) ) = 0;
    *( (u64*)( buf + 38 ) ) = 0;
    *( (u64*)( buf + 46 ) ) = 0;
    *( (u16*)( buf + 54 ) ) = 0;
  }

// if not unix, just use stl...
#ifdef __unix__
  int fd = -1;
  fd = ::open( filename.data(), O_CREAT | O_WRONLY );
  ::write( fd, (void*)buf, 56 );
#else
  std::fstream fs;
  fs.open( filename, std::ios::in | std::ios::out | std::ios::app );
  fs.write( buf, 56 );
#endif
  u32 BRGindex { 0u };
  u32 realdatasize = bgrdata.size();
  for ( u32 i = 0; i < line && BRGindex <= realdatasize; i++ ) {
#ifdef __unix__
    ::write( fd, bgrdata.data() + BRGindex, column * 3 );
#else
    fs.write( (const char*)( bgrdata.data() + BRGindex ), column * 3 );
#endif
    BRGindex += column * 3;
  }

#ifdef __unix__
  ::close( fd );
  ::chmod( filename.data(), 0b0110100100 ); // 0644
#else
  fs.close();
#endif
}

void bmp::GenRandomBMP( bool randomname )
{
  if ( randomname )
    filename = GenRandomStr();
  line = rnd() % 256;
  column = rnd() % 256;
  bgrdata.resize( line * column * 3 );
  for ( u32 i = 0; i < line; i++ ) {
    u32 offset = i * column * 3;
    for ( u32 j = 0; j < 3 * column; j++ ) {
      bgrdata[offset + j] = rnd() % UINT8_MAX;
    }
  }
  write();
}

void bmp::setIndex(u32 index, u8 val){
  bgrdata[index] = val;
}

}; // namespace bmp
}; // namespace vastina