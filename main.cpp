#include <iostream>
#include <fstream>
using namespace std;



void ReadBinFile(const string& path_to_file, int* buffer, size_t size_in_bytes){
    ifstream in_file(path_to_file, ios::binary);
    if(!in_file.is_open()) throw invalid_argument("File opening error");
    in_file.seekg(0, ios::end);
    if(in_file.tellg() == 0) return;
    in_file.seekg(0);
    in_file.read((char*)buffer, size_in_bytes);
    in_file.close();
}

void WriteBinFile(const string& path_to_file, int* buffer, size_t size_in_bytes){
    ofstream  out_file(path_to_file, ios::binary);
    if(!out_file.is_open()) throw invalid_argument("File opening error");
    out_file.write((char*)buffer, size_in_bytes);
    out_file.close();
}

void Issuing(int* banknotes_of_ATM, int& money){
    int denominations[5] = {100, 500, 1000, 2000, 5000};
    int count_banknotes;
    for(int i=4; i>=0; --i){
        if(money<denominations[i] || banknotes_of_ATM[i]==0)continue;
        count_banknotes = money/denominations[i];
        if(banknotes_of_ATM[i]>=count_banknotes) {
            banknotes_of_ATM[i] -= count_banknotes;
            money -= count_banknotes * denominations[i];
        }
        else {
            money -= banknotes_of_ATM[i] * denominations[i];
            banknotes_of_ATM = 0;
        }
        if(money==0)break;
    }
}

int main() {
    //номиналы купюр: 100 500 1000 2000 5000
    string path_to_file="D:\\teach programm skillbox\\20.5\\4 ATM\\ATM.bin";
    int banknotes_of_ATM[5] = {0, 0, 0, 0, 0};
    char op;
    cin >> op;
    if(op == '+'){
        int count_banknote=0;
        ReadBinFile(path_to_file, banknotes_of_ATM, 5*sizeof(int));
        for(int i=0; i<5; ++i){
            count_banknote += banknotes_of_ATM[i];
        }
        while(count_banknote<1000){
            banknotes_of_ATM[rand() % 5]++;
            count_banknote++;
        }
        WriteBinFile(path_to_file, banknotes_of_ATM, 5*sizeof(int));
        cout << "The ATM is full";
    }
    else if(op == '-'){
        int money;
        cin >> money;
        if(money % 100 != 0){
            cout << "The operation is not possible";
            return 0;
        }
        ReadBinFile(path_to_file, banknotes_of_ATM, 5*sizeof(int));
        Issuing(banknotes_of_ATM, money);
        if(money==0){
            WriteBinFile(path_to_file, banknotes_of_ATM, 5*sizeof(int));
            cout << "The issue operation was successful";
        }
        else cout << "The operation is not possible";
    }
    else {
        cerr << "Error of input";
    }
    return 0;
}