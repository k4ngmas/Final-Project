#include <iostream>
#include <string>

#include "PeminjamanPengembalian.h"
#include "MemberTeam.h"
#include "DaftarBuku.h"
#include "DaftarAnggota.h"

using namespace std;

void mainMenu() 
{
    system("cls");
    cout << "====== Perpustakaan Amikom ======" << endl;
    cout << "Amikom Sejahtera" << endl;
    cout << "Jln. Ngringin, Condongcatur" << endl;
    cout << "Menu Perpustakaan" << endl;
    cout << "1. Peminjaman & Pengembalian Buku" << endl;
    cout << "2. Daftar Buku" << endl;
    cout << "3. Daftar Anggota" << endl;
    cout << "4. Generate Report" << endl;
    cout << "5. Member Team" << endl;

    cout << "===============================" << endl;
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
    case 5:
        biodataTim();
        break;
    default:
        break;
    }

}
