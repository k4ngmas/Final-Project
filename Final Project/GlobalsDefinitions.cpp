#include <vector> // agar dapat menggunakan vector

#include "Globals.h" // agar dapat menggunakan semua global variables 
#include "GlobalsDefinitions.h" // header file penghubung antara Main.cpp dengan File ini

using namespace std;

// inisialisasi semua global variables yang didapat dari Globals.h
// tidak menggunakan kata extern didepannya karena disini adalah tempat inisialisasi nilai pertama kali
struct Buku buku;
struct Anggota anggota;
struct TableFormatter tableFormatter;

vector<Buku> bukuVector;
vector<Anggota> anggotaVector;
vector<Peminjaman> peminjamanVector;

// functions harus tetap di tuliskan diatas pertama kali
// kemudian function tersebut baru diberi detail di bawah
// ini merupakan aturan dari C++
void defineBuku();
void defineAnggota();

// main function pada file ini
void defineAll() 
{
	defineBuku();
	defineAnggota();
}

// mengisikan vector buku
void defineBuku() 
{
	// jika vector kosong maka proses pengisian awal akan dilakukan
	if (bukuVector.empty())
	{
		bukuVector.push_back({ "PRG001", "Clean Code", "Robert Cecil Martin", 2008, 15 });
		bukuVector.push_back({ "PRG002", "The Art Of Computer Programming", "Donald E. Knuth", 1968, 21 });
	}
}

// mengisikan vector anggota
void defineAnggota() 
{
	// jika vector kosong maka proses pengisian awal akan dilakukan
	if (anggotaVector.empty())
	{
		anggotaVector.push_back({ "ANG001", "Rafael Shah Johan", 18, "Kota Adm. Jakarta Pusat, DKI Jakarta" });
	}
}