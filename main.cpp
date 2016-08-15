#include <iostream>
#include <fstream>
#include <vector>
#include<string>

#include"RndFun.h"

#include"sha3.h"


using namespace std;
int BitRate = 576;


int main(int argc, char *argv[]){
//Test(sha3.h)
    SHA3 sha3;
    sha3.reset();
    char* xPtr;

//Datei->bit-Vektor
    vector<bool> input (0);
    ifstream datei (argv[1], fstream::in|fstream::binary);
    char x;
    string Sinput("");
    while(datei.get(x)){
        xPtr = &x;
        Sinput.push_back(x);
        sha3.add(xPtr, 1);
        for(int i=0; i<=7;++i){
            input.push_back((x >> (i)) & 1);
        }
    }

//InputOutput
    cout << "Input:";
    for(int n = 0; n<input.size(); n++){
        cout << input[n];
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


    cout << "\n ZU ABSORBIEREN: \n";
    for(int c = 0; c < input.size(); c++){cout << input[c];}
    cout << endl;

//State Array
    Sarray state(5,sheet(5,lane(64)));
        for(int x=0;x<5;x++){
            for(int y=0;y<5;y++){
                for(int z=0;z<64;z++){
                       state[x][y][z] = 0;
                }
            }
        }

//Sponge
for(int NR=0; NR<(input.size()/BitRate); NR++){
    state=Absorb(input, state, NR*BitRate);
    cout << "\n ABSORBIERT: \n"; PrintSarrBytes(state);
    state = RPerm(state);
    }

    vector<bool> Hash(512);
    for(int l=0; l< 512; l++){
        Hash[l]=Squeeze(state, l);
    }

//Sinput
    cout << Sinput << endl;


//BitHash-Output
    cout << "BitHash: " << endl;
    for(int t=0; t<Hash.size()/64;t++){
        for(int b = 0; b<64;b++){ cout << Hash[b+t*64] ;}
        cout << "\n";
    }


//Hash-Output
    int Hexadec;
    cout << "Hash:    ";
    for(int t=0; t<Hash.size()/8;t++){
        Hexadec = 8*Hash[8*t+7]+4*Hash[8*t+6]+2*Hash[8*t+5]+Hash[8*t+4];
        cout << hex << Hexadec;
        Hexadec = 8*Hash[8*t+3]+4*Hash[8*t+2]+2*Hash[8*t+1]+Hash[8*t];
        cout << hex << Hexadec;
    }
    cout << endl;

//Test
    cout << "TestHash:";


    string TestHash = sha3.getHash();
    cout << TestHash << endl;
    SHA3 sha32;

    return 0;
}
