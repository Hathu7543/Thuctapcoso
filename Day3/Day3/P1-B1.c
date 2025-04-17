/*
 * P1-B1.c
 *
 *  Created on: 17 thg 4, 2025
 *      Author: ADMIN
 */
#include <stdio.h>
int main() {
    //Tạo một biến kiểu char và khởi tạo giá trị ban đầu là 100
    char bien = 100;
    //In ra giá trị và địa chỉ bộ nhớ của biến vừa tạo
    printf("Gia tri ban dau cua bien: %d\n", bien);
    printf("Dia chi cua bien: %p\n", (void*)&bien);
    //Tạo một biến con trỏ và lưu địa chỉ của biến char
    char* ptr = &bien;
    //Đọc từ con trỏ
    char readValue = *ptr;
    //In ra dữ liệu vừa đọc
    printf("Gia tri doc duoc tu con tro: %d\n", readValue);
    //Ghi giá trị 65 vào vùng nhớ đó
    *ptr = 65;
    //In lại giá trị của biến myChar sau khi bị ghi
    printf("Gia tri cua bien sau khi ghi = 65: %d\n", bien);
    getchar();
    return 0;
}
