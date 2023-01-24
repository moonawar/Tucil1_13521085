/*
    Name    : Addin Munawwar Yusuf
    NIM     : 13521085
    Description : Modul untuk menjalankan algoritma vector yang diperlukan dalam 24 game solver
*/

#include <vector>
#include <string>
using namespace std;

bool isMember(vector<string> v, string t);
/*Mengecek apakah sebuah string t (yang berupa ekspresi) adalah anggota dari vector v*/

vector<vector<int>> permutateVector4(vector<int> v);
/*Menghasilkan semua permutasi dari vector v yang berisi 4 buah bilangan*/