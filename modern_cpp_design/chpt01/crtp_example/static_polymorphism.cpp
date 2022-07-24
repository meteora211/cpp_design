#include <iostream>

template<typename DType, typename Derived>
struct BinaryOperator {
DType operator()(DType x, DType y) {
  static_cast<Derived*>(this)->implementation(x, y);
}
};

template<typename DType>
struct Add : public BinaryOperator<DType, Add<DType>> {
DType implementation(DType x, DType y) {
  return x + y;
}
};

template<typename DType>
struct Subtract : public BinaryOperator<DType, Subtract<DType>> {
DType implementation(DType x, DType y) {
  return x - y;
}
};

template<typename OP, typename DType>
DType execute(OP op, DType x, DType y) {
  return op(x, y);
}

int main() {
  using DType = double;

  DType x = 4;
  DType y = 5;

  std::cout << execute(Add<DType>{}, x, y) << std::endl;
  std::cout << execute(Subtract<DType>{}, x, y) << std::endl;
}
