using namespace std;

#include <cmath>
#include <iostream>
#include <vector>

#define M 10
#define N 10

public void pivotelement(double &matr[M][N], int m, int n) {
    double help = 0;
    int row = 0;
    int col = 0;
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

    for (int i = 1; i < m; i++) {
        if (matr[i][col]) {
            helpv.push_back(matr[i][n-1] / matr[i][col]);
        }
    }

    for (int i = 0; i < helpv.size(); i++) {
        if(i){help < helpv.at(i) ? help = helpv.at(i)}
    }
}
