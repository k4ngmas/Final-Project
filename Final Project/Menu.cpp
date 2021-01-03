#include <iostream> // agar bisa menggunakan cout dan cin
#include <string> // agar bisa menggunakan tipe data string 

// include header file setiap fitur
#include "PeminjamanPengembalian.h"
#include "MemberTeam.h"
#include "DaftarBuku.h"
#include "GenerateFile.h"
#include "DaftarAnggota.h"

using namespace std;

// functions harus tetap di tuliskan diatas pertama kali
// kemudian function tersebut baru diberi detail di bawah
// ini merupakan aturan dari C++
void mainMenuSwitch();

// main function untuk main menu
void mainMenu() 
{
    system("cls");
	cout << "+- MAIN MENU PERPUSTAKAAN AMIKOM ------------------+" << endl;
	cout << "|  1. Daftar Peminjaman                            |" << endl;
	cout << "|  2. Daftar Buku                                  |" << endl;
	cout << "|  3. Daftar Anggota                               |" << endl;
    cout << "|  4. Generate text file                           |" << endl;
    cout << "|  5. Biodata Tim                                  |" << endl;
	cout << "+--------------------------------------------------+" << endl << endl;

    mainMenuSwitch();
}

// switch case untuk pemilihan sub-menu
void mainMenuSwitch()
{
    cout << "Pilih Menu : ";
    int menu;
    cin >> menu;

    switch (menu)
    {
    case 1:
        daftarPeminjaman();
        break;
    case 2:
        daftarBuku();
        break;
    case 3:
        daftarAnggota();
        break;
    case 4:
        generateFile();
        break;
    case 5:
        biodataTim();
        break;
    default:
        break;
    }
}
