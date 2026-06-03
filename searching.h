#ifndef SEARCHING_H
#define SEARCHING_H

#include <vector>
#include <string>
#include "sorting.h" // Memanggil struct Siswa dari sorting.h

int binarySearchSiswa(std::vector<Siswa> arr, int targetNilai);
int binarySearchString(std::vector<std::string> arr, std::string target);

#endif