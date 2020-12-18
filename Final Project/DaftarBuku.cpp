#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>

#include "Menu.h"
#include "DaftarBuku.h"
#include "Globals.h"

using namespace std;

extern struct Buku buku;
extern vector<Buku> bukuVector;
extern struct TableFormatter tableFormatter;

void formatBukuTable();
void formatBukuTableHeader();
void formatBukuTableChildRow();

void bukuMenu();
void bukuMenuSwitch();
void insertBuku();
void updateBuku();
void deleteBuku();

Buku insertBukuForm();
Buku updateBukuForm();
string deleteBukuForm();

bool insertToBukuVector(Buku buku);
bool updateBukuVector(Buku buku);
bool deleteFromBukuVector(string kodeBuku);

void daftarBuku()
{	
	system("cls");	
	formatBukuTable();
	bukuMenu();
}

void formatBukuTable()
{
	formatBukuTableHeader();
	formatBukuTableChildRow();
}

void formatBukuTableHeader()
{
	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR BUKU -";
	cout << "+";
	cout << endl;

	cout << "|  ";
	cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << "Judul";
	cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << "Penulis";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Terbit";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Stok";
	cout << "  |" << endl;

	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

void formatBukuTableChildRow()
{
	int count = 1;
	for (auto buku : bukuVector)
	{
		cout << "|  ";
		cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << count++;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku.kode;
		cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << buku.judul;
		cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << buku.penulis;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku.tahunTerbit;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku.stok;
		cout << "  |" << endl;
	}

	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

void bukuMenu()
{
	cout << endl;
	cout << "+- MENU ---------------------+" << endl;
	cout << "|  1. Tambah buku            |" << endl;
	cout << "|  2. Update buku            |" << endl;
	cout << "|  3. Hapus buku             |" << endl;
	cout << "|  9. Kembali ke menu utama  |" << endl;
	cout << "+----------------------------+" << endl << endl;
	
	bukuMenuSwitch();
}

void bukuMenuSwitch()
{
	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		insertBuku();
		break;
	case 2:
		updateBuku();
		break;
	case 3:
		deleteBuku();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

void insertBuku() 
{
	Buku buku = insertBukuForm();
	bool isInsertionSuccessful = insertToBukuVector(buku);
	
	cout << endl;
	if (isInsertionSuccessful)
	{
		cout << "Buku berhasil ditambahkan!" << endl;
	}

	Sleep(500);
	daftarBuku();
}

Buku insertBukuForm()
{
	system("cls");
	cout << "------------- TAMBAH BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (tidak boleh sama!) : ";
	getline(cin, buku.kode);

	cout << "Judul                    : ";
	getline(cin, buku.judul);

	cout << "Penulis                  : ";
	getline(cin, buku.penulis);

	cout << "Tahun terbit             : ";
	cin >> buku.tahunTerbit;

	cout << "Stok                     : ";
	cin >> buku.stok;

	return buku;
}

bool insertToBukuVector(Buku buku)
{
	bukuVector.push_back(buku);
	return true;
}

void updateBuku() 
{
	Buku buku = updateBukuForm();
	bool isUpdateSuccessful = updateBukuVector(buku);

	cout << endl;
	if (isUpdateSuccessful)
	{
		cout << "Buku berhasil diupdate!" << endl;
	}
	else
	{
		cout << "Buku gagal diupdate!" << endl;
		cout << "Buku dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(500);
	daftarBuku();
}

Buku updateBukuForm()
{
	system("cls");
	cout << "------------- UPDATE BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!) : ";
	getline(cin, buku.kode);

	cout << "Judul                           : ";
	getline(cin, buku.judul);

	cout << "Penulis                         : ";
	getline(cin, buku.penulis);

	cout << "Tahun terbit                    : ";
	cin >> buku.tahunTerbit;

	cout << "Stok                            : ";
	cin >> buku.stok;

	return buku;
}

bool updateBukuVector(Buku buku)
{
	auto updatedBuku = find_if(bukuVector.begin(), bukuVector.end(), [kode = buku.kode](const Buku& buku) { 
		return buku.kode == kode; 
	});

	if (updatedBuku != bukuVector.end())
	{
		updatedBuku->judul = buku.judul;
		updatedBuku->penulis = buku.penulis;
		updatedBuku->tahunTerbit = buku.tahunTerbit;
		updatedBuku->stok = buku.stok;

		return true;
	}

	return false;
}

void deleteBuku() 
{
	string kodeBuku = deleteBukuForm();
	bool isDeletionSuccessful = deleteFromBukuVector(kodeBuku);

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
	daftarBuku();
}

string deleteBukuForm()
{
	system("cls");
	cout << "------------- HAPUS BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!): ";
	string kode;
	getline(cin, kode);

	return kode;
}

bool deleteFromBukuVector(string kodeBuku)
{
	auto deletedBuku = remove_if(bukuVector.begin(), bukuVector.end(), [kodeBuku](const Buku& buku) { 
		return buku.kode == kodeBuku; 
	});

	if (deletedBuku != bukuVector.end())
	{
		bukuVector.erase(deletedBuku, bukuVector.end());
		return true;
	}
	
	return false;
}