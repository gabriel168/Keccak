#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include<iomanip>

#include"RndFun.h"

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
        return 1;
    }


//Datei->bit-Vektor
    vector<bool> input (0);
    char x;
    ifstream datei (argv[2], fstream::in|fstream::binary);
    while(datei.get(x)){
         for(int i=0; i<=7;++i){
            input.push_back((x >> i) & 1); //Jedes Byte der Inputdatei wird Bitweise dem Vektor hinzugefügt.
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

//Sponge-Konstruktion
    //Aufnahmephase
    for(int NR=0; NR < input.size(); NR += BitRate){
        state = Absorb(input, state, NR);
        state = RPerm(state);
    }
    //Ausgabephase
    vector<bool> Hash(Hashlength);
    for(int l=0; l< Hashlength; l++){
        Hash[l]=Squeeze(state, l);
    }

//Hash-Output, mit Umwandlung vom Binär- ins Hexadezimalsystem
    int output;
    cout << "SHA3-" << Hashlength << ": ";
    for(int t=0; t<Hash.size();t += 8){
        output = 128*Hash[t+7]+64*Hash[t+6]+32*Hash[t+5]+16*Hash[t+4]+8*Hash[t+3]+4*Hash[t+2]+2*Hash[t+1]+Hash[t];
        cout << setfill('0') << setw(2) << hex << output;
    }
    cout << endl;

    return 0;
}
