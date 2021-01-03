#include <iostream> // untuk cout cin
#include <string> // agar bisa menggunakan tipe data string 
#include <Windows.h> // untuk menggunakan function Sleep()
#include <iomanip> // untuk menggunakan setw(), setfill() dan left

#include "Menu.h" // penghubung agar function mainMenu() bisa dipanggil di file ini
#include "DaftarAnggota.h" // header file penghubung antara Main Menu dan Fitur Anggota
#include "Globals.h" // agar bisa menggunakan struct dan vector anggota yg tersimpan sebagai global variable

using namespace std;

// struct adalah semacam tipe data yang dapat di custom, biasanya berperan sebagai object
// vector adalah semacam array yang dinamis yang lebih fleksibel daripada array, 
// fleksibel dalam artian isi elemen dalam vector bisa bermacam-macam tidak perlu ditentukan dengan const
// extern menandakan bahwa variable berikut adalah variable yang sudah didefinisikan di file lain
// dalam kata lain, ini adalah penanda bahwa variable di bawah ini merupakan global variable
extern struct Anggota anggota;
extern vector<Anggota> anggotaVector;
extern struct TableFormatter tableFormatter;

// functions harus tetap di tuliskan diatas pertama kali
// kemudian function tersebut baru diberi detail di bawah
// ini merupakan aturan dari C++
void formatAnggotaTable();
void formatAnggotaTableHeader();
void formatAnggotaTableChildRow();

void anggotaMenu();
void anggotaMenuSwitch();
void insertAnggota();
void updateAnggota();
void deleteAnggota();

Anggota insertAnggotaForm();
Anggota updateAnggotaForm();
string deleteAnggotaForm();

bool insertToAnggotaVector(Anggota anggota);
bool updateAnggotaVector(Anggota anggota);
bool deleteFromAnggotaVector(string kodeAnggota);

// main function untuk keseluruhan fitur anggota
void daftarAnggota() {
	system("cls");
	formatAnggotaTable();
	anggotaMenu();
}

// format tabel data anggota secara keseluruhan
void formatAnggotaTable()
{
	formatAnggotaTableHeader();
	formatAnggotaTableChildRow();
}

// format untuk header tabel daftar anggota
void formatAnggotaTableHeader()
{
	// left untuk align text ke kiri
	// setw untuk menentukan jumlah karakter maksimal dalam 1 kali pemanggilan cout
	// setfill untuk menambahkan karakter sebagai pengganti 
	// pengganti ini akan mengisi ruang kosong yang tersisa jika string tidak mencapai batas maksimal
	cout << "+";
	cout << left << setw(89) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR ANGGOTA -";
	cout << "+";
	cout << endl;

	cout << "|  ";
	cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << "Nama";
	cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << "Alamat";
	cout << "  |" << endl;

	cout << "+";
	cout << left << setw(89) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

// format untuk kolom isian daftar anggota
void formatAnggotaTableChildRow()
{
	int count = 1;

	// looping untuk mengakses value bukuVector
	// menggunakan tanda & didepan variable agar variable itu terisi oleh reference
	// kenapa menggunakan reference? agar di memori tidak terjadi duplikasi data vector
	for (auto &anggota : anggotaVector)
	{
		// left untuk align text ke kiri
		// setw untuk menentukan jumlah karakter maksimal dalam 1 kali pemanggilan cout
		// setfill untuk menambahkan karakter sebagai pengganti 
		// pengganti ini akan mengisi ruang kosong yang tersisa jika string tidak mencapai batas maksimal
		cout << "|  ";
		cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << count++;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << anggota.kode;
		cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << anggota.nama;
		cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << anggota.alamat;
		cout << "  |" << endl;
	}

	cout << "+";
	cout << left << setw(89) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

// menampilkan menu fitur anggota
void anggotaMenu()
{
	cout << endl;
	cout << "+- MENU ---------------------+" << endl;
	cout << "|  1. Tambah anggota         |" << endl;
	cout << "|  2. Update anggota         |" << endl;
	cout << "|  3. Hapus anggota          |" << endl;
	cout << "|  9. Kembali ke menu utama  |" << endl;
	cout << "+----------------------------+" << endl << endl;

	// memanggil input pemilihan menu
	anggotaMenuSwitch();
}

// switch case untuk pemilihan menu daftar buku
void anggotaMenuSwitch()
{
	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		insertAnggota();
		break;
	case 2:
		updateAnggota();
		break;
	case 3:
		deleteAnggota();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

// main function untuk fitur tambah anggota
void insertAnggota() 
{
	// menampilkan form input menambah anggota dan menyimpan isinya dalam variable anggota
	Anggota anggota = insertAnggotaForm();
	// melakukan penambahan buku dan mengembalikan true / false tergantung keberhasilan penambahan
	bool isInsertionSuccessful = insertToAnggotaVector(anggota);

	// cek jika penambahan berhasil
	if (isInsertionSuccessful)
	{
		cout << "Anggota berhasil ditambahkan!" << endl;
	}
	else
	{
		cout << "Anggota gagal ditambahkan!" << endl;
		cout << "Anggota dengan kode tersebut sudah ada!" << endl;
	}
	
	Sleep(1000);
	daftarAnggota();
}

// form insert buku
// memiliki return type Anggota karena yang di return oleh si function adalah data dengan tipe data struct Anggota
Anggota insertAnggotaForm()
{
	system("cls");
	cout << "------------- TAMBAH ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (tidak boleh sama!) : ";
	getline(cin, anggota.kode);

	cout << "Nama                     : ";
	getline(cin, anggota.nama);

	cout << "Umur                     : ";
	cin >> anggota.umur;

	cin.ignore();

	cout << "Alamat                   : ";
	getline(cin, anggota.alamat);

	return anggota;
}

// proses penambahan anggota ke vector anggotaVector
bool insertToAnggotaVector(Anggota anggota)
{
	// cek jika kode buku sudah ada
	auto findAnggota = find_if(anggotaVector.begin(), anggotaVector.end(), [kode = anggota.kode](const Anggota& anggota) {
		return anggota.kode == kode;
	});

	// jika kode buku sudah ada, maka function akan return false
	// maka tidak akan terjadi penambahan
	if (findAnggota != anggotaVector.end())
	{
		return false;
	}

	// jika kode buku tidak ada maka proses penambahan dilakukan
	anggotaVector.push_back(anggota);
	// return true karena proses penambahan berhasil
	return true;
}

// main function untuk fitur update anggota
void updateAnggota() 
{
	// menampilkan form input dan menyimpan datanya dalam variable anggota
	Anggota anggota = updateAnggotaForm();
	// melakukan update anggota dan mengembalikan true / false tergantung keberhasilan update
	bool isUpdateSuccessful = updateAnggotaVector(anggota);

	cout << endl;
	// cek jika proses update berhasil atau tidak
	if (isUpdateSuccessful)
	{
		cout << "Anggota berhasil diupdate!" << endl;
	}
	else
	{
		cout << "Anggota gagal diupdate!" << endl;
		cout << "Anggota dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(1000);
	daftarAnggota();
}

// form update anggota
Anggota updateAnggotaForm()
{
	system("cls");
	cout << "------------- UPDATE ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!) : ";
	getline(cin, anggota.kode);

	cout << "Nama                            : ";
	getline(cin, anggota.nama);

	cout << "Umur                            : ";
	cin >> anggota.umur;

	cin.ignore();

	cout << "Alamat                          : ";
	getline(cin, anggota.alamat);

	return anggota;
}

// proses update anggota
bool updateAnggotaVector(Anggota anggota)
{
	// cek jika anggota dengan kode tertentu dapat ditemukan
	auto updatedAnggota = find_if(anggotaVector.begin(), anggotaVector.end(), [kode = anggota.kode](const Anggota& anggota) { 
		return anggota.kode == kode; 
	});

	// jika ditemukan maka anggota akan di update
	// return true karena proses update berhasil
	if (updatedAnggota != anggotaVector.end())
	{
		updatedAnggota->nama = anggota.nama;
		updatedAnggota->umur = anggota.umur;
		updatedAnggota->alamat = anggota.alamat;

		return true;
	}

	// jika tidak maka proses update tidak akan dilakukan
	// return false karena proses update tidak berhasil
	return false;
}

// main function untuk fitur hapus anggota
void deleteAnggota() 
{
	// menampilkan form input dan menyimpan data nya dalam variable kodeAnggota
	string kodeAnggota = deleteAnggotaForm();
	// melakukan proses hapus anggota
	bool isDeletionSuccessful = deleteFromAnggotaVector(kodeAnggota);

	cout << endl;
	// cek jika anggota berhasil dihapus atau tidak
	if (isDeletionSuccessful)
	{
		cout << "Anggota berhasil dihapus!" << endl;
	}
	else
	{
		cout << "Anggota gagal dihapus!" << endl;
		cout << "Anggota dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(1000);
	daftarAnggota();
}

// form hapus anggota
string deleteAnggotaForm()
{
	system("cls");
	cout << "------------- HAPUS ANGGOTA -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!): ";
	string kode;
	getline(cin, kode);

	return kode;
}

// proses penghapusan anggota dari vector
bool deleteFromAnggotaVector(string kodeAnggota)
{
	// mencari apakah anggota dengan kode tertentu dapat ditemukan dalam vector
	auto erasedAnggota = remove_if(anggotaVector.begin(), anggotaVector.end(), [kodeAnggota](const Anggota& anggota) {
		return anggota.kode == kodeAnggota;
	});

	// jika buku ditemukan maka buku itu akan dihapus dari vector
	// return true karena proses penghapusan berhasil
	if (erasedAnggota != anggotaVector.end())
	{
		anggotaVector.erase(erasedAnggota, anggotaVector.end());
		return true;
	}

	// jika buku tidak ditemukan maka buku tidak terhapus
	// return false karena buku tidak terhapus
	return false;
}