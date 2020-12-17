#include <vector>

#include "Globals.h"
#include "GlobalsDefinitions.h"

using namespace std;

struct Buku buku;
struct Anggota anggota;

vector<Buku> bukuVector;
vector<Anggota> anggotaVector;
vector<Peminjaman> peminjamanVector;

void defineBuku();
void defineAnggota();

void defineAll() {
	defineBuku();
	defineAnggota();
}

void defineBuku() {
	if (bukuVector.empty())
	{
		bukuVector.push_back({ "PRG001", "Clean Code", "Robert Cecil Martin", 2008, 15 });
		bukuVector.push_back({ "PRG002", "The Art Of Computer Programming", "Donald E. Knuth", 1968, 21 });
	}
}

void defineAnggota() {
	if (anggotaVector.empty())
	{
		anggotaVector.push_back({ "ANG001", "Rafael Shah Johan", 18, "Jakarta Pusat" });
	}
}