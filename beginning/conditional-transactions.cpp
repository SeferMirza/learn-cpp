#include <iostream>

using namespace std;

int main()
{
  int input = 0;
  cout << "input number: ";
  cin >> input;
  if (input > 10)
  {
    cout << "Your number bigger than 10" << endl;
    return 0;
  }

  cout << "Your number less than 10" << endl;
}