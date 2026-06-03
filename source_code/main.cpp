#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

#include "sorting.h"
#include "searching.h"

using namespace std;
using namespace chrono;

// ============================================================
// GLOBAL VARIABLES
// ============================================================
bool sudahSorting = false;

// ============================================================
// UTILITY FUNCTIONS - Display Data
// ============================================================

/**
 * Tampilkan semua data siswa dalam format tabel
 */
void tampilkanArraySiswa(const vector<Siswa>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << i + 1 << ". " << left << setw(25) << arr[i].nama 
             << " | Nilai: " << arr[i].nilai << endl;
    }
}

/**
 * Tampilkan ringkasan data siswa (10 pertama + 10 terakhir jika > 20 item)
 */
void tampilRingkasSiswa(const vector<Siswa>& arr) {
    int n = arr.size();
    if (n <= 20) {
        tampilkanArraySiswa(arr);
        return;
    }
    
    cout << "10 Data Pertama:\n";
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << ". " << left << setw(25) << arr[i].nama 
             << " | Nilai: " << arr[i].nilai << endl;
    }
    
    cout << "\n...\n\n10 Data Terakhir:\n";
    for (int i = n - 10; i < n; i++) {
        cout << i + 1 << ". " << left << setw(25) << arr[i].nama 
             << " | Nilai: " << arr[i].nilai << endl;
    }
}

/**
 * Tampilkan semua data string
 */
void tampilkanArrayString(const vector<string>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << i + 1 << ". " << arr[i] << endl;
    }
}

// ============================================================
// DATA GENERATION FUNCTIONS
// ============================================================

/**
 * Generate data siswa secara acak
 */
vector<Siswa> generateRandomSiswa(int n) {
    vector<Siswa> arr;
    for (int i = 0; i < n; i++) {
        Siswa s;
        s.nama = "Siswa_Acak_" + to_string(i + 1);
        s.nilai = rand() % 101;
        arr.push_back(s);
    }
    return arr;
}

// ============================================================
// FILE I/O FUNCTIONS
// ============================================================

/**
 * Baca data siswa dari file
 */
vector<Siswa> bacaFileSiswa(const string& namaFile) {
    vector<Siswa> data;
    ifstream file(namaFile);
    
    if (!file.is_open()) {
        cout << "File tidak ditemukan!\n";
        return data;
    }
    
    string baris;
    int counter = 1;
    
    while (getline(file, baris)) {
        if (baris.empty()) continue;
        
        string namaStr = "", angkaStr = "";
        for (char c : baris) {
            if (isdigit(c)) {
                angkaStr += c;
            } else {
                namaStr += c;
            }
        }
        
        Siswa s;
        if (!namaStr.empty() && (namaStr.back() == ' ' || namaStr.back() == '=')) {
            namaStr.pop_back();
        }
        
        s.nama = namaStr.empty() ? "Siswa " + to_string(counter) : namaStr;
        s.nilai = angkaStr.empty() ? 0 : stoi(angkaStr);
        data.push_back(s);
        counter++;
    }
    
    file.close();
    cout << data.size() << " Data Siswa berhasil dibaca dari file!\n";
    return data;
}

/**
 * Baca data string dari file
 */
vector<string> bacaFileString(const string& namaFile) {
    vector<string> data;
    ifstream file(namaFile);
    
    if (!file.is_open()) {
        cout << "File tidak ditemukan!\n";
        return data;
    }
    
    string kata;
    while (getline(file, kata)) {
        if (!kata.empty()) {
            data.push_back(kata);
        }
    }
    
    file.close();
    return data;
}

// ============================================================
// BENCHMARK FUNCTIONS
// ============================================================

/**
 * Benchmark perbandingan Counting Sort vs Bubble Sort untuk integer
 */
void benchmarkInt() {
    int ukuranData[] = {100, 500, 1000, 5000, 10000};
    stringstream dataCSV;
    dataCSV << "Data,Kondisi,Algoritma,Waktu(ms),Operasi\n";

    cout << "\n=========================================================\n";
    cout << "        PERBANDINGAN COUNTING VS BUBBLE SORT (INTEGER)\n";
    cout << "=========================================================\n";
    cout << left << setw(12) << "Data" << setw(15) << "Kondisi" 
         << setw(20) << "Algoritma" << setw(15) << "Waktu(ms)" 
         << setw(15) << "Operasi" << endl;
    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < 5; i++) {
        int n = ukuranData[i];
        vector<int> kondisi[4];
        
        for (int m = 0; m < n; m++) {
            kondisi[0].push_back(rand() % 10000);    // Acak
            kondisi[1].push_back(m);                  // Terurut
            kondisi[2].push_back(n - m);              // Terbalik
            kondisi[3].push_back(rand() % 10);        // Duplikat
        }
        
        string namaKondisi[4] = {"Acak", "Terurut", "Terbalik", "Duplikat"};

        for (int k = 0; k < 4; k++) {
            // COUNTING SORT
            {
                vector<int> arr = kondisi[k];
                int op;
                auto start = high_resolution_clock::now();
                countingSortIntBiasa(arr, op);
                auto stop = high_resolution_clock::now();
                long long time = duration_cast<milliseconds>(stop - start).count();
                
                cout << left << setw(12) << n << setw(15) << namaKondisi[k] 
                     << setw(20) << "Counting Sort" << setw(15) << time 
                     << setw(15) << op << endl;
                dataCSV << n << "," << namaKondisi[k] << ",Counting Sort," 
                        << time << "," << op << "\n";
            }

            // BUBBLE SORT
            {
                vector<int> arr = kondisi[k];
                int op;
                auto start = high_resolution_clock::now();
                bubbleSortIntBiasa(arr, op);
                auto stop = high_resolution_clock::now();
                long long time = duration_cast<milliseconds>(stop - start).count();
                
                cout << left << setw(12) << n << setw(15) << namaKondisi[k] 
                     << setw(20) << "Bubble Sort" << setw(15) << time 
                     << setw(15) << op << endl;
                dataCSV << n << "," << namaKondisi[k] << ",Bubble Sort," 
                        << time << "," << op << "\n";
            }
        }
    }
    
    cout << "=========================================================\n";
    
    // Pilihan ekspor ke CSV
    char pilihanEkspor;
    cout << "Apakah Anda ingin mengekspor hasil benchmark ini ke file CSV? (y/n): ";
    cin >> pilihanEkspor;

    if (pilihanEkspor == 'y' || pilihanEkspor == 'Y') {
        ofstream fileExport("hasil_benchmark.csv");
        if (fileExport.is_open()) {
            fileExport << dataCSV.str();
            cout << "\n[SUKSES] Tabel perbandingan telah diekspor ke file 'hasil_benchmark.csv'\n";
            fileExport.close();
        } else {
            cout << "\n[GAGAL] Tidak dapat membuat file ekspor.\n";
        }
    } else {
        cout << "\nHasil benchmark tidak diekspor.\n";
    }
}

// ============================================================
// MENU FUNCTIONS
// ============================================================

/**
 * Menu untuk operasi pada data Siswa (Integer)
 */
void menuDataSiswa() {
    vector<Siswa> dataSiswa;
    int pilihan;
    
    do {
        cout << "\n=== MENU DATA INTEGER ===\n";
        cout << "1. Input Manual\n";
        cout << "2. Generate Data Acak\n";
        cout << "3. Baca Data dari File\n";
        cout << "4. Tampilkan Data Siswa\n";
        cout << "5. Sorting Nilai (Counting Sort)\n";
        cout << "6. Searching Nilai (Binary Search)\n";
        cout << "7. Benchmark vs Bubble Sort\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int n;
                cout << "Jumlah siswa: ";
                cin >> n;
                dataSiswa.resize(n);
                
                for (int i = 0; i < n; i++) {
                    cout << "\nSiswa ke-" << i + 1 << endl;
                    cout << "Nama : ";
                    cin >> ws;
                    getline(cin, dataSiswa[i].nama);
                    cout << "Nilai: ";
                    cin >> dataSiswa[i].nilai;
                }
                sudahSorting = false;
                break;
            }
            
            case 2: {
                int n;
                cout << "Jumlah siswa acak: ";
                cin >> n;
                dataSiswa = generateRandomSiswa(n);
                cout << "Data siswa acak berhasil dibuat!\n";
                sudahSorting = false;
                break;
            }
            
            case 3: {
                string namaFile;
                cout << "Nama file (contoh: data.txt): ";
                cin >> ws;
                getline(cin, namaFile);
                dataSiswa = bacaFileSiswa(namaFile);
                sudahSorting = false;
                break;
            }
            
            case 4:
                cout << "\n================ DATA SISWA ================\n";
                if (!dataSiswa.empty()) {
                    tampilRingkasSiswa(dataSiswa);
                } else {
                    cout << "Data kosong!\n";
                }
                break;
            
            case 5: {
                if (dataSiswa.empty()) {
                    cout << "Data Kosong!\n";
                    break;
                }
                int op;
                auto start = high_resolution_clock::now();
                countingSortSiswa(dataSiswa, op);
                auto stop = high_resolution_clock::now();
                
                cout << "\nData berhasil di-sorting!\n";
                cout << "Jumlah Operasi: " << op << "\n";
                cout << "Waktu: " << duration_cast<milliseconds>(stop - start).count() 
                     << " ms\n";
                sudahSorting = true;
                break;
            }
            
            case 6: {
                if (!sudahSorting) {
                    cout << "Harus sorting nilai dulu!\n";
                    break;
                }
                int target;
                cout << "Masukkan nilai yang dicari: ";
                cin >> target;
                
                auto start = high_resolution_clock::now();
                int hasil = binarySearchSiswa(dataSiswa, target);
                auto stop = high_resolution_clock::now();
                
                if (hasil != -1) {
                    cout << "\n[DITEMUKAN]\n";
                    cout << "Nama: " << dataSiswa[hasil].nama << "\n";
                    cout << "Nilai: " << dataSiswa[hasil].nilai << "\n";
                    cout << "Index: " << hasil << endl;
                } else {
                    cout << "Tidak ditemukan!\n";
                }
                cout << "Waktu Pencarian: " << duration_cast<milliseconds>(stop - start).count() 
                     << " ms\n";
                break;
            }
            
            case 7: {
                benchmarkInt();
                break;
            }
        }
    } while (pilihan != 0);
}

/**
 * Menu untuk operasi pada data String
 */
void menuString() {
    vector<string> dataStr;
    int pilihan;
    
    do {
        cout << "\n=== MENU STRING ===\n";
        cout << "1. Input Manual\n";
        cout << "2. Baca Data dari File\n";
        cout << "3. Tampilkan Data\n";
        cout << "4. Sorting (Bubble Sort)\n";
        cout << "5. Searching (Binary Search)\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int n;
                cout << "Jumlah data teks: ";
                cin >> n;
                dataStr.resize(n);
                cin.ignore();
                
                for (int i = 0; i < n; i++) {
                    cout << "Teks ke-" << i + 1 << ": ";
                    getline(cin, dataStr[i]);
                }
                sudahSorting = false;
                break;
            }
            
            case 2: {
                string namaFile;
                cout << "Nama file: ";
                cin >> ws;
                getline(cin, namaFile);
                dataStr = bacaFileString(namaFile);
                sudahSorting = false;
                break;
            }
            
            case 3:
                cout << "\nIsi Data:\n";
                if (!dataStr.empty()) {
                    tampilkanArrayString(dataStr);
                } else {
                    cout << "Data kosong!\n";
                }
                break;
            
            case 4: {
                if (dataStr.empty()) {
                    cout << "Data Kosong!\n";
                    break;
                }
                int op;
                auto start = high_resolution_clock::now();
                bubbleSortString(dataStr, op);
                auto stop = high_resolution_clock::now();
                
                cout << "\nData berhasil di-sorting!\n";
                cout << "Jumlah Operasi: " << op << "\n";
                cout << "Waktu: " << duration_cast<milliseconds>(stop - start).count() 
                     << " ms\n";
                sudahSorting = true;
                break;
            }
            
            case 5: {
                if (!sudahSorting) {
                    cout << "Harus sorting dulu!\n";
                    break;
                }
                string target;
                cout << "Teks yang dicari: ";
                cin >> ws;
                getline(cin, target);
                
                auto start = high_resolution_clock::now();
                int hasil = binarySearchString(dataStr, target);
                auto stop = high_resolution_clock::now();
                
                if (hasil != -1) {
                    cout << "Ketemu di index " << hasil << endl;
                } else {
                    cout << "Tidak ditemukan!\n";
                }
                cout << "Waktu Pencarian: " << duration_cast<milliseconds>(stop - start).count() 
                     << " ms\n";
                break;
            }
        }
    } while (pilihan != 0);
}

// ============================================================
// MAIN PROGRAM
// ============================================================
int main() {
    srand(time(0));
    int pilihanUtama;
    
    do {
        cout << "\n======================================\n";
        cout << "       PROGRAM SORTING & SEARCHING    \n";
        cout << "======================================\n";
        cout << "Pilih Tipe Data:\n";
        cout << "1. Integer (Data Siswa)\n";
        cout << "2. String (Teks Biasa)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihanUtama;

        if (pilihanUtama == 1) {
            sudahSorting = false;
            menuDataSiswa();
        } else if (pilihanUtama == 2) {
            sudahSorting = false;
            menuString();
        }
    } while (pilihanUtama != 0);

    return 0;
}
