#include <iostream>
#include <string>

#include "PeminjamanPengembalian.h"
#include "MemberTeam.h"
#include "DaftarBuku.h"
#include "DaftarAnggota.h"

using namespace std;

void mainMenuSwitch();

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
        cout << "NOT IMPLEMENTED YET!" << endl;
        break;
    case 5:
        biodataTim();
        break;
    default:
        break;
    }
}
