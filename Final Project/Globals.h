#pragma once
#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

#include <string>
#include <vector>

// Global variables for Buku
extern struct Buku
{
	std::string kode;
	std::string judul;
	std::string penulis;
	int tahunTerbit;
	int stok;
};

extern std::vector<Buku> bukuVector;

// Global variables for Anggota
extern struct Anggota
{
	std::string kode;
	std::string nama;
	int umur;
	std::string alamat;
};

extern std::vector<Anggota> anggotaVector;

// Global variables for Peminjaman Pengembalian
struct BukuPinjaman
{
	std::string kode;
	int jumlah;
};

struct Peminjaman
{
	std::string kode;
	std::string kodeAnggota;
	std::string tanggalPeminjaman;
	std::string tanggalPengembalian;
	std::string status = "Dipinjamkan";
	int totalDenda = 0;
	std::vector<BukuPinjaman> bukuPinjamanVector;
};

extern std::vector<Peminjaman> peminjamanVector;
#endif
