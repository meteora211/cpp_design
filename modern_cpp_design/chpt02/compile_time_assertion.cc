#include <iostream>
#include <assert.h>
#include <type_traits>

// SFINAE
template<typename T>
class CanToString {
public:
  typedef int64_t YesType;
  typedef int16_t NoType;

  template<typename U>
  static YesType Check(decltype(std::cout<<std::declval<U>())) {
    return 0;
  }

  template<typename U>
  static NoType Check(...) {
    return 0;
  }

  static bool constexpr kvalue  = std::is_same<YesType, decltype(Check<T>(std::cout)) >::value;
};

template<bool> class CompileTimeError{
public:
  CompileTimeError(...) {
    std::cout << "constructor" << std::endl;
  };
  static void print() {
    std::cout << "template error." << std::endl;
  }
};
template<> class CompileTimeError<false> {
public:
  static void print() {
    std::cout << "false error" << std::endl;
  }
};

class test{};

#define STATIC_CHECK(expr, msg) \
{\
  class ERROR_##msg{};                     \
  (void) sizeof((CompileTimeError<(expr) != 0> (ERROR_##msg()))); \
}

int main() {
  double d = 1.0;
  int i = 1;

  STATIC_CHECK(sizeof(i) <= sizeof(d), id);

  // compile error in following static_check
  // STATIC_CHECK(sizeof(d) <= sizeof(i), narrow_down_cast);
  // same to:
  // static_assert(sizeof(d) <= sizeof(i), "narrow down cast")

  std::cout << CanToString<int>::kvalue << std::endl;
  std::cout << CanToString<test>::kvalue << std::endl;
}
