#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <unistd.h>

using namespace std;

#define SIZE 10000

#define UNIFORM 0
#define EXPONENTIAL 1
#define CONSTANT 2

double tau[SIZE];
double sigma[SIZE];

void generate_seq(double *mas, int type_distrib, double mx) {
    if (type_distrib == UNIFORM) {
        for (int i = 0; i < SIZE; ++i)
            mas[i] = ((double) rand() / RAND_MAX) * mx;
        return;
    } else if (type_distrib == EXPONENTIAL) {
        double lambda = 1 / mx;
        for (int i = 0; i < SIZE; ++i)
            mas[i] = (-1 * log(1 - ((double) rand() / RAND_MAX))) / lambda;
        return;
    } else {
        for (int i = 0; i < SIZE; ++i)
            mas[i] = mx;
        return;
    }
}

double mx_omega(double *sigma, double *tau) {
    double mx = 0.0, tmp = 0.0;
    for (int i = 1; i < SIZE; ++i) {
        tmp = max(0.0, (sigma[i - 1] + tmp - tau[i]));
        mx += tmp;
    }
    return mx / SIZE;
} 

const string get_str(int type) {
    switch(type) {
        case UNIFORM:
            return "uniform";
        case EXPONENTIAL:
            return "exponential";
        case CONSTANT:
            return "constant";
        default:
            return "";
    }
} 

void test(int type_tau, int type_sigma) {
    string fname = get_str(type_tau) + "_" + get_str(type_sigma) + ".out";
    FILE *fd = fopen(fname.c_str(), "w");
    for (double mx = 0.1; mx < 0.99; mx += 0.1) {
        generate_seq(sigma, type_sigma, mx);
        fprintf(fd, "%f\t", mx);
        for (double i = 0.1; i < 0.99; i += 0.1) {
            generate_seq(tau, type_tau, i);
            
            fprintf(fd, "%f\t", mx_omega(sigma, tau));
        }
        fprintf(fd, "\n");
    }
    fclose(fd);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    chdir("./out");
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            test(i, j);
    return 0;
}