#include <iostream>
#include <fstream>
#include <vector>
#include"RndFun.h"
#include<cmath>

using namespace std;
int BitRate = 576;

int main(int argc, char *argv[]){

//Datei->bit-Vektor
    vector<bool> input (0);
    ifstream datei (argv[1], fstream::in|fstream::binary);
    char x; int g = 0;
    while(datei.get(x)){
        for(int i=0; i<=7;++i){
            g=g+1;
            input.push_back((x >> (7-i)) & 1);
        }
     }

//01-Suffix
    input.push_back(0);
    input.push_back(1);

//pad10*1-
    input.push_back(1);
    while((input.size()+1)%BitRate>0){
        input.push_back(0);}
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

//Sponge
for(int NR=0; NR<(input.size()/BitRate); NR++){
    state=Absorb(input, state, NR*BitRate);
    state = RPerm(state);
}
vector<bool> Hash(512);
for(int l=0; l< 512; l++){
    Hash[l]=Squeeze(state, l);
}


//Hash-Output
for(unsigned long t=0; t<Hash.size();t++){cout << Hash[t]; }
cout << endl;
//State-Output

    return 0;
}
