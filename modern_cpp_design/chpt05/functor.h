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
  Functor(const Functor& rhs) : impl_(rhs.impl_) {}
  Functor& operator=(const Functor&);
  template<typename Fun>
    Functor(const Fun& fun);

  Functor(std::shared_ptr<FunctorImpl<R, TList>> impl) :
    impl_(impl) {}

  typedef R ResultType;
  typedef TList ParamList;
  typedef FunctorImpl<R, TList> Impl;
  typedef typename TL::TypeAtNonStrict<ParamList, 0, NullType>::Result Param1;
  typedef typename TL::TypeAtNonStrict<ParamList, 1, NullType>::Result Param2;
  typedef typename TL::TypeAtNonStrict<ParamList, 2, NullType>::Result Param3;

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
  std::shared_ptr<Impl> impl_;
};

template<typename R, class TList>
template<typename Fun>
Functor<R, TList>::Functor(const Fun& fun)
  : impl_(std::make_shared<FunctorHandler<Functor, Fun>>(fun)) {}

template <typename Incoming>
struct BinderFirstTraits {
  typedef typename Incoming::ResultType ResultType;
  typedef typename Incoming::ParamList ParamList;
  typedef Functor<ResultType, typename ParamList::Tail> Outgoing;
};

// Incoming Type: Functor<void, TYPELIST_2(int, int)>
// Outgoing Type: Functor<void, TYPELIST_1(int)>
template<typename Incoming>
typename BinderFirstTraits<Incoming>::Outgoing
BindFirst(Incoming func, typename Incoming::Param1 bound) {
  typedef typename BinderFirstTraits<Incoming>::Outgoing Outgoing;

  // Incoming:  Functor<void, TYPELIST_2(int, int)>
  //                    |
  //                   Impl
  //                    v
  // FunctorImpl<void, TYPELIST_1(int)>
  //                    |
  //                 derived
  //                    v
  // BinderFirst<Functor<void, TYPELIST_2(int, int)>>
  //                    |
  //                make_shared
  //                    v
  // shared_ptr<FunctorImpl<void, TypeList_1(int)>>
  //                    |
  //                 construct
  //                    v
  // Outgoing Functor<void, TYPELIST_1(int)>

  /* return Outgoing(std::make_shared<typename Outgoing::Impl>(BinderFirst<Incoming>(func, bound))); */
  return Outgoing(std::shared_ptr<typename Outgoing::Impl>(new BinderFirst<Incoming>(func, bound)));
}
