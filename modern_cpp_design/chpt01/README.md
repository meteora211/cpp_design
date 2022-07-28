# CRTP

CRTP: (Curiously Recurring Template Pattern)[https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern]

```cpp
template<typename T>
class Base {
pulic:
  void interface() {
    static_cast<T*>(this)->implementation();
  }

  static void static_fun() {
    T::static_sub_func();
  }
};
```


## example

`enable_shared_from_this` uses CRTP to allow retrieving `this` pointer from member function.

Following code crashes without `enable_shared_from_this`.

`reallyBad` is a common `shared_ptr` error where raw resource is used to initialize 2 `shared_ptr` respectly. And this cause a double-delete issue.

`testBad` is a similiar issue but in a subtle way. The constructed shared\_ptr `bad0` owns the resource, and member function `getptr` won't realize that and
construct a new shared\_ptr which cause the double-delete.

```cpp
// https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
#include <memory>
#include <iostream>

struct Bad
{
    std::shared_ptr<Bad> getptr() {
        return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};

void testBad()
{
    // Bad, each shared_ptr thinks it's the only owner of the object
    std::shared_ptr<Bad> bad0 = std::make_shared<Bad>();
    std::shared_ptr<Bad> bad1 = bad0->getptr();
    std::cout << "bad1.use_count() = " << bad1.use_count() << '\n';
} // UB: double-delete of Bad

void reallyBad() {
  // really Bad, but the same situation with testBad.
  // two shared_ptr are initialized seperately and will double release the resource.
  Bad* reallybad0 = new Bad();
  std::shared_ptr<Bad> reallybad1(reallybad0);
  std::shared_ptr<Bad> reallybad2(reallybad0);
  std::cout << "reallybad1.use_count() = " << reallybad1.use_count() << '\n';
  std::cout << "reallybad2.use_count() = " << reallybad2.use_count() << '\n';
}

int main() {
  std::cout << "test really bad" << '\n';
  reallyBad();

  std::cout << "test bad" << '\n';
  testBad();
}
```

`enable_shared_from_this` solves above problem.
```
struct Good : std::enable_shared_from_this<Good> // note: public inheritance
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};
```

When you do this, keep in mind that the object you call `shared_from_this` on must be owned by a `shared_ptr` object. This won't work:

```cpp
int main()
{
Good* not_so_good  = new Good;
shared_ptr<Good> bad = not_so_good->getptr();     // don't do this
}
```


# Policy class

软件设计的多样性，由此引出如何在程序库中包装出弹性又有优良设计的组件这一问题？
- DoItAll接口： 庞大的class难以阅读，而且死板。
- 多重继承：技术，型别信息，状态处理上有特定问题

解决方案：templates+多重继承。


## example:

PyTorch: torch/csrc/jit/api/module.h
