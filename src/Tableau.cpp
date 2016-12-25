#include "Tableau.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

class NoPivotException {
    char * msg;
    public:
    NoPivotException(char* msg){this->msg = msg;}
    void getMsg(){ cout << msg << '\0'; }
};

Tableau::~Tableau()
{
    //dtor
}

void Tableau::print(){
    cout << "Anzahl der Variablen: " << this->getN() << endl
        << "Anzahl der Nebenbedingungen: " << this->getK() << endl;

    cout << "ZF:\t";
    for(int i = 0; i < n; ++i)
        cout << zf[i] << '\t';
    cout << endl;

    for(int i = 0; i < k; ++i){
        cout << i << ". Gl:\t";
        for(int j = 0; j < n; ++j)
            cout << nb[i][j] << '\t';
        cout << "RS: " << rs[i];
        cout << endl;
    }

}

double Tableau::pivotElement(){
    // pivotspalte suchen
    // wenn: kein Eintrag in der ZF negativ -> throw ex. -> fertig
    // sonst: double wert des

    double help = 0;
    int row = 0;
    int col = 0;
    // den kleinsten nicht-neg. wert der zf. suchen
    for (int i = 0; i < n; i++) {
        if (zf[i] < help) {
            help = zf[i];
            col = i;
        }
    }

    if (!(help)) {
        throw NoPivotException("Kein Pivot wurde gefunden");
    }

    // auswahl der pivot-zeile
    help = std::numeric_limits<double>::max();
    for (int i = 0; i < k; ++i)
        if(nb[i][col] && rs[i] / nb[i][col] < help){
            row = i;
            help = rs[i] / nb[i][col];
        }

    //cout << "PZ:" << row;

    /*
    vector<double> helpv;

    for (int i = 0; i < k; i++) {
        if (nb[i][col]) {
            helpv.push_back(nb[i][n-1] / nb[i][col]);
        }
    }

    for (int i = 0; i < helpv.size(); i++) {
        if(i && help < helpv.at(i)){
             help = helpv.at(i);
        }
    }
    */

    return nb[row][col];
}

