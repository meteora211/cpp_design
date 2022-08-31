#pragma once
#include <iostream>
#include <memory>

#include "functor_impl.h"
#include "functor_handler.h"

template <typename R, class P>
class FunctorImpl;

template <typename R, class P>
class Functor {
public:
  Functor() {
    impl_ = std::make_shared<FunctorImpl<R,P>>();
  }
  Functor(const Functor&);
  Functor& operator=(const Functor&);
  template<typename Fun>
    Functor(const Fun& fun);

  typedef R ResultType;
  typedef P ParamType;

  R operator()() {
    return (*impl_)();
  }

  R operator()(P param) {
    return (*impl_)(param);
  }

private:
  std::shared_ptr<FunctorImpl<R, P>> impl_;
};

template<typename R, class P>
template<typename Fun>
Functor<R, P>::Functor(const Fun& fun)
  : impl_(std::make_shared<FunctorHandler<Functor, Fun>>(fun)) {}
