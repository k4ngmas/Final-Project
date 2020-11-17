#include <iostream>
#include <string>

#include "Login.h"

using namespace std;

bool loginMenu();
bool authentication(string username, string password);

bool loginMenu() {
	system("cls");
	cout << "Autentikasi awal" << endl;

	cout << "Username : ";
	string username;
	cin >> username;

	cout << "Password : ";
	string password;
	cin >> password;

	return authentication(username, password);
}

bool authentication(string username, string password) {
	if (username == "admin" && password == "admin")
	{
		return true;
	}
	else
	{
		cout << "Autentikasi gagal!";
		return false;
	}
}