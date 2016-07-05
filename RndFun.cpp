#include"RndFun.h"
#include<vector>
#include <iostream>
#include<fstream>
#include<cmath>
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
        int xtmp = x;
        x = y;
        y = (2*xtmp+3*y)%5;
        }
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
    Sarray B(5,sheet(5,lane(64)));
    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            for(int z=0;z<64;z++){
                   B[x][y][z] = A[x][y][z]^((A[(x+1)%5 ][y][z]^1)&(A[(x+1)%5 ][y][z]));
            }
        }
    }
}

bool rc(int t){
    vector<bool> R(8); R={0,0,0,0,0,0,0,1};
    for(int i = 1; i < (t%255);i++){
        R.push_back(0);
        R[8]=R[8]^R[0];
        R[4]=R[4]^R[0];
        R[3]=R[3]^R[0];
        R[2]=R[2]^R[0];
        R.erase(R.begin());
    }
    return R[7];
}

Sarray Iota(Sarray A,int RIndex){
    vector<bool> RC (64); for(int a = 0; a < 64; a++){ RC[a]=0;}
    for(int j=0; j<=6; j++){RC[pow(2,j)-1]=rc(j+7*RIndex);}
    for(int z=0; z<64 ;z++){A[0][0][z]=A[0][0][z]^RC[z];}
    return A;
}

