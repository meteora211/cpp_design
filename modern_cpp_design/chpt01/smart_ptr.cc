#include <iostream>
#include <mutex>
#include <thread>
#include "policy_class.h"

template <
typename T,
template <typename> class CheckingPolicy,
template <typename> class ThreadingModel
> class SmartPtr;

template <typename T> class SingleThreaded;

class ExtendedWidget : public Widget {
public:
  ExtendedWidget(const std::string& name="extended widget") : Widget(name) {
    std::cout << "initialize ExtendedWidget: " << name_ << std::endl;
  }
};

typedef SmartPtr<Widget, NoChecking, SingleThreaded> WidgetPtr;
typedef SmartPtr<Widget, EnforceNotNull, SingleThreaded> SafeWidgetPtr;
typedef SmartPtr<ExtendedWidget, NoChecking, SingleThreaded> ExtendedWidgetPtr;

template <
typename T,
template <typename> class CheckingPolicy,
template <class> class ThreadingModel=SingleThreaded
>
class SmartPtr : public CheckingPolicy<T>, public ThreadingModel<T> {
public:
  SmartPtr(T* pointee) : pointee_(pointee) {}

  template<typename T1, template<typename> class C1, template<typename> class T2>
    SmartPtr(const SmartPtr<T1, C1, T2>& other): pointee_(other.get_pointee()), CheckingPolicy<T>(other) {
      std::cout << "copy assign in SmartPtr." << std::endl;
    }


  T* operator->() {
    typename ThreadingModel<SmartPtr>::Lock guard(*this);
    std::cout << "SmartPtr -> operation." << std::endl;
    CheckingPolicy<T>::Check(pointee_);
    return pointee_;
  }

  T* get_pointee() {
    return pointee_;
  }
protected:
    T* pointee_;
};

template<typename T, template<typename> class CheckingPolicy>
class SimpleSmartPtr : public CheckingPolicy<T> {
public:
  SimpleSmartPtr(T* pointee) : pointee_(pointee) {}
  template<typename T1, template<typename> class CP1>
    SimpleSmartPtr(const SimpleSmartPtr<T1, CP1>& other) : pointee_(other.pointee_), CheckingPolicy<T>(other) {
      std::cout << "copy ctor" << std::endl;
    }
  T* pointee_;
};

int main() {
  auto widget_ptr = WidgetPtr(new Widget());
  widget_ptr->print();
  auto extened_widget_ptr = ExtendedWidgetPtr(new ExtendedWidget("test_widget"));
  extened_widget_ptr->print();

  /* WidgetPtr new_widget_ptr(extened_widget_ptr); */
  /* SafeWidgetPtr safe_widget_ptr(extened_widget_ptr); */

  // XXX: following example code from book doesn't work with gcc7. Haven't know why.
  /* auto simple_extended_widget_ptr_nochecking = SimpleSmartPtr<ExtendedWidget, NoChecking>(new ExtendedWidget()); */
  /* auto simple_widget_ptr_nochecking = SimpleSmartPtr<Widget, NoChecking>(simple_extended_widget_ptr_nochecking); */


}
