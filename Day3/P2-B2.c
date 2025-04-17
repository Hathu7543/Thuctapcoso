/*
 * P2-B2.c
 *
 *  Created on: 17 thg 4, 2025
 *      Author: ADMIN
 */
#include <stdio.h>
// Hàm duy nhất trả về tổng và tích của hai số bằng cách dùng tham chiếu (con trỏ)
void tinh_tong_va_tich(int a, int b, int *tong, int *tich) {
    *tong = a + b;
    *tich = a * b;
}
int main() {
    int x = 5;
    int y = 3;
    int tong, tich;
    // Gọi hàm tinh tong va tich
    tinh_tong_va_tich(x, y, &tong, &tich);
    // Tra ket qua tong va tich
    printf("Tong cua %d va %d la: %d\n", x, y, tong);
    printf("Tich cua %d va %d la: %d\n", x, y, tich);
    getchar();
    return 0;
}
