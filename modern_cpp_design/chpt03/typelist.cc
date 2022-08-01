#include "typelist.h"

typedef TYPELIST_4(
    unsigned char, unsigned short int,
    unsigned int, unsigned long int)
  UnsignedInts;
typedef TYPELIST_4(signed char, short int,
                   int, long int) SignedInts;
typedef TYPELIST_3(float, double, long double)
  Floats;


int main() {
  std::cout << TL::Length<TYPELIST_3(int, int32_t, int64_t)>::value << std::endl;
  std::cout << TL::Length<UnsignedInts>::value << std::endl;
  std::cout << TL::Length<Floats>::value << std::endl;

  typename TL::IndexAt<UnsignedInts, 2>::result i;
}
