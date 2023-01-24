/*
    Name    : Addin Munawwar Yusuf
    NIM     : 13521085
    Description :      
        - Script yang digunakan untuk men-generate kode dari fungsi evaluate() yang ada di main.cpp 
        - Tujuan dari script ini adalah untuk meningkatkan produktivitas dengan hard coding semua permutasi yang mungkin
          dari 24 game solver dengan brute force, sehingga kita tidak perlu mencari permutasi setiap kali menjalankan program
          (karena kita sudah melakukan hal tersebut di awal)
        - Output dari program ini akan disimpan di file evaluate.txt, yang kemudian akan di-copy secara manual ke program main.cpp
*/

int main();
/* I.S : Sembarang
   F.S : Kode lengkap yang dapat mengevaluasi ekspresi dengan 4 variabel dan semua permutasi dari 3 operator
         tertulis di evaluate.txt */

void writeCode(int i, int j, int k);
/* I.S : Sembarang
   F.S : Kode yang dapat mengevaluasi ekspresi dengan 4 variabel dan sebuah permutasi dari 3 operator
         tertulis di evaluate.txt */