#define _CRT_RAND_S

#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <cmath>
#include "gnuplot_iostream.h"
#include <numeric>
#include <cstdlib>


#include <stdlib.h>
using namespace std;

//range from 0 to 100
const int randMIN = 15;
const int randMINrange = 0;
const int randMAX = 36;
const int randMAXrange = 101;
const int iter = 20;



int main() {
    unsigned int number;
    unsigned int numberX;
    rand_s(&numberX);

    Gnuplot gp("D:/gnuplot/bin/gnuplot.exe");

    double x = static_cast<double>(numberX) / (static_cast<double>(UINT_MAX) + 1) * (randMAX - randMIN) + randMIN;
    double y = sin(x/10) * sin(x/200);
    double border = 21; //random in range 20;

    std::vector<std::pair<double,double>> points;

    gp << "set xrange["<<randMINrange<<":"<<randMAXrange<<"]\n";

    for (int i = 0; i < iter; i++) {
        rand_s(&number);

        double randInBorder = static_cast<double>(number) / (static_cast<double>(UINT_MAX) + 1) * border - border/2.0; // chossing number from 0 to 20 when is belove 10 means is negativ so he have to add -10
        double xpot = x + randInBorder;
        while (xpot < randMIN) {
            xpot += 0.1;
        }
        while (xpot > randMAX) {
            xpot -= 0.1;
        }
        double ypot = sin(xpot/10) * sin(xpot/200);

        // printing values in iteration
        std::cout << "Iteracja: " << i + 1
                  << "  x=" << xpot
                  << "  y=" << ypot
                  << "  rozrzut=" << border << "\n";

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
