#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "png/png.hpp"

int main() {
  FT_Library library;
    if (FT_Init_FreeType(&library)) {
        std::cerr << "Could not initialize FreeType library" << std::endl;
        return 1;
    }
    const char* font_path = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
    FT_Face face;
    if (FT_New_Face(library, font_path, 0, &face)) {
        std::cerr << "Could not open font" << std::endl;
        FT_Done_FreeType(library);
        return 1;
    }
  FT_Set_Char_Size(face, 0, 48 * 64, 0, 0);
  if (FT_Load_Char(face, 'A', FT_LOAD_RENDER)) {
        std::cerr << "Could not load character 'A'" << std::endl;
        FT_Done_Face(face);
        FT_Done_FreeType(library);
        return 1;
  }
  FT_Bitmap* bitmap = &face->glyph->bitmap;

  {
    ::system("mkdir -p test");
    ::system("rm -f test/char.png");
    using namespace vastina::png;
    auto p { png("test/char.png", bitmap->width, bitmap->rows) };
    unsigned index = 0;
    for(unsigned y = 0; y < bitmap->rows; ++y) {
      p.data[index++] = p.config.filter_method;
      for(unsigned x = 0; x < bitmap->width; ++x) {
        p.data[index++] = bitmap->buffer[y * bitmap->width + x];
        p.data[index++] = bitmap->buffer[y * bitmap->width + x];
        p.data[index++] = bitmap->buffer[y * bitmap->width + x];
      }
    }
    p.write();
  }

  return 0;
}