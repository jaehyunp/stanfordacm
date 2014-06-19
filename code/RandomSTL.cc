// Example for using stringstreams and next_permutation

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(void){
  vector<int> v;
  
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  
  // Expected output: 1 2 3 4
  //                  1 2 4 3
  //                  ...
  //                  4 3 2 1  
  do {
    ostringstream oss;
    oss << v[0] << " " << v[1] << " " << v[2] << " " << v[3];
    
    // for input from a string s,
    //   istringstream iss(s);
    //   iss >> variable;
    
    cout << oss.str() << endl;
  } while (next_permutation (v.begin(), v.end()));
  
  v.clear();
  
  v.push_back(1);
  v.push_back(2);
  v.push_back(1);
  v.push_back(3);
  
  // To use unique, first sort numbers.  Then call
  // unique to place all the unique elements at the beginning
  // of the vector, and then use erase to remove the duplicate
  // elements.
  
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  
  // Expected output: 1 2 3
  for (size_t i = 0; i < v.size(); i++)
    cout << v[i] << " ";
  cout << endl; 
}
