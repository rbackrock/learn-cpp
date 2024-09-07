#include <iostream>
#include <format>

using namespace std;

int main() {
  auto fn1 = [i = 3](int x) {
    return i + x;
  };
  auto result1 = fn1(9);

  cout << format("fn1 的值为{}", result1) << endl;
  cout << format("直接调用，{}", [](int x) { return format("传入的值为{}", x); }(3)) << endl;

  return 0;
}