#include <iostream>

class ModelDialog {
public:
  static void print() {
    std::cout << "ModalDialog" << std::endl;
  }
};

class MyController {
public:
  static void print() {
    std::cout << "MyController" << std::endl;
  }
};

template<class Window, class Control>
class Widget{
public:
  void print() {
    std::cout << " print widget " << std::endl;
  }
};

template<>
class Widget<ModelDialog, MyController> {
public:
  void print() {
    ModelDialog::print();
    MyController::print();
  }
};

int main() {
  Widget<ModelDialog, MyController> w;
  w.print();
}
