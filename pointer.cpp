#include <iostream>
#include <format>

using namespace std;

int main() {
  int* p_ptr = new int;
  *p_ptr = 3;
  cout << format("在堆申请的指针变量p的赋的值是{}", *p_ptr) << endl;
  delete p_ptr;
  cout << format("删除指针变量p之后存储的值是{}", *p_ptr) << endl;

  int* arr_ptr = new int[] { 3, 6, 9 };
  cout << arr_ptr[0] << endl; // 3
  delete[] arr_ptr;
  cout << arr_ptr[0] << endl; // 0

  float priceArray[] = { 3.3f, 6.6f, 9.9f };
  float* priceArray_ptr = priceArray;
  cout << "priceArray数组变量的值：" << priceArray << endl; // 0x...
  cout << "取priceArray数组变量的值：" << &priceArray << endl; // 0x... &priceArray 和 priceArray 输出的值一致，代表的是数组第一个元素的内存地址
  cout << "解priceArray数组的值：" << *priceArray << endl; // 3.3f
  // 数组下标的本质是内存地址的偏移量，偏移的值根据数据类型的字节决定
  cout << *(priceArray + 1) << endl; // 6.6
  /**
   * 数组名称不能改变地址，但是指针变量则可以
   */
  // 下面一行输出会报错
  // cout << *(++priceArray) << endl;
  // 下面这行不会报错
  cout << *(++priceArray_ptr) << endl; // 6.6

  int i = 3;
  int i_tmp = 6;
  const int* i_ptr1 = &i;
  const int* const i_ptr2 = &i;
  /**
   * 从右往左边进行判断更容易理解，第一个 const 代表内存地址为常数只能赋值一次，第二个 const 代表指针变量指向的值为常量，也只能赋值一次
   */
  // 下面这行会报错
  // *i_ptr1 = 333;
  // 下面这行不会报错
  i_ptr1 = &i_tmp;
  // 下面两行都会报错
  // *i_ptr2 = 333;
  // i_ptr2 = &i_tmp;

  /**
   * 唯一智能指针
   * # 不允许多个唯一指针指向同一个对象
   * # 不能复制
   * # 执行效率高
   */
  unique_ptr<int> unique_ptr1 { new int(3) };
  cout << format("唯一智能指针的值为{}", *unique_ptr1) << endl;
  unique_ptr1.reset();
  if (unique_ptr1 == nullptr) {
    cout << "唯一智能指针指向 nullptr" << endl;
  }
  // C++14 推荐的唯一智能指针推荐的赋值方法
  unique_ptr<int> unique_ptr2 = make_unique<int>(3);
  cout << format("唯一智能指针C++14推荐的值为{}", *unique_ptr2) << endl;
  // 智能指针的地址
  cout << unique_ptr2 << endl;
  // 智能指针的地址也可以用 get 函数
  cout << unique_ptr2.get() << endl;

  /**
   * 共享智能指针
   * # 允许多个共享指针指向同一个对象
   * # 可以复制
   * # 内置计数器记录引用次数，0时销毁，所以有一些 overhead
   */
  shared_ptr<int> shared_test_ptr1 { new int(333) };
  cout << format("共享指针shared_test_ptr1的值为：{}", *shared_test_ptr1) << endl;
  cout << format("共享指针shared_test_ptr1引用次数为：{}", shared_test_ptr1.use_count()) << endl; // 1
  shared_ptr<int> shared_test_ptr2 { shared_test_ptr1 };
  cout << format("共享指针shared_test_ptr1引用次数为：{}", shared_test_ptr1.use_count()) << endl; // 2
  cout << format("共享指针shared_test_ptr2引用次数为：{}", shared_test_ptr2.use_count()) << endl; // 2
  // 也可以用下面这张方式使用共享指针
  shared_ptr<int> shared_test_ptr3 { make_shared<int>(9) };
  cout << format("shared_test_ptr3的值为：{}", *shared_test_ptr3) << endl;

  /**
   * 弱指针
   * # 基于共享指针创建
   * # 指向对象但不会增加自身引用（无所有权）
   * # 用于防止互相引用时导致内存无法回收
   */
  class Right;
  class RightWeak;
  class Left {
    public:
      shared_ptr<Right> r_ptr;
    
    Left() {
      cout << "Left构造函数执行" << endl;
    }

    ~Left() {
      cout << "Left析构函数执行" << endl;
    }
  };
  class Right {
    public:
      shared_ptr<Left> l_ptr;
    
    Right() {
      cout << "Right构造函数执行" << endl;
    }

    ~Right() {
      cout << "Right析构函数执行" << endl;
    }
  };
  class LeftWeak {
    public:
      weak_ptr<RightWeak> r_weak_ptr;
    
    LeftWeak() {
      cout << "LeftWeak构造函数执行" << endl;
    }

    ~LeftWeak() {
      cout << "LeftWeak析构函数执行" << endl;
    }
  };
  class RightWeak {
    public:
      shared_ptr<LeftWeak> l_weak_ptr;

    RightWeak() {
      cout << "RightWeak构造函数执行" << endl;
    }

    ~RightWeak() {
      cout << "RightWeak析构函数执行" << endl;
    }
  };
  shared_ptr<Left> left1 { make_shared<Left>() };
  shared_ptr<Right> right1 { make_shared<Right>() };
  // 执行到这里如果就结束的话，left 和 right 类会结束，各自的析构函数会执行
  left1->r_ptr = right1;
  right1->l_ptr = left1;
  // 如果执行到这里，left 和 right 类的析构函数不会执行，因为互相引用了对象的指针，这会导致应该回收的内存没有进行回收
  shared_ptr<LeftWeak> left2 { make_shared<LeftWeak>() };
  shared_ptr<RightWeak> right2 { make_shared<RightWeak>() };
  left2->r_weak_ptr = right2;
  right2->l_weak_ptr = left2;
  // 为了解决以上问题，只要在其中一个类中使用 weak_ptr 就可以解决问题，结果就是两个类的析构函数就都可以执行了

  return 0;
}