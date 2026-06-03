# Panduan Kompilasi Program Sorting & Searching

## Persyaratan
- C++ Compiler (g++, clang, atau MSVC)
- C++11 atau lebih baru

## Kompilasi di Linux/Mac
```bash
cd source_code
g++ -std=c++11 -o program main.cpp sorting.cpp searching.cpp
./program
```

## Kompilasi di Windows (MinGW)
```bash
cd source_code
g++ -std=c++11 -o program.exe main.cpp sorting.cpp searching.cpp
program.exe
```

## Kompilasi di Windows (Visual Studio)
1. Buka Visual Studio
2. Create → New Project → Empty Project
3. Add Files:
   - main.cpp
   - sorting.cpp
   - searching.cpp
   - sorting.h
   - searching.h
4. Build → Build Solution
5. Debug → Start Without Debugging

## Troubleshooting
- **Error "file not found"**: Pastikan Anda berada di folder `source_code`
- **Error kompilasi**: Pastikan C++ compiler sudah terinstall
- **File input tidak ditemukan**: Pastikan file data berada di folder yang sama dengan executable
