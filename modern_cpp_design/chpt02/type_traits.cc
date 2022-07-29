#include <iostream>

class NullType {};

template <typename T>
class TypeTraits {
public:
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
};

int main() {
  std::cout << TypeTraits<int*>::is_pointer << std::endl;
}
