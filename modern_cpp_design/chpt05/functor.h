#pragma once
#include <iostream>
#include <memory>

#include "functor_impl.h"
#include "functor_handler.h"

template <typename R, class TList>
class FunctorImpl;

template <typename R, class TList>
class Functor {
public:
  Functor() {
    impl_ = std::make_shared<FunctorImpl<R,TList>>();
  }
  Functor(const Functor&);
  Functor& operator=(const Functor&);
  template<typename Fun>
    Functor(const Fun& fun);

  typedef R ResultType;
  typedef TList ParamList;
  typedef typename TL::TypeAtNonStrict<ParamList, 0, NullType>::Result Param1;
  typedef typename TL::TypeAtNonStrict<ParamList, 1, NullType>::Result Param2;

  R operator()() {
    return (*impl_)();
  }

  R operator()(Param1 param) {
    return (*impl_)(param);
  }

  R operator()(Param1 param1, Param2 param2) {
    return (*impl_)(param1, param2);
  }

private:
  std::shared_ptr<FunctorImpl<R, TList>> impl_;
};

template<typename R, class TList>
template<typename Fun>
Functor<R, TList>::Functor(const Fun& fun)
  : impl_(std::make_shared<FunctorHandler<Functor, Fun>>(fun)) {}
