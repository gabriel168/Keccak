#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include"RndFun.h"

using namespace std;

int BitRate;
int main(int argc, char *argv[]){
//Output-Länge&Bitrate
    int Hashlength = atoi(argv[1]);

    if(Hashlength != 512 && Hashlength != 384 && Hashlength != 256 && Hashlength != 224){
        cout << "Verwendung: ./Keccak [Output-Länge] [Datei]\n Output muss entweder 224, 256, 384 oder 512 Bits lang sein" << endl;
        return 1;
    }

    BitRate = 1600 - (2 * Hashlength);

//Datei->bit-Vektor
    vector<bool> input (0);
    char x;
    ifstream datei (argv[2], fstream::in|fstream::binary);
    while(datei.get(x)){
         for(int i=0; i<=7;++i){
            input.push_back((x >> i) & 1);
        }
    }

//01-Suffix
    input.push_back(0);
    input.push_back(1);

//pad10*1-
    input.push_back(1);
    while((input.size()+1)%(BitRate)>0){
        input.push_back(0);
    }
    input.push_back(1);

//State Array
    Sarray state(5,sheet(5,lane(64)));
        for(int x=0;x<5;x++){
            for(int y=0;y<5;y++){
                for(int z=0;z<64;z++){
                       state[x][y][z] = 0;
                }
            }
        }

//Sponge-Konstruktion
    for(int NR=0; NR < input.size(); NR += BitRate){
    state=Absorb(input, state, NR);
    state = RPerm(state);
    }

    vector<bool> Hash(Hashlength);
    for(int l=0; l< Hashlength; l++){
        Hash[l]=Squeeze(state, l);
    }



//Hash-Output
    int Hexadec;
    cout << "SHA3-" << Hashlength << ": ";
    for(int t=0; t<Hash.size()/8;t++){
        Hexadec = 8*Hash[8*t+7]+4*Hash[8*t+6]+2*Hash[8*t+5]+Hash[8*t+4];
        cout << hex << Hexadec;
        Hexadec = 8*Hash[8*t+3]+4*Hash[8*t+2]+2*Hash[8*t+1]+Hash[8*t];
        cout << hex << Hexadec;
    }
    cout << endl;

    return 0;
}
