#include "policy_class.h"

// host classes
template<class CreatePolicy>
class WidgetManager : public CreatePolicy {
public:
  WidgetManager() {
    std::cout << "initialize WidgetManager." << std::endl;
  }

  void DoSomething() {
    // Limitation:
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

  void DoSomething() {
    // XXX: with protected dtor, following code got an error.
    /* Gadget* pw = CreatePolicy<Gadget>().Create(); */
    std::cout << "DoSomething." << std::endl;
  }

  void SwitchProtoType(Widget* pNewPrototype) {
    std::cout << "SwitchProtoType" << std::endl;
    CreatePolicy<Widget>& myPolicy = *this;
    delete myPolicy.GetProtoType();
    myPolicy.SetProtoType(pNewPrototype);
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
  my_templated_widget_mr.DoSomething();

  std::cout << "==another policy.==" << std::endl;
  auto my_templated_widget_mr_proto = TemplatedWidgetManager<PrototypeCreator>();
  auto* new_widget = new Widget();
  my_templated_widget_mr_proto.SwitchProtoType(new_widget);

  // OpCreator policy has no GetProtoType/SetProtoType interface
  // and it is still compilable with SwitchProtoType member function.
  auto my_templated_widget_mr_op = TemplatedWidgetManager<OpCreator>();
  // But call SwitchProtoType with OpCreator Policy will cause an error.
  // my_templated_widget_mr_op.SwitchProtoType(new_widget);
}
