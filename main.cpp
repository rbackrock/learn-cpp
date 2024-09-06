#include <iostream>
#include <format>

using namespace std;

void test(string name = "test") {
  cout << name << endl;
}

int main() {
  test();

  return 0;
}