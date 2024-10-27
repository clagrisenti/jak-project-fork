#include "soundcommon.h"

#include <algorithm>
#include <cstring>
#include <string>

namespace jak3 {
void jak3_overlord_init_globals_soundcommon() {}

// Only for use with 16 character sound names!
void strcpy_toupper(char* dest, const char* source) {
  // clear the dest string
  memset(dest, 0, 16);
  std::string string(source);
  std::ranges::transform(string, string.begin(), ::toupper);
  std::ranges::replace(string, '-', '_');
  string.copy(dest, 16);
}
}  // namespace jak3