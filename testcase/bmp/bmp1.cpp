#include "bmp/bmp.hpp"

int main( int argc, char** argv )
{
  {
    using namespace vastina::bmp;
    {
      // bmp b{"1", 0, 0, {}};
      // b.write();
    }
    {
      if ( argc > 1 ) {
        bmp b {};
        b.filename = std::string_view( argv[1] );
        b.GenRandomBMP( false );
      }
    }
    {
      bmp b {};
      b.filename = "test/black.bmp";
      b.resize( 256, 256 );
      for ( unsigned i = 0; i < b.line; i++ ) {
        for ( unsigned j = 0; j < 3 * b.column; j++ ) {
          b.bgrdata[i * b.column * 3 + j] = 0;
        }
      }
      b.write();
    }
    {
      bmp b {};
      b.filename = "test/white.bmp";
      b.resize( 256, 256 );
      for ( unsigned i = 0; i < b.line; i++ ) {
        unsigned offset = i * b.column * 3;
        for ( unsigned j = 0; j < 3 * b.column; j++ ) {
          b.bgrdata[offset + j] = UINT8_MAX;
        }
      }
      b.write();
    }
    {
      bmp b {};
      b.filename = "test/hhalf.bmp";
      b.resize( 512, 512 );
      constexpr unsigned rr1 = 511 * 511 - 512;
      constexpr unsigned rr2 = 511 * 511 + 512;
      for ( unsigned i = 0; i < b.line; i++ ) {
        unsigned offset = i * b.column * 3;
        for ( unsigned j = 0; j < b.column; j++ ) {
          const auto rr { i * i + j * j };
          if ( rr >= rr1 && rr <= rr2 )
            b.bgrdata[offset + j * 3] = UINT8_MAX;
          else
            b.bgrdata[offset + j * 3] = 0;
          b.bgrdata[offset + j * 3 + 1] = 0;
          b.bgrdata[offset + j * 3 + 2] = 0;
        }
      }
      b.write();
    }
  }

  return 0;
}