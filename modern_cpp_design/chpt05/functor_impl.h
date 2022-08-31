#pragma once
class NullType {};

template <typename R, class P>
class FunctorImpl {
public:
  FunctorImpl() {}
  virtual R operator()(P param) = 0;
  /* virtual FunctorImpl* Clone() const = 0; */
  virtual ~FunctorImpl() {}
};

template <typename R>
class FunctorImpl<R, NullType> {
public:
  FunctorImpl() {}
  virtual R operator()() = 0;
  /* virtual FunctorImpl* Clone() const = 0; */
  virtual ~FunctorImpl() {}
};

