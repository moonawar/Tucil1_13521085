/*
    Name    : Addin Munawwar Yusuf
    NIM     : 13521085
    Description : Program utama untuk 24 game solver
*/

#include "./main.h"
#include "./vectoralgo.h"
#include "./cards.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

int RESULT = 24;
vector<string> solutions;

double execTime;

int main(){
/* Program utama yang menjalankan 24 game solver */
    vector<int> nums = handleInputCards(); // Input kartu
    
    auto start_s = high_resolution_clock::now(); // Mulai timer
    vector<vector<int>> permutations = permutateVector4(nums); // Permutasi kartu
    for (int i = 0; i < permutations.size(); i++){ // Evaluasi permutasi kartu
        evaluate(permutations[i][0], permutations[i][1], permutations[i][2], permutations[i][3]);
    }

    // Output
    if (solutions.size() == 0) { // Jika tidak ada solusi
        cout << "Tidak ada solusi." << endl;
    } else { // Jika ada solusi
        cout << "Solusi ditemukan: " << solutions.size() << endl;
        for (int i = 0; i < solutions.size(); i++) {
            cout << solutions[i] << endl;
        }
    }
    auto stop_s = high_resolution_clock::now(); // Stop timer

    // Hitung waktu eksekusi
    execTime = duration_cast<milliseconds>(stop_s - start_s).count();
    cout << endl << "Execution time: " << execTime << " ms" << endl;

    // Simpan ke file (jika diminta)
    handleFileSave(nums, solutions);

    return 0;
}

vector<int> handleInputCards(){
/* Mengembalikan input kartu, baik melalui input maupun random generation */
    cout << endl << "Apakah anda ingin memasukkan input sendiri atau generate secara random?" << endl << "1. Masukkan sendiri" << endl << "2. Generate random" << endl << endl;
    int input;
    cout << "Masukkan pilihan: ";
    cin >> input;
    if (input == 1){
        char a, b, c, d;
        cout << endl << "Masukkan 4 kartu yang ingin dihitung dengan spasi sebagai pemisah: " << endl << "Contoh: A 3 4 Q" << endl << endl;
        cin >> a >> b >> c >> d; // Input kartu
        while (!isValid(a) || !isValid(b) || !isValid(c) || !isValid(d)){
            cout << "Input tidak valid! Silahkan ulangi!" << endl << flush;
            char e, f, g, h;
            cin >> e >> f >> g >> h; // Input kartu
            a = e;
            b = f;
            c = g;
            d = h;
        }
        vector<int> cards = {charToInt(a), charToInt(b), charToInt(c), charToInt(d)};
        return cards;
    } else if (input == 2){
        srand(time(0));
        vector<int> cards = {rand() % 12 + 1, rand() % 12 + 1, rand() % 12 + 1, rand() % 12 + 1}; // Generate kartu secara random
        cout << endl << "Kartu yang dihasilkan: " << intToChar(cards[0]) << " " << 
        intToChar(cards[1]) << " " << intToChar(cards[2]) << " " << intToChar(cards[3]) << endl << endl;
        return cards;
    } else {
        cout << "Input tidak valid! Silahkan ulangi!" << endl;
        return handleInputCards();
    }
}

void handleFileSave(vector<int> cards, vector<string> solutions){
/*I.S : Solusi dari 24 game solver sudah ditemukan
  F.S : Solusi disimpan (ataupun tidak) ke dalam file di folder test*/
    cout << endl << "Apakah anda ingin menyimpan hasil ke file?" << endl << "1. Ya" << endl << "2. Tidak" << endl << endl;
    int input;
    cout << "Masukkan pilihan: ";
    cin >> input;
    if (input == 1){
        cout << "Masukkan nama file: "; // Input nama file
        string filename;
        cin >> filename;
        cout << endl;
        ofstream file;
        
        string filepath = "../test/" + filename + ".txt";

        file.open(filepath);

        // Tulis ke file
        file << "Kartu : " << intToChar(cards[0]) << " " << intToChar(cards[1]) << " " << intToChar(cards[2]) << " " << intToChar(cards[3]) << endl << endl;
        file << "Solusi ditemukan : " << solutions.size() << endl;
        for (int i = 0; i < solutions.size(); i++) {
            file << solutions[i] << endl;
        }
        file << endl << "Execution time : " << execTime << " ms" << endl;
        file.close();
        cout << "File berhasil disimpan di folder test" << endl;
    } else if (input == 2){
        cout << "File tidak disimpan" << endl;
    } else {
        cout << "Input tidak valid! Silahkan ulangi!" << endl;
        handleFileSave(cards, solutions);
    }
}

void evaluate(float a, float b, float c, float d) {
/*I.S : Input kartu sudah ada
  F.S : Evaluasi kombinasi kartu dengan segala kemungkinan permutasi operator dan tanda kurung yang ada
        dan menyimpan solusi yang menghasilkan 24
        
  Kode pada prosedur ini digenerate oleh brutecoder.cpp*/

    char sol_char[50];
    string sol_str;

    // Hasil dari brutecoder.cpp
    if ((float)((a + b) + (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) + (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) + c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) + %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b + c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d + %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b + c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d + %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b + (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d + (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + b) + (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) + (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) + c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) + %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b + c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d + %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b + c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d + %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b + (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d + (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + b) + (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) + (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) + c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) + %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b + c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d + %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b + c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d + %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b + (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d + (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a + b) + (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) + (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a + b) + c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) + %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a + (b + c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d + %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a + ((b + c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d + %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a + (b + (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d + (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((float)((a + b) - (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) - (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) - c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) - %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b - c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d - %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b - c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d - %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b - (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d - (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + b) - (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) - (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) - c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) - %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b - c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d - %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b - c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d - %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b - (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d - (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + b) - (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) - (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) - c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) - %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b - c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d - %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b - c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d - %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b - (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d - (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a + b) - (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) - (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a + b) - c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) - %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a + (b - c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d - %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a + ((b - c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d - %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a + (b - (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d - (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((float)((a + b) * (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) * (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) * c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) * %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b * c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d * %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b * c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d * %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b * (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d * (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + b) * (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) * (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) * c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) * %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b * c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d * %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b * c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d * %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b * (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d * (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + b) * (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) * (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a + b) * c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) * %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a + (b * c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d * %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + ((b * c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d * %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a + (b * (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d * (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a + b) * (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) * (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a + b) * c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) * %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a + (b * c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d * %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a + ((b * c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d * %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a + (b * (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d * (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c + d != 0) {
    if ((float)((a + b) / (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) / (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a + b) / c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) / %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a + (b / c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d / %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a + ((b / c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d / %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c + d) != 0) {
    if ((float)(a + (b / (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d / (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c - d != 0) {
    if ((float)((a + b) / (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) / (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a + b) / c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) / %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a + (b / c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d / %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a + ((b / c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d / %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c - d) != 0) {
    if ((float)(a + (b / (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d / (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c * d != 0) {
    if ((float)((a + b) / (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) / (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a + b) / c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) / %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a + (b / c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d / %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a + ((b / c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d / %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c * d) != 0) {
    if ((float)(a + (b / (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d / (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if (c / d != 0) {
    if ((float)((a + b) / (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d + %d) / (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)(((a + b) / c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d + %d) / %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)((a + (b / c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d + (%d / %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)(a + ((b / c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d + ((%d / %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if ((c / d) != 0) {
    if ((float)(a + (b / (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d + (%d / (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if ((float)((a - b) + (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) + (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) + c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) + %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b + c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d + %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b + c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d + %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b + (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d + (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - b) + (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) + (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) + c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) + %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b + c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d + %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b + c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d + %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b + (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d + (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - b) + (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) + (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) + c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) + %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b + c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d + %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b + c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d + %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b + (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d + (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a - b) + (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) + (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a - b) + c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) + %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a - (b + c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d + %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a - ((b + c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d + %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a - (b + (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d + (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((float)((a - b) - (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) - (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) - c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) - %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b - c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d - %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b - c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d - %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b - (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d - (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - b) - (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) - (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) - c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) - %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b - c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d - %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b - c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d - %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b - (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d - (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - b) - (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) - (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) - c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) - %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b - c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d - %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b - c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d - %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b - (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d - (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a - b) - (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) - (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a - b) - c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) - %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a - (b - c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d - %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a - ((b - c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d - %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a - (b - (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d - (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((float)((a - b) * (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) * (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) * c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) * %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b * c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d * %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b * c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d * %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b * (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d * (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - b) * (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) * (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) * c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) * %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b * c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d * %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b * c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d * %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b * (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d * (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - b) * (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) * (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a - b) * c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) * %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a - (b * c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d * %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - ((b * c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d * %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a - (b * (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d * (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a - b) * (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) * (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a - b) * c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) * %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a - (b * c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d * %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a - ((b * c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d * %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a - (b * (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d * (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c + d != 0) {
    if ((float)((a - b) / (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) / (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a - b) / c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) / %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a - (b / c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d / %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a - ((b / c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d / %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c + d) != 0) {
    if ((float)(a - (b / (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d / (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c - d != 0) {
    if ((float)((a - b) / (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) / (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a - b) / c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) / %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a - (b / c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d / %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a - ((b / c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d / %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c - d) != 0) {
    if ((float)(a - (b / (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d / (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c * d != 0) {
    if ((float)((a - b) / (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) / (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a - b) / c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) / %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a - (b / c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d / %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a - ((b / c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d / %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c * d) != 0) {
    if ((float)(a - (b / (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d / (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if (c / d != 0) {
    if ((float)((a - b) / (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d - %d) / (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)(((a - b) / c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d - %d) / %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)((a - (b / c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d - (%d / %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)(a - ((b / c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d - ((%d / %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if ((c / d) != 0) {
    if ((float)(a - (b / (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d - (%d / (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if ((float)((a * b) + (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) + (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) + c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) + %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b + c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d + %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b + c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d + %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b + (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d + (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * b) + (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) + (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) + c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) + %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b + c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d + %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b + c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d + %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b + (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d + (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * b) + (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) + (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) + c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) + %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b + c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d + %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b + c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d + %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b + (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d + (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a * b) + (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) + (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a * b) + c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) + %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a * (b + c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d + %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a * ((b + c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d + %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a * (b + (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d + (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((float)((a * b) - (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) - (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) - c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) - %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b - c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d - %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b - c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d - %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b - (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d - (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * b) - (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) - (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) - c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) - %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b - c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d - %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b - c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d - %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b - (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d - (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * b) - (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) - (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) - c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) - %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b - c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d - %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b - c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d - %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b - (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d - (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a * b) - (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) - (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a * b) - c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) - %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a * (b - c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d - %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a * ((b - c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d - %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a * (b - (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d - (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((float)((a * b) * (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) * (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) * c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) * %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b * c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d * %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b * c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d * %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b * (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d * (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * b) * (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) * (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) * c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) * %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b * c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d * %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b * c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d * %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b * (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d * (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * b) * (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) * (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(((a * b) * c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) * %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)((a * (b * c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d * %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * ((b * c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d * %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if ((float)(a * (b * (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d * (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    if (d != 0) {
    if ((float)((a * b) * (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) * (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(((a * b) * c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) * %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)((a * (b * c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d * %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a * ((b * c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d * %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if ((float)(a * (b * (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d * (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c + d != 0) {
    if ((float)((a * b) / (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) / (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a * b) / c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) / %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a * (b / c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d / %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a * ((b / c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d / %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c + d) != 0) {
    if ((float)(a * (b / (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d / (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c - d != 0) {
    if ((float)((a * b) / (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) / (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a * b) / c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) / %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a * (b / c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d / %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a * ((b / c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d / %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c - d) != 0) {
    if ((float)(a * (b / (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d / (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c * d != 0) {
    if ((float)((a * b) / (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) / (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(((a * b) / c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) / %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)((a * (b / c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d / %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (c != 0) {
    if ((float)(a * ((b / c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d / %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((c * d) != 0) {
    if ((float)(a * (b / (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d / (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (d != 0) {
    if (c / d != 0) {
    if ((float)((a * b) / (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d * %d) / (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)(((a * b) / c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d * %d) / %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)((a * (b / c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d * (%d / %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((float)(a * ((b / c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d * ((%d / %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if ((c / d) != 0) {
    if ((float)(a * (b / (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d * (%d / (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) + (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) + (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) + c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) + %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b + c != 0) {
    if ((float)((a / (b + c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d + %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b + c) + d != 0) {
    if ((float)(a / ((b + c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d + %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b + (c + d) != 0) {
    if ((float)(a / (b + (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d + (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) + (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) + (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) + c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) + %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b + c != 0) {
    if ((float)((a / (b + c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d + %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b + c) - d != 0) {
    if ((float)(a / ((b + c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d + %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b + (c - d) != 0) {
    if ((float)(a / (b + (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d + (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) + (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) + (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) + c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) + %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b + c != 0) {
    if ((float)((a / (b + c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d + %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b + c) * d != 0) {
    if ((float)(a / ((b + c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d + %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b + (c * d) != 0) {
    if ((float)(a / (b + (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d + (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if (d != 0) {
    if ((float)((a / b) + (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) + (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (d != 0) {
    if ((float)(((a / b) + c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) + %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b + c != 0) {
    if (d != 0) {
    if ((float)((a / (b + c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d + %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if ((b + c) / d != 0) {
    if ((float)(a / ((b + c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d + %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if (b + (c / d) != 0) {
    if ((float)(a / (b + (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d + (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) - (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) - (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) - c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) - %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b - c != 0) {
    if ((float)((a / (b - c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d - %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b - c) + d != 0) {
    if ((float)(a / ((b - c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d - %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b - (c + d) != 0) {
    if ((float)(a / (b - (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d - (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) - (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) - (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) - c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) - %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b - c != 0) {
    if ((float)((a / (b - c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d - %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b - c) - d != 0) {
    if ((float)(a / ((b - c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d - %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b - (c - d) != 0) {
    if ((float)(a / (b - (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d - (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) - (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) - (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) - c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) - %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b - c != 0) {
    if ((float)((a / (b - c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d - %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b - c) * d != 0) {
    if ((float)(a / ((b - c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d - %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b - (c * d) != 0) {
    if ((float)(a / (b - (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d - (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if (d != 0) {
    if ((float)((a / b) - (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) - (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (d != 0) {
    if ((float)(((a / b) - c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) - %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b - c != 0) {
    if (d != 0) {
    if ((float)((a / (b - c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d - %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if ((b - c) / d != 0) {
    if ((float)(a / ((b - c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d - %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if (b - (c / d) != 0) {
    if ((float)(a / (b - (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d - (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) * (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) * (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) * c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) * %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b * c != 0) {
    if ((float)((a / (b * c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d * %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b * c) + d != 0) {
    if ((float)(a / ((b * c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d * %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b * (c + d) != 0) {
    if ((float)(a / (b * (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d * (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) * (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) * (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) * c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) * %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b * c != 0) {
    if ((float)((a / (b * c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d * %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b * c) - d != 0) {
    if ((float)(a / ((b * c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d * %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b * (c - d) != 0) {
    if ((float)(a / (b * (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d * (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)((a / b) * (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) * (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if ((float)(((a / b) * c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) * %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b * c != 0) {
    if ((float)((a / (b * c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d * %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if ((b * c) * d != 0) {
    if ((float)(a / ((b * c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d * %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b * (c * d) != 0) {
    if ((float)(a / (b * (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d * (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    if (b != 0) {
    if (d != 0) {
    if ((float)((a / b) * (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) * (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (d != 0) {
    if ((float)(((a / b) * c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) * %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b * c != 0) {
    if (d != 0) {
    if ((float)((a / (b * c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d * %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if ((b * c) / d != 0) {
    if ((float)(a / ((b * c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d * %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (d != 0) {
    if (b * (c / d) != 0) {
    if ((float)(a / (b * (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d * (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (c + d != 0) {
    if ((float)((a / b) / (c + d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) / (%d + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (c != 0) {
    if ((float)(((a / b) / c) + d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) / %d) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (b / c != 0) {
    if ((float)((a / (b / c)) + d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d / %d)) + %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if ((b / c) + d != 0) {
    if ((float)(a / ((b / c) + d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d / %d) + %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if ((c + d) != 0) {
    if (b / (c + d) != 0) {
    if ((float)(a / (b / (c + d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d / (%d + %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (c - d != 0) {
    if ((float)((a / b) / (c - d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) / (%d - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (c != 0) {
    if ((float)(((a / b) / c) - d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) / %d) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (b / c != 0) {
    if ((float)((a / (b / c)) - d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d / %d)) - %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if ((b / c) - d != 0) {
    if ((float)(a / ((b / c) - d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d / %d) - %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if ((c - d) != 0) {
    if (b / (c - d) != 0) {
    if ((float)(a / (b / (c - d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d / (%d - %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (c * d != 0) {
    if ((float)((a / b) / (c * d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) / (%d * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (c != 0) {
    if ((float)(((a / b) / c) * d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) / %d) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if (b / c != 0) {
    if ((float)((a / (b / c)) * d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d / %d)) * %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (c != 0) {
    if ((b / c) * d != 0) {
    if ((float)(a / ((b / c) * d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d / %d) * %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if ((c * d) != 0) {
    if (b / (c * d) != 0) {
    if ((float)(a / (b / (c * d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d / (%d * %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    if (b != 0) {
    if (d != 0) {
    if (c / d != 0) {
    if ((float)((a / b) / (c / d)) == (float)RESULT) {
        sprintf(sol_char, "(%d / %d) / (%d / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    }
    if (b != 0) {
    if (c != 0) {
    if (d != 0) {
    if ((float)(((a / b) / c) / d) == (float)RESULT) {
        sprintf(sol_char, "((%d / %d) / %d) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    }
    if (c != 0) {
    if (b / c != 0) {
    if (d != 0) {
    if ((float)((a / (b / c)) / d) == (float)RESULT) {
        sprintf(sol_char, "(%d / (%d / %d)) / %d", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    }
    if (c != 0) {
    if (d != 0) {
    if ((b / c) / d != 0) {
    if ((float)(a / ((b / c) / d)) == (float)RESULT) {
        sprintf(sol_char, "%d / ((%d / %d) / %d)", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    }
    if (d != 0) {
    if ((c / d) != 0) {
    if (b / (c / d) != 0) {
    if ((float)(a / (b / (c / d))) == (float)RESULT) {
        sprintf(sol_char, "%d / (%d / (%d / %d))", (int)a, (int)b, (int)c, (int)d);
        sol_str.assign(sol_char);
        if (!isMember(solutions, sol_str)){
        solutions.push_back(sol_str);
    }
    }
    }
    }
    }

}