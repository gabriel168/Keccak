#include"RndFun.h"
#include<vector>
#include <iostream>
using namespace std;


Sarray Theta(Sarray A){
    vector< vector<bool> > C(5, vector<bool>(64));
    vector< vector<bool> > D(5, vector<bool>(64));

    for(int x=0;x<5;x++){
        for(int z=0;z<64;z++){
            C[x][z] = A[x][0][z]^A[x][1][z]^A[x][2][z]^A[x][3][z]^A[x][4][z];
        }
    }

    for(int x=0;x<5;x++){
        for(int z=0;z<64;z++){
            D[x][z] = C[(x-1)%5][z]^C[(x+1)%5][(z-1)%64];
        }
    }

    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            for(int z=0;z<64;z++){
                A[x][y][z]=A[x][y][z]^D[x][y];
            }
        }
    }
    return A;
}

Sarray Rho(Sarray A){
    Sarray B(5,sheet(5,lane(64)));
    for(int z = 0; z++; z<64){
        B[0][0][z] = A[0][0][z];
    }
    unsigned int x=1,y=0;
    for(unsigned int t=0;t<24;t++){
        for(int z = 0; z++; z<64){
            B[0][0][z] = A[0][0][(z-(t+1)*(t+2)/2)%64];
        }
    int p = x;
    x = y;
    y = (2*p+3*y)%5;
    }
    return B;
}

Sarray Pi(Sarray A){
    Sarray B(5,sheet(5,lane(64)));
    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            for(int z=0;z<64;z++){
                   B[x][y][z] = A[(x+3*y)%5][x][z];
            }
        }
    }
    return B;
}

Sarray Chi(Sarray A){

}
