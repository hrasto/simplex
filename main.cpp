#include <iostream>
#include <cstdlib>
#include <cmath>
#include <Tableau.h>

using namespace std;

void lpsolve(int n, double* c, int k, double** A, double* b){

    // int n, double* c, int k, double** A, double* b
    // n - Anzahl der Variablen
    // k - Anzahl der Nebenbedingungen
    // c - Koeffizienten der Zielfunktion
    // A - Koeffizienten der Nebenbedingungen
    // b - rechte Seite

    // create a tableau instance
    // reorganize the tableau until the wanted state is here (while loop)

    try{
        Tableau t = Tableau(n,k);
        t.setNb(A);
        t.setRs(b);
        t.setZf(c);
        t.print();
        double pe = t.pivotElement();
        cout << "Pivotelement: " << pe << endl;
    }catch(...){
        cout << "No pivot element found" << endl;
    }
}

int main()
{
    //cout << "Hello world!" << endl;

    // Daten einlesen
    // Lpsolve Funktion aufrufen

    int n = 3;
    int k = 2;

    double* c = new double[n];
    for(int i = 0; i < n; ++i)
        c[i] = pow(-1, i+1) * (rand()%10);

    double** A = new double*[k];
    for(int i = 0; i < k; ++i){
        A[i] = new double[n];
        for(int j = 0; j < n; ++j)
            A[i][j] = pow(-1, j) * (rand() % 10);
    }

    double* b = new double[k];
    for(int i = 0; i < k; ++i)
        b[i] = rand() % 10;

    lpsolve(n, c, k, A, b);

    return 0;
}
