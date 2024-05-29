#include "bmp/bmp.hpp"

#include <algorithm>
#include <cstdint>
#include <fcntl.h>
#include <functional>
#include <random>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

namespace vastina {
namespace bmp {

std::random_device rd {};
std::mt19937 mt( rd() );
std::uniform_int_distribution<int> dist( 0, 1000000 );
auto rnd { std::bind( dist, mt ) };

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

void bmp::resize(u32 ln, u32 col){
  line = ln;
  column = col;
  bgrdata.resize(ln*col*3);
}

void bmp::write()
{
  int fd = -1;
  if ( !filename.ends_with( ".bmp" ) )
    filename.append( ".bmp" );
  fd = ::open( filename.data(), O_CREAT | O_WRONLY );
  {
    // file head
    u32 column_len = column * 3;
    if ( column_len & 3 )
      column_len = ( ( column_len >> 2 ) + 1 ) << 2;
    u32 file_len = 56 /*head*/ + ( line * column_len );

    char buf[5] { 'B', 'M', 0, 0, 0 };
    ::write( fd, (void*)buf, 2 ); // 0
    *( (u32*)buf ) = file_len;
    ::write( fd, (void*)buf, 4 ); // 2
    *( (u32*)buf ) = 0;
    ::write( fd, (void*)buf, 4 ); // 6
    *( (u32*)buf ) = 56;          // after 56 bit lies color data, for align, take 56
    ::write( fd, (void*)buf, 4 ); // 10
    *( (u32*)buf ) = 40;          // filehead length
    ::write( fd, (void*)buf, 4 ); // 14
    *( (i32*)buf ) = column;
    ::write( fd, (void*)buf, 4 ); // 18
    *( (i32*)buf ) = line;
    ::write( fd, (void*)buf, 4 ); // 22
    *( (u16*)buf ) = 1;
    ::write( fd, (void*)buf, 2 ); // 26
    *( (u16*)buf ) = 24;          // 8*3, rgb length
    ::write( fd, (void*)buf, 2 ); // 28
    *( (u32*)buf ) = 0;
    ::write( fd, (void*)buf, 4 ); // 30
    *( (u32*)buf ) = 0;
    ::write( fd, (void*)buf, 4 ); // 34
    *( (i32*)buf ) = 0;
    ::write( fd, (void*)buf, 4 ); // 38
    *( (i32*)buf ) = 0;
    ::write( fd, (void*)buf, 4 ); // 42
    *( (u32*)buf ) = 0;
    ::write( fd, (void*)buf, 4 ); // 46
    *( (u32*)buf ) = 0;
    ::write( fd, (void*)buf, 4 ); // 50
    *( (u16*)buf ) = 0;
    ::write( fd, (void*)buf, 2 ); // 54
  }

  u32 BRGindex { 0u };
  u32 realdatesize = bgrdata.size();
  for ( u32 i = 0; i < line && BRGindex <= realdatesize; i++ ) {
    ::write( fd, bgrdata.data() + BRGindex, column * 3 );
    BRGindex += column * 3;
  }
  ::close( fd );
  ::chmod( filename.data(), 0b0110100100 ); // 0644
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

}; // namespace bmp
}; // namespace vastina