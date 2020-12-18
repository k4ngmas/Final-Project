#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>

#include "Menu.h"
#include "DaftarAnggota.h"
#include "Globals.h"

using namespace std;

extern struct Anggota anggota;
extern vector<Anggota> anggotaVector;
extern struct TableFormatter tableFormatter;

void formatAnggotaTable();
void formatAnggotaTableHeader();
void formatAnggotaTableChildRow();

void anggotaMenu();
void anggotaMenuSwitch();
void insertAnggota();
void updateAnggota();
void deleteAnggota();

Anggota insertAnggotaForm();
Anggota updateAnggotaForm();
string deleteAnggotaForm();

bool insertToAnggotaVector(Anggota anggota);
bool updateAnggotaVector(Anggota anggota);
bool deleteFromAnggotaVector(string kodeAnggota);

void daftarAnggota() {
	system("cls");
	formatAnggotaTable();
	anggotaMenu();
}

void formatAnggotaTable()
{
	formatAnggotaTableHeader();
	formatAnggotaTableChildRow();
}

void formatAnggotaTableHeader()
{
	cout << "+";
	cout << left << setw(89) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR ANGGOTA -";
	cout << "+";
	cout << endl;

	cout << "|  ";
	cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << "Nama";
	cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << "Alamat";
	cout << "  |" << endl;

	cout << "+";
	cout << left << setw(89) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

void formatAnggotaTableChildRow()
{
	int count = 1;
	for (auto anggota : anggotaVector)
	{
		cout << "|  ";
		cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << count++;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << anggota.kode;
		cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << anggota.nama;
		cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << anggota.alamat;
		cout << "  |" << endl;
	}

	cout << "+";
	cout << left << setw(89) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

void anggotaMenu()
{
	cout << endl;
	cout << "+- MENU ---------------------+" << endl;
	cout << "|  1. Tambah anggota         |" << endl;
	cout << "|  2. Update anggota         |" << endl;
	cout << "|  3. Hapus anggota          |" << endl;
	cout << "|  9. Kembali ke menu utama  |" << endl;
	cout << "+----------------------------+" << endl << endl;

	anggotaMenuSwitch();
}

void anggotaMenuSwitch()
{
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
		deleteAnggota();
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
	bool isInsertionSuccessful = insertToAnggotaVector(anggota);

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

bool insertToAnggotaVector(Anggota anggota)
{
	anggotaVector.push_back(anggota);
	return true;
}

void updateAnggota() 
{
	Anggota anggota = updateAnggotaForm();
	bool isUpdateSuccessful = updateAnggotaVector(anggota);

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

bool updateAnggotaVector(Anggota anggota)
{
	auto updatedAnggota = find_if(anggotaVector.begin(), anggotaVector.end(), [kode = anggota.kode](const Anggota& anggota) { 
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

void deleteAnggota() 
{
	string kodeAnggota = deleteAnggotaForm();
	bool isDeletionSuccessful = deleteFromAnggotaVector(kodeAnggota);

	cout << endl;
	if (isDeletionSuccessful)
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

string deleteAnggotaForm()
{
	system("cls");
	cout << "------------- HAPUS ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!): ";
	string kode;
	getline(cin, kode);

	return kode;
}

bool deleteFromAnggotaVector(string kodeAnggota)
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