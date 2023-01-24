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

#include "./brutecoder.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

vector<char> ops = {'+', '-', '*', '/'}; // operator
ofstream ofile; // Output file : evaluate.txt

int main() {
/* I.S : Sembarang
   F.S : Kode lengkap yang dapat mengevaluasi ekspresi dengan 4 variabel dan semua permutasi dari 3 operator
         tertulis di evaluate.txt */

    ofile.open("evaluate.txt");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                // Tulis kode untuk setiap permutasi operator
                writeCode(i, j, k);
            }
        }
    }

    ofile.close();
    return 0;
}

void writeCode(int i, int j, int k) {
/* I.S : Sembarang
   F.S : Kode yang dapat mengevaluasi ekspresi dengan 4 variabel dan sebuah permutasi dari 3 operator
         tertulis di evaluate.txt */
         
    char codeline[75]; // Container sementara untuk menampung kode
    
    // Evaluasi untuk setiap kasus tanda kurung

    // --- A. 1 group of 2 ---
    // Dapat diabaikan karena hasil dari kasus ini tertampung di kasus lain

    // --- B. 2 group of 2 --- 
    // Satu-satunya kasus (a op b) op (c op d)
    if (ops[i] == '/'){ // Handle division by zero
        sprintf(codeline, "if (b != 0) {");
        ofile << codeline << endl;
    }
    if (ops[k] == '/'){
        sprintf(codeline, "if (d != 0) {");
        ofile << codeline << endl;
    }

    if (ops[j] == '/'){
        sprintf(codeline, "if (c %c d != 0) {", ops[k]);
        ofile << codeline << endl;
    }

    // Tulis kode ke evaluate.txt
    sprintf(codeline, "if ((float)((a %c b) %c (c %c d)) == (float)RESULT) {", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sprintf(sol_char, \"(%%d %c %%d) %c (%%d %c %%d)\", (int)a, (int)b, (int)c, (int)d);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sol_str.assign(sol_char);");
    ofile << codeline << endl;
    sprintf(codeline, "    if (!isMember(solutions, sol_str)){");
    ofile << codeline << endl;
    sprintf(codeline, "    solutions.push_back(sol_str);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    ofile << "}" << endl;
    ofile << "}" << endl;

    if (ops[i] == '/'){
        ofile << "}" << endl;
    }
    if (ops[j] == '/'){
        ofile << "}" << endl;
    }

    if (ops[k] == '/'){
        ofile << "}" << endl;
    }

    // --- C. 1 group of 3 --- 
    // Dapat diabaikan karena hasil dari kasus ini tertampung di kasus lain

    // --- D.  group of 3 (with 2 inside) ---
    // Kasus 1 ((a op b) op c) op d
    if (ops[i] == '/'){ // Handle division by zero
        sprintf(codeline, "if (b != 0) {");
        ofile << codeline << endl;
    }

    if (ops[j] == '/'){
        sprintf(codeline, "if (c != 0) {");
        ofile << codeline << endl;
    }

    if (ops[k] == '/'){
        sprintf(codeline, "if (d != 0) {");
        ofile << codeline << endl;
    }

    sprintf(codeline, "if ((float)(((a %c b) %c c) %c d) == (float)RESULT) {", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sprintf(sol_char, \"((%%d %c %%d) %c %%d) %c %%d\", (int)a, (int)b, (int)c, (int)d);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sol_str.assign(sol_char);");
    ofile << codeline << endl;
    sprintf(codeline, "    if (!isMember(solutions, sol_str)){");
    ofile << codeline << endl;
    sprintf(codeline, "    solutions.push_back(sol_str);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    ofile << "}" << endl;
    ofile << "}" << endl;

    if (ops[i] == '/'){
        ofile << "}" << endl;
    }
    if (ops[j] == '/'){
        ofile << "}" << endl;
    }

    if (ops[k] == '/'){
        ofile << "}" << endl;
    }

    // Kasus 2 (a op (b op c)) op d
    if (ops[j] == '/'){  // Handle division by zero
        sprintf(codeline, "if (c != 0) {");
        ofile << codeline << endl;
    }


    if (ops[i] == '/'){
        sprintf(codeline, "if (b %c c != 0) {", ops[j]);
        ofile << codeline << endl;
    }

    if (ops[k] == '/'){
        sprintf(codeline, "if (d != 0) {");
        ofile << codeline << endl;
    }

    sprintf(codeline, "if ((float)((a %c (b %c c)) %c d) == (float)RESULT) {", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sprintf(sol_char, \"(%%d %c (%%d %c %%d)) %c %%d\", (int)a, (int)b, (int)c, (int)d);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sol_str.assign(sol_char);");
    ofile << codeline << endl;
    sprintf(codeline, "    if (!isMember(solutions, sol_str)){");
    ofile << codeline << endl;
    sprintf(codeline, "    solutions.push_back(sol_str);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    ofile << "}" << endl;
    ofile << "}" << endl;

    if (ops[i] == '/'){
        ofile << "}" << endl;
    }
    if (ops[j] == '/'){
        ofile << "}" << endl;
    }

    if (ops[k] == '/'){
        ofile << "}" << endl;
    }

    // Kasus 3 a op ((b op c) op d)
    if (ops[j] == '/'){ // Handle division by zero
        sprintf(codeline, "if (c != 0) {");
        ofile << codeline << endl;
    }

    if (ops[k] == '/'){
        sprintf(codeline, "if (d != 0) {");
        ofile << codeline << endl;
    }

    if (ops[i] == '/'){ 
        sprintf(codeline, "if ((b %c c) %c d != 0) {", ops[j], ops[k]);
        ofile << codeline << endl;
    }

    sprintf(codeline, "if ((float)(a %c ((b %c c) %c d)) == (float)RESULT) {", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sprintf(sol_char, \"%%d %c ((%%d %c %%d) %c %%d)\", (int)a, (int)b, (int)c, (int)d);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sol_str.assign(sol_char);");
    ofile << codeline << endl;
    sprintf(codeline, "    if (!isMember(solutions, sol_str)){");
    ofile << codeline << endl;
    sprintf(codeline, "    solutions.push_back(sol_str);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    ofile << "}" << endl;
    ofile << "}" << endl;

    if (ops[i] == '/'){
        ofile << "}" << endl;
    }
    if (ops[j] == '/'){
        ofile << "}" << endl;
    }

    if (ops[k] == '/'){
        ofile << "}" << endl;
    }
    
    // Kasus 4 a op (b op (c op d))
    if (ops[k] == '/'){ // Handle division by zero
        sprintf(codeline, "if (d != 0) {");
        ofile << codeline << endl;
    }    

    if (ops[j] == '/'){
        sprintf(codeline, "if ((c %c d) != 0) {", ops[k]);
        ofile << codeline << endl;
    }

    if (ops[i] == '/'){ 
        sprintf(codeline, "if (b %c (c %c d) != 0) {", ops[j], ops[k]);
        ofile << codeline << endl;
    }

    sprintf(codeline, "if ((float)(a %c (b %c (c %c d))) == (float)RESULT) {", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sprintf(sol_char, \"%%d %c (%%d %c (%%d %c %%d))\", (int)a, (int)b, (int)c, (int)d);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    sprintf(codeline, "    sol_str.assign(sol_char);");
    ofile << codeline << endl;
    sprintf(codeline, "    if (!isMember(solutions, sol_str)){");
    ofile << codeline << endl;
    sprintf(codeline, "    solutions.push_back(sol_str);", ops[i], ops[j], ops[k]);
    ofile << codeline << endl;
    ofile << "}" << endl;
    ofile << "}" << endl;

    if (ops[i] == '/'){
        ofile << "}" << endl;
    }
    if (ops[j] == '/'){
        ofile << "}" << endl;
    }

    if (ops[k] == '/'){
        ofile << "}" << endl;
    }

}