#include"RndFun.h"
#include<vector>
#include <iostream>
#include<fstream>
#include<cmath>
#include<deque>
using namespace std;


Sarray Theta(Sarray A){

    vector< vector<bool> > C(5, vector<bool>(64));

    for(int x=0;x<5;x++){
        for(int z=0;z<64;z++){
            C[x][z] = A[x][0][z]^A[x][1][z]^A[x][2][z]^A[x][3][z]^A[x][4][z];
        }
    }

    vector< vector<bool> > D(5, vector<bool>(64));

    for(int x=0;x<5;x++){
        for(int z=0;z<64;z++){
            D[x][z] = C[(x+4)%5][z]^C[(x+1)%5][(z+63)%64];
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
    for(int z=0;z<64;z++){
    B[0][0][z]=A[0][0][z];
    B[1][0][z] = A[1][0][(z+63)%64];
    B[0][2][z] = A[0][2][(z+61)%64];
    B[2][1][z] = A[2][1][(z+58)%64];
    B[1][2][z] = A[1][2][(z+54)%64];
    B[2][3][z] = A[2][3][(z+49)%64];
    B[3][3][z] = A[3][3][(z+43)%64];
    B[3][0][z] = A[3][0][(z+36)%64];
    B[0][1][z] = A[0][1][(z+28)%64];
    B[1][3][z] = A[1][3][(z+19)%64];
    B[3][1][z] = A[3][1][(z+9)%64];
    B[1][4][z] = A[1][4][(z+62)%64];
    B[4][4][z] = A[4][4][(z+50)%64];
    B[4][0][z] = A[4][0][(z+37)%64];
    B[0][3][z] = A[0][3][(z+23)%64];
    B[3][4][z] = A[3][4][(z+8)%64];
    B[4][3][z] = A[4][3][(z+56)%64];
    B[3][2][z] = A[3][2][(z+39)%64];
    B[2][2][z] = A[2][2][(z+21)%64];
    B[2][0][z] = A[2][0][(z+2)%64];
    B[0][4][z] = A[0][4][(z+46)%64];
    B[4][2][z] = A[4][2][(z+25)%64];
    B[2][4][z] = A[2][4][(z+3)%64];
    B[4][1][z] = A[4][1][(z+44)%64];
    B[1][1][z] = A[1][1][(z+20)%64];
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
                   B[x][y][z] = A[x][y][z]^((A[(x+1)%5][y][z]^1)&(A[(x+2)%5][y][z]));
            }
        }
    }
    return B;
}

bool rc(int t){
    deque<bool> R(8); R={1,0,0,0,0,0,0,0};
    for(int i = 0; i < (t%255);i++){
        R.push_front(0);
        R[0]=R[0]^R[8];
        R[4]=R[4]^R[8];
        R[5]=R[5]^R[8];
        R[6]=R[6]^R[8];
        R.pop_back();
    }
    return R[7];
}

Sarray Iota(Sarray A,int RIndex){
    vector<bool> RC (64);
    for(int a = 0; a < 64; a++){
        RC[a]=0;
    }
    for(int j=0; j<=6; j++){
        RC[(j << 1)-1]=rc(j+7*RIndex);
    }
    for(int z=0; z<64 ;z++){
        A[0][0][z]=A[0][0][z]^RC[z];}
    return A;
}

Sarray RPerm(Sarray A){
    for(int RIndex = 0; RIndex < 24; RIndex++){
        A = Iota(Chi(Pi(Rho(Theta(A)))),RIndex);
    }
    return A;
}

Sarray Absorb(vector<bool> M, Sarray A, int Pos){
    for(int n = 0; n < BitRate; n++){
        A[(n/64)%5][(n/320)%5][n%64]=A[(n/64)%5][(n/320)%5][n%64]^M[n+Pos];
    }
    return A;
}

bool Squeeze(Sarray A, int Pos){
    return (A[(Pos/64)%5][(Pos/320)%5][Pos%64]);
}


