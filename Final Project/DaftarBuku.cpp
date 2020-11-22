#include <iostream>
#include <string>
#include <vector>

#include "Menu.h"
#include "DaftarBuku.h"
#include "Globals.h"

using namespace std;

extern vector<Buku> bukuVector;

void tambahBuku();
void updateBuku();
void hapusBuku();

void daftarBuku()
{	
	system("cls");
	cout << "------------- DAFTAR BUKU -------------" << endl;
	cout << endl;

	int count = 1;
	for (auto buku : bukuVector)
	{
		cout << count++ << ". " << buku.kode << " - " << buku.judul 
			 << " (" << buku.penulis << ", " << buku.tahunTerbit << "), stok: " << buku.stok << endl;
	}

	cout << endl;
	cout << "--- Menu ---" << endl;
	cout << "1. Tambah buku" << endl;
	cout << "2. Update buku" << endl;
	cout << "3. Hapus buku" << endl;
	cout << "9. Kembali ke menu utama" << endl << endl;

	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		tambahBuku();
		break;
	case 2:
		updateBuku();
		break;
	case 3:
		hapusBuku();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

void tambahBuku() {
	system("cls");
	cout << "------------- TAMBAH BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (tidak boleh sama!) : ";
	string kode;
	getline(cin, kode);

	cout << "Judul                    : ";
	string judul;
	getline(cin, judul);

	cout << "Penulis                  : ";
	string penulis;
	getline(cin, penulis);

	cout << "Tahun terbit             : ";
	int tahunTerbit;
	cin >> tahunTerbit;

	cout << "Stok                     : ";
	int stok;
	cin >> stok;

	bukuVector.push_back({kode, judul, penulis, tahunTerbit, stok});
	daftarBuku();
}

void updateBuku() {
	system("cls");
	cout << "------------- UPDATE BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!) : ";
	string kode;
	getline(cin, kode);

	cout << "Judul                           : ";
	string judul;
	getline(cin, judul);

	cout << "Penulis                         : ";
	string penulis;
	getline(cin, penulis);

	cout << "Tahun terbit                    : ";
	int tahunTerbit;
	cin >> tahunTerbit;

	cout << "Stok                            : ";
	int stok;
	cin >> stok;

	for (auto iter = bukuVector.begin(); iter != bukuVector.end(); ++iter)
	{
		if (iter->kode == kode)
		{
			iter->judul = judul;
			iter->penulis = penulis;
			iter->tahunTerbit = tahunTerbit;
			iter->stok = stok;
			break;
		}
	}

	daftarBuku();
}

void hapusBuku() {
	system("cls");
	cout << "------------- HAPUS BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!): ";
	string kode;
	getline(cin, kode);

	for (auto iter = bukuVector.begin(); iter != bukuVector.end(); ++iter)
	{
		if (iter->kode == kode)
		{
			iter = bukuVector.erase(iter);
			break;
		}
	}

	daftarBuku();
}
