#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include"RndFun.h"
#include <bitset>
using namespace std;

int BitRate;
int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "Verwendung: ./Keccak [Output-Länge] [Datei]\nDer Output muss entweder 224, 256, 384 oder 512 Bits lang sein" << endl;
        return 0;
    }

    //Output-Länge&Bitrate
    int Hashlength = atoi(argv[1]);
    BitRate = 1600 - (2*Hashlength);

    if(Hashlength != 512 && Hashlength != 384 && Hashlength != 256 && Hashlength != 224){
        cout << "Verwendung: ./Keccak [Output-Länge] [Datei]\n Output muss entweder 224, 256, 384 oder 512 Bits lang sein" << endl;
        return 1;
    }

    //Datei->vector<char>
    vector<char> input (0);
    char x;
    ifstream datei (argv[2], fstream::in|fstream::binary);
    while(datei.get(x)){
        input.push_back(x);
    }

    //01-Suffix & pad10*1
    int toInsert = (BitRate/8) - (input.size() %(BitRate/8));
    if(toInsert == 1){
        input.push_back(0b10000110);
    }else{
        input.push_back(0b00000110);
        for(int t = 0; t < toInsert-2; t++){
            input.push_back(0b00000000);
        }
        input.push_back(0b10000000);
    }

    //State Array
    vector< vector<uint64_t> > state (5, vector<uint64_t> (5, 0));

    //Sponge-Konstruktion
    for(int NR=0; NR < input.size(); NR += BitRate/8){
        state = Absorb(input, state, NR);
        state = RPerm(state);
    }
    vector<uint32_t> Hash; // 224/64 = 3.5 -> daher uint32_t stat uint64_t
    for(int l=0; l< Hashlength/32; l++){
        Hash.push_back(Squeeze(state, l));
    }

    //Hash-Output
    int Hexadec;
    for(int t=0; t<Hash.size();t++){
        for(int b = 0; b < 4; b++){
            int by = (Hash[t] >> 8*b) & 255;
            cout << hex << setfill('0') << setw(2) << by;
        }
    }
    cout << endl;


    return 0;
}
