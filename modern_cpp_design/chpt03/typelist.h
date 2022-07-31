#include <iostream>

namespace TL {
  class NullType{};
  struct Typelist;

  #define TYPELIST_1(T1) Typelist<T1, NullType>
  #define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2)>
  #define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3)>
  #define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4)>

  template <typename T, typename U>
  struct Typelist {
    typedef T Head;
    typedef U Tail;
  };

  template <typename TList> struct Length;
  template <typename T> struct Length<NullType> {
    enum {value = 0};
  };
  template <typename T, typename U> struct Length<Typelist<T, U>> {
    enum {value = 1 + Length<U>::value};
  };
}

