#include "SimpleH.h";
#include <iostream>;
using namespace std;
using namespace mynmspace;

int main() {
	int a = 5;
	int b = 14;
	int return_value=MyClass::Sum(a, b);

	cout << "a: " << a << " b: " << b << endl;
	cout << "return value: " << return_value << endl;
	system("PAUSE");

}