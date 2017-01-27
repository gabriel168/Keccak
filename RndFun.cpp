#include"RndFun.h"
#include<cmath>
#include<iostream>
#include<iomanip>
#include<bitset>

/*'Rotiert' uint64_ts - über den Rand hinausgeschobene
 *Bits werden am anderen Ende einefügt*/
uint64_t rot(uint64_t v, int offset){
    int s =  offset % 64;
    return (v<<s) | (v>>(64-s));
}

Sarray Theta(Sarray A){
    vector<uint64_t> TmpArr1 (5);
    for(int x=0;x<5;x++){
        TmpArr1[x] = A[x][0]^A[x][1]^A[x][2]^A[x][3]^A[x][4];
    }

    vector<uint64_t> TmpArr2 (5,0);
    for(int x=0;x<5;x++){
        TmpArr2[x] = (TmpArr1[(x+4)%5])^(rot(TmpArr1[(x+1)%5],1));
    }

    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            A[x][y] = A[x][y]^TmpArr2[x];
        }
    }
    return A;
}

Sarray Rho(Sarray A){
    vector< vector<uint64_t> > B (5, vector<uint64_t> (5, 0));
    B[0][0] = A[0][0];
    B[1][0] = rot(A[1][0], 1);
    B[0][2] = rot(A[0][2], 3);
    B[2][1] = rot(A[2][1], 6);
    B[1][2] = rot(A[1][2], 10);
    B[2][3] = rot(A[2][3], 15);
    B[3][3] = rot(A[3][3], 21);
    B[3][0] = rot(A[3][0], 28);
    B[0][1] = rot(A[0][1], 36);
    B[1][3] = rot(A[1][3], 45);
    B[3][1] = rot(A[3][1], 55);
    B[1][4] = rot(A[1][4], 2);
    B[4][4] = rot(A[4][4], 14);
    B[4][0] = rot(A[4][0], 27);
    B[0][3] = rot(A[0][3], 41);
    B[3][4] = rot(A[3][4], 56);
    B[4][3] = rot(A[4][3], 8);
    B[3][2] = rot(A[3][2], 25);
    B[2][2] = rot(A[2][2], 43);
    B[2][0] = rot(A[2][0], 62);
    B[0][4] = rot(A[0][4], 18);
    B[4][2] = rot(A[4][2], 39);
    B[2][4] = rot(A[2][4], 61);
    B[4][1] = rot(A[4][1], 20);
    B[1][1] = rot(A[1][1], 44);
    return B;
}

Sarray Pi(Sarray A){
    vector< vector<uint64_t> > B (5, vector<uint64_t> (5));
    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            B[x][y] = A[(x+3*y)%5][x];
        }
    }
    return B;
}

Sarray Chi(Sarray A){
    vector< vector<uint64_t> > B (5, vector<uint64_t> (5));
    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            B[x][y] = A[x][y] ^ ((0xFFFFFFFFFFFFFFFF^A[(x+1)%5][y]) & (A[(x+2)%5][y]));
        }
    }
    return B;
}

Sarray Iota(Sarray A,int index){
    vector<uint64_t> v = {
        0b0000000000000000000000000000000000000000000000000000000000000001,
        0b0000000000000000000000000000000000000000000000001000000010000010,
        0b1000000000000000000000000000000000000000000000001000000010001010,
        0b1000000000000000000000000000000010000000000000001000000000000000,
        0b0000000000000000000000000000000000000000000000001000000010001011,
        0b0000000000000000000000000000000010000000000000000000000000000001,
        0b1000000000000000000000000000000010000000000000001000000010000001,
        0b1000000000000000000000000000000000000000000000001000000000001001,
        0b0000000000000000000000000000000000000000000000000000000010001010,
        0b0000000000000000000000000000000000000000000000000000000010001000,
        0b0000000000000000000000000000000010000000000000001000000000001001,
        0b0000000000000000000000000000000010000000000000000000000000001010,
        0b0000000000000000000000000000000010000000000000001000000010001011,
        0b1000000000000000000000000000000000000000000000000000000010001011,
        0b1000000000000000000000000000000000000000000000001000000010001001,
        0b1000000000000000000000000000000000000000000000001000000000000011,
        0b1000000000000000000000000000000000000000000000001000000000000010,
        0b1000000000000000000000000000000000000000000000000000000010000000,
        0b0000000000000000000000000000000000000000000000001000000000001010,
        0b1000000000000000000000000000000010000000000000000000000000001010,
        0b1000000000000000000000000000000010000000000000001000000010000001,
        0b1000000000000000000000000000000000000000000000001000000010000000,
        0b0000000000000000000000000000000010000000000000000000000000000001,
        0b1000000000000000000000000000000010000000000000001000000000001000,
    };
    A[0][0] = A[0][0]^(v[index]);
    return A;
}

Sarray RPerm(Sarray A){
    for(int RIndex = 0; RIndex < 24; RIndex++){
        A = Iota(Chi(Pi(Rho(Theta(A)))),RIndex);
    }
    return A;
}

void pad(vector<char>& input, int index){
    int toInsert = (BitRate/8)-index;
    if(toInsert == 1){
        input[index] = (0b10000110);
    }else{
        input[index] = (0b00000110);
        for(int t = 1; t < toInsert-1; t++){
            input[index+t] = (0b00000000);
        }
        input[index+toInsert-1] = (0b10000000);
    }
}

Sarray Absorb(vector<char> InputBuffer, Sarray A){
    for(int n = 0; n < BitRate/64; n++){
        int x = (8*n);
        for(int i = 0; i < 8; i++){
            uint64_t in = InputBuffer[x+i] & 255;
            in <<= (8*i);
            A[n%5][(n/5)%5] ^= in;
        }
    }
    return A;
}

uint32_t Squeeze(Sarray A, int Pos){
    uint64_t v = A[(Pos/2) % 5][(Pos/2)/5];
    return ((Pos % 2)==0) ? (v & 0xFFFFFFFF) : ((v >> 32) & 0xFFFFFFFF);
}


void PrintSarrBytes(Sarray A){
    bool b = true;
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            for(int i = 0; i < 8; i ++){
                uint64_t a = A[x][y] >> (8*i);
                int x = a&255;
                cout <<  setw(2) << setfill('0') << hex << x;
            }
            if(b){cout << ' ';}
            else{ cout << endl;}
            b = !b;
        }

    }
    cout << endl;
}
