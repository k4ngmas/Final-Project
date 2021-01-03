#include <iostream> // agar bisa menggunakan cout dan cin
#include <string> // agar bisa menggunakan tipe data string

#include "Login.h" // header file penghubung antara login dengan Main

using namespace std;

// functions harus tetap di tuliskan diatas pertama kali
// kemudian function tersebut baru diberi detail di bawah
// ini merupakan aturan dari C++
bool loginMenu();
bool authentication(string username, string password);

// form pengisian untuk login
bool loginMenu() {
	system("cls");
	cout << "Autentikasi awal" << endl;

	cout << "Username : ";
	string username;
	cin >> username;

	cout << "Password : ";
	string password;
	cin >> password;

	// return true or false tergantung function authentication mengeluarkan true / false
	return authentication(username, password);
}

// cek jika input form benar salah dan return true / false
bool authentication(string username, string password) {
	// jika input username dan password sama dengan admin maka benar
	// jika tidak maka false
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