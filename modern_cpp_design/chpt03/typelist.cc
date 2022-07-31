#include "typelist.h"

int main() {

  TYPELIST_3(int, int32_t, int64_t) typelist_3;
  std::cout << TL::Length<typelist_3>::value << std::endl;
}
