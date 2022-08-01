#include <iostream>

class NullType {};

template <typename T>
class TypeTraits {
public:
  // PointerTraits
  template <typename U>
  struct PointerTraits {
    enum { value = false };
    typedef NullType PointeeType;
  };
  template <typename U>
  struct PointerTraits<U*> {
    enum { value = true };
    typedef U PointeeType;
  };
  enum {is_pointer = PointerTraits<T>::value};
  /* static const bool is_pointer = PointerTraits<T>::value; */
  typedef typename PointerTraits<T>::PointeeType PointeeType;

  // ReferenceTraits
  template <typename U>
  struct ReferenceTraits {
    enum { value = false };
    typedef NullType RefType;
  };
  template <typename U>
  struct ReferenceTraits<U&> {
    enum { value = true };
    typedef U RefType;
  };
  enum {is_reference = ReferenceTraits<T>::value};
  typedef typename ReferenceTraits<T>::RefType RefType;

  // ConstTraits
  template <typename U>
  struct ConstTraits {
    enum { value = false };
    typedef NullType ConstType;
  };
  template <typename U>
  struct ConstTraits<const U> {
    enum { value = true };
    typedef U ConstType;
  };
  enum {is_const = ConstTraits<T>::value};
  typedef typename ConstTraits<T>::ConstType ConstType;

  // Pointer to member
  template <typename U>
  struct PtoMTraits {
    enum { value = false };
    typedef NullType PtoMType;
  };
  template <typename U, typename V>
  struct PtoMTraits<U V::*> {
    enum { value = true };
    typedef U PtoMType;
  };
  enum {is_ptom = PtoMTraits<T>::value};
  typedef typename PtoMTraits<T>::PtoMType PtoMType;
};

struct test {int m;};

int main() {
  std::cout << TypeTraits<int*>::is_pointer << std::endl;
  std::cout << TypeTraits<int&>::is_reference << std::endl;
  std::cout << TypeTraits<const int>::is_const << std::endl;
  std::cout << TypeTraits<int test::*>::is_ptom << std::endl;
}
