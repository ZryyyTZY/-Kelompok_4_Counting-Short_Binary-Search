# Program Sorting & Searching - Kelompok 4

## Deskripsi
Program C++ untuk demonstrasi algoritma sorting (Counting Sort dan Bubble Sort) serta searching (Binary Search) dengan data integer (nama dan nilai siswa) dan string.

## Fitur Utama
- **Counting Sort**: Algoritma sorting yang efisien untuk bilangan bulat
- **Bubble Sort**: Algoritma sorting klasik untuk perbandingan
- **Binary Search**: Pencarian cepat pada data yang sudah terurut
- **Benchmark**: Perbandingan performa antara Counting Sort dan Bubble Sort
- **Data Management**: Input manual, generate acak, atau baca dari file

## Struktur Folder
```
Kelompok4_NamaTeknik/
├── source_code/
│   ├── main.cpp
│   ├── sorting.cpp
│   ├── sorting.h
│   ├── searching.cpp
│   ├── searching.h
│   └── README_compile.txt
├── laporan/
│   └── Laporan_Kelompok4.pdf
├── slide/
│   └── Presentasi_Kelompok4.pptx
└── README.md
```

## Cara Kompilasi

### Linux/Mac
```bash
cd source_code
g++ -std=c++11 -o program main.cpp sorting.cpp searching.cpp
./program
```

### Windows (MinGW)
```bash
cd source_code
g++ -std=c++11 -o program.exe main.cpp sorting.cpp searching.cpp
program.exe
```

## Penggunaan
1. Jalankan program
2. Pilih tipe data (Integer atau String)
3. Pilih operasi yang diinginkan dari menu
4. Ikuti instruksi yang diberikan

## Algoritma yang Digunakan

### Counting Sort (Integer)
- **Kompleksitas Waktu**: O(n + k) dimana k adalah range nilai
- **Keuntungan**: Sangat cepat untuk range nilai yang kecil
- **Kelemahan**: Memerlukan array counting dengan ukuran maksimal

### Bubble Sort (String)
- **Kompleksitas Waktu**: O(n²)
- **Keuntungan**: Mudah dipahami dan diimplementasikan
- **Kelemahan**: Lambat untuk data besar

### Binary Search
- **Kompleksitas Waktu**: O(log n)
- **Persyaratan**: Data harus sudah terurut (sorted)
- **Keuntungan**: Pencarian sangat cepat

## Author
Kelompok 4
