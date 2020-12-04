#include <iostream>
#include <Windows.h>

#include "Login.h"
#include "Menu.h"
#include "GlobalsDefinitions.h"

using namespace std;

int main() {
	bool authenticationStatus = loginMenu();

	while (!authenticationStatus)
	{
		Sleep(300);
		authenticationStatus = loginMenu();
	}

	defineAll();
	mainMenu();

	system("pause");
	return 0;
}