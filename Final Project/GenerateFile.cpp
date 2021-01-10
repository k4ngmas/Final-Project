#include <iostream> // untuk cout cin
#include <fstream> // untuk keperluan yang berkaitan dengan filesystem seperti ofstream 
#include <iomanip> // untuk menggunakan setw(), setfill() dan left
#include <string> // agar bisa menggunakan tipe data string 

#include "Menu.h" // penghubung agar function mainMenu() bisa dipanggil di file ini
#include "GenerateFile.h" // header file penghubung antara Main Menu dan Fitur Generate File
#include "Globals.h" // agar bisa menggunakan struct dan vector peminjaman yg tersimpan sebagai global variable

using namespace std;

// struct adalah semacam tipe data yang dapat di custom, biasanya berperan sebagai object
// vector adalah semacam array yang dinamis yang lebih fleksibel daripada array, 
// fleksibel dalam artian isi elemen dalam vector bisa bermacam-macam tidak perlu ditentukan dengan const
// extern menandakan bahwa variable berikut adalah variable yang sudah didefinisikan di file lain
// dalam kata lain, ini adalah penanda bahwa variable di bawah ini merupakan global variable
extern vector<Peminjaman> peminjamanVector;
extern struct TableFormatter tableFormatter;
extern vector<Anggota> anggotaVector;
extern vector<Buku> bukuVector;

string generateFileForm();
bool findPeminjamanFromVector(string kodePeminjaman, ofstream& peminjamanFile);
string findAnggotaFromKode(string kodeAnggota);
void formatDetailPeminjamanTable(vector<BukuPinjaman>& bukuPinjamanVector, ofstream& peminjamanFile);
void formatDetailPeminjamanTableHeader(ofstream& peminjamanFile);
void formatDetailPeminjamanTableChildRow(vector<BukuPinjaman>& bukuPinjamanVector, ofstream& peminjamanFile);
void generateFileMenuSwitch();

// main function untuk fitur generate file
void generateFile(){
	system("cls");
	cout << "GENERATE FILE DETAIL PEMINJAMAN" << endl << endl;

	string kodePeminjaman = generateFileForm();

	ofstream peminjamanFile;
	peminjamanFile.open("DATA-PEMINJAMAN-" + kodePeminjaman + ".txt");

	if (peminjamanFile.is_open())
	{
		bool isFileGeneratedSuccessfully = findPeminjamanFromVector(kodePeminjaman, peminjamanFile);
		if (isFileGeneratedSuccessfully)
		{
			cout << endl;
			cout << "Berhasil Generate File!" << endl;
			cout << "Silahkan cek folder anda!" << endl;
		}
		else
		{
			cout << endl;
			cout << "Gagal generate file!" << endl;
			cout << "Peminjaman dengan kode tersebut tidak ditemukan!" << endl;
		}
	}
	else
	{
		cout << endl;
		cout << "Terjadi eror saat generate file!" << endl;
	}

	generateFileMenuSwitch();
}

string generateFileForm()
{
	cout << "Kode peminjaman : ";
	string kodePeminjaman;
	cin >> kodePeminjaman;

	return kodePeminjaman;
}

// format header tabel data peminjaman  
// peminjamanFile ditambahi tanda & didepannya
// karena jika tidak ditambahi tanda & maka parameter tidak akan diterima
// dan akan menyebabkan eror
bool findPeminjamanFromVector(string kodePeminjaman, ofstream &peminjamanFile)
{
	// cek jika peminjaman dengan kode yang telah di input ada atau tidak
	auto peminjaman = find_if(peminjamanVector.begin(), peminjamanVector.end(), [kodePeminjaman](const Peminjaman& peminjaman) {
		return peminjaman.kode == kodePeminjaman;
	});

	// jika peminjaman dengan kode tersebut ditemukan maka tampilan detail akan muncul
	if (peminjaman != peminjamanVector.end())
	{
		peminjamanFile << "Nama Anggota         : " << findAnggotaFromKode(peminjaman->kodeAnggota) << endl;
		peminjamanFile << "Tanggal Peminjaman   : " << peminjaman->tanggalPeminjaman << endl;
		peminjamanFile << "Jadwal Pengembalian  : " << peminjaman->jadwalPengembalian << endl;
		peminjamanFile << "Tanggal Kembali      : " << peminjaman->tanggalDikembalikan << endl;
		peminjamanFile << "Status               : " << peminjaman->status << endl;
		peminjamanFile << "Denda                : " << peminjaman->dendaTelat << endl;

		formatDetailPeminjamanTable(peminjaman->bukuPinjamanVector, peminjamanFile);

		return true;
	}

	return false;
}

// function untuk mencari anggota dari kode anggota
string findAnggotaFromKode(string kodeAnggota)
{
	// cek jika anggota dengan kode anggota yang didapat dari detail ada atau tidak
	auto anggota = find_if(anggotaVector.begin(), anggotaVector.end(), [kodeAnggota](const Anggota& anggota) {
		return anggota.kode == kodeAnggota;
	});

	// jika ada maka function akan me return nama anggota
	if (anggota != anggotaVector.end())
	{
		return anggota->nama;
	}
}

// format tampilan tabel buku pada detail peminjaman secara keseluruhan
void formatDetailPeminjamanTable(vector<BukuPinjaman> &bukuPinjamanVector, ofstream &peminjamanFile)
{
	peminjamanFile << endl;
	formatDetailPeminjamanTableHeader(peminjamanFile);
	formatDetailPeminjamanTableChildRow(bukuPinjamanVector, peminjamanFile);
}

// format header tabel buku pada detail peminjaman
void formatDetailPeminjamanTableHeader(ofstream &peminjamanFile)
{
	peminjamanFile << "+";
	peminjamanFile << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR BUKU PINJAMAN -";
	peminjamanFile << "+";
	peminjamanFile << endl;

	peminjamanFile << "|  ";
	peminjamanFile << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	peminjamanFile << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << "Judul";
	peminjamanFile << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << "Penulis";
	peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Terbit";
	peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Jumlah";
	peminjamanFile << "  |" << endl;

	peminjamanFile << "+";
	peminjamanFile << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	peminjamanFile << "+";
	peminjamanFile << endl;
}

// format kolom isian tabel buku pada detail peminjaman
void formatDetailPeminjamanTableChildRow(vector<BukuPinjaman> &bukuPinjamanVector, ofstream &peminjamanFile)
{
	int counter = 1;
	for (auto& bukuPinjaman : bukuPinjamanVector)
	{
		auto buku = find_if(bukuVector.begin(), bukuVector.end(), [kode = bukuPinjaman.kode](const Buku& buku) {
			return buku.kode == kode;
		});

		if (buku != bukuVector.end())
		{
			peminjamanFile << "|  ";
			peminjamanFile << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << counter++;
			peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku->kode;
			peminjamanFile << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << buku->judul;
			peminjamanFile << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << buku->penulis;
			peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku->tahunTerbit;
			peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << bukuPinjaman.jumlah;
			peminjamanFile << "  |" << endl;
		}
	}

	peminjamanFile << "+";
	peminjamanFile << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	peminjamanFile << "+";
	peminjamanFile << endl;
}

// switch case untuk menu kembali ke main menu
void generateFileMenuSwitch()
{
	cout << endl;
	cout << "Kembali ke halaman utama [y/n]: ";
	char menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 'y':
		mainMenu();
		break;
	case 'n':
		break;
	default:
		cout << "Input invalid";
		break;
	}
}