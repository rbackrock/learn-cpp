#include <iostream>
#include <format>

using namespace std;

class Student {
  private:
    string name;

  public:
    void setName(string name) {
      this->name = name;
    }

    string getName() {
      return this->name;
    }

  Student() {
    cout << "构造函数执行" << endl;
  }

  // 冒号之后是初始化列表，在生成类的同时就已经赋值一步到位
  Student(string _name) : name { _name } {
    cout << "带参析构函数执行" << name << endl;
  }

  ~Student() {
    cout << "析构函数执行" << endl;
  }
};

void showStudent(Student& stu) {
  cout << stu.getName() << endl;
}

class Exmaple1 {
  static int totalObject;

  public:
    static void showTotalObject() {
      cout << format("数量总数为{}", totalObject) << endl;
    }

  Exmaple1() {
    ++totalObject;
  }
};
int Exmaple1::totalObject = 0;

int main() {
  Student zhangsan;
  zhangsan.setName("张三");
  cout << zhangsan.getName() << endl;

  Student* lisi = new Student;
  lisi->setName("李四");
  cout << lisi->getName() << endl;
  // 使用类的指针，析构函数只有在手动调用 delete 时才执行
  delete lisi;

  Student wangwu = { "王五" };
  showStudent(wangwu);
  cout << wangwu.getName() << endl;

  Exmaple1 e1;
  Exmaple1 e2;
  Exmaple1 e3;
  Exmaple1::showTotalObject();

  return 0;
}