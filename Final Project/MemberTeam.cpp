#include <iostream>

#include "Menu.h"
#include "MemberTeam.h"

using namespace std;

void biodataTimMenuSwitch();

void biodataTim()
{
	system("cls");
	cout << "+-------------------------------------------+\n";
	cout << "|                BIODATA TIM                |\n";
	cout << "+----+--------------------------------------+\n";
	cout << "| 1. | Rakandhiya Daanii R    (20.11.3304)  |\n";
	cout << "| 2. | Hasif Priyambudi       (20.11.3305)  |\n";
	cout << "| 3. | Azzila Isme Karen      (20.11.3312)  |\n";
	cout << "| 4. | Sandy Wildani Bachtiar (20.11.3333)  |\n";
	cout << "| 5. | Muhammad Abiyyu        (20.11.3346)  |\n";
	cout << "+----+--------------------------------------+\n";

	biodataTimMenuSwitch();
}

void biodataTimMenuSwitch()
{
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