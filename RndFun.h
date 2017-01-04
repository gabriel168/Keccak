#ifndef ROUNDFUN_H
#define ROUNDFUN_H
#include<vector>
#include<inttypes.h>
using namespace std;
extern int BitRate;

typedef vector< vector<uint64_t> > Sarray;

uint64_t rot(uint16_t v, int shift);
Sarray Theta(Sarray A);
Sarray Rho(Sarray A);
Sarray Pi(Sarray A);
Sarray Chi(Sarray A);
Sarray Iota(Sarray A, int index);
Sarray RPerm(Sarray A);

Sarray Absorb(vector<char> M, Sarray A, int Pos);
uint32_t Squeeze(Sarray A, int Pos);

void PrintSarrBytes(Sarray A);

#endif // ROUNDFUN_H
