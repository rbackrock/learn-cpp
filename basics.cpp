#include <iostream>
#include <format>

using namespace std;

int main() {
  int i { 3 };
  cout << format("i变量值为{}", i) << endl; // 3

  int arr[] { 3, 6, 9 };
  cout << format("数组中第三个元素的值是{}", arr[2]) << endl; // 9

  string str = "string";
  cout << format("str的值为{}", str) << endl; // string

  int n { 3 };
  int* n_ptr = &n;
  int nValue = *n_ptr;
  cout << "n的指针值为" << n_ptr << endl; // 0x...
  cout << format("n的指针变量取值以后的结果值为{}", nValue) << endl; // 3

  int val { 3 };
  cout << format("val的原始值为{}", val) << endl; // 3
  // 一旦初始化引用变量，就不能再指定其他变量
  int& val_copy = val;
  // 引用变量在使用时会自动解引用
  val_copy = 9;
  cout << format("val的引用变量val_copy引用会改变val，结果为{}", val) << endl; // 9

  // 左值：具有名称，非常数可修改
  // 右值：非左值的内容，可明确复制给左值的内容
  int i { 3 };
  float n { 3.33f };
  // 引用变量必须参考左值类型数据
  int& i_ref = i;

  /**
   * const 技巧，通过看 const 修饰的左边是什么
   * 也可以通过顶层 const (top-level const) 来表示指针自身是常量，
   * 而底层 const (low-level const) 则表示指针指向的值是常量
   * 从右往左阅读 const 修饰的内容，依次是顶层 const 和底层 const
   **/
  int *const p1 = new int; // 不能重新指向其他指针
  int const* p2 = new int; // 不能修改指针指向的值
  int const *const p3 = new int; // 不能修改指针自身的值，也不能修改指针指向的值

  return 0;
}