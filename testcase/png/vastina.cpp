#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

#include "png/png.hpp"

int main()
{
  FT_Library library;
  if ( FT_Init_FreeType( &library ) ) {
    std::cerr << "Could not initialize FreeType library" << std::endl;
    return 1;
  }
  const char* font_path = "./test/KAISG.ttf";

  unsigned wa = 0, h = 0, w[7] = { 0 };

  FT_Face face[7];
  const char name[] { "vastina" };
  FT_Bitmap* bitmaps[7];
  for ( int i = 0; i < 7; i++ ) {
    if ( FT_New_Face( library, font_path, 0, &face[i] ) ) {
      std::cerr << "Could not open font" << std::endl;
      FT_Done_FreeType( library );
      return 1;
    }
    FT_Set_Char_Size( face[i], 0, 48 * 64, 0, 0 );
    if ( FT_Load_Char( face[i], name[i], FT_LOAD_RENDER ) ) {
      std::cerr << "Could not load character 'A'" << std::endl;
      FT_Done_Face( face[i] );
      FT_Done_FreeType( library );
      return 1;
    }
    bitmaps[i] = &face[i]->glyph->bitmap;
    wa += bitmaps[i]->width;
    if ( i > 0 )
      w[i] = w[i - 1] + bitmaps[i]->width;
    h = h > bitmaps[i]->rows ? h : bitmaps[i]->rows;
  }

  {
    ::system( "mkdir -p test" );
    ::system( "rm -f test/vastina.png" );
    using namespace vastina::png;
    auto p { png( "test/vastina.png", wa, h ) };
    for ( int i = 0; i < 7; i++ ) {
      for ( unsigned y = h - bitmaps[i]->rows, yi = 0; y < h; y++, yi++ )
        for ( unsigned x = 0; x < bitmaps[i]->width; x++ ) {
          auto val { bitmaps[i]->buffer[yi * bitmaps[i]->width + x] };
          p.setIndex( x + w[i], y, { val, val, val } );
        }
    }
    p.write();
  }

  FT_Done_FreeType( library );
  for( int i = 0; i < 7; i++ )
    FT_Done_Face( face[i] );
  return 0;
}