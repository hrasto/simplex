#include "../include/Tableau.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <stdexcept>

using namespace std;

class NoPivotException {
    string msg;
    public:
    NoPivotException(string msg){this->msg = msg;}
    void getMsg(){ cout << msg; }
};

Tableau::Tableau(int n, int k, double* zf, double** nb, double* rs)
{
    if(n < 1 || k < 1) //$M hier wurde nur n und k gleich null überprüft mit !(n && k)
        throw std::invalid_argument("n und k muessen groesser-gleich 1 sein"); //$M lt. stackoverflow ohne "new"

    this->l = 1;
    this->n = n;
    this->k = k;
	this->it = 0;
    this->tab = new double*[k+1]; // # von nebenbed. + zielfunktion

    // auffuellen des Tableau mit Werten
    for (int i = 0; i < k+1; ++i){

        this->tab[i] = new double[n+k+1];

        for(int j = 0; j < n+k+1; ++j)
            if(i == 0 && j < n) // Zielfunktion - bis anzahl der variablen
                this->tab[i][j] = zf[j];
            else
                if(i && j < n) // Nebenbedingungen - bis anzahl der variablen
                    this->tab[i][j] = nb[i-1][j];
                else if(i && j >= n && j < n+k && i-1 == j-n) // Einheitsmatrix
                    this->tab[i][j] = 1;
                else if(i && j == n+k) // rechte Seite
                    this->tab[i][j] = rs[i-1];
                else
                    this->tab[i][j] = 0;
    }

    cout << endl << "----------- Anfangstableau ----------" << endl;
    print();
}

Tableau::~Tableau()
{
    //dtor
}

void Tableau::print(){
    //cout << "Anzahl der Variablen: " << this->getN() << endl
    //    << "Anzahl der Nebenbedingungen: " << this->getK() << endl;

    for(int i = 0; i < k+1; ++i){
        if(i)
            cout << i << ".\t";
        else
            cout << "ZF\t";
        for(int j = 0; j < n+k+1; ++j){

            cout << tab[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;

}

int Tableau::pivotSpalte(){
    double help = 0;
    //int row = 0;
    int col = 0;
    // den kleinsten nicht-neg. wert der zf. suchen
    for (int i = 0; i < n; i++) {
        if (tab[0][i] < help) {
            help = tab[0][i];
            col = i;
        }
    }

    if (!(help)) {
        throw NoPivotException("Keine Pivotspalte gefunden");
        // weiss nicht ob exception das beste fuer diesen zweck ist :))
    }

	
	
    return col;
}

int Tableau::pivotZeile(int col){

    int row = 0;
    // auswahl der pivot-zeile
    double help = std::numeric_limits<double>::max();

    for (int i = 1; i < k+1; ++i)
        if(tab[i][col] > 0 && tab[i][n+k] / tab[i][col] <= help){
            row = i;
            help = tab[i][n+k] / tab[i][col];
        }

    if(!row)
        throw NoPivotException("Keine Pivotzeile gefunden");

    return row;
}

double Tableau::pivotElement(int col, int row){
	this->it++;
    return tab[row][col];

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
}

bool Tableau::umformen(){
    int col,row,pe;

    try{
        col = pivotSpalte();
        row = pivotZeile(col);
        pe = pivotElement(col, row);
		rowsv.push_back(row);
		colsv.push_back(col);
    }catch(NoPivotException& ex){
        if(l){
            ex.getMsg();
            cout << endl << "Prozess ist beendet." << endl << endl
                 << "Die optimale Loesung nach " << this->it << " Iterationen ist (";
            for (int i = 1; i < k+1; ++i) {
                cout << tab[i][n+k];
                (i==k)?(cout << ") "):(cout << ", ");
            }
            cout << "mit ZF-Wert " << tab[0][n+k] << "." << endl;
        }
        return false;
    }

    if(l)
        cout << "-------------- Umformen -------------" << endl
			<< "Iterationen: " << this->it << endl
            << "Pivotspalte: " << col << endl
            << "Pivotzeile: " << row << endl
            << "Pivotelement: " << pe << endl << endl;

    for(int i = 0; i < k+1; ++i){

        // wenn i == row -> in der for schleife danach (zeile 174)
        if(i != row){

            if(l == 2)
                cout << "Updating row[ " << i << " ]" << endl;

            // koeff. zum multiplizieren der pivotzeile
            double x = tab[i][col];

            for(int j = 0; j < n+k+1; ++j){
                if(l == 2)
                    cout << "\tUpdating element[ " << j << " ] -> " << tab[i][j]
                        << " - " << x << "*" << tab[row][j] << "/" << pe << " = " << tab[i][j] - x*tab[row][j]/pe << endl;

                tab[i][j] -= x*tab[row][j]/pe;
            }

        }
    }

    if(l == 2)
        cout << "Updating row[ " << row << " ] (Pivotzeile)" << endl;

    for (int j = 0; j < n+k+1; ++j){
        if(l == 2)
            cout << "\tUpdating element[ " << j << " ] -> " << tab[row][j] << "/" << pe << " = " << tab[row][j]/pe << endl;
        tab[row][j] /= pe;
    }

    if(l) print();
    return true;
}

void Tableau::setL(int val){
    if(val >= 0 && val <= 2)
        this->l = val;
}

int* Tableau::resultat(){
    int* res = new int[n+k];

    for(int i = 0; i < n+k; ++i){
        bool check = false;
        int row = 0;

        for(int j = 0; j < k+1; ++j){
            if(tab[j][i] == 1){
                if(check == true){
                    check = false;
                    break; // set the check to false, break the loop -> res. will be 0
                }else{
                    row = j;
                    check = true;
                }

            }else if(tab[j][i] != 0 && check){
                check = false;
                break; // set the check to false, break the loop -> res. will be 0
            }
        }

        if(check){
            res[i] = tab[row][n+k];
        }else{
            res[i] = 0;
        }
    }

    return res;
}

void Tableau::printResultat(){
    int* res = this->resultat();

    cout << "Resultat: [";
    for(int i = 0; i < n+k; ++i){
        if(i) cout << ", ";
        cout << res[i];
    }
    cout << "]" << endl;
}

void Tableau::getShadowprices(){
	/*double* res = new double[k];
	
	cout << endl << "Schattenpreise:" << endl;
	
	for (int i = 0; i < k; i++) {
		res[i] = this->tab[0][i+n];
		cout << "Pi_" << i+1 << " = " << res[i] << endl;
	}*/
	
	cout << endl << "x_(n+1)\tZeile" << endl;
	
	for (unsigned int i = 0; i < rowsv.size(); i++) {
		cout << colsv[i] << "\t" << rowsv[i] << endl;
	}
	
	cout << "colsv\trowsv" << endl;
	
	cout << endl;
}

void Tableau::rhs_sensitivity(int var, double* zielfunktion) {
	int index = var;
	double help;
	double neg = 0;
	double pos = 0;
	
	cout << " --- Sensitivitaetsanalyse der rechten Seite ---" << endl;
	
	for (unsigned int i = 0; i < colsv.size(); i++) {
		if (colsv.at(i) == var) {
			index = rowsv.at(i);
		}
	}
	
	for (int i = 0; i < n + k; i++) {
		if (i != var && tab[index][i]) {
			help = tab[0][i] / tab[index][i];
			
			if (help > 0) {
				if (pos && help < pos) {pos = help;} else if (!pos) {pos = help;}
			}
			if (help < 0) {
				if (neg && help > neg) {neg = help;} else if (!neg) {neg = help;}
			}
		}
	}
	
	help = tab[var+1][n+k];
	
	cout << endl << "Aendert sich x" << var + 1 << " von " << abs(zielfunktion[var]) << " auf "
		 << abs(zielfunktion[var]) << " + t" << var +  1 << " (mit ";
	if (neg) {cout << neg << " <= ";}
	cout << "t" << var + 1;
	if (pos) {cout << " <= " << pos;}
	cout << "), waehrend die anderen\nVariablen unveraendert bleiben, so bleibt die Optimalloesung erhalten.\nDann ist " << tab[0][n+k];
	if (help < 0) {cout << " - " << abs(help);} else {cout << " + " << help;}
	cout << "t" << var + 1 << " der neue maximale Zielfunktionswert." << endl;
}