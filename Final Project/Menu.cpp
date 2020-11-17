#include <iostream>
#include <string>

#include "MemberTeam.h"
#include "DaftarBuku.h"

using namespace std;

void mainMenu() 
{
    system("cls");

    int menu;
    int inputbuku;
        
    cout << "====== Perpustakaan Amikom ======" << endl;
    cout << "Amikom Sejahtera" << endl;
    cout << "Jln. Ngringin, Condongcatur" << endl;
    cout << "Menu Perpustakaan" << endl;
    cout << "1. Peminjaman Buku" << endl;
    cout << "2. Pengembalian Buku" << endl;
    cout << "3. Daftar Buku" << endl;
    cout << "4. Daftar Anggota" << endl;
    cout << "5. Generate Report" << endl;
    cout << "6. Member Team" << endl;
    cout << "===============================" << endl;
    cout << "Pilih Menu : ";

    cin >> menu;

    if (menu == 3)
    {
        daftarBuku();
    }

    else if (menu == 6)
    {
        biodataTim();
    }
}







