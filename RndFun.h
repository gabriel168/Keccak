#ifndef ROUNDFUN_H
#define ROUNDFUN_H
#include<vector>
#include<inttypes.h>
#include<fstream>

using namespace std;
extern int BitRate;
typedef vector< vector<uint64_t> > Sarray;

void Theta(Sarray &A, Sarray &B, vector<uint64_t> &C, vector<uint64_t> &D);
void Rho(Sarray &A, Sarray &B);
void Pi(Sarray &A, Sarray &B);
void Chi(Sarray &A, Sarray &B);
void Iota(Sarray &A,int index);
void RPerm(Sarray &A, Sarray &B, vector<uint64_t> &C, vector<uint64_t> &D);

uint64_t rot(uint16_t v, int shift);
void pad(Sarray &state, int StartIndex);
void Absorb(char Input, Sarray &A, int pos);
uint32_t Squeeze(Sarray A, int Pos);

void PrintSarrBytes(Sarray A);

#endif // ROUNDFUN_H
