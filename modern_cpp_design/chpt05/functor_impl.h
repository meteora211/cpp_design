#pragma once
class NullType {};

template <typename R, class P>
class FunctorImpl {
public:
  FunctorImpl() {}
  virtual R operator()(P param) {
    std::cout << "operator <R,P> called" << std::endl;
    return static_cast<R>(param);
  }
  /* virtual FunctorImpl* Clone() const = 0; */
  virtual ~FunctorImpl() {}
};

template <typename R>
class FunctorImpl<R, NullType> {
public:
  FunctorImpl() {}
  virtual R operator()() {
    std::cout << "operator <R,NullType> called" << std::endl;
    return 0;
  }
  /* virtual FunctorImpl* Clone() const = 0; */
  virtual ~FunctorImpl() {}
};

