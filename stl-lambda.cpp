#include <iostream>
#include <format>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 简单模版方法
 */
template<typename T>
T addFn(T v1, T v2) {
  return v1 + v2;
}

/**
 * 模版类
 */
template<typename T, int N>
class Array {
private:
  T m_array[N];

public:
  T getSize() {
    return N;
  }
};

/**
 * 方法参数为匿名函数的使用
 */
template<typename Func>
void fn1(int i, Func fn) {
  fn(i);
}

int main() {
  cout << addFn<int>(2, 9) << endl;
  cout << addFn<float>(0.2f, 0.9f) << endl;

  Array<int, 2> arr;
  cout << arr.getSize() << endl;

  fn1(2, [](int input) {
    std::cout << format("input值为{}", input) << std::endl;
  });

  
  /**
   * lambda 最简单的使用
   */
  auto fn2 = [i = 3](int x) {
    return i + x;
  };
  auto result1 = fn2(9);

  cout << format("fn1 的值为{}", result1) << endl;
  cout << format("直接调用，{}", [](int x) { return format("传入的值为{}", x); }(3)) << endl;

  return 0;
}