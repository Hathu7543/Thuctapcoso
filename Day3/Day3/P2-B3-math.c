/*
 * P2-B3-math.c
 *
 *  Created on: 17 thg 4, 2025
 *      Author: ADMIN
 */
#include "P2-B3-math.h"
int cong(int a, int b) {
    return a + b;
}

int tru(int a, int b) {
    return a - b;
}

int nhan(int a, int b) {
    return a * b;
}

float chia(int a, int b) {
    if (b == 0) return 0.0f;
    return (float)a / b;
}
