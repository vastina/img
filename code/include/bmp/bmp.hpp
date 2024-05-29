#ifndef _VAS_BMP_H_
#define _VAS_BMP_H_

#include <cstdint>
#include <string>
#include <string_view>

namespace vastina {

using std::string;
using std::string_view;
using u32 = std::uint32_t;
using i32 = std::int32_t;
using u16 = std::uint16_t;
using u8 = unsigned char;

namespace bmp {
// for more why, see https://zhuanlan.zhihu.com/p/698234015

struct bmp
{
  string filename; // 文件名
  u32 line;        // 行数
  u32 column;      // 列数
  std::basic_string<u8> bgrdata;  // rgb reverse

  void resize(u32, u32);
  void GenRandomBMP( bool );
  void write();
  void read( const string_view& path );
};

}
}

#endif