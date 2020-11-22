#include <vector>

#include "Globals.h"
#include "GlobalsDefinitions.h"

using namespace std;

vector<Buku> bukuVector;
vector<Anggota> anggotaVector;

void defineBuku();
void defineAnggota();

void defineAll() {
	defineBuku();
	defineAnggota();
}

void defineBuku() {
	if (bukuVector.empty())
	{
		bukuVector.push_back({ "P01", "Clean Code", "Robert Cecil Martin", 2008, 15 });
		bukuVector.push_back({ "P02", "The Art Of Computer Programming", "Donald E. Knuth", 1968, 7 });
	}
}

void defineAnggota() {
	if (anggotaVector.empty())
	{
		anggotaVector.push_back({ "ANG001", "Rafael Shah Johan", 18, "Jakarta Pusat" });
	}
}