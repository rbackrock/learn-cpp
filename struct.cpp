#include <iostream>
#include <format>

using namespace std;

struct position {
  string lng;
  string lat;
};

int main() {
  position kunmingPositon;
  kunmingPositon.lng = "102.712251";
  kunmingPositon.lat = "25.040609";

  cout << format("昆明经度为{}", kunmingPositon.lng) << endl;
  cout << format("昆明纬度为{}", kunmingPositon.lat) << endl;

  position qujingPositon { "103.797851", "25.501557" };

  cout << format("曲靖经度为{}", qujingPositon.lng) << endl;
  cout << format("曲靖纬度为{}", qujingPositon.lat) << endl;

  return 0;
}