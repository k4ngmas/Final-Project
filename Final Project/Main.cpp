#include <iostream>
#include <Windows.h>

#include "Login.h"
#include "Menu.h"
#include "GlobalsDefinitions.h"

using namespace std;

int main() {
	// jalankan login
	bool authenticationStatus = loginMenu();

	// lakukan loop login
	// jika salah maka login diulang
	while (!authenticationStatus)
	{
		Sleep(700);
		authenticationStatus = loginMenu();
	}

	// menginisialisasikan nilai globals (Buku, Anggota, Peminjaman - Pengembalian)
	defineAll();
	// menjalankan main menu 
	mainMenu();

	system("pause");
	return 0;
}