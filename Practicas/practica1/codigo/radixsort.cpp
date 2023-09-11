#include <iostream>
#include <vector>
#include <string>
using namespace std;

// A utility function to print an array
void print(vector<int> arr, int n)
{
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

// A utility function to print an array
void print(vector<string> arr, int n)
{
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}


// Precondicion: El array no puede ser vacio y tiene que ser de tipo int
// Postcondicion : Devuelve el número de mayor valor en el array
int getMax(vector<int> arr, int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > mx){
            mx = arr[i];
        }
    }
    return mx;
}

int obtenerCifrasMaximo(vector<string> arr, int n)
{
    string s = arr[0];
    for (int i = 1; i < n; i++){
        string aux = arr[i];
        if (aux.length() > s.length()){
            s = arr[i];
        }
    }
    return s.length();
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(vector<int>& arr, int n, int exp)
{

    // Output array
    vector<int> output;
    for(int j = 0; j < n; j++){
        output.push_back(0);
    }
    
    int i, count[10] = {0};

    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++){
        count[(arr[i] / exp) % 10]++;
    }
    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        
        count[(arr[i] / exp) % 10]--;
        output[count[(arr[i] / exp) % 10]] = arr[i];
    }
    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++){
        arr[i] = output[i];
    }
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(vector<string>& arr, const int n, int cifra)
{
    // Inicializamos el array
    vector<string> output;
    int i;
    int count[10] = { 0 };

    for(int j = 0; j < n; j++){
        output.push_back("");
    }
    
    
    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++){
        int l = arr[i].length();
        cout << "\nnumero : " << arr[i] << " longitud: " << l << endl;
        char c; 
        if (l < cifra){
            c = '0';
        }
        else{
            string saux = arr[i];
            c = saux[l-cifra];
        }
        int numero = c - '0';
        cout << "\nnumero : " << numero << endl;
        count[numero]++;
    }
        

    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        int l = arr[i].length();
        string saux = arr[i];
        char c;
        if (l < cifra){
            c = '0';
        }
        else{
            string saux = arr[i];
            c = saux[l-cifra];
        }
        int numero = c - '0';
        count[numero]--;
        output[count[numero]] = arr[i];
    }
    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++){
        arr[i] = output[i];
    }
}




// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(vector<int>& arr, int n)
{

    // Find the maximum number to
    // know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10){
        countSort(arr, n, exp);
    }
        
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(vector<string>& arr, int n)
{

    // Find the maximum number to
    // know number of digits
    int m = obtenerCifrasMaximo(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int c = 1; c <= m; c++){
        countSort(arr, n, c);
        
    print(arr, n);
    }
}






// Driver Code
int main()
{
    vector<int> arr = { 2,43,910,9,2};
    int n = arr.size();
    // Function Call
    radixsort(arr, n);
    print(arr, n);

    vector<string> arrS = {"2","43","910","9","2"};
    // for(int i = 0; i < n; i++){
    //     arrS.push_back(to_string(arr[i]));
    // }

    // Function Call
    radixsort(arrS, n);
    print(arrS, n);
    return 0;
}