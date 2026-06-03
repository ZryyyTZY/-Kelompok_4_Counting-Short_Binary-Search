#ifndef SEARCHING_H
#define SEARCHING_H

#include <vector>
#include <string>
#include "sorting.h"

// Fungsi Binary Search untuk mencari Siswa berdasarkan nilai
int binarySearchSiswa(const std::vector<Siswa>& arr, int targetNilai);

// Fungsi Binary Search untuk mencari String
int binarySearchString(const std::vector<std::string>& arr, const std::string& target);

#endif
