#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <time.h> 
#include <cmath> 
#include <string>
#include <string.h>
#include <fstream>
#include <vector>


#define pi 3.14

using namespace std;

/*	Метод отбраковки	*/
float methodReject() {
	float a = 0, b = pi, c = 1, x1, x2;
	do {
		x1 = (float) rand() / RAND_MAX;
		x2 = (float) rand() / RAND_MAX;
	} while (sinf(a + (b - a) * x1) < c * x2);
	/*x2 *= c;
	x1 = a + (b - a) * x1;*/
	return a + (b - a) * x1;
}

/*	Распределение без повторений */
void A_(int n, int nexp, string& fname) {
	vector<int> nums, temp;
	int it, k = 3 * n / 4, mas[n], part = nexp / k + 1;
	float p;

	memset(mas, 0, sizeof(int) * n);
	for(int i = 0; i < n; i++)
		temp.push_back(i);	
	for(int j = 0; j < part; j++) {
		nums = temp;
		if (j == part - 1) k = nexp % k;
		for(int i = 0; i < k; i++) {
			p = 1.0 / (n - i);
			it = (float) rand() / RAND_MAX / p;
			++mas[nums[it]];
			nums.erase(nums.begin() + it);
		}
	}
	FILE *fp = fopen(fname.c_str(), "w");
	for(int i = 0; i < n; i++) {
		fprintf(fp, "%d\t%.4f\n", i, (float) mas[i] / nexp);
	}
	fclose(fp);
}

/*	Распределение с повторением */
void A(int n, int nexp, string& fname) {
	float p = 1, intervals[n], x, sum;
	int mas[n];

	memset(mas, 0, sizeof(int) * n);
	for(int i = 0; i < n - 1; i++) {
		intervals[i] = abs(remainder((float) rand() / RAND_MAX, p));
		p -= intervals[i];
		//printf("%.6f ", intervals[i]);
	}

	intervals[n - 1] = p;
	printf("%.6f\n", p);

	for(int i = 0; i < nexp; i++) {
		x = (float) rand() / RAND_MAX;
		sum = 0;
		for (int j = 0; j < n; j++) {
			sum += intervals[j];
			if (x < sum) {
				++mas[j];
				break;
			}
		}
	}
	FILE *fp = fopen(fname.c_str(), "w");
	for(int i = 0; i < n; i++) {
		fprintf(fp, "%d\t%.4f\t%.4f\n", i, intervals[i], (float) mas[i] / nexp);
	}
	fclose(fp);
}

void testMethodRej(int n, int m, const char *fname) {
	float x;
	int mas[n];
	FILE *fp = fopen(fname, "w");
	
	memset(mas, 0, sizeof(int) * n);
	for (int i = 0; i < m; i++) {
		x = methodReject();
		++mas[(int)(x / pi * n)];
	}
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%d\t%d\n", i, mas[i]);
	}
	fprintf(fp, "%d\n", n); 
}

int main(int argc, char const *argv[])
{

	string s[3] = {"out_A", "out_A_", "out_rej"};
	

	srand(time(NULL));

	A_(10, 10000, s[1]);
	A(10, 10000, s[0]);
	testMethodRej(40, 100000, s[2].c_str());

	return 0;
}
