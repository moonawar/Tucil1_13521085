/*
    Name    : Addin Munawwar Yusuf
    NIM     : 13521085
    Description : Modul untuk menjalankan operasi kartu yang diperlukan dalam 24 game solver
*/

bool isValid(char c) {
//Mengecek apakah sebuah karakter merupakan kartu yang valid
    return (c == 'A' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8'
    || c == '9' || c == 'J' || c == 'Q' || c == 'K');
}

int charToInt(char c) {
//Mengubah sebuah karakter kartu menjadi bilangan
    if (c == 'A') {
        return 1;
    } else if (c == 'J') {
        return 11;
    } else if (c == 'Q') {
        return 12;
    } else if (c == 'K') {
        return 13;
    } else {
        return c - '0';
    }
}

char intToChar(int i) {
//Mengubah sebuah bilangan kartu menjadi karakter
    if (i == 1) {
        return 'A';
    } else if (i == 11) {
        return 'J';
    } else if (i == 12) {
        return 'Q';
    } else if (i == 13) {
        return 'K';
    } else {
        return i + '0';
    }
}