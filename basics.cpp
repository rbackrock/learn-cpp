#include <iostream>
#include <format>
#include <string>
#include <array>

using namespace std;

int main() {
  /**
   * 赋值
   */
  int i { 3 };
  cout << format("i变量值为{}", i) << endl; // 3

  /**
   * 数组
   */
  // C 风格数组
  int arr[] { 3, 6, 9 };
  cout << format("数组中第三个元素的值是{}", arr[2]) << endl; // 9
  // std::array 数组，需要引用 #include <array> 下面例子是基于 C++17 的推断
  std::array arr1 { 1, 2 };
  // std::array 创建2个长度的 int 空数组，其实初始值都是 0
  std::array<int, 2> arr2;
  // std::array 其中一个好处就是可以使用迭代器，并且可以用 size() 拿到数组长度
  for (const auto it : arr2) {
    std::cout << it << std::endl; // [0, 0]
  }
  cout << format("arr2 数组长度为{}", arr2.size()) << endl; // 2

  /**
   * 引用
   */
  int val { 3 };
  cout << format("val的原始值为{}", val) << endl; // 3
  // 一旦初始化引用变量，就不能再指定其他变量
  int& val_copy = val;
  // 引用变量在使用时会自动解引用
  val_copy = 9;
  cout << format("val的引用变量val_copy引用会改变val，结果为{}", val) << endl; // 9

  /**
   * 结构化绑定，其实相当于 JavaScript 中的解构
   */
  // 数组
  array structuringArr1 { 1, 2 };
  auto [ sa1, sa2 ] { structuringArr1 };
  cout << format("sa1={},sa2={}", sa1, sa2) << endl;
  // 结构体
  struct structuringPoint { double x, y, z; };
  structuringPoint sp1;
  sp1.x = 1.0; sp1.y = 2.0; sp1.z = 9.0;
  auto [ sp1x, sp1y, sp1z ] { sp1 };
  cout << format("sp1x={},sp1y={},sp1z={}", sp1x, sp1y, sp1z) << endl;

  /**
   * for 范围循环的完成用法，有一个初始化器
   */
  // arr1 作用域为循环体内
  for (array arr1 { 1, 2 }; auto &it : arr1) {
    cout << it << endl;
  }

  /**
   * 指派初始化器(结构体)C++20支持，非常简洁
   */
  struct struct_dz {
    int x;
    int y;
  };
  struct_dz sd1 {
    .x = 1,
    .y = 2
  };
  cout << format("x={},y={}", sd1.x, sd1.y) << endl;

  return 0;
}