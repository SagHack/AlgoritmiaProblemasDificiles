#include "radixsort.cpp"
#include<vector>
#include <iostream>
using namespace std;


// Overload the << operator for vector<int>
ostream& operator<<(ostream& os, const vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << " ";
    }
    return os;
}

// Overload the << operator for vector<string>
ostream& operator<<(ostream& os, const vector<string>& v) {
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << " ";
    }
    return os;
}


int main(){
    //vector<int> v_desord_int = {32, 822, 732, 40, 50, 5, -1, 6, 9, 73}; //Falla por el numero negativo
    //vector<int> v_desord_int = {-3,-2,-93,-7};
    
    vector<int> v_desord_int = {32, 822, 732, 40, 50, 5, 2, 1, 9, 73};
    radixsort(v_desord_int);
    cout << v_desord_int << endl;

    cout << "Ahora el que va con strings" << endl;

    vector<string> v_desord = {"32", "822", "732", "40", "50", "5", "2", "1", "9", "73"};
    radixsort(v_desord);
    cout << v_desord << endl;


    
}