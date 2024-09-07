#include <iostream>
#include <format>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<int> v) {
  for (auto element : v) {
    cout << element << endl;
  }

  cout << "---------------" << endl;
}

int main() {
  vector<int> v1 = { 3, 6, 9 };
  print(v1);
  reverse(v1.begin(), v1.end());
  print(v1);
  v1.pop_back();
  print(v1);
  v1.push_back(3);
  print(v1);

  return 0;
}