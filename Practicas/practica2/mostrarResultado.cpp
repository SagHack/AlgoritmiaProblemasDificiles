#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <map>
using namespace std;

void leerCL(string ficheroEntrada,vector<int>& v, int n){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        int i = 0, j = 0;
        while(getline(entrada,s)){
            stringstream linea(s);
            while(getline(linea,s,' ')){
                if(s.compare("*") != 0){
                    int num;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){
                        cerr << "El elemento de la fila " << i+1 << " y columna " << j+1 << " no es * o un número\n";
                        exit(1);
                    }
                    v[i*n+j] = num;

                }
                j++;
            }

            if(j!=n){
                cerr << "La fila " << i+1 << " no tiene " << n << " columnas\n";
                exit(1);
            }
            i++;
            j = 0;
        }

        if(i!=n){
            cerr << "No hay " << n << " filas\n";
            exit(1);
        }
    }
}

using KeyTuple = tuple<int,int,int>;

void leerVariables(string ficheroEntrada,map<KeyTuple,int>& variables){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        KeyTuple kt;
        int i,j,k,variable;

        while(getline(entrada,s)){
            stringstream linea(s);
            getline(linea,s,'(');

            getline(linea,s,',');
            i = stoi(s);
            getline(linea,s,',');
            j = stoi(s);
            getline(linea,s,')');
            k = stoi(s);

            getline(linea,s,':');
            getline(linea,s);
            variable = stoi(s);

            kt = make_tuple(i,j,k);
            variables[kt] = variable;
        }
    }
}

void leerResultado(string ficheroEntrada,const map<KeyTuple,int>& variables,vector<int>& CL,int n){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        KeyTuple kt;
        int i,j,k,variable;
        getline(entrada,s);
        while(getline(entrada,s,' ')){
            variable = stoi(s);
            if(variable < 0) continue;
            else if(variable == 0) break;
            for (const auto& a : variables) {
                if (a.second == variable) {
                    kt = a.first;
                    break;
                }
            }
            
            i = get<0>(kt);
            j = get<1>(kt);
            k = get<2>(kt);
            if(CL[i*n + j] != 0){
                cerr << "Para la celda (" << i+1 << "," << j+1 << ") hay más de un valor posible como resultado\n";
                exit(1);
            }
            CL[i*n + j] = k+1;
        
        }
    }
}

void mostrarResultado(const vector<int>& CL, int n){ 
    cout << "Resultado :" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << CL[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    int n = stoi(argv[1]);
    vector<int> CL(n*n,0);
    leerCL("CL.txt",CL,n);
    map<KeyTuple,int> variables;
    leerVariables("variables.txt",variables);
    leerResultado("resultado.txt",variables,CL,n);
    mostrarResultado(CL,n);
}