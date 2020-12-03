#include <iostream>
#include <string>

#include "Menu.h"
#include "DaftarAnggota.h"
#include "Globals.h"

using namespace std;

extern vector<Anggota> anggotaVector;

void tambahAnggota();
void updateAnggota();
void hapusAnggota();

void daftarAnggota() {
	system("cls");
	cout << "------------- DAFTAR ANGGOTA -------------" << endl;
	cout << endl;


	int count = 1;
	for (auto anggota : anggotaVector)
	{
		cout << count++ << ". " << anggota.kode << " - " << anggota.nama
			<< " (" << anggota.umur << ", " << anggota.alamat << ")" << endl;
	}

	cout << endl;
	cout << "--- Menu ---" << endl;
	cout << "1. Tambah anggota" << endl;
	cout << "2. Update anggota" << endl;
	cout << "3. Hapus angggota" << endl;
	cout << "9. Kembali ke menu utama" << endl << endl;

	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		tambahAnggota();
		break;
	case 2:
		updateAnggota();
		break;
	case 3:
		hapusAnggota();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

void tambahAnggota() {
	system("cls");
	cout << "------------- TAMBAH ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (tidak boleh sama!) : ";
	string kode;
	getline(cin, kode);

	cout << "Nama                     : ";
	string nama;
	getline(cin, nama);

	cout << "Umur                     : ";
	int umur;
	cin >> umur;

	cin.ignore();

	cout << "Alamat                   : ";
	string alamat;
	getline(cin, alamat);

	anggotaVector.push_back({ kode, nama, umur, alamat });
	daftarAnggota();
}

void updateAnggota() {
	system("cls");
	cout << "------------- UPDATE ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!) : ";
	string kode;
	getline(cin, kode);

	cout << "Nama                     : ";
	string nama;
	getline(cin, nama);

	cout << "Umur                     : ";
	int umur;
	cin >> umur;

	cin.ignore();

	cout << "Alamat                   : ";
	string alamat;
	getline(cin, alamat);

	for (auto iter = anggotaVector.begin(); iter != anggotaVector.end(); ++iter)
	{
		if (iter->kode == kode)
		{
			iter->nama = nama;
			iter->umur = umur;
			iter->alamat = alamat;
			break;
		}
	}

	daftarAnggota();
}

void hapusAnggota() {
	system("cls");
	cout << "------------- HAPUS ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!): ";
	string kode;
	getline(cin, kode);

	for (auto iter = anggotaVector.begin(); iter != anggotaVector.end(); ++iter)
	{
		if (iter->kode == kode)
		{
			iter = anggotaVector.erase(iter);
			break;
		}
	}

	daftarAnggota();
}
