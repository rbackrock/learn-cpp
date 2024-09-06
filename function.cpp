#include <iostream>
#include <format>

using namespace std;

/**
 * 值传递
 * 
 * 形参对实参进行拷贝，以在函数内，任何运算都不影响传入的参数
 */
void fn1(int i) {
  cout << format("普通函数，传入的参数为{}", i) << endl;
}

/**
 * 引用传递 - 指针
 * 
 * 形参是实参的别名，直接共享实参地址，函数内对该值修改相当于直接修改实参
 * 形参p为传入的是一个指针地址
 */
void fn2(int* p) {
  // 从右往左意为，把p指针解引用之后的值乘以2再赋值给p内存地址所指向的值
  *p = *p * 2;
}

/**
 * 返回指针函数，比较p1和p2指针指向值的大小，返回最大值对应的指针
 */
int* fn3(int* p1, int* p2) {
  if (*p1 > *p2) {
    return p1;
  } else {
    return p2;
  }
}

/**
 * 注意！永远不要输出局部变量的地址，而是输出动态分配到堆的地址（堆指针）
 * 局部变量地址在 stack 上，方法执行完内存地址会被系统回收，所以无法确认再次引用该地址时，究竟修改了什么
 */
int* fn4(int size) {
  int *p = nullptr;
  p = new int[size];

  for (int i = 0, v = 3; i < size; i++) {
    *(p + i) = v;
    v += 3;
  }

  for (int i = 0, v = 3; i < size; i++) {
    cout << format("{}, ", *(p + i));
  }
  cout << endl;

  return p;
}

int fn5(int& i) {
  return i * 3;
}

int main() {
  fn1(3);

  int fn2_i = 3;
  fn2(&fn2_i);
  cout << format("fn2函数执行之后，i的值为：{}", fn2_i) << endl;

  int fn3_i = 3;
  int fn3_n = 6;
  int* fn3_result_ptr = fn3(&fn3_i, &fn3_n);
  cout << format("最大的值为：{}", *fn3_result_ptr) << endl;

  int* fn4_result_ptr = fn4(3);
  // 执行完之后，删除申请的数组指针
  delete[] fn4_result_ptr;

  // 左值：具有名称，非常数可修改
  // 右值：非左值的内容，可明确复制给左值的内容
  int fn5_val = 3;
  // fn5_val 属于左值范畴
  int fn5_result = fn5(fn5_val);
  // 下面这行报错，因为方法形参需要传一个引用类型，而 10 是属于右值范畴
  // int fn5_result = fn5(10);

  return 0;
}