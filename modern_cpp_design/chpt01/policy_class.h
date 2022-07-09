#include <iostream>
#include <string>

class Widget {
public:
  Widget (const std::string& name="widget") : name_(name) {
    std::cout << "initialize Widget: " << name_ << std::endl;
  }
  void print() {
    std::cout << "Widget " << name_ << " printing" << std::endl;
  }
protected:
  std::string name_;
};

class Gadget {
public:
  Gadget () {
    std::cout << "initialize Gadget." << std::endl;
  }
};

// Policy classes
template<typename T>
class OpCreator {
public:
  static T* Create() {
    std::cout << "Create." << std::endl;
    return new T;
  }
protected:
  // deconstructor is created as protected to avoid following case:
  // MyWidgetMr wm;
  // OpCreator<Widget>* pCreator = &wm; // dubious but legal
  // delete wm; // compiles fine but undefined behavior
  ~OpCreator() {
    std::cout << "Deconstruct OpCreator" << std::endl;
  }
};

template<typename T>
class PrototypeCreator {
public:
  PrototypeCreator(T* pObj = nullptr) : pPrototype_(pObj) {}
  T* Create() {
    return pPrototype_? pPrototype_->Clone() : nullptr;
  }
  T* GetProtoType() {return pPrototype_;}
  void SetProtoType(T* pObj) {pPrototype_ = pObj;}

private:
  T* pPrototype_;
};


template<typename T>
class SingleThreaded {
public:
  class Lock {
    public:
      Lock(T&) {
        std::cout << "++++++++++++++++locking++++++++++++++++" << std::endl;
        mutex_.lock();
      }
      ~Lock() {
        std::cout << "----------------unlocking----------------" << std::endl;
        mutex_.unlock();
      }
    private:
      std::mutex mutex_;
  };
};

template <typename T> class NoChecking {
public:
  static void Check(T*) {}
};

template <typename T> class EnforceNotNull {
  class NullPointerException : public std::exception {};
  static void Check(T* ptr) {
    if (!ptr) throw NullPointerException();
  }
};

