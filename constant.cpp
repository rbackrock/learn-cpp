#include <iostream>

void fn1(const int i) {
  // i = 2; // 不能这样么做，因为方法形参被声明了 const 不能修改 i 变量
}

class c1 {
private:
  int i;

  void fn1() const {
    // i = 2; // const 在类中成员方法的运用，意思是不能在方法中修改成员变量
  }
};

int main() {
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

  /**
   * const 引用
   */
  // int& c1 { 1 };
  // 上面一行代码不可以是因为，不能创建未命名值得引用，比如整数字面量，下面这行代码可以是因为加了 const.
  // c1 的引用指向了一个整数字面量，可以更改 "1" 得值，这没有意义，不能对非 const 引用赋右值所以不能编译
  // 对于临时对象也是如此，这里结合左值右值的概念来理解
  const int& c2 { 2 };

  return 0;
}