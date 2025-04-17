/*
 * P2-B3-main.c
 *
 *  Created on: 17 thg 4, 2025
 *      Author: ADMIN
 */
#include <stdio.h>
#include "P2-B3-math.h"
int main(void)
{
    int a = 8, b = 2;
    printf("Cong: %d + %d = %d\n", a, b, cong(a, b));
    printf("Tru: %d - %d = %d\n", a, b, tru(a, b));
    printf("Nhan: %d * %d = %d\n", a, b, nhan(a, b));
    printf("Chia: %d / %d = %.2f\n", a, b, chia(a, b));
    getchar();
    return 0;
}
