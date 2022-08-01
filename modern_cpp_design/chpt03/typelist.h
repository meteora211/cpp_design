#include <iostream>
#define TYPELIST_1(T1) TL::Typelist<T1, TL::NullType>
#define TYPELIST_2(T1, T2) TL::Typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) TL::Typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) TL::Typelist<T1, TYPELIST_3(T2, T3, T4)>


namespace TL {
  class NullType{};

  template <typename T, typename U>
  struct Typelist {
    typedef T Head;
    typedef U Tail;
  };

  template <typename TList> struct Length;

  // Following is not correct partial specialize
  // template <T> struct Length<NullType> {
  // 特例化版本的参数类型必须与一个先前声明的模板中对应的类型相匹配
  template <> struct Length<NullType> {
    enum {value = 0};
  };

  template <typename T, typename U> struct Length<Typelist<T, U>> {
    enum {value = 1 + Length<U>::value};
  };
}

