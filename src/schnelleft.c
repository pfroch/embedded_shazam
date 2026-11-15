#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//(Cooley-Tukey algorithm)
void fft(double complex *X, int n) {
    if (n <= 1) return; //basecase

    double complex *even = (double complex *)malloc(n / 2 * sizeof(double complex));
    double complex *odd = (double complex *)malloc(n / 2 * sizeof(double complex));
    
    for (int i = 0; i < n / 2; i++) {
        even[i] = X[2 * i];
        odd[i] = X[2 * i + 1];
    }

    fft(even, n / 2);
    fft(odd, n / 2);

    //butterfly
    for (int k = 0; k < n / 2; k++) {
        double complex t = cexp(-2.0 * I * M_PI * k / n) * odd[k];
        X[k]         = even[k] + t;
        X[k + n / 2] = even[k] - t;
    }

    
    free(even);
    free(odd);
}

int main() {
    int n = 8;
    double complex X[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};

    printf("Original Signal (Time Domain):\n");
    for (int i = 0; i < n; i++) {
        printf("X[%d] = %.2f + %.2fi\n", i, creal(X[i]), cimag(X[i]));
    }
    fft(X, n);

    printf("\nFourier Transform (Frequency Domain):\n");
    for (int i = 0; i < n; i++) {
        printf("X[%d] = %.2f + %.2fi\n", i, creal(X[i]), cimag(X[i]));
    }

    return 0;
}