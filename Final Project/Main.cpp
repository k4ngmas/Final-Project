#include <iostream>
#include <Windows.h>

#include "Login.h"
#include "Menu.h"
#include "GlobalsDefinitions.h"

using namespace std;

int main() {
	bool authenticationStatus = loginMenu();

	Sleep(300);
	if (authenticationStatus)
	{
		defineAll();
		mainMenu();
	}
	else
	{
		loginMenu();
	}

	system("pause");
	return 0;
}