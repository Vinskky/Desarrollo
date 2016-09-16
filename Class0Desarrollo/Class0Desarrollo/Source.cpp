#include "Vector3.h"
#include <iostream>

using namespace std;

int main()
{
	Vector3<int> alpha( 3, 5, 6);
	Vector3<int> beta(4, 5, 6);

	
	if (8 == (int)alpha.getModule())
		cout << "Works" << endl;
	else 
		cout << "fck this shit" << endl;

	system("pause");

	return 0;
}
