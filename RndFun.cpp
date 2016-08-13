#include"RndFun.h"
#include<vector>
#include <iostream>
#include<fstream>
#include<deque>
#include<cmath>
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
                A[x][y][z]=A[x][y][z]^D[x][z];
            }
        }
    }
    return A;
}

Sarray Rho(Sarray A){
    Sarray B(5,sheet(5,lane(64)));
    for(int z=0;z<64;z++){
        B[0][0][z] = A[0][0][z];
        B[1][0][(z+1)%64] = A[1][0][z];
        B[0][2][(z+3)%64] = A[0][2][z];
        B[2][1][(z+6)%64] = A[2][1][z];
        B[1][2][(z+10)%64] = A[1][2][z];
        B[2][3][(z+15)%64] = A[2][3][z];
        B[3][3][(z+21)%64] = A[3][3][z];
        B[3][0][(z+28)%64] = A[3][0][z];
        B[0][1][(z+36)%64] = A[0][1][z];
        B[1][3][(z+45)%64] = A[1][3][z];
        B[3][1][(z+55)%64] = A[3][1][z];
        B[1][4][(z+66)%64] = A[1][4][z];
        B[4][4][(z+78)%64] = A[4][4][z];
        B[4][0][(z+91)%64] = A[4][0][z];
        B[0][3][(z+105)%64] = A[0][3][z];
        B[3][4][(z+120)%64] = A[3][4][z];
        B[4][3][(z+136)%64] = A[4][3][z];
        B[3][2][(z+153)%64] = A[3][2][z];
        B[2][2][(z+171)%64] = A[2][2][z];
        B[2][0][(z+190)%64] = A[2][0][z];
        B[0][4][(z+210)%64] = A[0][4][z];
        B[4][2][(z+231)%64] = A[4][2][z];
        B[2][4][(z+253)%64] = A[2][4][z];
        B[4][1][(z+276)%64] = A[4][1][z];
        B[1][1][(z+300)%64] = A[1][1][z];
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
    if(t%255 == 0){return 1;}
    deque<bool> R(8); R={1,0,0,0,0,0,0,0};
    for(int i = 1; i <= (t%255);i++){
        R.push_front(0);
        R[0]=R[0]^R[8];
        R[4]=R[4]^R[8];
        R[5]=R[5]^R[8];
        R[6]=R[6]^R[8];
        R.pop_back();
    }
    return R[0];
}

Sarray Iota(Sarray A,int RIndex){
    vector<bool> RC (64);
    for(int a = 0; a < 64; a++){
        RC[a]=0;
    }
    for(int j=0; j<=6; j++){
        RC[pow(2,j)-1]=rc(j+(7*RIndex));
    }
    for(int z=0; z<64 ;z++){
        A[0][0][z]=A[0][0][z]^RC[z];}
    return A;
}

Sarray RPerm(Sarray A){
    for(int RIndex = 0; RIndex < 24; RIndex++){
        cout << ">>RUNDE" << dec << RIndex << "<<:\n";
        A = Theta(A); cout << "Theta\n"; PrintSarrBytes(A);
        A = Rho(A); cout << "Rho\n"; PrintSarrBytes(A);
        A = Pi(A); cout << "Pi\n"; PrintSarrBytes(A);
        A = Chi(A); cout << "Chi\n"; PrintSarrBytes(A);
        A = Iota(A, RIndex); cout << "Iota\n"; PrintSarrBytes(A);
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

void PrintSarrBytes(Sarray A){
    int ByteVal;
    for(int y=0;y<5;y++){
        for(int x=0;x<5;x++){
            for(int z=0;z<64/8;z++){
                ByteVal = A[x][y][(z*8)]+2*A[x][y][1+(z*8)]+4*A[x][y][2+(z*8)]+8*A[x][y][3+(z*8)]+16*A[x][y][4+(z*8)]+32*A[x][y][5+(z*8)]+64*A[x][y][6+(z*8)]+128*A[x][y][7+(z*8)];
                if(ByteVal < 16){cout << "0";}
                cout << hex << ByteVal << " ";
            }
        if((x+y)%2 != 0 || (y == 4 && x == 4)){cout << "\n";}
        }
    }
}
