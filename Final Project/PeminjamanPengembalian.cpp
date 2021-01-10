#include <iostream> // agar dapat menggunakan cout dan cin
#include <string> // agar dapat menggunakan tipe data string
#include <sstream> // agar dapat menggunakan stringstream()
#include <Windows.h> // agar dapat menggunakan function Sleep()
#include <iomanip> // agar dapat menggunakan left, setw() dan setfill()

#include "Menu.h" // penghubung agar function mainMenu() bisa dipanggil di file ini
#include "PeminjamanPengembalian.h" // header file penghubung antara Main Menu dan Fitur PeminjamanPengembalian
#include "Globals.h" // agar bisa menggunakan struct dan vector buku, anggota dan peminjaman yg tersimpan sebagai global variable

using namespace std;

// struct adalah semacam tipe data yang dapat di custom, biasanya berperan sebagai object
// vector adalah semacam array yang dinamis yang lebih fleksibel daripada array, 
// fleksibel dalam artian isi elemen dalam vector bisa bermacam-macam tidak perlu ditentukan dengan const
// extern menandakan bahwa variable berikut adalah variable yang sudah didefinisikan di file lain
// dalam kata lain, ini adalah penanda bahwa variable di bawah ini merupakan global variable
extern vector<Peminjaman> peminjamanVector;
extern vector<Buku> bukuVector;
extern vector<Anggota> anggotaVector;

extern struct TableFormatter tableFormatter;
struct Peminjaman peminjaman;
struct BukuPinjaman bukuPinjaman;

// struct untuk pengisian form pengembalian
struct Pengembalian {
	string kode;
	string tanggalPengembalian;
} pengembalian;

// functions harus tetap di tuliskan diatas pertama kali
// kemudian function tersebut baru diberi detail di bawah
// ini merupakan aturan dari C++
void formatPeminjamanTable();
void formatPeminjamanTableHeader();
void formatPeminjamanTableChildRow();
string findAnggotaByKode(string kode);

void peminjamanPengembalianMenu();
void peminjamanPengembalianMenuSwitch();
void insertPeminjaman();
void detailPeminjaman();
void returnPeminjaman();

Peminjaman insertPeminjamanForm();
Peminjaman insertBukuPinjamanForm(Peminjaman peminjaman);
string detailPeminjamanForm();
Pengembalian returnPeminjamanForm();
int payDendaForm(int denda);
void detailPeminjamanMenuSwitch();

void formatDetailPeminjamanTable(vector<BukuPinjaman>& bukuPinjamanVector);
void formatDetailPeminjamanTableHeader();
void formatDetailPeminjamanTableChildRow(vector<BukuPinjaman>& bukuPinjamanVector);

bool insertToPeminjamanVector(Peminjaman peminjaman);
void isBukuEligibleForPeminjaman(Peminjaman &peminjaman, BukuPinjaman bukuPinjaman);
void decreaseBukuFromBukuVector(string kode);
void findPeminjamanFromVector(string kodePeminjaman);
bool returnPeminjamanFromVector(Pengembalian pengembalian);
void returnBukuPinjaman(vector<BukuPinjaman>& bukuPinjamanVector);
int countDenda(vector<BukuPinjaman>& bukuPinjamanVector, int daysBetween);
void payDenda(vector<BukuPinjaman>& bukuPinjamanVector, int daysBetween);
int getDaysBetweenDates(string firstDate, string secondDate);

// main function untuk fitur peminjaman-pengembalian
void daftarPeminjaman()
{
	system("cls");
	formatPeminjamanTable();
	peminjamanPengembalianMenu();
}

// format tabel secara keseluruhan 
void formatPeminjamanTable()
{
	formatPeminjamanTableHeader();
	formatPeminjamanTableChildRow();
}

// format untuk header tabel daftar peminjaman-pengembalian
void formatPeminjamanTableHeader()
{
	// left untuk align text ke kiri
	// setw untuk menentukan jumlah karakter maksimal dalam 1 kali pemanggilan cout
	// setfill untuk menambahkan karakter sebagai pengganti 
	// pengganti ini akan mengisi ruang kosong yang tersisa jika string tidak mencapai batas maksimal
	cout << "+";
	cout << left << setw(113) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR PEMINJAMAN -";
	cout << "+";
	cout << endl;

	cout << "|  ";
	cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Anggota";
	cout << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << "Tanggal pinjam";
	cout << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << "Jadwal kembali";
	cout << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << "Tanggal kembali";
	cout << left << setw(tableFormatter.statusColumnLength) << setfill(tableFormatter.columnSeparator) << "Status";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Denda";
	cout << "  |" << endl;

	cout << "+";
	cout << left << setw(113) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

// format untuk kolom isian daftar buku
void formatPeminjamanTableChildRow()
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
		cout << "|  ";
		cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << count++;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.kode;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.kodeAnggota;
		cout << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.tanggalPeminjaman;
		cout << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.jadwalPengembalian;
		cout << left << setw(tableFormatter.dateColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.tanggalDikembalikan;
		cout << left << setw(tableFormatter.statusColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.status;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << peminjaman.dendaTelat;
		cout << "  |" << endl;
	}

	// cek jika vector peminjamanVector kosong
	// jika kosong maka batas bawah tidak akan ditampilkan supaya tampilan tabel lebih rapi
	if (!peminjamanVector.empty())
	{
		cout << "+";
		cout << left << setw(113) << setfill(tableFormatter.headerRowSeparator) << "";
		cout << "+";
		cout << endl;
	}
}

// menampilkan menu fitur peminjaman-pengembalian
void peminjamanPengembalianMenu()
{
	cout << endl;
	cout << "+- MENU -----------------------+" << endl;
	cout << "|  1. Tambah peminjaman        |" << endl;
	cout << "|  2. Detail peminjaman        |" << endl;
	cout << "|  3. Pengembalian peminjaman  |" << endl;
	cout << "|  9. Kembali ke menu utama    |" << endl;
	cout << "+------------------------------+" << endl << endl;
	
	peminjamanPengembalianMenuSwitch();
}

// switch case pemilihan sub-menu pada fitur peminjaman-pengembalian
void peminjamanPengembalianMenuSwitch()
{
	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		insertPeminjaman();
		break;
	case 2:
		detailPeminjaman();
		break;
	case 3:
		returnPeminjaman();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

// main function untuk menambah peminjaman buku
void insertPeminjaman()
{
	// menampilkan form input menambah peminjaman dan menyimpan isinya dalam variable peminjaman
	Peminjaman peminjaman = insertPeminjamanForm();
	// melakukan proses peminjaman
	bool isInsertionSuccessful = insertToPeminjamanVector(peminjaman);

	cout << endl;
	if (isInsertionSuccessful)
	{
		cout << "Peminjaman berhasil ditambahkan!" << endl;
	}
	else
	{
		cout << "Peminjaman gagal dilakukan!" << endl;
		cout << "Peminjaman dengan kode tersebut sudah ada!" << endl;
	}

	Sleep(1000);
	daftarPeminjaman();
}

// form input tambah peminjaman
Peminjaman insertPeminjamanForm()
{
	system("cls");
	cout << "------------- TAMBAH PEMINJAMAN -------------" << endl;

	cout << "Kode (tidak boleh sama!)          : ";
	cin >> peminjaman.kode;

	cout << "Kode Anggota                      : ";
	cin >> peminjaman.kodeAnggota;

	cout << "Tanggal Peminjaman [yyyy-mm-dd]   : ";
	cin >> peminjaman.tanggalPeminjaman;

	cout << "Jadwal Pengembalian [yyyy-mm-dd]  : ";
	cin >> peminjaman.jadwalPengembalian;

	Peminjaman peminjamanWithBuku = insertBukuPinjamanForm(peminjaman);
	return peminjamanWithBuku;
}

// form input untuk pengisian detail peminjaman
// berapa jenis buku yang ingin dipinjam, kode buku yang ingin dipinjam dan jumlahnya
Peminjaman insertBukuPinjamanForm(Peminjaman peminjaman)
{
	cout << endl;
	cout << "---- DETAIL BUKU ----" << endl;
	cout << "Berapa jenis buku yang ingin dipinjam : ";
	int jumlahJenisBuku;
	cin >> jumlahJenisBuku;

	// looping pengisian buku
	for (int i = 0; i < jumlahJenisBuku; i++)
	{
		cout << endl;
		cout << "Kode Buku : ";
		cin >> bukuPinjaman.kode;

		cout << "Jumlah    : ";
		cin >> bukuPinjaman.jumlah;

		// cek jika buku memiliki kondisi yang pas untuk dipinjam
		isBukuEligibleForPeminjaman(peminjaman, bukuPinjaman);
	}

	return peminjaman;
}

void isBukuEligibleForPeminjaman(Peminjaman &peminjaman, BukuPinjaman bukuPinjaman)
{
	// cek jika buku dengan kode itu ada dan stoknya bukan 0
	auto findBuku = find_if(bukuVector.begin(), bukuVector.end(), [kode = bukuPinjaman.kode](const Buku& buku) {
		return buku.kode == kode && buku.stok > 0;
	});

	// jika buku tersedia
	if (findBuku != bukuVector.end())
	{
		// cek jika sisa stok buku setelah dikurangi jumlah peminjaman lebih dari sama dengan 0 atau tidak
		int sisaBuku = findBuku->stok - bukuPinjaman.jumlah;
		// jika lebih maka peminjaman akan di proses
		if (sisaBuku >= 0)
		{
			peminjaman.bukuPinjamanVector.push_back(bukuPinjaman);
			decreaseBukuFromBukuVector(bukuPinjaman.kode);
		}
		// jika tidak maka peminjaman tidak akan di proses
		else
		{
			cout << endl;
			cout << "Peminjaman gagal dilakukan!" << endl;
			cout << "Stok buku kurang!" << endl;

			Sleep(700);
			daftarPeminjaman();
		}
	}
	// jika buku tidak tersedia maka peminjaman tidak akan di proses
	else
	{
		cout << endl;
		cout << "Peminjaman gagal dilakukan!" << endl;
		cout << "Buku dengan kode tersebut tidak ditemukan!" << endl;

		Sleep(700);
		daftarPeminjaman();
	}
}

// function untuk mengurangi stok buku yang dipinjamn
void decreaseBukuFromBukuVector(string kode)
{
	// cari buku berdasarkan kode yang diinputkan
	auto buku = find_if(bukuVector.begin(), bukuVector.end(), [kode](const Buku& buku) {
		return buku.kode == kode;
	});

	// jika buku ditemukan maka stoknya akan dikurangi
	if (buku != bukuVector.end())
	{
		buku->stok -= bukuPinjaman.jumlah;
	}
}

// proses pengisian ke vector peminjamanVector
bool insertToPeminjamanVector(Peminjaman peminjaman)
{
	// cek jika kode peminjaman sudah ada
	auto findPeminjaman = find_if(peminjamanVector.begin(), peminjamanVector.end(), [kode = peminjaman.kode](const Peminjaman& peminjaman) {
		return peminjaman.kode == kode;
	});

	// jika kode peminjaman sudah ada, maka function akan return false
	// maka tidak akan terjadi penambahan
	if (findPeminjaman != peminjamanVector.end())
	{
		return false;
	}

	// jika kode buku tidak ada maka proses penambahan dilakukan
	peminjamanVector.push_back(peminjaman);
	// return true karena proses penambahan berhasil
	return true;
}

// main function untuk detail peminjaman
void detailPeminjaman()
{
	// menampilkan form dan menyimpan datanya dalam variable kodePeminjaman
	string kodePeminjaman = detailPeminjamanForm();
	// melakukan proses pencarian berdasarkan kode dan menampilkan detail
	findPeminjamanFromVector(kodePeminjaman);
	detailPeminjamanMenuSwitch();
}

// form input detail peminjaman
string detailPeminjamanForm()
{
	system("cls");
	cout << "-- DETAIL PEMINJAMAN -----------------" << endl;

	cout << "Kode Peminjaman      : ";
	string kode;
	cin >> kode;

	return kode;
}

// proses pencarian peminjaman dari vector
void findPeminjamanFromVector(string kodePeminjaman)
{
	// cek jika peminjaman dengan kode yang telah di input ada atau tidak
	auto peminjaman = find_if(peminjamanVector.begin(), peminjamanVector.end(), [kodePeminjaman](const Peminjaman& peminjaman) {
		return peminjaman.kode == kodePeminjaman;
	});

	// jika peminjaman dengan kode tersebut ditemukan maka tampilan detail akan muncul
	if (peminjaman != peminjamanVector.end())
	{
		cout << "Nama Anggota         : " << findAnggotaByKode(peminjaman->kodeAnggota) << endl;
		cout << "Tanggal Peminjaman   : " << peminjaman->tanggalPeminjaman << endl;
		cout << "Jadwal Pengembalian  : " << peminjaman->jadwalPengembalian << endl;
		cout << "Tanggal Kembali      : " << peminjaman->tanggalDikembalikan << endl;
		cout << "Status               : " << peminjaman->status << endl;
		cout << "Denda                : " << peminjaman->dendaTelat << endl;
			 
		formatDetailPeminjamanTable(peminjaman->bukuPinjamanVector);
	}
	// jika tidak maka akan keluar sebuah warning
	else
	{
		cout << "Tidak dapat memuat detail peminjaman!" << endl;
		cout << "Peminjaman dengan kode tersebut tidak ditemukan!" << endl;
	}
}

// function untuk mencari anggota dari kode anggota
string findAnggotaByKode(string kode)
{
	// cek jika anggota dengan kode anggota yang didapat dari detail ada atau tidak
	auto anggota = find_if(anggotaVector.begin(), anggotaVector.end(), [kode](const Anggota& anggota) {
		return anggota.kode == kode;
	});

	// jika ada maka function akan me return nama anggota
	if (anggota != anggotaVector.end())
	{
		return anggota->nama;
	}
}

// format tampilan tabel buku pada detail peminjaman secara keseluruhan
void formatDetailPeminjamanTable(vector<BukuPinjaman>& bukuPinjamanVector)
{
	cout << endl;
	formatDetailPeminjamanTableHeader();
	formatDetailPeminjamanTableChildRow(bukuPinjamanVector);
}

// format header tabel buku pada detail peminjaman
void formatDetailPeminjamanTableHeader()
{
	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR BUKU PINJAMAN -";
	cout << "+";
	cout << endl;

	cout << "|  ";
	cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << "Judul";
	cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << "Penulis";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Terbit";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Jumlah";
	cout << "  |" << endl;

	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

// format kolom isian tabel buku pada detail peminjaman
void formatDetailPeminjamanTableChildRow(vector<BukuPinjaman>& bukuPinjamanVector)
{
	int counter = 1;
	for (auto &bukuPinjaman : bukuPinjamanVector)
	{
		auto buku = find_if(bukuVector.begin(), bukuVector.end(), [kode = bukuPinjaman.kode](const Buku& buku) {
			return buku.kode == kode;
		});

		if (buku != bukuVector.end())
		{
			cout << "|  ";
			cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << counter++;
			cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku->kode;
			cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << buku->judul;
			cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << buku->penulis;
			cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku->tahunTerbit;
			cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << bukuPinjaman.jumlah;
			cout << "  |" << endl;
		}
	}

	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

// switch case untuk kembali ke menu awal fitur peminjaman-pengembalian
void detailPeminjamanMenuSwitch()
{
	cout << endl;
	cout << "Kembali ke menu peminjaman & pengembalian [y/n]: ";
	char menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 'y':
		daftarPeminjaman();
		break;
	case 'n':
		break;
	default:
		cout << "Input invalid";
		break;
	}
}

// main function untuk pengembalian peminjaman
void returnPeminjaman()
{
	// menampilkan form input pengembalian dan menyimpan isinya dalam variable pengembalian
	Pengembalian pengembalian = returnPeminjamanForm();
	// melakukan proses pengembalian
	bool isReturnedSuccessfully = returnPeminjamanFromVector(pengembalian);

	cout << endl;
	if (isReturnedSuccessfully)
	{
		cout << "Peminjaman telah dikembalikan!" << endl;
	}
	else
	{
		cout << "Peminjaman tidak dapat dikembalikan!" << endl;
		cout << "Peminjaman dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(1000);
	daftarPeminjaman();
}

// form input pengembalian peminjaman
Pengembalian returnPeminjamanForm()
{
	system("cls");
	cout << "------------- KEMBALIKAN PEMINJAMAN -------------" << endl;

	cout << "Kode (harus ada di tabel data!)        : ";
	cin >> pengembalian.kode;

	cout << "Tanggal pengembalian [yyyy-mm-dd]      : ";
	cin >> pengembalian.tanggalPengembalian;

	return pengembalian;
}

// melakukan proses pengembalian peminjaman
bool returnPeminjamanFromVector(Pengembalian pengembalian)
{
	// mencari jika peminjaman dengan kode yang telah diinputkan ada atau tidak
	auto peminjaman = find_if(peminjamanVector.begin(), peminjamanVector.end(), [kode = pengembalian.kode](const Peminjaman& peminjaman) {
		return peminjaman.kode == kode;
	});

	cout << endl;

	// jika ada maka proses pengembalian akan dilakukan
	// return true karena proses pengembalian berhasil
	if (peminjaman != peminjamanVector.end())
	{
		peminjaman->status = "Sudah dikembalikan";

		// mengembalikan stok buku yang dipinjam
		returnBukuPinjaman(peminjaman->bukuPinjamanVector);

		// melakukan pengecekan denda
		peminjaman->tanggalDikembalikan = pengembalian.tanggalPengembalian;
		int daysBetween = getDaysBetweenDates(peminjaman->jadwalPengembalian, pengembalian.tanggalPengembalian);
		// bayar denda jika terbukti ada keterlambatan pengembalian
		if (daysBetween > 0)
		{
			payDenda(peminjaman->bukuPinjamanVector, daysBetween);
			peminjaman->dendaTelat = countDenda(peminjaman->bukuPinjamanVector, daysBetween);
		}

		return true;
	}
	// jika tidak maka proses pengembalian tidak akan dilakukan
	// return false karena proses pengembalian gagal
	else
	{
		return false;
	}
}

// mengembalikan stok buku yang dipinjam
void returnBukuPinjaman(vector<BukuPinjaman> &bukuPinjamanVector)
{
	for (auto &bukuPinjaman : bukuPinjamanVector)
	{
		auto buku = find_if(bukuVector.begin(), bukuVector.end(), [kode = bukuPinjaman.kode](const Buku& buku) {
			return buku.kode == kode;
		});

		if (buku != bukuVector.end())
		{
			buku->stok += bukuPinjaman.jumlah;
		}
	}
}

// form input pembayaran denda telat
int payDendaForm(int denda)
{
	cout << "---- Bayar Denda Telat ----" << endl;
	cout << "Total denda : " << denda << endl;
	cout << "Uang        : ";
	int bayar;
	cin >> bayar;

	return bayar;
}

// melakukan proses pembayaran denda 
void payDenda(vector<BukuPinjaman> &bukuPinjamanVector, int daysBetween)
{
	int denda = countDenda(bukuPinjamanVector, daysBetween);
	int bayar = payDendaForm(denda);

	if (bayar > denda)
	{
		cout << "Kembalian   : " << (bayar - denda) << endl;
	}
}

// hitung total denda
// dengan rumus 5000 * total buku yang dipinjamn * jumlah hari keterlambatan
int countDenda(vector<BukuPinjaman> &bukuPinjamanVector, int daysBetween)
{
	int totalBuku = 0;
	for (auto &bukuPinjaman : bukuPinjamanVector)
	{
		totalBuku += bukuPinjaman.jumlah;
	}

	return 5000 * totalBuku * daysBetween;
}

// function untuk membandingkan antara 2 tanggal
int getDaysBetweenDates(string firstDate, string secondDate)
{
	stringstream ss(firstDate + "-" + secondDate);
	int year, month, day;
	char hyphen;

	// Melakukan parsing untuk tanggal pertama 
	ss >> year >> hyphen >> month >> hyphen >> day;
	struct tm starttm = { 0, 0, 0, day, month - 1, year - 1900 };
	// membuat variable start untuk menyimpan waktu
	time_t start = mktime(&starttm);

	// Melakukan parsing untuk tanggal kedua 
	ss >> hyphen >> year >> hyphen >> month >> hyphen >> day;
	struct tm endtm = { 0, 0, 0, day, month - 1, year - 1900 };
	// membuat variable end untuk menyimpan waktu
	time_t end = mktime(&endtm);

	// Menghitung perbedaan antar tanggal
	// Kemudian dibagi 86400 agar perbedaan tersebut bisa menjadi perbedaan hari
	return (end - start) / 86400;
}
