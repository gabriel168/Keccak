#ifndef ROUNDFUN_H
#define ROUNDFUN_H
#include<vector>
using namespace std;
extern unsigned int rate;

typedef vector<bool> lane;
typedef vector<lane> sheet;
typedef vector<sheet> Sarray;

Sarray Theta(Sarray A);
Sarray Rho(Sarray A);
Sarray Pi(Sarray A);
Sarray Chi(Sarray A);

#endif // ROUNDFUN_H
