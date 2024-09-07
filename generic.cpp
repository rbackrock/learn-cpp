#include <iostream>
#include <format>

using namespace std;

template<class T> T sum(T n) {
  return n * (n + 1) / 2;
}

template<class T> class PlayerInfo {
private:
  string name;
  T value;

public:
  PlayerInfo(string _name, T _value) : name { _name }, value { _value } {
  }

  void setName(string _name) {
    this->name = _name;
  }

  string getName() const {
    return this->name;
  }

  void setValue(T _value) {
    this->value = _value;
  }

  T getValue() const {
    return this->value;
  }
};

int main() {
  cout << sum<int>(3) << endl;

  PlayerInfo<int> player1 { "leo", 3 };
  cout << format("name={}, value={}", player1.getName(), player1.getValue()) << endl;

  PlayerInfo<PlayerInfo<int>> player2 = { "alex", player1 };
  cout <<
    format(
      "外部name={} 内部name={} 内部val={}",
      player2.getName(),
      player2.getValue().getName(),
      player2.getValue().getValue()
    )
  << endl;

  return 0;
}