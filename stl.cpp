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

int main() {
  cout << addFn<int>(2, 9) << endl;
  cout << addFn<float>(0.2f, 0.9f) << endl;

  Array<int, 2> arr;
  cout << arr.getSize() << endl;

  return 0;
}