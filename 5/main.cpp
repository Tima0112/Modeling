#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <vector>
#include <iostream>


using namespace std;

#define SIZE 10000

#define FIFO 0
#define SF 1
#define SL 2

vector<double> tau(SIZE);
vector<double> sigma(SIZE);

struct {
    bool operator()(double a, double b)
    {   
        return a < b;
    }   
} Less;

struct {
    bool operator()(double a, double b)
    {   
        return a > b;
    }   
} More;


template <class T> 
void generate_uniform(vector<T> &mas, double mx) {
    for (int i = 0; i < SIZE; ++i)
        mas[i] = ((double) rand() / RAND_MAX) * mx;
}

template <class T> 
double mx_omega(vector<T> &sigma, vector<T> &tau) {
    double mx = 0.0, tmp = 0.0;
    for (int i = 1; i < SIZE; ++i) {
        tmp = max(0.0, (sigma[i - 1] + tmp - tau[i]));
        mx += tmp;
    }
    return mx / SIZE;
} 


const string get_str(int type) {
    switch(type) {
        case FIFO:
            return "fifo";
        case SL:
            return "sl";
        case SF:
            return "sf";
        default:
            return "";
    }
} 

template <class T>
void sorting(vector<T> &sigma, int type) {
    switch(type) {
        case SL:
            sort(sigma.begin(), sigma.end(), Less);
            break;
        case SF:
            sort(sigma.begin(), sigma.end(), More);
            break;
        default:
            return;
    }
}

void test(int type) {
   string fname = get_str(type) + ".out";
    FILE *fd = fopen(fname.c_str(), "w");

    for (double mx = 0.1; mx < 0.99; mx += 0.1) {
        generate_uniform(sigma, mx);
        sorting(sigma, type);
        fprintf(fd, "%f\t", mx);
        for (double i = 0.1; i < 0.99; i += 0.1) {
            generate_uniform(tau, i);
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
        test(i);

 
    return 0;
}