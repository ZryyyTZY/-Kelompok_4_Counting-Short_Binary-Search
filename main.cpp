#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream> // Library untuk fitur ekspor CSV


#include "sorting.h"
#include "searching.h"

using namespace std;
using namespace chrono;

bool sudahSorting = false;

// =====================================
// HELPER 1: COUNTING SORT (KHUSUS BENCHMARK ANGKA)
// =====================================
void countingSortIntBiasa(vector<int>& arr, int &operasi) {
    operasi = 0; if (arr.empty()) return;
    int maxVal = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        operasi++; if (arr[i] > maxVal) maxVal = arr[i];
    }
    vector<int> count(maxVal + 1, 0);
    for (size_t i = 0; i < arr.size(); i++) { count[arr[i]]++; operasi++; }
    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) { arr[index] = i; index++; count[i]--; operasi++; }
    }
}

// =====================================
// HELPER 2: BUBBLE SORT (KHUSUS BENCHMARK ANGKA)
// =====================================
void bubbleSortIntBiasa(vector<int>& arr, int &operasi) {
    operasi = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            operasi++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                operasi++;
            }
        }
    }
}

// =====================================
// FUNGSI UTILITY (TAMPIL DATA)
// =====================================
void tampilkanArraySiswa(vector<Siswa> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << i + 1 << ". " << left << setw(25) << arr[i].nama << " | Nilai: " << arr[i].nilai << endl;
    }
}

void tampilRingkasSiswa(vector<Siswa> arr) {
    int n = arr.size();
    if (n <= 20) { tampilkanArraySiswa(arr); return; }
    cout << "10 Data Pertama:\n";
    for (int i = 0; i < 10; i++) cout << i + 1 << ". " << left << setw(25) << arr[i].nama << " | Nilai: " << arr[i].nilai << endl;
    cout << "\n...\n\n10 Data Terakhir:\n";
    for (int i = n - 10; i < n; i++) cout << i + 1 << ". " << left << setw(25) << arr[i].nama << " | Nilai: " << arr[i].nilai << endl;
}

void tampilkanArrayString(vector<string> arr) {
    for (int i = 0; i < arr.size(); i++) cout << i + 1 << ". " << arr[i] << endl;
}

// =====================================
// FUNGSI GENERATE (KHUSUS DATA SISWA)
// =====================================
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

// =====================================
// FUNGSI BACA FILE
// =====================================
vector<Siswa> bacaFileSiswa(string namaFile) {
    vector<Siswa> data;
    ifstream file(namaFile);
    if (!file.is_open()) { cout << "File tidak ditemukan!\n"; return data; }
    
    string baris;
    int counter = 1;
    while (getline(file, baris)) {
        if (baris.empty()) continue;
        string namaStr = "", angkaStr = "";
        for (char c : baris) {
            if (isdigit(c)) angkaStr += c;
            else namaStr += c;
        }
        Siswa s;
        if (!namaStr.empty() && (namaStr.back() == ' ' || namaStr.back() == '=')) namaStr.pop_back();
        s.nama = namaStr.empty() ? "Siswa " + to_string(counter) : namaStr;
        s.nilai = angkaStr.empty() ? 0 : stoi(angkaStr);
        data.push_back(s);
        counter++;
    }
    file.close();
    cout << data.size() << " Data Siswa berhasil dibaca dari file!\n";
    return data;
}

vector<string> bacaFileString(string namaFile) {
    vector<string> data;
    ifstream file(namaFile);
    if (!file.is_open()) { cout << "File tidak ditemukan!\n"; return data; }
    string kata;
    while (getline(file, kata)) {
        if(!kata.empty()) data.push_back(kata);
    }
    file.close();
    return data;
}

// =====================================
// ANALISIS EKSPERIMENTAL (BENCHMARK)
// =====================================
void benchmarkInt() {
    int ukuranData[] = {100, 500, 1000, 5000, 10000};
    
    // Menggunakan stringstream untuk menyimpan data CSV sementara di memori
    stringstream dataCSV;
    dataCSV << "Data,Kondisi,Algoritma,Waktu(ms),Operasi\n";

    cout << "\n=========================================================\n";
    cout << "        PERBANDINGAN COUNTING VS BUBBLE SORT (INTEGER)\n";
    cout << "=========================================================\n";
    cout << left << setw(12) << "Data" << setw(15) << "Kondisi" << setw(20) << "Algoritma" << setw(15) << "Waktu(ms)" << setw(15) << "Operasi" << endl;
    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < 5; i++) {
        int n = ukuranData[i];
        vector<int> kondisi[4];
        for(int m=0; m<n; m++) {
            kondisi[0].push_back(rand() % 10000); kondisi[1].push_back(m);
            kondisi[2].push_back(n - m);          kondisi[3].push_back(rand() % 10);
        }
        string namaKondisi[4] = {"Acak", "Terurut", "Terbalik", "Duplikat"};

        for (int k = 0; k < 4; k++) {
            // PROSES COUNTING SORT
            vector<int> arr1 = kondisi[k]; int op1;
            auto start1 = high_resolution_clock::now();
            countingSortIntBiasa(arr1, op1);
            auto stop1 = high_resolution_clock::now();
            long long time1 = duration_cast<milliseconds>(stop1 - start1).count();
            
            // Print ke terminal
            cout << left << setw(12) << n << setw(15) << namaKondisi[k] << setw(20) << "Counting Sort"
                 << setw(15) << time1 << setw(15) << op1 << endl;
            // Simpan ke memori CSV
            dataCSV << n << "," << namaKondisi[k] << ",Counting Sort," << time1 << "," << op1 << "\n";

            // PROSES BUBBLE SORT (Menggunakan helper di atas)
            vector<int> arr2 = kondisi[k]; int op2;
            auto start2 = high_resolution_clock::now();
            bubbleSortIntBiasa(arr2, op2);
            auto stop2 = high_resolution_clock::now();
            long long time2 = duration_cast<milliseconds>(stop2 - start2).count();
            
            // Print ke terminal
            cout << left << setw(12) << n << setw(15) << namaKondisi[k] << setw(20) << "Bubble Sort"
                 << setw(15) << time2 << setw(15) << op2 << endl;
            // Simpan ke memori CSV
            dataCSV << n << "," << namaKondisi[k] << ",Bubble Sort," << time2 << "," << op2 << "\n";
        }
    }
    cout << "=========================================================\n";
    
    // Pilihan Manual untuk Ekspor
    char pilihanEkspor;
    cout << "Apakah Anda ingin mengekspor hasil benchmark ini ke file CSV? (y/n): ";
    cin >> pilihanEkspor;

    if (pilihanEkspor == 'y' || pilihanEkspor == 'Y') {
        ofstream fileExport("hasil_benchmark.csv");
        if (fileExport.is_open()) {
            fileExport << dataCSV.str(); // Tulis data dari memori ke file asli
            cout << "\n[SUKSES] Tabel perbandingan telah diekspor ke file 'hasil_benchmark.csv'\n";
            fileExport.close();
        } else {
            cout << "\n[GAGAL] Tidak dapat membuat file ekspor.\n";
        }
    } else {
        cout << "\nHasil benchmark tidak diekspor.\n";
    }
}

// =====================================
// MENU DATA SISWA
// =====================================
void menuDataSiswa() {
    vector<Siswa> dataSiswa;
    int pilihan;
    do {
        cout << "\n=== MENU DATA INTEGER ===\n";
        cout << "1. Input Manual\n2. Generate Data Acak\n3. Baca Data dari File\n";
        cout << "4. Tampilkan Data Siswa\n5. Sorting Nilai (Counting Sort)\n6. Searching Nilai (Binary Search)\n";
        cout << "7. Benchmark vs Bubble Sort\n0. Kembali ke Menu Utama\nPilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int n; cout << "Jumlah siswa: "; cin >> n;
                dataSiswa.resize(n);
                for (int i = 0; i < n; i++) { 
                    cout << "\nSiswa ke-" << i+1 << endl;
                    cout << "Nama : "; cin >> ws; getline(cin, dataSiswa[i].nama);
                    cout << "Nilai: "; cin >> dataSiswa[i].nilai;
                }
                sudahSorting = false; break;
            }
            case 2: {
                int n; cout << "Jumlah siswa acak: "; cin >> n;
                dataSiswa = generateRandomSiswa(n);
                cout << "Data siswa acak berhasil dibuat!\n";
                sudahSorting = false; break;
            }
            case 3: {
                string namaFile; cout << "Nama file (contoh: data.txt): "; cin >> ws; getline(cin, namaFile);
                dataSiswa = bacaFileSiswa(namaFile);
                sudahSorting = false; break;
            }
            case 4:
                cout << "\n================ DATA SISWA ================\n"; 
                tampilRingkasSiswa(dataSiswa); break;
            case 5: {
                if(dataSiswa.empty()) { cout<<"Data Kosong!\n"; break; }
                int op;
                auto start = high_resolution_clock::now();
                countingSortSiswa(dataSiswa, op);
                auto stop = high_resolution_clock::now();
                cout << "\nData berhasil di-sorting!\nJumlah Operasi: " << op 
                     << "\nWaktu: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";
                sudahSorting = true; break;
            }
            case 6: {
                if (!sudahSorting) { cout << "Harus sorting nilai dulu!\n"; break; }
                int target; cout << "Masukkan nilai yang dicari: "; cin >> target;
                auto start = high_resolution_clock::now();
                int hasil = binarySearchSiswa(dataSiswa, target);
                auto stop = high_resolution_clock::now();
                if (hasil != -1) {
                    cout << "\n[DITEMUKAN]\nNama: " << dataSiswa[hasil].nama << "\nNilai: " << dataSiswa[hasil].nilai << "\nIndex: " << hasil << endl;
                } else cout << "Tidak ditemukan!\n";
                cout << "Waktu Pencarian: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";
                break;
            }
            case 7: {
                benchmarkInt();
                break;
            }
        }
    } while (pilihan != 0);
}

// =====================================
// MENU STRING
// =====================================
void menuString() {
    vector<string> dataStr;
    int pilihan;
    do {
        cout << "\n=== MENU STRING ===\n";
        cout << "1. Input Manual\n2. Baca Data dari File\n3. Tampilkan Data\n";
        cout << "4. Sorting (Bubble Sort)\n5. Searching (Binary Search)\n0. Kembali ke Menu Utama\nPilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int n; cout << "Jumlah data teks: "; cin >> n;
                dataStr.resize(n);
                cin.ignore();
                for (int i = 0; i < n; i++) { cout << "Teks ke-" << i+1 << ": "; getline(cin, dataStr[i]); }
                sudahSorting = false; break;
            }
            case 2: {
                string namaFile; cout << "Nama file: "; cin >> ws; getline(cin, namaFile);
                dataStr = bacaFileString(namaFile);
                sudahSorting = false; break;
            }
            case 3:
                cout << "\nIsi Data:\n"; tampilkanArrayString(dataStr); break;
            case 4: {
                if(dataStr.empty()) { cout<<"Data Kosong!\n"; break; }
                int op;
                auto start = high_resolution_clock::now();
                bubbleSortString(dataStr, op);
                auto stop = high_resolution_clock::now();
                cout << "\nData berhasil di-sorting!\nJumlah Operasi: " << op 
                     << "\nWaktu: " << duration_cast<milliseconds>(stop - start).count() << " ms\n";
                sudahSorting = true; break;
            }
            case 5: {
                if (!sudahSorting) { cout << "Harus sorting dulu!\n"; break; }
                string target; cout << "Teks yang dicari: "; cin >> ws; getline(cin, target);
                auto start = high_resolution_clock::now();
                int hasil = binarySearchString(dataStr, target);
                auto stop = high_resolution_clock::now();
                if (hasil != -1) cout << "Ketemu di index " << hasil << endl;
                else cout << "Tidak ditemukan!\n";
                break;
            }
        }
    } while (pilihan != 0);
}

// =====================================
// MAIN PROGRAM
// =====================================
int main() {
    srand(time(0));
    int pilihanUtama;
    do {
        cout << "\n======================================\n";
        cout << "       PROGRAM SORTING & SEARCHING    \n";
        cout << "======================================\n";
        cout << "Pilih Tipe Data:\n1. Integer\n2. String (Teks Biasa)\n0. Keluar\nPilihan: ";
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