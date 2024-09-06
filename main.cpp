#include <iostream>
#include <format>

using namespace std;

class Base {
  public:
    void test() {
      cout << "base test" << endl;
    }
};

class Child : public Base {
  public:
    void test() {
      cout << "child test" << endl;
    }
};

int main() {
  Base* obj = new Child;
  obj->test();
  delete obj;

  return 0;
}