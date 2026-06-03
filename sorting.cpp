#include "sorting.h"
#include <iostream>

using namespace std;

void countingSortSiswa(vector<Siswa>& arr, int &operasi) {
    operasi = 0;
    if (arr.empty()) return;

    int maxVal = arr[0].nilai;
    for (size_t i = 1; i < arr.size(); i++) {
        operasi++;
        if (arr[i].nilai > maxVal) maxVal = arr[i].nilai;
    }

    vector<vector<Siswa>> urutan(maxVal + 1);

    for (size_t i = 0; i < arr.size(); i++) {
        urutan[arr[i].nilai].push_back(arr[i]);
        operasi++;
    }

    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        for (size_t j = 0; j < urutan[i].size(); j++) {
            arr[index] = urutan[i][j];
            index++;
            operasi++;
        }
    }
}

void bubbleSortString(vector<string>& arr, int &operasi) {
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