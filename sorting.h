#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <string>

// Struct untuk menyatukan Nama dan Nilai
struct Siswa {
    std::string nama;
    int nilai;
};

void countingSortSiswa(std::vector<Siswa>& arr, int &operasi);
void bubbleSortString(std::vector<std::string>& arr, int &operasi);

#endif