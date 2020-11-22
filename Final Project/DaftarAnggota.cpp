#include <iostream>
#include <string>

#include "Menu.h"
#include "DaftarAnggota.h"
#include "Globals.h"

using namespace std;

vector<Anggota> anggotaVector;

void initialAnggotaData() {
	if (anggotaVector.empty())
	{
		anggotaVector.push_back({ "ANG001", "Rafael Shah Johan", 18, "Jakarta Pusat" });
	}
}


void daftarAnggota() {
	initialAnggotaData();

	// lanjutkan disini disamakan dengan daftarBuku.cpp
}

void tambahAnggota() {

}

void updateAnggota() {

}

void hapusAnggota() {

}
