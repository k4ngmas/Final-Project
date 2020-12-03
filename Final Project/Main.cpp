#include <iostream>
#include <Windows.h>

#include "Login.h"
#include "Menu.h"
#include "GlobalsDefinitions.h"

using namespace std;

int main() {
	bool authenticationStatus = loginMenu();

	Sleep(300);
	while (!authenticationStatus)
	{
		authenticationStatus = loginMenu();
	}

	defineAll();
	mainMenu();

	system("pause");
	return 0;
}