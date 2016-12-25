#ifndef TABLEAU_H
#define TABLEAU_H

#include <stdexcept>

class Tableau
{
    // Anzahl der Variablen
    int n;

    // Anzahl der Nebenbedingungen
    int k;

    // Koeffizienten der Zielfunktion
    double* zf;

    // Koeffizienten der Nebenbedingungen
    double** nb;

    // Rechte Seite
    double* rs;

    public:
        Tableau(int n, int k) {
            if(!(n && k))
                throw new std::invalid_argument("n und k muessen groesser-gleich 1 sein");
            this->n = n; this->k = k;
        }
        virtual ~Tableau();
        void setZf(double* zf) { this->zf = zf; }
        void setNb(double** nb) { this->nb = nb; }
        void setRs(double* rs) { this->rs = rs; }
        double* getZf(){ return this->zf; }
        double** getNb() { return this->nb; }
        double* getRs(){ return this->rs; }
        int getN(){ return this->n; }
        int getK(){ return this->k; }
        void print();
        double pivotElement();
    protected:
    private:
};

#endif // TABLEAU_H
