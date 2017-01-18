#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "include/Tableau.h"

using namespace std;

int* lpsolve(int n, double* c, int k, double** A, double* b){

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

    //int* res = t.resultat();

    t.printResultat();

    return t.resultat();
}

int main(int argc, char **argv)
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
    ifstream f;

    if (argc == 1) {

        f.open("testfiles/test2.txt");

    } else if (argc == 2) {

        string cache = argv[1];

        if (cache == "-f") {

            string filename;
            cout << "Geben Sie bitte den Pfad der Testdatei ein: " << endl;
            cin >> filename;
            f.open(filename);

        } else if (cache == "-h") {

            int systemRet = system("less Readme.txt");
            if(systemRet == -1) {cerr << endl << "Readme.txt nicht gefunden!" << endl; return 1;}

            return 0;

        } else if (cache == "-s") {
			
			cout << endl << "Sensitivitaetsanalyse noch nicht funktionsfaehig" << endl << endl;
			return 0;
			
        } else {

            cerr << endl << "Ungueltige Parameter! Fuer Hilfe lesen sie die Datei readme.txt" << endl << endl;
            return 1;

        }

    } else if (argc == 3) {

        string cache = argv[1];

        if (cache == "-f") {

            f.open(argv[2]);

		} else if (cache == "-s") {
			
			cout << endl << "Sensitivitaetsanalyse noch nicht funktionsfaehig" << endl << endl;
			return 0;
			
        } else {

            cerr << endl << "Ungueltige Parameter! Fuer Hilfe lesen sie die Datei readme.txt" << endl << endl;
            return 1;

        }

	} else if (argc == 4) {
		
		string help = argv[1];
		
		if (help != "-s") {
			cerr << endl << "Ungueltige Parameter! Fuer Hilfe lesen sie die Datei readme.txt" << endl << endl;
            return 1;
		}
		
		string cache = argv[2];

        if (cache == "-f") {

            cout << endl << "Sensitivitaetsanalyse noch nicht funktionsfaehig" << endl << endl;
			return 0;

        } else {

            cerr << endl << "Ungueltige Parameter! Fuer Hilfe lesen sie die Datei readme.txt" << endl << endl;
            return 1;

        }
		
    } else {

        cerr << endl << "Ungueltige Anzahl an Parametern! Fuer Hilfe lesen sie die Datei readme.txt" << endl << endl;
        return 1;

    }



    f >> n;

    f >> k;
    //cout << n << ' ' << k <<endl;
    double* c = new double[n];
    for( i = 0; i < n; i++)
    {
        f >> x;
        c[i] = x;
    }

   /* for(int i = 0; i < n; i++)
       cout << c[i] << ' ';
    cout << endl;*/

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
