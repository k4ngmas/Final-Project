#include <iostream>
#include <vector>

#include "Menu.h"
#include "PeminjamanPengembalian.h"
#include "Globals.h"

using namespace std;

extern vector<Peminjaman> peminjamanVector;

void featureMenu();
void tambahPeminjaman();
void returnPeminjaman();
void detailPeminjaman();

void daftarPeminjaman()
{
	system("cls");
	cout << "------------- DAFTAR PEMINJAMAN -------------" << endl;
	cout << endl;

	int count = 1;
	for (auto peminjaman : peminjamanVector)
	{
		cout << count++ << ". " << peminjaman.kode << " - " << peminjaman.kodeAnggota
			 << " - " << peminjaman.tanggalPeminjaman << " s/d "<< peminjaman.tanggalPengembalian;
	}

	featureMenu();
}

void featureMenu()
{
	cout << endl;
	cout << "--- Menu ---" << endl;
	cout << "1. Tambah peminjaman" << endl;
	cout << "2. Kembalikan peminjaman" << endl;
	cout << "3. Detail peminjaman" << endl;
	cout << "9. Kembali ke menu utama" << endl << endl;

	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		tambahPeminjaman();
		break;
	case 2:
		returnPeminjaman();
		break;
	case 3:
		detailPeminjaman();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

void tambahPeminjaman()
{
	system("cls");
	cout << "------------- TAMBAH PEMINJAMAN -------------" << endl;

	cout << "Kode (tidak boleh sama!) : ";
	string kode;
	cin >> kode;

	cout << "Kode Anggota             : ";
	string kodeAnggota;
	cin >> kodeAnggota;

	cout << "Tanggal Peminjaman       : ";
	string tanggalPeminjaman;
	cin >> tanggalPeminjaman;

	cout << "Tanggal Pengembalian     : ";
	string tanggalPengembalian;
	cin >> tanggalPengembalian;

	Peminjaman newPeminjaman;
	newPeminjaman.kode = kode;
	newPeminjaman.kodeAnggota = kodeAnggota;
	newPeminjaman.tanggalPeminjaman = tanggalPeminjaman;
	newPeminjaman.tanggalPengembalian = tanggalPengembalian;

	cout << endl;
	cout << "---- DETAIL BUKU ----" << endl;
	cout << "Berapa jenis buku yang ingin dipinjam : ";
	int jumlahJenisBuku;
	cin >> jumlahJenisBuku;

	for (int i = 0; i < jumlahJenisBuku; i++)
	{
		cout << endl;
		cout << "Kode Buku : ";
		string kodeBuku;
		cin >> kodeBuku;

		cout << "Jumlah    : ";
		int jumlahBuku;
		cin >> jumlahBuku;

		newPeminjaman.bukuPinjamanVector.push_back({ kodeBuku, jumlahBuku });
	}

	peminjamanVector.push_back(newPeminjaman);
	daftarPeminjaman();
}

void returnPeminjaman()
{

}

void detailPeminjaman()
{
	system("cls");
	cout << "------------- DETAIL PEMINJAMAN -------------" << endl;
	
	cout << "Kode : ";
	string kode; 
	cin >> kode;

	cout << endl;
	for (auto iter = peminjamanVector.begin(); iter != peminjamanVector.end(); ++iter)
	{
		if (iter->kode == kode)
		{
			cout << "Kode Peminjaman      : " << iter->kode << endl;
			cout << "Kode Anggota         : " << iter->kodeAnggota << endl;
			cout << "Tanggal Peminjaman   : " << iter->tanggalPeminjaman << endl;
			cout << "Tanggal Pengembalian : " << iter->tanggalPengembalian << endl;
			cout << "Status               : " << iter->status << endl;

			cout << endl;
			cout << "---- DETAIL BUKU PINJAMAN ----" << endl;

			for (auto bukuPinjaman : iter->bukuPinjamanVector)
			{
				cout << endl;
				cout << "Kode Buku : " << bukuPinjaman.kode << endl;
				cout << "Jumlah    : " << bukuPinjaman.jumlah << " buah" << endl;
			}

			break;
		}
	}

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