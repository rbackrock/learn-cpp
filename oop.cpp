#include <iostream>
#include <format>

using namespace std;

/**
 * 静态绑定
 * 在编译器编译源代码时绑定，消耗低，效率高
 * 调用成员方法时，指针变量根据指向对象的类型动态绑定不同的函数实现多态
 * 
 * 动态绑定
 * 在程序运行中绑定，Base对象可以灵活的代表包括自身在内的所有字累对象（虚函数/应用多态的情况）
 * 
 * 最好所有用于重写的方法在声明上都加上 virtual
 */
class Base {
public:
  void staticBindingPrint() {
    cout << "base static print" << endl;
  }

  virtual void dynamicBindingPrint() {
    cout << "base dynamic print" << endl;
  }
};

class Child : public Base {
public:
  void staticBindingPrint() {
    cout << "child static print" << endl;
  }

  virtual void dynamicBindingPrint() override {
    cout << "child print" << endl;
  }
};

/**
 * C++ 中，抽象类有这几个特点
 * # 不能生成对象
 * # 一般用于继承中的父类，也常用于接口
 * # 至少包含一个纯虚函数
 */
class GunBase {
private:
  string name;
  int ammo;

public:
  // 此为纯虚函数
  virtual void print() = 0;

  void setName(string _name) {
    this->name = _name;
  }

  string getName() {
    return this->name;
  }

  void setAmmo(int ammo) {
    this->ammo = ammo;
  }

  int getAmmo() {
    return this->ammo;
  }

  GunBase(string _name, int _ammon) : name { _name }, ammo { _ammon } {
  }
  // TODO 当使用堆上分配空间创建对象时，析构函数不添加 virtual 关键字 delete 时会提示该类是个抽象类，但是没有虚析构函数
  virtual ~GunBase() {}
};

class I_Combat {
public:
  virtual void fire() = 0;
};

class Rifle : public GunBase, public I_Combat {
public:
  Rifle(string _name, int _ammon) : GunBase(_name, _ammon){
  }

  virtual void print() override {
    cout << format("执行了Rifle的print方法，武器名称为{}子弹数为{}",this->getName(), this->getAmmo()) << endl;
  }

  virtual void fire() override {
    cout << format("Rifle 的{}武器开火", this->getName()) << endl;
  }
};

int main() {
  /**
   * 裸指针
   * 默认静态绑定到Base类，地址指向Base对象，在堆上分配Child所需空间
   * Child也是Base(is-a关系)
   * 结果总是调用Base的方法
   */
  Base* obj = new Child;
  obj->staticBindingPrint(); // base static print
  obj->dynamicBindingPrint(); // child print
  delete obj;

  Rifle* mp5 = new Rifle("mp5冲锋枪", 30);
  mp5->print(); // 执行了Rifle的setSkeletalMesh方法，武器名称为mp5冲锋枪子弹数为30
  mp5->fire(); // Rifle 的mp5冲锋枪武器开
  delete mp5;

  /**
   * 智能指针的写法
   */
  unique_ptr<Rifle> wuzi_ptr = make_unique<Rifle>("乌兹冲锋枪", 99);
  wuzi_ptr->print(); // 执行了Rifle的setSkeletalMesh方法，武器名称为乌兹冲锋枪子弹数为99
  wuzi_ptr->fire(); // Rifle 的乌兹冲锋枪武器开火

  GunBase* g1 = new Rifle("G1冲锋枪", 30);
  g1->print();
  // 下面这行代码报错，因为指针指向父类，但是实例化的为子类，只能调用父类有的方法
  // g1->fire();
  delete g1;

  return 0;
}


