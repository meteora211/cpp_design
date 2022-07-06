#include <iostream>

class Widget {
public:
  Widget () {
    std::cout << "initialize Widget." << std::endl;
  }
};

class Gadget {
public:
  Gadget () {
    std::cout << "initialize Gadget." << std::endl;
  }
};

template<typename T>
class OpCreator {
public:
  static T* Create() {
    std::cout << "Create." << std::endl;
    return new T;
  }
};

template<class CreatePolicy>
class WidgetManager : public CreatePolicy {
public:
  WidgetManager() {
    std::cout << "initialize WidgetManager." << std::endl;
  }

  void DoSomething() {
    // Cannot initialize another type with CreatePolicy
    // Gadget* pw = CreatePolicy<Gadget>().Create();
    std::cout << "DoSomething." << std::endl;
  }
};

typedef WidgetManager<OpCreator<Widget>> MyWidgetMr;

template<template<class> class CreatePolicy>
class TemplatedWidgetManager : public CreatePolicy<Widget> {
public:
  TemplatedWidgetManager() {
    std::cout << "initialize TemplatedWidgetManager." << std::endl;
  }

  Gadget* DoSomething() {
    Gadget* pw = CreatePolicy<Gadget>().Create();
    std::cout << "DoSomething." << std::endl;
    return pw;
  }
};

int main() {
  std::cout << "==init my_widget_mr.==" << std::endl;
  MyWidgetMr my_widget_mr;
  std::cout << "==create my_widget.==" << std::endl;
  auto my_widget = my_widget_mr.Create();

  std::cout << "==init my_template_widget_mr.==" << std::endl;
  auto my_templated_widget_mr = TemplatedWidgetManager<OpCreator>();
  std::cout << "==create my_template_widget.==" << std::endl;
  auto my_templated_widget = my_templated_widget_mr.Create();
  std::cout << "==create my_template_gadget.==" << std::endl;
  auto my_templated_gadget = my_templated_widget_mr.DoSomething();
}
