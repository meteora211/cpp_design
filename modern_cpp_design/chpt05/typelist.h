#pragma once
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

  // TypeList Length
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

  // TypeList IndexAt
  template<typename T, unsigned int index>
  struct IndexAt;

  template<typename T, typename U, unsigned int index>
  struct IndexAt<Typelist<T, U>, index> {
    typedef typename IndexAt<U, index-1>::Result Result;
  };
  template<typename T, typename U>
  struct IndexAt<Typelist<T, U>, 0> {
    typedef T Result;
  };

  // TypeList IndexOf
  template<typename TList, typename Indexed>
  struct IndexOf;

  template<typename T, typename U, typename Indexed>
  struct IndexOf<Typelist<T, U>, Indexed> {
  private:
    enum {temp = IndexOf<U, Indexed>::value};
  public:
    enum {value = temp == -1 ? -1 : 1 + temp};
  };
  template<typename T, typename U>
  struct IndexOf<Typelist<T, U>, T> {
    enum {value = 0};
  };
  template<typename Indexed>
  struct IndexOf<NullType, Indexed> {
    enum {value = -1};
  };

  // TypeList Append
  template<typename TList, typename ToAppend>
  struct Append;

  template<typename T, typename U, typename ToAppend>
  struct Append<Typelist<T, U>, ToAppend> {
    typedef Typelist<T, typename Append<U,ToAppend>::Result> Result;
  };
  template<>
  struct Append<NullType, NullType> {
    typedef NullType Result;
  };
  template<typename ToAppend>
  struct Append<NullType, ToAppend> {
    typedef Typelist<ToAppend, NullType> Result;
  };

  template<typename TList, unsigned int Indexed, typename EmptyType = NullType>
  struct TypeAtNonStrict {
    typedef EmptyType Result;
  };

  template<typename T, typename U, unsigned int Indexed, typename EmptyType>
  struct TypeAtNonStrict<Typelist<T, U>, Indexed, EmptyType>{
    typedef typename TypeAtNonStrict<U, Indexed-1, EmptyType>::Result Result;
  };

  template<typename T, typename U, typename EmptyType>
  struct TypeAtNonStrict<Typelist<T, U>, 0, EmptyType>{
    typedef T Result;
  };

}

