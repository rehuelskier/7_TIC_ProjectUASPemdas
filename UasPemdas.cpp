#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Barang {
    string kode, nama;
    int stok;
};

// Menggunakan pointer ke array Barang
Barang daftar[100];
int jumlah = 0;

void tambah() {
    if (jumlah >= 100) {
        cout << "Penuh!\n";
        return;
    }
    
    cout << "\nTambah Barang\n";
    cout << "Kode: "; cin >> daftar[jumlah].kode;
    cout << "Nama: "; cin >> daftar[jumlah].nama;
    cout << "Stok: "; cin >> daftar[jumlah].stok;
    jumlah++;
    cout << "Berhasil!\n";
}

void tampil() {
    cout << "\nDaftar Barang:\n";
    cout << "Kode\tNama\tStok\n";
    for (int i = 0; i < jumlah; i++) {
        Barang* ptr = &daftar[i];
        cout << ptr->kode << "\t" 
             << ptr->nama << "\t" 
             << ptr->stok << endl;
    }
}

void updateStok() {
    string kode;
    int baru;
    
    cout << "\nUpdate Stok\n";
    cout << "Kode: "; cin >> kode;
    cout << "Stok +/-: "; cin >> baru;
    
    for (int i = 0; i < jumlah; i++) {
        Barang* ptr = &daftar[i];
        if (ptr->kode == kode) {
            ptr->stok += baru;
            cout << "Stok baru: " << ptr->stok << endl;
            return;
        }
    }
    cout << "Tidak ditemukan!\n";
}

int cariSeq(string kode) {
    for (int i = 0; i < jumlah; i++) {
        if (daftar[i].kode == kode) return i;
    }
    return -1;
}

// Rekursif binary search
int cariBin(string arr[], string kode, int kiri, int kanan) {
    if (kiri > kanan) return -1;

    int tengah = (kiri + kanan) / 2;

    if (arr[tengah] == kode) return tengah;
    else if (arr[tengah] < kode)
        return cariBin(arr, kode, tengah + 1, kanan);
    else
        return cariBin(arr, kode, kiri, tengah - 1);
}

void cari() {
    string kode;
    cout << "\nCari Barang\n";
    cout << "Kode: "; cin >> kode;

    int idx = cariSeq(kode);
    if (idx != -1) {
        Barang* ptr = &daftar[idx];
        cout << "Ditemukan!\n";
        cout << "Nama: " << ptr->nama 
             << ", Stok: " << ptr->stok << endl;
    } else {
        cout << "Tidak ditemukan!\n";
    }

    // Binary search demo
    cout << "\nDemo Binary Search:\n";
    string kodes[100];
    for (int i = 0; i < jumlah; i++) kodes[i] = daftar[i].kode;

    // Sort
    for (int i = 0; i < jumlah-1; i++)
        for (int j = i+1; j < jumlah; j++)
            if (kodes[i] > kodes[j]) swap(kodes[i], kodes[j]);

    int idxBin = cariBin(kodes, kode, 0, jumlah - 1);
    if (idxBin != -1)
        cout << "Binary Search: ditemukan di index " << idxBin << endl;
}

void laporanStokRendah() {
    int batas;
    cout << "\nLaporan Stok Rendah\n";
    cout << "Batas stok: "; cin >> batas;

    cout << "\nBarang stok rendah:\n";
    for (int i = 0; i < jumlah; i++) {
        Barang* ptr = &daftar[i];
        if (ptr->stok <= batas) {
            cout << ptr->kode << " - " 
                 << ptr->nama << " (" 
                 << ptr->stok << ")\n";
        }
    }
}

// Fitur delete menggunakan pointer
void hapus() {
    string kode;
    cout << "\nHapus Barang\n";
    cout << "Kode: "; cin >> kode;

    int idx = cariSeq(kode);
    if (idx == -1) {
        cout << "Tidak ditemukan!\n";
        return;
    }

    // pointer ke data yang dihapus
    Barang* ptr = &daftar[idx];

    cout << "Menghapus: " << ptr->nama << endl;

    // geser array menggunakan pointer
    for (int i = idx; i < jumlah - 1; i++) {
        Barang* a = &daftar[i];
        Barang* b = &daftar[i+1];
        *a = *b;  // copy isi
    }

    jumlah--;
    cout << "Berhasil dihapus!\n";
}

void simpan() {
    ofstream file("stok.txt");
    for (int i = 0; i < jumlah; i++) {
        file << daftar[i].kode << " "
             << daftar[i].nama << " "
             << daftar[i].stok << endl;
    }
    file.close();
    cout << "Disimpan ke stok.txt\n";
}

void load() {
    ifstream file("stok.txt");
    jumlah = 0;
    while (file >> daftar[jumlah].kode 
                >> daftar[jumlah].nama 
                >> daftar[jumlah].stok) {
        jumlah++;
    }
    file.close();
    cout << "Dimuat dari stok.txt\n";
}

int main() {
    cout << "=== APLIKASI STOK BARANG ===\n";

    while (true) {
        cout << "\nMENU:\n";
        cout << "1. Tambah barang\n2. Tampilkan semua barang\n3. Update Stok barang\n";
        cout << "4. Cari kode barang\n5. Laporan Stok Rendah\n";
        cout << "6. Simpan ke file\n7. Load file\n8. Hapus barang\n0. Keluar\n";
        cout << "Pilih: ";

        int pilihan;
        cin >> pilihan;
        
        // Bersihin buffer kalo input gagal
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid! Masukkan angka.\n";
            continue;
        }

        switch(pilihan) {
            case 1: tambah(); break;
            case 2: tampil(); break;
            case 3: updateStok(); break;
            case 4: cari(); break;
            case 5: laporanStokRendah(); break;
            case 6: simpan(); break;
            case 7: load(); break;
            case 8: hapus(); break;
            case 0:
                cout << "Keluar...\n";
                return 0;
            default:
                cout << "Pilihan salah!\n";
        }
    }
}