#pragma once
#include <vector>
#include <string>
using namespace std;

bool generarCuadradoLatinoCompleto(vector<string>& CL, int n);

void generarCuadradoLatinoParcial(vector<string>& CL,const int n,const double porcentaje);

void escribirCuadradoLatinoParcial(const vector<string>& CL,const string ficheroSalida,const int n);

