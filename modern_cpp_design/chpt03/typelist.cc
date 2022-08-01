#include "typelist.h"

int main() {
  std::cout << TL::Length<TYPELIST_3(int, int32_t, int64_t)>::value << std::endl;
}
