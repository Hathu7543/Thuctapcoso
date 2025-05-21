#include <stdint.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_rcc.h>

// Define Logic GPIO_PIN

#define BTN_PRESS								0 //Khi nhấn nút chân sẽ ở mức thấp LOW(0)
#define GPIO_PIN_SET							1
#define GPIO_PIN_RESET							0

// Define GPIO PIN
//LED GREEN on Board(LD2) = PA5
#define LED_GPIO_PORT							GPIOA
#define LED_GPIO_PIN							GPIO_Pin_5

////LED RGB - GREEN1 = PA0 (Kit mở rộng)
#define LED_GREEN1_GPIO_PORT					GPIOA
#define LED_GREEN1_GPIO_PIN						GPIO_Pin_0

//LED RGB - BLUE2 = PA10 (Kit mở rộng)
#define LED_BLUE2_GPIO_PORT						GPIOA
#define LED_BLUE2_GPIO_PIN						GPIO_Pin_10

//LED_1 - RED = PA1 (Kit mở rộng)
#define LED_RED1_GPIO_PORT						GPIOA
#define LED_RED1_GPIO_PIN						GPIO_Pin_1

//BUTTON B4(SW4) = PB0 (Kit mở rộng)
#define BUTTON_B4_GPIO_PORT						GPIOB
#define BUTTON_B4_GPIO_PIN						GPIO_Pin_0

//BUTTON B3(SW3) = PA4 (Kit mở rộng)
#define BUTTON_B3_GPIO_PORT						GPIOA
#define BUTTON_B3_GPIO_PIN						GPIO_Pin_4

//BUZZER = PC9 (Kit mở rộng)
#define BUZZER_GPIO_PORT						GPIOC
#define BUZZER_GPIO_PIN							GPIO_Pin_9

//Cấu hình các chân của LED, Buzeer, BUTTON.
static void GPIO_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA |
                           RCC_AHB1Periph_GPIOB |
                           RCC_AHB1Periph_GPIOC, ENABLE);

    // ==== CẤU HÌNH OUTPUT ====

    // LED: PA5, PA10, PA1.
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN | LED_RED1_GPIO_PIN | LED_GREEN1_GPIO_PIN | LED_BLUE2_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    // BUZZER: PC9.
    GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // ==== CẤU HÌNH INPUT ====

	// B4 (PB0).
	GPIO_InitStructure.GPIO_Pin = BUTTON_B4_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

    // B3 (PA4)
    GPIO_InitStructure.GPIO_Pin = BUTTON_B3_GPIO_PIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4000; i++);
}

//Hàm điều khiển LED, Buzzer.
static void Set_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN, uint8_t Status) {
	if (Status == GPIO_PIN_SET) {
		GPIOx->BSRRL = GPIO_PIN;
	}
	if (Status == GPIO_PIN_RESET) {
		GPIOx->BSRRH = GPIO_PIN;
	}
}

//Hàm đọc giá trị nút nhấn BUTTON.
static uint8_t Read_Button(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
	uint8_t Read_Pin = 0x00;

	if ((GPIOx->IDR & GPIO_PIN) != (uint32_t) Bit_RESET) {
		Read_Pin = (uint8_t) Bit_SET;
	} else {
		Read_Pin = (uint8_t) Bit_RESET;
	}

return Read_Pin;
}

//Hàm BLINK_LED(Chớp nháy LED).
static void Blink_LED(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN, uint8_t times) {
    for (uint8_t i = 0; i < times; i++) {
        Set_pin(GPIOx, GPIO_PIN, GPIO_PIN_SET); //LED sáng.
        delay_ms(200); //delay 200ms
        Set_pin(GPIOx, GPIO_PIN, GPIO_PIN_RESET); //LED tắt.
        delay_ms(200); //delay 200ms
    }
}

int main(void) {
	GPIO_init();

    // 1: Nháy LED PA5 (trên board) 2 lần khi cấp nguồn (times: 2).
    Blink_LED(LED_GPIO_PORT, LED_GPIO_PIN, 2);

	uint8_t b4_count = 0;
	uint8_t status = 0;
	while (1) {
		// 2. Xử lý nhấn nút B4 (PB0) hai lần.
		if (Read_Button(BUTTON_B4_GPIO_PORT, BUTTON_B4_GPIO_PIN) == BTN_PRESS)
		{
			delay_ms(50); //đợi 50ms chống rung nút nhấn.
			b4_count++;
			while(Read_Button(BUTTON_B4_GPIO_PORT, BUTTON_B4_GPIO_PIN) == BTN_PRESS); // đợi nhả nút

	        if (b4_count == 2) {
	            // Nháy LED GREEN1 (PA0), BLUE2 (PA10)  + còi bíp (PC9) 2 lần
	            for (uint8_t i = 0; i < 2; i++) {
	                Set_pin(LED_GREEN1_GPIO_PORT, LED_GREEN1_GPIO_PIN, GPIO_PIN_SET);
	                Set_pin(LED_BLUE2_GPIO_PORT, LED_BLUE2_GPIO_PIN, GPIO_PIN_SET);
	                Set_pin(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_SET);
	                delay_ms(200);
	                Set_pin(LED_GREEN1_GPIO_PORT, LED_GREEN1_GPIO_PIN, GPIO_PIN_RESET);
	                Set_pin(LED_BLUE2_GPIO_PORT, LED_BLUE2_GPIO_PIN, GPIO_PIN_RESET);
	                Set_pin(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_RESET);
	                delay_ms(200);
	            }
	            b4_count = 0; // reset đếm lần nhấn
	        }
		}

		// 3. Nhấn nút B3 (PA4)  bật LED (PA1) đỏ; thả tắt LED
			if (Read_Button(BUTTON_B3_GPIO_PORT, BUTTON_B3_GPIO_PIN) == BTN_PRESS) {
					delay_ms(50); //đợi 50ms chống rung nút nhấn.
					status++;
					while(Read_Button(BUTTON_B3_GPIO_PORT, BUTTON_B3_GPIO_PIN) == BTN_PRESS);
			}
			if (status == 1) {
				Set_pin(LED_RED1_GPIO_PORT, LED_RED1_GPIO_PIN, GPIO_PIN_SET);
			} else {
				Set_pin(LED_RED1_GPIO_PORT, LED_RED1_GPIO_PIN, GPIO_PIN_RESET);
				status = 0;
			}
	}
	return 0;
}
