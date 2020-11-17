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
		mainMenu();
	}
	else
	{
		loginMenu();
	}

	system("pause");
	return 0;
}