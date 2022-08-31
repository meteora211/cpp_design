#include "functor.h"

struct TestOperator {
  void operator()(int i) {
    std::cout << "TestOperator: " << i << std::endl;
  }

};

int main() {
  Functor<int, int> myFunctor1;
  Functor<int, NullType> myFunctor2;

  myFunctor1(1);
  myFunctor2();

  TestOperator op;
  Functor<void, int> fun(op);
  fun(1);
}
