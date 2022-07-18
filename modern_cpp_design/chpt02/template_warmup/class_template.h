#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>

// friend pre-declaration. This is a MUST.
template<typename> class BlobPtr;
template<typename> class Blob;
template<typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

// class template
template <typename T>
class Blob {
  friend bool operator==<T>(const Blob<T>&lhs, const Blob<T>&rhs);
public:
  typedef T value_type;
  typedef typename std::vector<T>::size_type size_type;

  Blob();
  Blob(std::initializer_list<T> i);
  size_type size() const {return data->size();}
  bool empty() const {return data->empty();}
  void push_back(const T& elem) {data->push_back(elem);}
  void pop_back();

  T& back();
  T& operator[](size_type i);

  void print() const {
    for (auto elem : *(data)) {
      std::cout << elem << std::endl;
    }
  }

  std::shared_ptr<std::vector<T>> data;
private:
  void check(size_type i, const std::string &msg);
};

template <typename T>
class BlobPtr {
public:
  BlobPtr() : curr(0) {}
  BlobPtr(Blob<T>& a, size_t sz=0) :
    wptr(a.data), curr(sz) {}
  T& operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }

  // BlobPtr<T> is simplified inside class
  BlobPtr& operator++();
  BlobPtr& operator--();
private:
  std::weak_ptr<std::vector<T>> wptr;
  std::size_t curr;

  std::shared_ptr<std::vector<T>>
    check(std::size_t, const std::string&) const;

};

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }

template <typename T>
Blob<T>::Blob(std::initializer_list<T> i) : data(std::make_shared<std::vector<T>>(i)) { }

template <typename T>
void Blob<T>::pop_back() {
  check(0, "pop_back on empty Blob");
  data->pop_back();
}

template <typename T>
void Blob<T>::check(size_type i, const std::string& msg) {
  if (i >= data->size()) {
    throw std::out_of_range(msg);
  }
}

template <typename T>
T& Blob<T>::operator[](size_type i){
  check(i, "subscript out of range");
  return *(data)[i];
}

// BlobPtr
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
  check(curr, "increment out of range");
  ++curr;
  return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
  --curr;
  check(curr, "decrement out of range");
  return *this;
}

template <typename T>
std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string& msg) const {
  auto ret = wptr.lock();
  if (i >= ret->size() || i < 0) {
    throw std::out_of_range(msg);
  }
  return ret;
}

template <typename T>
bool operator==(const Blob<T>&lhs, const Blob<T>&rhs) {
  return lhs.data == rhs.data;
}
