#include <iostream> // agar dapat menggunakan cout dan cin

#include "Menu.h" // penghubung agar function mainMenu() bisa dipanggil di file ini
#include "MemberTeam.h" // header file penghubung antara Main Menu dan Fitur MemberTeam

using namespace std;

// functions harus tetap di tuliskan diatas pertama kali
// kemudian function tersebut baru diberi detail di bawah
// ini merupakan aturan dari C++
void biodataTimMenuSwitch();

// main function untuk fitur Member Team
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

// switch case untuk kembali ke halaman main menu
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