
int main() {
    vector<int> v, v_radixsort, v_quicksort, v_mergesort;
    for (int n = 10; n < 10000000; n *= 5) {
        generarFicheros(n, n / 10, n / 10);
        leerNumerosDeArchivo("aleatorios.txt", v);
        v_radixsort = v;
        v_quicksort = v;
        v_mergesort = v;
        cout << "N:" << n << endl;
        auto start = chrono::high_resolution_clock::now();
        radixsort(v_radixsort);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "\tradixsort: " << duration.count() << " ms" << endl;

        start = chrono::high_resolution_clock::now();  // Reutilizamos las variables
        quicksort(v_quicksort);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "\tquicksort: " << duration.count() << " ms" << endl;

        start = chrono::high_resolution_clock::now();  // Reutilizamos las variables
        mergesort(v_mergesort);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "\tmergesort: " << duration.count() << " ms" << endl;
        
        if (!areEqual(v_radixsort, v_quicksort, v_mergesort)) {
            exit(-1);
        }
    }

    return 0;
}
