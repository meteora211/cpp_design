#pragma once

#include "typelist.h"

using NullType = TL::NullType;

template <typename R, class TList>
class FunctorImpl;

template <typename R>
class FunctorImpl<R, NullType> {
public:
  FunctorImpl() {}
  virtual R operator()() = 0;
  /* virtual FunctorImpl* Clone() const = 0; */
  virtual ~FunctorImpl() {}
};

template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)> {
public:
  FunctorImpl() {}
  virtual R operator()(P1) = 0;
  /* virtual FunctorImpl* Clone() const = 0; */
  virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1, P2)> {
public:
  FunctorImpl() {}
  virtual R operator()(P1, P2) = 0;
  /* virtual FunctorImpl* Clone() const = 0; */
  virtual ~FunctorImpl() {}
};

// It should derived from FunctorImpl <typename Incoming::ResultType, typename Incoming::ParamList::Tail>
// instead of             FunctorImpl <typename Incoming::ResultType, typename Incoming::ParamList>
// Find the type casting in function BindFirst.
template <typename Incoming>
class BinderFirst :
  public FunctorImpl <
  typename Incoming::ResultType,
  typename Incoming::ParamList::Tail> {
public:
  typedef typename Incoming::ResultType ResultType;
  typedef typename Incoming::Param1 Bound;
  typedef typename Incoming::Param2 Param1;
  typedef typename Incoming::Param3 Param2;

  BinderFirst(Incoming func, Bound bound) :
    func_(func), bound_(bound)
  {}

  ResultType operator()() {
    return func_(bound_);
  }

  ResultType operator()(Param1 param1) {
    return func_(bound_, param1);
  }

  ResultType operator()(Param1 param1, Param2 param2) {
    return func_(bound_, param1, param2);
  }

private:
  Incoming func_;
  Bound bound_;
};
