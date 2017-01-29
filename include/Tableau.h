/*

Beispiel der Struktur der Variable tab

     +---+---+---+---+---+----+
     |x1 |x2 |x3 |x4 |x5 |r.S.|
+----+---+---+---+---+---+----+
|ZF  |   |   |0  |0  |0  |    |
+----+---+---+---+---+---+----+
|NB1 |   |   |1  |0  |0  |    |
+----+---+---+---+---+---+----+
|NB2 |   |   |0  |1  |0  |    |
+----+---+---+---+---+---+----+
|NB3 |   |   |0  |0  |1  |    |
+----+---+---+---+---+---+----+

*/

#ifndef TABLEAU_H
#define TABLEAU_H

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <stdexcept>

using namespace std;

class Tableau
{
    // Anzahl der Variablen
    int n;

    // Anzahl der Nebenbedingungen (also auch Schlupfvariablen)
    int k;

    // Status logs: 0->keine, 1->Zustand des Tableau (def.), 2->Alle Berechnungen
    int l;

	//Anzahl der Iterationen
	int it;
	
    // Die eigentlichen Daten
    double** tab;
	
	vector<double> rowsv;
	vector<double> colsv;

    public:
        Tableau(int, int, double*, double**, double*);
        virtual ~Tableau();

        /*
        void setZf(double* zf) { this->zf = zf; }
        void setNb(double** nb) { this->nb = nb; }
        void setRs(double* rs) { this->rs = rs; }
        double* getZf(){ return this->zf; }
        double** getNb() { return this->nb; }
        double* getRs(){ return this->rs; }
        */

        void setL(int);
        int getN() {return this->n;}
        int getK() {return this->k;}
		int getIt() {return this->it;}
        void print();
        int pivotSpalte();
        int pivotZeile(int);
        double pivotElement(int col, int row);
        bool umformen();
        double* resultat();
		void printResultat();
        void printResultat(int var);
		void getShadowprices();
		void zf_sensitivity(int var, double* zielfunktion);
		void rhs_sensitivity(int var, double* rhs);
    protected:
    private:
};

#endif // TABLEAU_H
