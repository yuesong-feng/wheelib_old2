#include "str.h"
#include "log.h"
#include <string.h>

int main(int argc, char const* argv[]) {
  str_t str = STR_INITIALIZER;
  char buf[10240] = {0};
  memset(buf, 0, 10240);
  str_init(&str);
  for (int i = 0; i < 100; ++i) {
    str_append(&str, "12345678", 8);
  }
  LOG_INFO("%d %s", str.len, str.buf);
  str_dump(&str, buf);
  LOG_INFO("dump: %s", buf);
  str_destroy(&str);
  return 0;
}
