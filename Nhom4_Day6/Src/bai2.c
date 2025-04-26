#include <stdint.h>

//Định nghĩa các địa chỉ cơ bản và offset cho RCC và GPIOA
#define RCC_BASE_ADDR          0x40023800UL
#define RCC_CFGR_REG_OFFSET    0x08UL
#define RCC_CR_REG_OFFSET      0x00UL

#define RCC_CFGR_REG_ADDR      (RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define RCC_CR_REG_ADDR        (RCC_BASE_ADDR + RCC_CR_REG_OFFSET)

#define GPIOA_BASE_ADDR        0x40020000UL

int main(void)
{
	//Khai báo hai con trỏ kiểu uint32_t* trỏ đến địa chỉ các thanh ghi
	uint32_t *pRccCrReg = (uint32_t*)RCC_CR_REG_ADDR;
	uint32_t *pRccCfgrReg =  (uint32_t*) RCC_CFGR_REG_ADDR;

	//Bật xung clock HSE bằng cách set bit 16 (HSEON) trong thanh ghi CR
	*pRccCrReg |= ( 1 << 16);

	//Chờ cho đến khi bộ dao động HSE ổn định bằng cách kiểm tra bit 17 (HSERDY)
	while( ! (*pRccCrReg & ( 1 << 17) ) );
	*pRccCfgrReg |= ( 1 << 0);

	//Cấu hình các bit trong thanh ghi RCC_CFGR để chọn HSE làm nguồn xung cho MCO1
	*pRccCfgrReg |= (1 << 22);

	//Cấu hình hệ số chia (prescaler) cho tín hiệu ra MCO1 là 4
	*pRccCfgrReg |= (1 << 25);
	*pRccCfgrReg |= (1 << 26);

	//Cấp xung clock cho PORTA
	uint32_t *pRCCAhb1Enr = (uint32_t *)(RCC_BASE_ADDR + 0x30);
	*pRCCAhb1Enr |= (1 << 0);  // Enable clock for GPIOA

	//Cấu hình PA8 làm Alternate Function
	uint32_t *pGPIOAModeReg = (uint32_t *)(GPIOA_BASE_ADDR + 0x00);
	*pGPIOAModeReg &= ~(0x3 << 16);  // Clear MODER8
	*pGPIOAModeReg |=  (0x2 << 16);  // Set MODER8 to alternate function (10)

	//Chọn chế độ Alternate Function 0 cho PA8 (tương ứng MCO1)
	uint32_t *pGPIOAAltFunHighReg = (uint32_t *)(GPIOA_BASE_ADDR + 0x24);
	*pGPIOAAltFunHighReg &= ~(0x0F << 0);  // Clear AFRH0 (PA8)

    /* Loop forever */
	for(;;);
}
