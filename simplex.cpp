using namespace std;

#include <cmath>
#include <iostream>
#include <vector>

#define M 10
#define N 10

public void pivotelement(double &matr[M][N], int m, int n, vector<int> elmt) {
    double help = 0;
    int row = 0;
    int col = 0;

    //PIVOTSPALTE
    for (int i = 0; i < n; i++) {
        if (matr[0][i] < help) {
            help = matr[0][i];
            col = i;
        }
    }
    if (!(help)) {
        //FERTIG
    }

    vector<double> helpv;
    vector<int> indexv;

    //PIVOTZEILE
    for (int i = 1; i < m; i++) { //Zuerst alle Quotienten in Vektor speichern
        if (matr[i][col]) { //Wenn Element 0 Division nicht möglich, wird daher übersprungen
            helpv.push_back(matr[i][n-1] / matr[i][col]); //Entspricht (rechte Seite)/(Koeffizient von x_j)
            indexv.push_back(i); //Index der Zeile
        }
    }

    for (int i = 0; i < helpv.size(); i++) {
        if (!(i)) {help = helpv.at(i); row = indexv.at(i);}
        if (i) {        //Erst ab 2. Element
            if (help < helpv.at(i)) {
                help = helpv.at(i);
                row = indexv.at(i);
            }
        }
    }
}
