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

/* template <typename Incoming> */
/* class BindFirst : */
/*   public FunctorImpl < */
/*   typename Incoming::ResultType, */
/*   typename Incoming::ParamType> { */

/* typedef */

/* public: */
/*   BindFirst(Incoming func, Bound bound) : */
/*     func_(func), bound_(bound) */
/*   {} */

/* private: */
/*   Incoming func_; */
/*   Bound bound_; */

/* } */
