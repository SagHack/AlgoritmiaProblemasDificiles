#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>


#include <random>
using namespace std;

bool generarCuadradoLatino(string ficheroSalida,int n, double porcentaje){
    ofstream salida(ficheroSalida);
    if(salida.is_open()){

        int i = 0, j = 0, asteriscos = 0;
        int MAX_ASTERISCOS = ceil(((n * n)*porcentaje) / 100.0);
        int MIN_ASTERISCOS = ((n * n)*porcentaje) / 100.0;
        vector<int> valores_posibles(2*n,(1<<n)-1);
        
        srand(time(NULL));


        while(i < n){
            double random = static_cast<double>(rand())/RAND_MAX;
            random = random * 100.0;
            string s;
            if(random < porcentaje){
                s = "*";
                asteriscos++;
            }
            else{
                int valido;
                int num;
                int mascara;
                int nrep = 0;
                do{
                    num = rand()%10 + 1;
                    mascara = 1 << (num-1);
                    valido = valores_posibles[i] & mascara & valores_posibles[n+j];
                    if((valores_posibles[i] & valores_posibles[n+j]) == 0) return false;

                } while(valido == 0);
                valores_posibles[i] &= ~mascara;
                valores_posibles[n+j] &= ~mascara;
                s = to_string(num);
            }

            if(++j == n){
                salida << s << endl;
                i++;
                j = 0;
            }
            else{
                salida << s << " ";
            }
        }

        if(MIN_ASTERISCOS > asteriscos || asteriscos > MAX_ASTERISCOS){
            return false;
        }

    }
    return true;
}


int main(int argc, char* argv[]) {
    if(argc != 4){
        exit(1);
    }

    string ficheroSalida = argv[1];
    int n = stoi(argv[2]);
    double p = stod(argv[3]);
    while(!generarCuadradoLatino(ficheroSalida,n,p));
}