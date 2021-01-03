#include <iostream> // untuk cout cin
#include <string> // agar bisa menggunakan tipe data string 
#include <Windows.h> // untuk menggunakan function Sleep()
#include <iomanip> // untuk menggunakan setw(), setfill() dan left

#include "Menu.h" // penghubung agar function mainMenu() bisa dipanggil di file ini
#include "DaftarBuku.h" // header file penghubung antara Main Menu dan Fitur Buku
#include "Globals.h" // agar bisa menggunakan struct dan vector buku yg tersimpan sebagai global variable

using namespace std;

// struct adalah semacam tipe data yang dapat di custom, biasanya berperan sebagai object
// vector adalah semacam array yang dinamis yang lebih fleksibel daripada array, 
// fleksibel dalam artian isi elemen dalam vector bisa bermacam-macam tidak perlu ditentukan dengan const
// extern menandakan bahwa variable berikut adalah variable yang sudah didefinisikan di file lain
// dalam kata lain, ini adalah penanda bahwa variable di bawah ini merupakan global variable
extern struct Buku buku;
extern vector<Buku> bukuVector;
extern struct TableFormatter tableFormatter;

// functions harus tetap di tuliskan diatas pertama kali
// kemudian function tersebut baru diberi detail di bawah
// ini merupakan aturan dari C++
void formatBukuTable();
void formatBukuTableHeader();
void formatBukuTableChildRow();

void bukuMenu();
void bukuMenuSwitch();
void insertBuku();
void updateBuku();
void deleteBuku();

Buku insertBukuForm();
Buku updateBukuForm();
string deleteBukuForm();

bool insertToBukuVector(Buku buku);
bool updateBukuVector(Buku buku);
bool deleteFromBukuVector(string kodeBuku);

// main function untuk keseluruhan fitur buku
void daftarBuku()
{	
	system("cls");	
	formatBukuTable();
	bukuMenu();
}

// format tabel secara keseluruhan 
void formatBukuTable()
{
	formatBukuTableHeader();
	formatBukuTableChildRow();
}

// format untuk header tabel daftar buku
void formatBukuTableHeader()
{
	// left untuk align text ke kiri
	// setw untuk menentukan jumlah karakter maksimal dalam 1 kali pemanggilan cout
	// setfill untuk menambahkan karakter sebagai pengganti 
	// pengganti ini akan mengisi ruang kosong yang tersisa jika string tidak mencapai batas maksimal
	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "- DAFTAR BUKU -";
	cout << "+";
	cout << endl;

	cout << "|  ";
	cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << "#";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Kode";
	cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << "Judul";
	cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << "Penulis";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Terbit";
	cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << "Stok";
	cout << "  |" << endl;

	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

// format untuk kolom isian daftar buku
void formatBukuTableChildRow()
{
	int count = 1;

	// looping untuk mengakses value bukuVector
	// menggunakan tanda & didepan variable agar variable itu terisi oleh reference
	// kenapa menggunakan reference? agar di memori tidak terjadi duplikasi data vector
	for (auto &buku : bukuVector)
	{
		// left untuk align text ke kiri
		// setw untuk menentukan jumlah karakter maksimal dalam 1 kali pemanggilan cout
		// setfill untuk menambahkan karakter sebagai pengganti 
		// pengganti ini akan mengisi ruang kosong yang tersisa jika string tidak mencapai batas maksimal
		cout << "|  ";
		cout << left << setw(tableFormatter.counterColumnLength) << setfill(tableFormatter.columnSeparator) << count++;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku.kode;
		cout << left << setw(tableFormatter.stringColumnLength) << setfill(tableFormatter.columnSeparator) << buku.judul;
		cout << left << setw(tableFormatter.nameColumnLength) << setfill(tableFormatter.columnSeparator) << buku.penulis;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku.tahunTerbit;
		cout << left << setw(tableFormatter.numColumnLength) << setfill(tableFormatter.columnSeparator) << buku.stok;
		cout << "  |" << endl;
	}

	cout << "+";
	cout << left << setw(109) << setfill(tableFormatter.headerRowSeparator) << "";
	cout << "+";
	cout << endl;
}

// menampilkan menu fitur buku
void bukuMenu()
{
	cout << endl;
	cout << "+- MENU ---------------------+" << endl;
	cout << "|  1. Tambah buku            |" << endl;
	cout << "|  2. Update buku            |" << endl;
	cout << "|  3. Hapus buku             |" << endl;
	cout << "|  9. Kembali ke menu utama  |" << endl;
	cout << "+----------------------------+" << endl << endl;
	
	// memanggil input pemilihan menu
	bukuMenuSwitch();
}

// switch case untuk pemilihan menu daftar buku
void bukuMenuSwitch()
{
	cout << "Pilih menu: ";
	int menuSelection;
	cin >> menuSelection;

	switch (menuSelection)
	{
	case 1:
		insertBuku();
		break;
	case 2:
		updateBuku();
		break;
	case 3:
		deleteBuku();
		break;
	case 9:
		mainMenu();
		break;
	default:
		cout << "Input tidak valid!";
		break;
	}
}

// main function untuk fitur tambah buku
void insertBuku() 
{
	// menampilkan form input menambah buku dan menyimpan isinya dalam variable buku
	Buku buku = insertBukuForm();
	// melakukan penambahan buku dan mengembalikan true / false tergantung keberhasilan penambahan
	bool isInsertionSuccessful = insertToBukuVector(buku);
	
	cout << endl;

	// cek jika penambahan berhasil
	if (isInsertionSuccessful)
	{
		cout << "Buku berhasil ditambahkan!" << endl;
	}
	else
	{
		cout << "Buku gagal ditambahkan!" << endl;
		cout << "Buku dengan kode tersebut sudah ada!" << endl;
	}

	Sleep(1000);
	daftarBuku();
}

// form insert buku
// memiliki return type Buku karena yang di return oleh si function adalah data dengan tipe data struct Buku
Buku insertBukuForm()
{
	system("cls");
	cout << "------------- TAMBAH BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (tidak boleh sama!) : ";
	getline(cin, buku.kode);

	cout << "Judul                    : ";
	getline(cin, buku.judul);

	cout << "Penulis                  : ";
	getline(cin, buku.penulis);

	cout << "Tahun terbit             : ";
	cin >> buku.tahunTerbit;

	cout << "Stok                     : ";
	cin >> buku.stok;

	return buku;
}

// proses penambahan buku ke vector bukuVector
bool insertToBukuVector(Buku buku)
{
	// cek jika kode buku sudah ada
	auto findBuku = find_if(bukuVector.begin(), bukuVector.end(), [kode = buku.kode](const Buku& buku) {
		return buku.kode == kode;
	});

	// jika kode buku sudah ada, maka function akan return false
	// maka tidak akan terjadi penambahan
	if (findBuku != bukuVector.end())
	{
		return false;
	}

	// jika kode buku tidak ada maka proses penambahan dilakukan
	bukuVector.push_back(buku);
	// return true karena proses penambahan berhasil
	return true;
}

// main function untuk fitur update buku
void updateBuku() 
{
	// menampilkan form input dan menyimpan datanya dalam variable buku
	Buku buku = updateBukuForm();
	// melakukan update buku dan mengembalikan true / false tergantung keberhasilan update
	bool isUpdateSuccessful = updateBukuVector(buku);

	cout << endl;
	// cek jika proses update berhasil atau tidak
	if (isUpdateSuccessful)
	{
		cout << "Buku berhasil diupdate!" << endl;
	}
	else
	{
		cout << "Buku gagal diupdate!" << endl;
		cout << "Buku dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(1000);
	daftarBuku();
}

// form update buku
Buku updateBukuForm()
{
	system("cls");
	cout << "------------- UPDATE BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!) : ";
	getline(cin, buku.kode);

	cout << "Judul                           : ";
	getline(cin, buku.judul);

	cout << "Penulis                         : ";
	getline(cin, buku.penulis);

	cout << "Tahun terbit                    : ";
	cin >> buku.tahunTerbit;

	cout << "Stok                            : ";
	cin >> buku.stok;

	return buku;
}

// proses update buku
bool updateBukuVector(Buku buku)
{
	// cek jika buku dengan kode tertentu dapat ditemukan
	auto updatedBuku = find_if(bukuVector.begin(), bukuVector.end(), [kode = buku.kode](const Buku& buku) { 
		return buku.kode == kode; 
	});

	// jika ditemukan maka buku akan di update
	// return true karena proses update berhasil
	if (updatedBuku != bukuVector.end())
	{
		updatedBuku->judul = buku.judul;
		updatedBuku->penulis = buku.penulis;
		updatedBuku->tahunTerbit = buku.tahunTerbit;
		updatedBuku->stok = buku.stok;

		return true;
	}

	// jika tidak maka proses update tidak akan dilakukan
	// return false karena proses update tidak berhasil
	return false;
}

// main function untuk fitur hapus buku
void deleteBuku() 
{
	// menampilkan form input dan menyimpan data nya dalam variable kodeBuku
	string kodeBuku = deleteBukuForm();
	// melakukan proses hapus buku
	bool isDeletionSuccessful = deleteFromBukuVector(kodeBuku);

	cout << endl;
	// cek jika buku berhasil dihapus atau tidak
	if (isDeletionSuccessful)
	{
		cout << "Buku berhasil dihapus!" << endl;
	}
	else
	{
		cout << "Buku gagal dihapus!" << endl;
		cout << "Buku dengan kode tersebut tidak ditemukan!" << endl;
	}

	Sleep(1000);
	daftarBuku();
}

// form hapus buku
string deleteBukuForm()
{
	system("cls");
	cout << "------------- HAPUS BUKU -------------" << endl;
	cin.ignore();

	cout << "Kode (harus ada di tabel data!): ";
	string kode;
	getline(cin, kode);

	return kode;
}

// proses penghapusan buku dari vector
bool deleteFromBukuVector(string kodeBuku)
{
	// mencari apakah buku dengan kode tertentu dapat ditemukan dalam vector
	auto deletedBuku = remove_if(bukuVector.begin(), bukuVector.end(), [kodeBuku](const Buku& buku) { 
		return buku.kode == kodeBuku; 
	});

	// jika buku ditemukan maka buku itu akan dihapus dari vector
	// return true karena proses penghapusan berhasil
	if (deletedBuku != bukuVector.end())
	{
		bukuVector.erase(deletedBuku, bukuVector.end());
		return true;
	}
	
	// jika buku tidak ditemukan maka buku tidak terhapus
	// return false karena buku tidak terhapus
	return false;
}