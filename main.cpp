#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "include/Tableau.h"

using namespace std;

int* lpsolve(int n, double* c, int k, double** A, double* b, bool sensitivity){

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
	t.setL(0);

	while (t.umformen());

	//int* res = t.resultat();

	t.printResultat();

	if (sensitivity) {
		for (int i = 0; i < n; i++) {
			t.rhs_sensitivity(i, c);
		}
	} 
	
    return t.resultat();
}

int illegal_par() {
	cerr << endl << "Ungueltige Parameter! Fuer Hilfe lesen Sie die Datei readme.txt" << endl << endl;
    return 1;
}

int illegal_par_count() {
	cerr << endl << "Ungueltige Anzahl an Parametern! Fuer Hilfe lesen Sie die Datei readme.txt" << endl << endl;
    return 1;
}

string get_filename() {
	string fn;
    cout << "Geben Sie bitte den Pfad der Testdatei ein: " << endl;
    cin >> fn;
	return fn;
}

int main(int argc, char **argv)
{
	
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
	
	bool sensitivity = false;
	
    ifstream f;

	/////////////////////////////////////////////////////////
	// ARGUMENTS
	
	/*
	for (int i = 1; i < argc; i++) {
		string cache = argv[i];
		if (cache == "-s") {
			cout << endl << "Sensitivitaetsanalyse noch nicht funktionsfaehig" << endl << endl;
			return 0;
		}
	}//*/
	
    if (argc == 1) { // $ ./simplex

        f.open("testfiles/test2.txt");

    } else if (argc == 2) {

        string cache = argv[1];

        if (cache == "-f") { // $ ./simplex -f

            f.open(get_filename());

        } else if (cache == "-h") { // $ ./simplex -h

            int systemRet = system("less Readme.txt");
            if(systemRet == -1) {cerr << endl << "Readme.txt nicht gefunden!" << endl; return 1;}

            return 0;

        } else if (cache == "-s") { // $ ./simplex -s
			
			f.open("testfiles/test2.txt");
			sensitivity = true;
			
        } else {return illegal_par();}

    } else if (argc == 3) {

        string cache = argv[1];
		string help = argv[2];

        if (cache == "-f") {  // $ ./simplex -f <path>

            f.open(help);

		} else if (cache == "-s") {  // $ ./simplex -s -f
			
			if (help != "-f") {return illegal_par();}
			
            f.open(get_filename());
			sensitivity = true;
			
        } else {return illegal_par();}

	} else if (argc == 4) {
		
		string help = argv[1];
		
		if (help != "-s") {return illegal_par();}
		
		string cache = argv[2];

        if (cache == "-f") {  // $ ./simplex -s -f <path>

			f.open(argv[3]);
			sensitivity = true;

        } else {return illegal_par();}
		
    } else {return illegal_par_count();}
	/////////////////////////////////////////////////////////

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

    lpsolve(n, c, k, A, b, sensitivity);

    return 0;
}
