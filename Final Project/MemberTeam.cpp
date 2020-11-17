#include <iostream>

#include "Menu.h"
#include "MemberTeam.h"

using namespace std;

void biodataTim()
{
	system("cls");
	cout << "+-------------------------------------------+\n";
	cout << "|                BIODATA TIM                |\n";
	cout << "+----+--------------------------------------+\n";
	cout << "| 1. | Rakandhiya Daanii R    (20.11.3304)  |\n";
	cout << "| 2. | Hasif Priyambudi       (20.11.3306)  |\n";
	cout << "| 3. | Azzila Isme Karen      (20.11.3312)  |\n";
	cout << "| 4. | Sandy Wildani Bachtiar (20.11.3333)  |\n";
	cout << "| 5. | Muhammad Abiyyu        (20.11.3346)  |\n";
	cout << "+----+--------------------------------------+\n";

	cout << endl;
	cout << "Kembali ke halaman utama [y/n]: ";
	char menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 'y':
		mainMenu();
		break;
	case 'n':
		break;
	default:
		cout << "Input invalid";
		break;
	}
}