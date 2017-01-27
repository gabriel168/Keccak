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
        cout << "Verwendung: ./Keccak [Output-Länge] [Datei]\nDer Output muss entweder 224, 256, 384 oder 512 Bits lang sein" << endl;
        return 0;
    }

    vector< vector<uint64_t> > state (5, vector<uint64_t> (5, 0)); //State Array

    ifstream datei (argv[2], fstream::in|fstream::binary);
    char x;
    vector<char> InputBuffer (BitRate/8);

    //Sponge-Konstruktion
    bool DateiZuEnde = false;
    while(!DateiZuEnde){
        for(int i = 0; i < BitRate/8 && !DateiZuEnde; i++){
            if(datei.get(x)){
                InputBuffer[i] = x;
            }else{
                DateiZuEnde = true;
                pad(InputBuffer, i);
            }
        }
        state = Absorb(InputBuffer, state);
        state = RPerm(state);
    }
    datei.close();

    vector<uint32_t> Hash; // 224/64 = 3.5 -> daher uint32_t statt uint64_t
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
