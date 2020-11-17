#pragma once
#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

#include <string>
#include <vector>

using namespace std;

// Global variables for Buku
extern struct Buku
{
	string kode;
	string judul;
	string penulis;
	int tahunTerbit;
};

extern vector <Buku> bukuVector{
	{"P01", "Clean Code", "Robert Cecil Martin", 2008},
	{"P02", "The Art Of Computer Programming", "Donald E. Knuth", 1968}
};

#endif