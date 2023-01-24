/*
    Name    : Addin Munawwar Yusuf
    NIM     : 13521085
    Description : Program utama untuk 24 game solver
*/

#include <vector>
#include <string>
using namespace std;

int main();
/*Program utama yang menjalankan 24 game solver*/

vector<int> handleInputCards();
/*Mengembalikan input kartu, baik melalui input maupun random generation*/

void handleFileSave(vector<int> cards, vector<string> solutions);
/*I.S : Solusi dari 24 game solver sudah ditemukan
  F.S : Solusi disimpan (ataupun tidak) ke dalam file di folder test*/

void evaluate(float a, float b, float c, float d);
/*I.S : Input kartu sudah ada
  F.S : Evaluasi kombinasi kartu dengan segala kemungkinan permutasi operator dan tanda kurung yang ada
        dan menyimpan solusi yang menghasilkan 24
        
  Kode pada prosedur ini digenerate oleh brutecoder.cpp*/
