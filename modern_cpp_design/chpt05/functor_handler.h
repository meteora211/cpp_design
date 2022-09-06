#pragma once
template<class ParentFunctor,typename Fun>
class FunctorHandler :
  public FunctorImpl
    <
      typename ParentFunctor::ResultType,
      typename ParentFunctor::ParamList
    >
{
public:
  typedef typename ParentFunctor::ResultType ResultType;
  typedef typename ParentFunctor::ParamList ParamList;
  typedef typename ParentFunctor::Param1 Param1;
  typedef typename ParentFunctor::Param2 Param2;

  FunctorHandler(const Fun& fun) : fun_(fun) {}

  ResultType operator()() {
    return fun_();
  }

  ResultType operator()(Param1 param) {
    return fun_(param);
  }

  ResultType operator()(Param1 param1, Param2 param2) {
    return fun_(param1, param2);
  }

private:
  Fun fun_;
};
