#include <iostream>
#include <string>
#include <sstream> 
#include <Windows.h>

#include "Menu.h"
#include "PeminjamanPengembalian.h"
#include "Globals.h"

using namespace std;

extern vector<Peminjaman> peminjamanVector;
extern vector<Buku> buku;
struct Peminjaman peminjaman;
struct BukuPinjaman bukuPinjaman;
struct Pengembalian {
	string kode;
	string tanggalPengembalian;
} pengembalian;

void peminjamanPengembalianMenu();
void insertPeminjaman();
void detailPeminjaman();
void returnPeminjaman();

Peminjaman insertPeminjamanForm();
Peminjaman insertBukuPinjamanForm(Peminjaman peminjaman);
string detailPeminjamanForm();
Pengembalian returnPeminjamanForm();
int payDendaForm(int denda);

bool insertToPeminjamanVector(Peminjaman peminjaman);
void decreaseBukuFromBukuVector(string kode);
void findPeminjamanFromVector(string kodePeminjaman);
bool returnPeminjamanFromVector(Pengembalian pengembalian);
void returnBukuPinjaman(vector<BukuPinjaman>& bukuPinjamanVector);
int countDenda(vector<BukuPinjaman>& bukuPinjamanVector, int daysBetween);
void payDenda(vector<BukuPinjaman>& bukuPinjamanVector, int daysBetween);
int getDaysBetweenDates(string firstDate, string secondDate);

void daftarPeminjaman()
{
	system("cls");
	cout << "------------- DAFTAR PEMINJAMAN -------------" << endl;
	cout << endl;

	int count = 1;
	for (auto peminjaman : peminjamanVector)
	{
		cout << count++ << ". " << peminjaman.kode << " - " << peminjaman.kodeAnggota
			 << " - " << peminjaman.tanggalPeminjaman << " s/d " << peminjaman.tanggalPengembalian 
			 << " - " << peminjaman.status << endl;
	}

	peminjamanPengembalianMenu();
}

void peminjamanPengembalianMenu()
{
	cout << endl;
	cout << "--- Menu ---" << endl;
	cout << "1. Tambah Peminjaman" << endl;
	cout << "2. Detail Peminjaman" << endl;
	cout << "3. pengembalian Buku" << endl;
	cout << "9. Kembali ke menu utama" << endl << endl;

	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		insertPeminjaman();
		break;
	case 2:
		detailPeminjaman();
		break;
	case 3:
		returnPeminjaman();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

void insertPeminjaman()
{
	Peminjaman peminjaman = insertPeminjamanForm();
	bool isInsertionSuccessful = insertToPeminjamanVector(peminjaman);

	cout << endl;
	if (isInsertionSuccessful)
	{
		cout << "Peminjaman berhasil ditambahkan!" << endl;
	}

	Sleep(500);
	daftarPeminjaman();
}

Peminjaman insertPeminjamanForm()
{
	system("cls");
	cout << "------------- TAMBAH PEMINJAMAN -------------" << endl;

	cout << "Kode (tidak boleh sama!)          : ";
	cin >> peminjaman.kode;

	cout << "Kode Anggota                      : ";
	cin >> peminjaman.kodeAnggota;

	cout << "Tanggal Peminjaman [yyyy-mm-dd]   : ";
	cin >> peminjaman.tanggalPeminjaman;

	cout << "Tanggal Pengembalian [yyyy-mm-dd] : ";
	cin >> peminjaman.tanggalPengembalian;

	Peminjaman peminjamanWithBuku = insertBukuPinjamanForm(peminjaman);
	return peminjamanWithBuku;
}

Peminjaman insertBukuPinjamanForm(Peminjaman peminjaman)
{
	cout << endl;
	cout << "---- DETAIL BUKU ----" << endl;
	cout << "Berapa jenis buku yang ingin dipinjam : ";
	int jumlahJenisBuku;
	cin >> jumlahJenisBuku;

	for (int i = 0; i < jumlahJenisBuku; i++)
	{
		cout << endl;
		cout << "Kode Buku : ";
		cin >> bukuPinjaman.kode;

		cout << "Jumlah    : ";
		cin >> bukuPinjaman.jumlah;

		peminjaman.bukuPinjamanVector.push_back(bukuPinjaman);
		decreaseBukuFromBukuVector(bukuPinjaman.kode);
	}

	return peminjaman;
}

void decreaseBukuFromBukuVector(string kode)
{
	auto buku = find_if(bukuVector.begin(), bukuVector.end(), [kode](const Buku& buku) {
		return buku.kode == kode;
	});

	if (buku != bukuVector.end())
	{
		buku->stok -= bukuPinjaman.jumlah;
	}
}

bool insertToPeminjamanVector(Peminjaman peminjaman)
{
	peminjamanVector.push_back(peminjaman);
	return true;
}

void detailPeminjaman()
{
	string kodePeminjaman = detailPeminjamanForm();
	findPeminjamanFromVector(kodePeminjaman);

	cout << endl << endl;
	cout << "Kembali ke menu peminjaman & pengembalian [y/n]: ";
	char menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 'y':
		daftarPeminjaman();
		break;
	case 'n':
		break;
	default:
		cout << "Input invalid";
		break;
	}
}

string detailPeminjamanForm()
{
	system("cls");
	cout << "------------- DETAIL PEMINJAMAN -------------" << endl;

	cout << "Kode Peminjaman      : ";
	string kode;
	cin >> kode;

	return kode;
}

void findPeminjamanFromVector(string kodePeminjaman)
{
	auto peminjaman = find_if(peminjamanVector.begin(), peminjamanVector.end(), [kodePeminjaman](const Peminjaman& peminjaman) {
		return peminjaman.kode == kodePeminjaman;
	});

	if (peminjaman != peminjamanVector.end())
	{
		cout << "Kode Anggota         : " << peminjaman->kodeAnggota << endl;
		cout << "Tanggal Peminjaman   : " << peminjaman->tanggalPeminjaman << endl;
		cout << "Tanggal Pengembalian : " << peminjaman->tanggalPengembalian << endl;
		cout << "Status               : " << peminjaman->status << endl;

		cout << endl;
		cout << "---- DETAIL BUKU PINJAMAN ----" << endl;
		for (auto bukuPinjaman : peminjaman->bukuPinjamanVector)
		{
			cout << endl;
			cout << "Kode Buku : " << bukuPinjaman.kode << endl;
			cout << "Jumlah    : " << bukuPinjaman.jumlah << " buah" << endl;
		}

	}
	else
	{
		cout << "Tidak dapat memuat detail peminjaman!" << endl;
		cout << "Peminjaman dengan kode tersebut tidak ditemukan!" << endl;
	}
}

void returnPeminjaman()
{
	Pengembalian pengembalian = returnPeminjamanForm();
	bool isReturnedSuccessfully = returnPeminjamanFromVector(pengembalian);

	cout << endl;
	if (isReturnedSuccessfully)
	{
		cout << "Peminjaman telah dikembalikan!" << endl;
	}
	else
	{
		cout << "Peminjaman tidak dapat dikembalikan!" << endl;
		cout << "Peminjaman dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(500);
	daftarPeminjaman();
}

Pengembalian returnPeminjamanForm()
{
	system("cls");
	cout << "------------- KEMBALIKAN PEMINJAMAN -------------" << endl;

	cout << "Kode (harus ada di tabel data!)        : ";
	cin >> pengembalian.kode;

	cout << "Tanggal pengembalian [yyyy-mm-dd]      : ";
	cin >> pengembalian.tanggalPengembalian;

	return pengembalian;
}

bool returnPeminjamanFromVector(Pengembalian pengembalian)
{
	auto peminjaman = find_if(peminjamanVector.begin(), peminjamanVector.end(), [kode = pengembalian.kode](const Peminjaman& peminjaman) {
		return peminjaman.kode == kode;
	});

	cout << endl;
	if (peminjaman != peminjamanVector.end())
	{
		peminjaman->status = "Sudah dikembalikan";
		returnBukuPinjaman(peminjaman->bukuPinjamanVector);

		int daysBetween = getDaysBetweenDates(peminjaman->tanggalPengembalian, pengembalian.tanggalPengembalian);
		if (daysBetween > 0)
		{
			payDenda(peminjaman->bukuPinjamanVector, daysBetween);
			peminjaman->dendaTelat = countDenda(peminjaman->bukuPinjamanVector, daysBetween);
		}

		return true;
	}
	else
	{
		return false;
	}
}

void returnBukuPinjaman(vector<BukuPinjaman> &bukuPinjamanVector)
{
	for (auto bukuPinjaman : bukuPinjamanVector)
	{
		auto buku = find_if(bukuVector.begin(), bukuVector.end(), [kode = bukuPinjaman.kode](const Buku& buku) {
			return buku.kode == kode;
		});

		if (buku != bukuVector.end())
		{
			buku->stok += bukuPinjaman.jumlah;
		}
	}
}

int payDendaForm(int denda)
{
	cout << "---- Bayar Denda Telat ----" << endl;
	cout << "Total denda : " << denda << endl;
	cout << "Uang        : ";
	int bayar;
	cin >> bayar;

	return bayar;
}

void payDenda(vector<BukuPinjaman> &bukuPinjamanVector, int daysBetween)
{
	int denda = countDenda(bukuPinjamanVector, daysBetween);
	int bayar = payDendaForm(denda);

	if (bayar > denda)
	{
		cout << "Kembalian   : " << (bayar - denda) << endl;
	}
}

int countDenda(vector<BukuPinjaman> &bukuPinjamanVector, int daysBetween)
{
	int totalBuku = 0;
	for (auto bukuPinjaman : bukuPinjamanVector)
	{
		totalBuku += bukuPinjaman.jumlah;
	}

	return 5000 * totalBuku * daysBetween;
}

int getDaysBetweenDates(string firstDate, string secondDate)
{
	stringstream ss(firstDate + "-" + secondDate);
	int year, month, day;
	char hyphen;

	// Parse the first date into seconds 
	ss >> year >> hyphen >> month >> hyphen >> day;
	struct tm starttm = { 0, 0, 0, day, month - 1, year - 1900 };
	time_t start = mktime(&starttm);

	// Parse the second date into seconds 
	ss >> hyphen >> year >> hyphen >> month >> hyphen >> day;
	struct tm endtm = { 0, 0, 0, day, month - 1, year - 1900 };
	time_t end = mktime(&endtm);

	// Find out the difference and divide it 
	// by 86400 to get the number of days 
	return (end - start) / 86400;
}

