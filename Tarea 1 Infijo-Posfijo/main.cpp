#include <iostream>
#include <cstring>
#include "PruebasAFN.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	PruebasAFN *p = new PruebasAFN();
  string cadena;
  AFN afn;
  cout << "Ingresa una ER: ";
  cin >> cadena;
  afn = p->convertirERaAFN(cadena);
  p->probarCadenasAFN(afn);
	return 0;
}
