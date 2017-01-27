#ifndef ROUNDFUN_H
#define ROUNDFUN_H
#include<vector>
#include<inttypes.h>
#include<fstream>

using namespace std;
extern int BitRate;
typedef vector< vector<uint64_t> > Sarray;

Sarray Theta(Sarray A);
Sarray Rho(Sarray A);
Sarray Pi(Sarray A);
Sarray Chi(Sarray A);
Sarray Iota(Sarray A, int index);
Sarray RPerm(Sarray A);

uint64_t rot(uint16_t v, int shift);
void pad(vector<char>& input, int index);
Sarray Absorb(vector<char> M, Sarray A);
uint32_t Squeeze(Sarray A, int Pos);

void PrintSarrBytes(Sarray A);

#endif // ROUNDFUN_H
