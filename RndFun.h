#ifndef ROUNDFUN_H
#define ROUNDFUN_H
#include<vector>
using namespace std;
extern int BitRate;


typedef vector<bool> lane;
typedef vector<lane> sheet;
typedef vector<sheet> Sarray;

Sarray Theta(Sarray A);
Sarray Rho(Sarray A);
Sarray Pi(Sarray A);
Sarray Chi(Sarray A);
bool rc(int t);
Sarray Iota(Sarray A, int RIndex);
Sarray RPerm(Sarray A);

Sarray Absorb(vector<bool> M, Sarray A, int Pos);
bool Squeeze(Sarray A, int Pos);

void PrintSarrBytes(Sarray A);

#endif // ROUNDFUN_H
