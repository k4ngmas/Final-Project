#include <iostream>
#include <string>
#include <Windows.h>

#include "Menu.h"
#include "DaftarAnggota.h"
#include "Globals.h"

using namespace std;

extern struct Anggota anggota;
extern vector<Anggota> anggotaVector;

void localMenu();
void insertAnggota();
void updateAnggota();
void eraseAnggota();
Anggota insertAnggotaForm();
Anggota updateAnggotaForm();
string eraseAnggotaForm();
bool insert(Anggota anggota);
bool update(Anggota anggota);
bool erase(string kodeAnggota);

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

	localMenu();
}

void localMenu()
{
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
		insertAnggota();
		break;
	case 2:
		updateAnggota();
		break;
	case 3:
		eraseAnggota();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

void insertAnggota() 
{
	Anggota anggota = insertAnggotaForm();
	bool isInsertionSuccessful = insert(anggota);

	if (isInsertionSuccessful)
	{
		cout << "Buku berhasil ditambahkan!" << endl;
	}
	
	Sleep(500);
	daftarAnggota();
}

Anggota insertAnggotaForm()
{
	system("cls");
	cout << "------------- TAMBAH ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (tidak boleh sama!) : ";
	getline(cin, anggota.kode);

	cout << "Nama                     : ";
	getline(cin, anggota.nama);

	cout << "Umur                     : ";
	cin >> anggota.umur;

	cin.ignore();

	cout << "Alamat                   : ";
	getline(cin, anggota.alamat);

	return anggota;
}

bool insert(Anggota anggota)
{
	anggotaVector.push_back({ anggota.kode, anggota.nama, anggota.umur, anggota.alamat });
	return true;
}

void updateAnggota() 
{
	Anggota anggota = updateAnggotaForm();
	bool isUpdateSuccessful = update(anggota);

	cout << endl;
	if (isUpdateSuccessful)
	{
		cout << "Anggota berhasil diupdate!" << endl;
	}
	else
	{
		cout << "Anggota gagal diupdate!" << endl;
		cout << "Anggota dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(500);
	daftarAnggota();
}

Anggota updateAnggotaForm()
{
	system("cls");
	cout << "------------- UPDATE ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!) : ";
	getline(cin, anggota.kode);

	cout << "Nama                            : ";
	getline(cin, anggota.nama);

	cout << "Umur                            : ";
	cin >> anggota.umur;

	cin.ignore();

	cout << "Alamat                          : ";
	getline(cin, anggota.alamat);

	return anggota;
}

bool update(Anggota anggota)
{
	string kode = anggota.kode;
	auto updatedAnggota = find_if(anggotaVector.begin(), anggotaVector.end(), [kode](const Anggota& anggota) { 
			return anggota.kode == kode; 
	});

	if (updatedAnggota != anggotaVector.end())
	{
		updatedAnggota->nama = anggota.nama;
		updatedAnggota->umur = anggota.umur;
		updatedAnggota->alamat = anggota.alamat;

		return true;
	}

	return false;
}

void eraseAnggota() 
{
	string kodeAnggota = eraseAnggotaForm();
	bool isErasionSuccessful = erase(kodeAnggota);

	cout << endl;
	if (isErasionSuccessful)
	{
		cout << "Buku berhasil dihapus!" << endl;
	}
	else
	{
		cout << "Buku gagal dihapus!" << endl;
		cout << "Buku dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(500);
	daftarAnggota();
}

string eraseAnggotaForm()
{
	system("cls");
	cout << "------------- HAPUS ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!): ";
	string kode;
	getline(cin, kode);

	return kode;
}

bool erase(string kodeAnggota)
{
	auto erasedAnggota = remove_if(anggotaVector.begin(), anggotaVector.end(), [kodeAnggota](const Anggota& anggota) {
		return anggota.kode == kodeAnggota;
	});

	if (erasedAnggota != anggotaVector.end())
	{
		anggotaVector.erase(erasedAnggota, anggotaVector.end());
		return true;
	}

	return false;
}