/*
 * P2-B1.c
 *
 *  Created on: 17 thg 4, 2025
 *      Author: ADMIN
 */
#include <stdio.h>
// Hàm hoán đổi bằng cách truyền theo giá trị
void truyentheothamtri(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("Trong ham truyentheogiatri: a = %d, b = %d\n", a, b);
}
// Hàm hoán đổi bằng cách truyền theo tham chiếu (dùng con trỏ)
void truyentheothamchieu(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("Trong ham truyentheothamchieu: a = %d, b = %d\n", *a, *b);
}
int main() {
    int x = 10;
    int y = 20;
    printf("Truyen theo gia tri\n");
    printf("Truoc khi goi truyentheogiatri: x = %d, y = %d\n", x, y);
    truyentheothamtri(x, y);
    printf("Sau khi goi truyentheogiatri:  x = %d, y = %d\n", x, y);
    printf("\nTruyen theo tham chieu\n");
    printf("Truoc khi goi truyentheothamchieu: x = %d, y = %d\n", x, y);
    truyentheothamchieu(&x, &y);
    printf("Sau khi goi truyentheothamchieu:  x = %d, y = %d\n", x, y);
    getchar();
    return 0;
}
