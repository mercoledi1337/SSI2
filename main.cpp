#define _CRT_RAND_S

#include <iostream>
#include <fstream>
#include "gnuplot_iostream.h"
#include <stdlib.h>

using namespace std;

//range from 0 to 100
const int randMIN = 0;
const int randMINrange = 0;
const int randMAX = 100;
const int randMAXrange = 100;
const int iter = 100;



int main() {
    unsigned int number;
    unsigned int numberX;
    rand_s(&numberX);

    Gnuplot gp("D:/gnuplot/bin/gnuplot.exe");

    double x = (double)(numberX) / ((double)(UINT_MAX) + 1) * randMAX + randMIN;
    double y = sin(x/10) * sin(x/200);
    double border = 10; //random in range 20;

    std::vector<std::pair<double,double>> points;

    gp << "set xrange["<<randMINrange<<":"<<randMAXrange<<"]\n";

    for (int i = 0; i < iter; i++) {
        rand_s(&number);
        double randInBorder = border * ( (double)number / (double)UINT_MAX * 2.0 - 1.0 ); //choosing betwen -1 1 and then multiply by border
        double xpot = x + randInBorder;
        while (xpot < randMIN) xpot += (randMAX - randMIN);
        while (xpot > randMAX) xpot -= (randMAX - randMIN);
        double ypot = sin(xpot/10) * sin(xpot/200);

        // printing values in iteration
        std::cout << "Iteracja: " << i + 1 << "  x=" << xpot << "  y=" << ypot << "  rozrzut=" << border << "\n";

        if (ypot >= y) {
            y = ypot;
            x = xpot;
            border *= 1.1;
        } else {
            border /= 1.1;
        }

        // saving poing into vector for gnuplot
        points.emplace_back(xpot, ypot);

        gp << "plot "
              "sin(x/10)*sin(x/200) w l lw 2 title 'Funkcja', "
              "'-' using 1:2 w points pt 7 lc rgb 'red' title 'punkty'\n";
        gp.send1d(points);
    }

    cin.get();
    return 0;
}
