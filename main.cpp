#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "RndFun.h"
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

    vector< vector<uint64_t> > state_main (5, vector<uint64_t> (5, 0)); //State Array
    vector< vector<uint64_t> > state_alt (5, vector<uint64_t> (5, 0)); //Für Zwischenresultate in RPerm
    vector<uint64_t> TmpArr1 (5), TmpArr2 (5); //Für Zwischenresultate in Theta

    ifstream datei (argv[2], fstream::in|fstream::binary);
    vector<char> InputBuffer (BitRate/8);
    char InputByte;

    //Sponge-Konstruktion
    bool DateiZuEnde = false;
    while(!DateiZuEnde){
        for(int i = 0; i < BitRate/8 && !DateiZuEnde; i++){
            if(datei.get(InputByte)){
                InputBuffer[i] = InputByte;
            }else{
                DateiZuEnde = true;
                pad(InputBuffer, i);
            }
        }
        Absorb(InputBuffer, state_main);
        RPerm(state_main, state_alt, TmpArr1, TmpArr2);
    }
    datei.close();

    //Hash-Output
    for(int t=0; t < Hashlength/32; t++){
        uint32_t Hash = Squeeze(state_main, t); //224/64 = 3.5 -> uint32_t statt uint64_t
        for(int b = 0; b < 4; b++){
            int by = (Hash >> 8*b) & 255;
            cout << hex << setfill('0') << setw(2) << by;
        }
    }
    cout << endl;

    return 0;
}
