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

struct Good : std::enable_shared_from_this<Good> // note: public inheritance
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};

struct Best : std::enable_shared_from_this<Best> // note: public inheritance
{
    std::shared_ptr<Best> getptr() {
        return shared_from_this();
    }
    // No public constructor, only a factory function,
    // so there's no way to have getptr return nullptr.
    [[nodiscard]] static std::shared_ptr<Best> create() {
        // Not using std::make_shared<Best> because the c'tor is private.
        return std::shared_ptr<Best>(new Best());
    }
private:
    Best() = default;
};

void testGood()
{
    // Good: the two shared_ptr's share the same object
    std::shared_ptr<Good> good0 = std::make_shared<Good>();
    std::shared_ptr<Good> good1 = good0->getptr();
    std::cout << "good1.use_count() = " << good1.use_count() << '\n';
}


void misuseGood()
{
    // Bad: shared_from_this is called without having std::shared_ptr owning the caller
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch(std::bad_weak_ptr& e) {
        // undefined behavior (until C++17) and std::bad_weak_ptr thrown (since C++17)
        std::cout << e.what() << '\n';
    }
}


void testBest()
{
    // Best: Same but can't stack-allocate it:
    std::shared_ptr<Best> best0 = Best::create();
    std::shared_ptr<Best> best1 = best0->getptr();
    std::cout << "best1.use_count() = " << best1.use_count() << '\n';

    // Best stackBest; // <- Will not compile because Best::Best() is private.
}

int main() {
  testGood();
  testBest();
  std::cout << "test not so good" << '\n';
  misuseGood();

  std::cout << "test really bad" << '\n';
  reallyBad();

  std::cout << "test bad" << '\n';
  testBad();
}
