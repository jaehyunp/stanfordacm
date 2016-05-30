#include <iostream>
using namespace std;
int main() {
  string s;
  bool cut = false;
  while (getline(cin, s)) {
    if (s.length() >= 2 && s.find("// BEGIN CUT") != string::npos) {
      cut = true;
    } else if (s.length() >= 2 && s.find("// END CUT") != string::npos) {
      cut = false;
    } else {
      if (!cut) cout << s << endl;
    }
  }
  return 0;
}
