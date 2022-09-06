#include <string>
#include "functor.h"
#include "typelist.h"

struct TestOperator {
  void operator()(int i) {
    std::cout << "TestOperator: " << i << std::endl;
  }
};

void TestFunction(int i) {
  std::cout << "TestFunction: " << i << std::endl;
}

void TestFunction() {
  std::cout << "TestFunction void input " << std::endl;
}

void TestFunction(int i, int j) {
  std::cout << "TestFunction: " << i << " and " << j << std::endl;
}

const char* TestCastFunction() {
  static const char buffer[] = "HELLO";
  return buffer;
}

int main() {
  TestOperator op;
  Functor<void, TYPELIST_1(int)> fun(op);
  fun(1);

  typedef void(*unary)(int);
  typedef void(*no_input)();
  typedef void(*binary)(int, int);
  Functor<void, TYPELIST_1(int)> fun2(static_cast<unary>(&TestFunction));
  Functor<void, NullType> fun3(static_cast<no_input>(&TestFunction));
  Functor<void, TYPELIST_2(int, int)> fun4(static_cast<binary>(&TestFunction));
  fun2(2);
  fun3();
  fun4(1, 3);

  Functor<std::string, NullType> fun5(&TestCastFunction);
  std::cout << fun5().substr(3) << std::endl;

  /* Functor<void> binded_func(BindFirst(func, 10)); */
}
