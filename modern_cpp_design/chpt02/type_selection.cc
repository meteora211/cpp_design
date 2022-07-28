#include <iostream>
#include <vector>

template <int v>
class Int2Type {
  enum {value = v};
};

template <bool value, typename T, typename U>
struct Select {
  typedef T Result;
};

template <typename T, typename U>
struct Select<false, T, U> {
  typedef U Result;
};

template <typename T, bool isPolymorphic>
class NiftyContainer {
  typedef typename Select<isPolymorphic, T, T*>::Result value;
public:
  // Following code is not compilable since compiler compile both branch
  // void DoSomething () {
  //   T* pSomeObj = ...;
  //   if (isPolymorphic) {
  //     T* pNewObj = pSomeObj->Clone();
  //   } else {
  //     T* pNewObj = new T(*pSomeObj);
  //   }
  // }
  void DoSomething(T* obj) {
    DoSomething(obj, Int2Type<isPolymorphic>());
  }

  void push_back(value val) {
    container_.push_back(val);
  }

  void print() {
    for (auto i : container_) {
      std::cout << i << std::endl;
    }
  }

private:
  void DoSomething(T* obj, Int2Type<true>) {
    std::cout << "true branch" << std::endl;
    std::cout << obj << std::endl;
  }
  void DoSomething(T* obj, Int2Type<false>) {
    std::cout << "false branch" << std::endl;
    std::cout << obj << std::endl;
  }

  std::vector<value> container_;
};

int main() {
  auto true_branch = NiftyContainer<int, true>();
  auto false_branch = NiftyContainer<int, false>();

  int i = 0;
  int j = 1;
  true_branch.DoSomething(&i);
  false_branch.DoSomething(&i);

  true_branch.push_back(i);
  false_branch.push_back(&i);
  true_branch.push_back(j);
  false_branch.push_back(&j);

  true_branch.print();
  false_branch.print();
}
