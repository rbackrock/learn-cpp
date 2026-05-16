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
   * const 技巧，通过看 const 修饰的左边是什么
   * 也可以通过顶层 const (top-level const) 来表示指针自身是常量，
   * 而底层 const (low-level const) 则表示指针指向的值是常量
   * 从右往左阅读 const 修饰的内容，依次是顶层 const 和底层 const
   **/
  int *const p1 = new int; // 不能重新指向其他指针
  int const* p2 = new int; // 不能修改指针指向的值
  int const *const p3 = new int; // 不能修改指针自身的值，也不能修改指针指向的值

  /**
   * 上面是一般教材的说法，这里是自己的理解，核心在于看 const 所处的位置
   */
  // 普通的赋值语句
  int* p1 = new int { 2 };
  // const 之后是 p2, p2 是指针变量，所以不能对 p2 指针赋值
  int* const p2 = new int { 2 };
  // const 之后是 int* 相当于指针指向的值，所以不能对 p4 指针指向的值赋值
  const int* p4 = new int { 2 };
  // const 最左边这种写法还有一种等价的写法是 p5 这样
  int const * p5 = new int { 2 };

  return 0;
}