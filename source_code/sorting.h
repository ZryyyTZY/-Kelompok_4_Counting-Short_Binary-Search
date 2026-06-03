#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <string>

// Struct untuk menyatukan Nama dan Nilai Siswa
struct Siswa {
    std::string nama;
    int nilai;
};

// Fungsi Sorting untuk data Siswa
void countingSortSiswa(std::vector<Siswa>& arr, int& operasi);

// Fungsi Sorting untuk data String
void bubbleSortString(std::vector<std::string>& arr, int& operasi);

// Fungsi Sorting helper untuk benchmark (integer)
void bubbleSortIntBiasa(std::vector<int>& arr, int& operasi);
void countingSortIntBiasa(std::vector<int>& arr, int& operasi);

#endif
