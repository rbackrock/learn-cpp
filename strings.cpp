#include <iostream>
#include <string>
#include <format>
#include <vector>

using namespace std;

int main() {
  {
    // 原始字符串字面量
    cout << R"("Hello")" << endl;
  }

  {
    // 字符串字面量通常解释为 const char* 或者 const char[]
    string str1 { "hello" };
    // 如果要解释为 std::string 需要加 s
    string str2 { "hello"s };
    // 对字符串 vector 使用 CTAD 时要小时，推到的类型是 vector<const char*> 
    // 可能导致代码出奇怪的问题甚至崩溃，这取决于之后对 vector 的处理方式
    vector v { "hello"s, "world"s };
    // 对 auto 也是类似
    // 类型为 const char*
    auto str4 { "hello" };
    // 类型为 std::string
    auto str5 { "hello"s };
  }

  {
    string str = "9";
    // stio(没有异常)
    int num1 = std::stoi(str);
    cout << format("使用stio转化值为:{}", num1) << endl;
    // stio(有异常)
    try {
      int num1 = std::stoi(str);
      cout << format("使用stio(有异常)转化值为:{}", num1) << endl;
    } catch (const std::invalid_argument& ex) {
      cout << format("使用stio(有异常)结果转化失败", num1) << endl;
    }
    // from_chars(有异常，C++17，高性能)
    int num2 = 0;
    auto [ ptr, ex ] = std::from_chars(str.data(), str.data() + str.size(), num2);
    if (ex == std::errc()) {
      cout << format("使用from_chars(处理异常)转化值为:{}", num2) << endl;
    } else {
      cout << format("使用from_chars(处理异常)结果转化失败") << endl;
    }
  }

  {
    // std::string_view 类，当只接收只读字符串时，使用它最合适，例如在函数或者方法中，通常按值传递因为复制成本极低
    // 无法连接 std::string 和 std::string_view
    // 每当函数需要只读字符串时，可以用 std::string_view 代替 const std::string& 或者 const char*
    // 返回字符串的函数应该返回 string 不应该返回 string_view
    // 建议作为类的数据成员时候，存储 std::string
    std::string_view sv1 = { "hello" };
    // 转化为 std::string 有两种办法
    // 一种是使用字符串构造函数
    string str1 { sv1 };
    // 另一种是使用 append
    string str2 { "hello" };
    str2.append(sv1.data(), sv1.size());
    // 虽然能执行在我尝试的时候结果正确也没有报错，但是最好不要这么干，不要使用 string_view 保存临时字符串的视图
    string ss4 { "hello" };
    string_view sv2 { ss4 + "world" };
    cout << sv2 << endl;
    // 在使用 auto 的时候，可以提示这是 std::string_view，使用 sv
    auto sv4 { "hello world"sv };
  }

  return 0;
}