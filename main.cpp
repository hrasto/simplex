#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Tableau.h"

using namespace std;

void lpsolve(int n, double* c, int k, double** A, double* b){

    // int n, double* c, int k, double** A, double* b
    // n - Anzahl der Variablen
    // k - Anzahl der Nebenbedingungen
    // c - Koeffizienten der Zielfunktion
    // A - Koeffizienten der Nebenbedingungen
    // b - rechte Seite

    // eine Tableau instance erstellen
    // umformen, bis möglich
    // array mit resultaten retournieren

    Tableau t = Tableau(n,k,c,A,b);
    t.setL(1);

    while (t.umformen());

}

int main()
{
    //cout << "Hello world!" << endl;

    // Daten einlesen
    // Lpsolve Funktion aufrufen

   /* int n = 2;
    int k = 3;

    double* c = new double[n]; // zielfunk.
    c[0] = -3;
    c[1] = -5;

    double** A = new double*[k]; // nb
    A[0] = new double[n];
    A[0][0] = 1;
    A[0][1] = 0;
    A[1] = new double[n];
    A[1][0] = 0;
    A[1][1] = 2;
    A[2] = new double[n];
    A[2][0] = 3;
    A[2][1] = 2;

    double* b = new double[k];
    b[0] = 4;
    b[1] = 12;
    b[2] = 18;*/



int x, i, j, n, k;

    string filename;
    cin >> filename;
    ifstream f;
    f.open(filename);


    f >> x;
    n = x;

    f >> x;
    k = x;
    //cout << n << ' ' << k <<endl;
    double* c = new double[n];
    for( i = 0; i < n; i++)
    {
        f >> x;
        c[i] = x;
    }

    for(int i = 0; i < n; i++)
       cout << c[i] << ' ';
    cout << endl;

    double** A = new double*[k]; // nb
    //double A[100][100];
    double* b = new double[k];
   //cout<< n << ' ' << k;

    for(i = 0; i < k; i++)
    {
        A[i] = new double[n];
        for(j = 0; j < n; j++)
        {
            f >> x;
            A[i][j] = x;
        }
        if(j+1 == n+1)
        {
            f >> x;
            b[i] = x;
        }

    }

    /* random werte:

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
    */

    lpsolve(n, c, k, A, b);

    return 0;
}
