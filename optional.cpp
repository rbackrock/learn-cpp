#include <iostream>
#include <thread>
#include <string>
#include <format>
#include <vector>
#include <utility>
#include <array>
#include <optional>

using namespace std;

std::optional<int> fn1(bool isIt) {
  if (isIt) {
    return 1;
  }

  return {};
}

int main() {
  std::optional<int> result1 = fn1(false);
  // 如果对非"正常"返回值使用 value() 会抛出异常
  if (result1.has_value()) { // 判断是否返回"正常"的值
    cout << format("说明返回了 int 值,值为:{}", result1.value()) << endl; // 1
  } else {
    cout << "说明返回了非 int 值,也许在某种情况下属于一种特殊的值" << endl;
  }
  // 如果是非"正常"返回值那么就返回指定的值
  cout << format("展示一种常用的用法,结果为:{}", result1.value_or(-1)) << endl; // -1

  return 0;
}