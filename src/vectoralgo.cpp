/*
    Name    : Addin Munawwar Yusuf
    NIM     : 13521085
    Description : Modul untuk menjalankan algoritma vector yang diperlukan dalam 24 game solver
*/

#include "./vectoralgo.h"

bool isMember(vector<string> v, string s) {
/*Mengecek apakah sebuah string t (yang berupa ekspresi) adalah anggota dari vector v*/
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == s)
        {
            return true;
        }
    }
    return false;
}

vector<vector<int>> permutateVector4(vector<int> v){
/*Menghasilkan semua permutasi dari vector v yang berisi 4 buah bilangan*/
    vector<vector<int>> result;
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            for (int k = 0; k < v.size(); k++)
            {
                for (int l = 0; l < v.size(); l++)
                {
                    if (i != j && i != k && i != l && j != k && j != l && k != l)
                    {
                        vector<int> temp;
                        temp.push_back(v[i]);
                        temp.push_back(v[j]);
                        temp.push_back(v[k]);
                        temp.push_back(v[l]);
                        result.push_back(temp);
                    }
                }
            }
        }
    }
    return result;
}