#include <stdint.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_rcc.h>

/******************************************************************************/
/*                     PRIVATE TYPES and DEFINITIONS                         */
/******************************************************************************/


/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define BTN_PRESS							0
// Define Logic GPIO_PIN

#define GPIO_PIN_SET						1
#define GPIO_PIN_RESET						0

// Define GPIO PIN

#define BUZZER_GPIO_PORT					GPIOC
#define BUZZER_GPIO_PIN						GPIO_Pin_9
#define BUZZERControl_SetClock				RCC_AHB1Periph_GPIOC

#define BUTTON_GPIO_PORT					GPIOB
#define BUTTON_GPIO_PIN						GPIO_Pin_4
#define BUTTONControl_SetClock				RCC_AHB1Periph_GPIOB

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

void delay() {
	for (uint32_t i = 0; i < 500000; i++);
}
//Cấu hình chân PC9 of Buzzer.
static void buzzer_Init(void) {
	//Khai báo biến thuộc kiểu dữ liệu struct GPIO.
	GPIO_InitTypeDef GPIO_InitStructure;

	//Cấp xung clock hoạt động cho port C
	RCC_AHB1PeriphClockCmd(BUZZERControl_SetClock, ENABLE);

	//Chọn chân sử dụng với chức năng điều khiển LED.
	GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;

	//Chọn mode Output.
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

	//Tốc độ xử lý trên chân.
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//Chọn chế độ Output Push Pull.
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	//Trạng thái ban đầu trên chân là kéo xuống GND Pull Down.
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	//Khoi tao tat ca cac gia tri ben tren: Truyền đối số --> Áp dụng cấu hình GPIO trên.
	GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);
}

//Cấu hình chân B5(PB3) of Button.
static void button_Init(void) {
	//Khai báo biến thuộc kiểu dữ liệu struct GPIO.
	GPIO_InitTypeDef GPIO_InitStructure;

	//Cấp xung clock hoạt động cho port B
	RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);

	//Chọn chân làm chức năng nút nhấn.
	GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;

	//Chọn MODE Input.
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

	//Tốc độ xử lý.
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//Trạng thái kéo trở lên nguồn +3.3V(Pull Up)
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	//Áp dụng cấu hình GPIO trên.
	GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);
}

//Hàm điều khiển Buzzer.(Tương tự bai1)
static void buzzerControlSetStatus(GPIO_TypeDef *pGPIOx, uint16_t wGPIO_Pin, uint8_t byStatus) {
	// SET bit in BSRR Registers

	if (byStatus == GPIO_PIN_SET) {
		pGPIOx->BSRRL = wGPIO_Pin;
	}
	if (byStatus == GPIO_PIN_RESET) {
		pGPIOx->BSRRH = wGPIO_Pin;
	}
}

//Hàm đọc giá trị nút nhấn.(Tương tự bai1)
static uint8_t buttonReadStatus(GPIO_TypeDef *pGPIOx, uint16_t wGPIO_Pin) {
	uint8_t Read_Pin = Bit_RESET;

	if ((pGPIOx->IDR & wGPIO_Pin) != (uint32_t) Bit_RESET) {
		Read_Pin = (uint8_t) Bit_SET;
	} else {
		Read_Pin = (uint8_t) Bit_RESET;
	}
	return Read_Pin;
}

int main(void) {
    uint8_t byStatus = 1;
    buzzer_Init();
    button_Init();

    while (1) {
        if (buttonReadStatus(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN) == BTN_PRESS) {
            delay(); // debounce
            byStatus++;

            if (byStatus % 2 == 0) {
                buzzerControlSetStatus(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_SET);
            } else {
                buzzerControlSetStatus(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_RESET);
            }

            // Chờ đến khi nút được thả ra
            while (buttonReadStatus(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN) == BTN_PRESS);
        }
    }

    return 0;
}
