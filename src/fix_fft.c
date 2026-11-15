#include "fix_fft.h"


int fix_fft(int8_t *fr, int8_t *fi, uint8_t m, uint8_t inverse) {
    int mr, nn, i, j, l, k, istep, n;
    int tr, ti;

    n = 1 << m;
    if (n > 128) return -1;

    nn = n >> 1;
    mr = 0;
    
    for (i = 0; i < n - 1; ++i) {
        if (i < mr) {
            tr = fr[i];
            fr[i] = fr[mr];
            fr[mr] = (int8_t)tr;
            if (fi != 0) {
                ti = fi[i];
                fi[i] = fi[mr];
                fi[mr] = (int8_t)ti;
            }
        }
        l = nn;
        while (l <= mr) {
            mr -= l;
            l >>= 1;
        }
        mr += l;
    }

    l = 1;
    k = m - 1;
    
    while (l < n) {
        istep = l << 1;
        for (int m_idx = 0; m_idx < l; ++m_idx) {
            for (i = m_idx; i < n; i += istep) {
                j = i + l;
                tr = fr[j];
                ti = fi[j];
                fr[j] = fr[i] - (int8_t)tr;
                fi[j] = fi[i] - (int8_t)ti;
                fr[i] += (int8_t)tr;
                fi[i] += (int8_t)ti;
            }
        }
        l = istep;
        k--;
    }
    return 0;
}