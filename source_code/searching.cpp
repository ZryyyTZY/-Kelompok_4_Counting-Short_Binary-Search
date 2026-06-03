#include "searching.h"
#include <iostream>

using namespace std;

int binarySearchSiswa(vector<Siswa> arr, int targetNilai) {
    int kiri = 0, kanan = arr.size() - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (arr[tengah].nilai == targetNilai) return tengah;
        if (arr[tengah].nilai < targetNilai) kiri = tengah + 1;
        else kanan = tengah - 1;
    }
    return -1;
}

int binarySearchString(vector<string> arr, string target) {
    int kiri = 0, kanan = arr.size() - 1;
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (arr[tengah] == target) return tengah;
        if (arr[tengah] < target) kiri = tengah + 1;
        else kanan = tengah - 1;
    }
    return -1;
}