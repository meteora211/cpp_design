#pragma once
template<class ParentFunctor,typename Fun>
class FunctorHandler :
  public FunctorImpl
    <
      typename ParentFunctor::ResultType,
      typename ParentFunctor::ParamType
    >
{
public:
  typedef typename ParentFunctor::ResultType ResultType;
  typedef typename ParentFunctor::ParamType ParamType;

  FunctorHandler(const Fun& fun) : fun_(fun) {}

  ResultType operator()() {
    return fun_();
  }

  ResultType operator()(ParamType param) {
    return fun_(param);
  }

private:
  Fun fun_;
};
