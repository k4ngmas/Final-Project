#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "Menu.h"
#include "GenerateFile.h"
#include "Globals.h"

using namespace std;

extern vector<Peminjaman> peminjamanVector;
extern struct TableFormatter tableFormatter;

void formatFileTableHeader(ofstream &peminjamanFile);
void formatFileTableChildRow(ofstream &peminjamanFile);
void generateFileMenuSwitch();

void generateFile(){
	system("cls");
	cout << "GENERATE FILE DATA PEMINJAMAN-PENGEMBALIAN" << endl << endl;

	string fileLocation = "data-peminjaman.txt";

	ofstream peminjamanFile;
	peminjamanFile.open(fileLocation);

	if (peminjamanFile.is_open())
	{
		cout << "Generating file..." << endl;
		formatFileTableHeader(peminjamanFile);
		formatFileTableChildRow(peminjamanFile);

		peminjamanFile.close();
		cout << "File generated at " << fileLocation << "!" << endl;
	}

	generateFileMenuSwitch();
}

void formatFileTableHeader(ofstream &peminjamanFile)
{
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

void formatFileTableChildRow(ofstream &peminjamanFile)
{
	int count = 1;
	for (auto &peminjaman : peminjamanVector)
	{
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

	if (!peminjamanVector.empty())
	{
		peminjamanFile << "+";
		peminjamanFile << left << setw(113) << setfill(tableFormatter.headerRowSeparator) << "";
		peminjamanFile << "+";
		peminjamanFile << endl;
	}
}

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