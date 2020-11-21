#pragma once
#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

#include <string>
#include <vector>

using namespace std;

// Global variables for Buku
struct Buku
{
	string kode;
	string judul;
	string penulis;
	int tahunTerbit;
	int stok;
};

extern vector <Buku> bukuVector{
	{"P01", "Clean Code", "Robert Cecil Martin", 2008, 15},
	{"P02", "The Art Of Computer Programming", "Donald E. Knuth", 1968, 7}
};

#endif