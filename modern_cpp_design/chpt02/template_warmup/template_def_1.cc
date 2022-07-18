#include <type_traits>
#include <typeinfo>
#include <string.h>
#include "class_template.h"
// function template
template<typename T>
int compare(const T& v1, const T& v2) {
  if (v1 < v2) return -1;
  if (v2 < v1) return 1;
  return 0;
}

// type parameter
template<typename T, typename U>
T compare(const T&, const U&);

// nontype parameter
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
  // char(&p1)[N]: array ref in function parameter
  return strcmp(p1, p2);
}

// possible move implementation
template <typename T>
typename std::remove_reference<T>::type&& possible_move_impl(T&& in) {
  return static_cast<typename std::remove_reference<T>::type&&>(in);
}

// For the last elem printing, possible overload 1.
template<typename T>
void print_args(T&& t) {
  std::cout << __PRETTY_FUNCTION__ << typeid(t).name() << ": " << t << std::endl;
}

// For the last elem printing, possible overload 2.
/* template<typename... Args> */
/* void print_args(Args&&... args) { */
/*   std::cout << std::endl; */
/* } */

template<typename T, typename... Args>
void print_args(T&& t, Args&&... args) {
  std::cout << __PRETTY_FUNCTION__ << typeid(t).name() << ": " << t << std::endl;;
  print_args(std::forward<Args>(args)...);
}

template<typename... Args>
void variadic_func(Args&&... args) {
  print_args(std::forward<Args>(args)...);
}

// tailing return
template<typename IT>
auto fcn(IT begin, IT end) -> typename std::remove_reference<decltype(*begin)>::type {
  return *begin;
}

int main() {
  std::cout << compare(1,0) << std::endl;
  std::cout << compare("hello","temp") << std::endl;

  Blob<std::string> string_blob{"a", "b", "c"};
  string_blob.push_back("test");
  string_blob.print();

  BlobPtr<std::string> string_blob_ptr(string_blob);
  std::cout << (string_blob==string_blob) << std::endl;
  std::cout << *string_blob_ptr << std::endl;
  ++string_blob_ptr;
  std::cout << *string_blob_ptr << std::endl;

  std::cout << fcn(string_blob.data->begin(), string_blob.data->end()) << std::endl;;


  // variadic template
  int i = 0;
  const int& a = i;
  variadic_func("test", 1, i, a, possible_move_impl(a));
}
