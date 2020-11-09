#include <iostream>

#include <Windows.h>
#include "Login.h"
#include "Menu.h"

using namespace std;

int main() {
	bool authenticationStatus = loginMenu();

	Sleep(300);
	if (authenticationStatus)
	{
		system("cls");
		mainMenu();
	}
	else
	{
		system("cls");
		loginMenu();
	}

	system("pause");
	return 0;
}