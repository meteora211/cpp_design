#include "functor.h"

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

int main() {
  TestOperator op;
  Functor<void, int> fun(op);
  fun(1);

  typedef void(*unary)(int);
  typedef void(*no_input)();
  Functor<void, int> fun2(static_cast<unary>(&TestFunction));
  Functor<void, NullType> fun3(static_cast<no_input>(&TestFunction));
  fun2(2);
  fun3();
}
