#include"RndFun.h"
#include<cmath>
#include<deque>

/*Ersetzt jedes Element mit Koordinaten (a,b,c) durch den XOr-Wert von sich selbst und der
 * XOr-Summe aller Elemente mit den (x,z)-Koordinaten (a - 1,c) oder (a + 1,c - 1) */
Sarray Theta(Sarray A){
    vector< vector<bool> > TmpArr1(5, vector<bool>(64));
    for(int x=0;x<5;x++){
        for(int z=0;z<64;z++){
            TmpArr1[x][z] = A[x][0][z]^A[x][1][z]^A[x][2][z]^A[x][3][z]^A[x][4][z];
        }
    }

    vector< vector<bool> > TempArr2(5, vector<bool>(64));
    for(int x=0;x<5;x++){
        for(int z=0;z<64;z++){
            TempArr2[x][z] = TmpArr1[(x+4)%5][z]^TmpArr1[(x+1)%5][(z+63)%64];
        }
    }

    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            for(int z=0;z<64;z++){
                A[x][y][z]=A[x][y][z]^TempArr2[x][z];
            }
        }
    }
    return A;
}
/*Verschiebt alle Elemente in der z-Richtung um einen Wert, der von den (x,y)-Koordinaten abhängt.*/
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

/*Ersetzt jede z-Reihe (bzw Lane) mit den (x,y)-Koordinaten (a,b)
 * durch die Reihe mit (x,y)-Koordinaten (a + 3b,a)*/
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

/*Ersetzt jedes Element durch den XOr-Wert von sich selbst und einer Funktion aus zwei anderen Elementen*/
Sarray Chi(Sarray A){
    Sarray B(5,sheet(5,lane(64)));
    for(int x=0;x<5;x++){
        for(int y=0;y<5;y++){
            for(int z=0;z<64;z++){
                   B[x][y][z] = A[x][y][z] ^ (!A[(x+1)%5][y][z] & (A[(x+2)%5][y][z]));
            }
        }
    }
    return B;
}

bool rc(int t){
    vector<bool> v = {1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,1,0,
                      1,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0,1,0,1,0,1,1,0,0,1,1,0,0,1,0,
                      1,1,1,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,0,1,1,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,
                      0,1,1,0,1,0,0,0,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,};
    return v[t];
}

/*Modifiziert einige der Elemente der Reihe (0,0,z), deren z-Koordinate eine Zweierpotenz ist.*/
Sarray Iota(Sarray A,int index){
    vector<bool> RC (64);
    for(int a = 0; a < 64; a++){
        RC[a]=0;
    }
    for(int j=0; j<=6; j++){
        RC[pow(2,j)-1]=rc(j+(7*index));
    }
    for(int z=0; z<64 ;z++){
        A[0][0][z]=A[0][0][z]^RC[z];}
    return A;
}

//Alle Permutationsfunktionen einer Runde zusammen
Sarray RPerm(Sarray A){
    for(int RIndex = 0; RIndex < 24; RIndex++){
        A=Iota(Chi(Pi(Rho(Theta(A)))),RIndex);
        }
    return A;
}

//Nimmt neue Bits des Inputs in das State-Array auf
Sarray Absorb(vector<bool> M, Sarray A, int Pos){
    for(int n = 0; n < BitRate; n++){
        A[(n/64)%5][(n/320)%5][n%64]=A[(n/64)%5][(n/320)%5][n%64]^M[n+Pos];
    }
    return A;
}

//Gibt ein Bit aus dem State-Array zurück (für das Herauslesen des Hashes)
bool Squeeze(Sarray A, int Pos){
    return (A[(Pos/64)%5][(Pos/320)%5][Pos%64]);
}
