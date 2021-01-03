#pragma once
#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

#include <string> // include agar dapat menggunakan tipe data string
#include <vector> // include agar dapat menggunakan tipe data vector

// Global table formatter
extern struct TableFormatter
{
	int counterColumnLength = 5;
	int stringColumnLength = 40;
	int nameColumnLength = 30;
	int numColumnLength = 10;
	int dateColumnLength = 18;
	int statusColumnLength = 20;
	char columnSeparator = ' ';
	char headerRowSeparator = '-';
};

// Global variables for Buku
extern struct Buku
{
	std::string kode;
	std::string judul;
	std::string penulis;
	int tahunTerbit = 0;
	int stok = 0;
};

extern std::vector<Buku> bukuVector;

// Global variables for Anggota
extern struct Anggota
{
	std::string kode;
	std::string nama;
	int umur = 0;
	std::string alamat;
};

extern std::vector<Anggota> anggotaVector;

// Global variables for Peminjaman Pengembalian
struct BukuPinjaman
{
	std::string kode;
	int jumlah = 0;
};

struct Peminjaman
{
	std::string kode;
	std::string kodeAnggota;
	std::string tanggalPeminjaman;
	std::string jadwalPengembalian;
	std::string tanggalDikembalikan = "-";
	std::string status = "Dipinjamkan";
	std::vector<BukuPinjaman> bukuPinjamanVector;
	int dendaTelat = 0;
};

extern std::vector<Peminjaman> peminjamanVector;
#endif
