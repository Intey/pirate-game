
#include <string>
#include <iostream>

using namespace std;

void expect(bool valid, const string &message)
{
    string result = (valid? "PASS": "FAILED");
    cout << message << " : " << result << endl;
}
