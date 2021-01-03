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

void formatFileTableHeader(ofstream &peminjamanFile);
void formatFileTableChildRow(ofstream &peminjamanFile);
void generateFileMenuSwitch();

// main function untuk fitur generate file
void generateFile(){
	system("cls");
	cout << "GENERATE FILE DATA PEMINJAMAN-PENGEMBALIAN" << endl << endl;

	string fileName = "data-peminjaman.txt";

	// deklarasi output stream untuk file
	ofstream peminjamanFile;
	// open output stream agar kita bisa bekerja dengan file tersebut
	peminjamanFile.open(fileName);

	// cek jika proses open berhasil
	if (peminjamanFile.is_open())
	{
		cout << "Generating file..." << endl;
		formatFileTableHeader(peminjamanFile);
		formatFileTableChildRow(peminjamanFile);

		peminjamanFile.close();
		cout << "File generated at " << fileName << "!" << endl;
	}

	generateFileMenuSwitch();
}

// format header tabel data peminjaman  
// peminjamanFile ditambahi tanda & didepannya
// karena jika tidak ditambahi tanda & maka parameter tidak akan diterima
// dan akan menyebabkan eror
void formatFileTableHeader(ofstream &peminjamanFile)
{
	// left untuk align text ke kiri
	// setw untuk menentukan jumlah karakter maksimal dalam 1 kali pemanggilan cout
	// setfill untuk menambahkan karakter sebagai pengganti 
	// pengganti ini akan mengisi ruang kosong yang tersisa jika string tidak mencapai batas maksimal
	peminjamanFile << "+";
	peminjamanFile << left << setw(113) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR PEMINJAMAN -";
	peminjamanFile << "+";
	peminjamanFile << endl;

	peminjamanFile << "|  ";
	peminjamanFile << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Anggota";
	peminjamanFile << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << "Tanggal pinjam";
	peminjamanFile << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << "Jadwal kembali";
	peminjamanFile << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << "Tanggal kembali";
	peminjamanFile << left << setw(tableFormatter.statusColumnLength) << setfill(tableFormatter.columnSeparator) << "Status";
	peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Denda";
	peminjamanFile << "  |" << endl;

	peminjamanFile << "+";
	peminjamanFile << left << setw(113) << setfill(tableFormatter.headerRowSeparator) << "";
	peminjamanFile << "+";
	peminjamanFile << endl;
}

// format untuk kolom isian daftar anggota
void formatFileTableChildRow(ofstream &peminjamanFile)
{
	int count = 1;

	// looping untuk mengakses value bukuVector
	// menggunakan tanda & didepan variable agar variable itu terisi oleh reference
	// kenapa menggunakan reference? agar di memori tidak terjadi duplikasi data vector
	for (auto &peminjaman : peminjamanVector)
	{
		// left untuk align text ke kiri
		// setw untuk menentukan jumlah karakter maksimal dalam 1 kali pemanggilan cout
		// setfill untuk menambahkan karakter sebagai pengganti 
		// pengganti ini akan mengisi ruang kosong yang tersisa jika string tidak mencapai batas maksimal
		peminjamanFile << "|  ";
		peminjamanFile << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << count++;
		peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.kode;
		peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.kodeAnggota;
		peminjamanFile << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.tanggalPeminjaman;
		peminjamanFile << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.jadwalPengembalian;
		peminjamanFile << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.tanggalDikembalikan;
		peminjamanFile << left << setw(tableFormatter.statusColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.status;
		peminjamanFile << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.dendaTelat;
		peminjamanFile << "  |" << endl;
	}

	// jika vector kosong maka pembatas bawah tidak akan dimunculkan
	// biar rapi
	if (!peminjamanVector.empty())
	{
		peminjamanFile << "+";
		peminjamanFile << left << setw(113) << setfill(tableFormatter.headerRowSeparator) << "";
		peminjamanFile << "+";
		peminjamanFile << endl;
	}
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