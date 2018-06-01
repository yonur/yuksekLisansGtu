#include <stdint.h>

#include "stm32f446xx.h"

#define BASE_ADDR_OF_PERIPH_GPIOC GPIOC

void button_init(void);
void uart2_init(void);
void dma1_init(void);
void send_some_data(void);

int main(void) {
	
	button_init();
	uart2_init();
	send_some_data();
	dma1_init();
	
	while(1);
	return 0;
}

void button_init(void) {
//Buton GPIOC'nin 13 numarali pinine baglanmistir.
	GPIO_TypeDef *pGPIOC;
	pGPIOC = BASE_ADDR_OF_PERIPH_GPIOC;
	
	RCC_TypeDef *pRCC;
	pRCC = RCC;
	
	EXTI_TypeDef *pEXTI;
	pEXTI = EXTI;
	
	SYSCFG_TypeDef *pSYSCFG;
	pSYSCFG = SYSCFG;

//1. GPIOC perirheralin clock aktiflestirilir.
	pRCC->AHB1ENR |= (1 << 2);
	
//2. Pin input mode olarak set edilir.
	pGPIOC->MODER &= ~(0x3 << 26);
	
//3. Pin i�in interrupt etkinlestirilir.
	pEXTI->IMR |= (1 << 13);

//4. SYSCFG i�in 14 clock set edilir.
	pRCC->APB2ENR |= (1 << 14);

//5. GPIOC pin13 i�in external interrupt etkinlestirlir.
	pSYSCFG->EXTICR[3] &= ~(0xF << 4); //Once alan temizlenir.
	pSYSCFG->EXTICR[3] |=  (0x2 << 4); //GPIOC pin 13 i�in set edilir.
	
//6. Pin i�in edge detection set edilir. Yani y�kselen kenarda mi yoksa d�sen kenarda mi algilama yapilacak.
pEXTI->FTSR |= (1 << 13); //GPIOC peripheralin 13 nolu pini d�sen kenar i�in tetiklenir.

//7. NVIC registerindaki bu pin ile ilgili IRQ etkinlestirilir.
NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void uart2_init(void) {
	RCC_TypeDef *pRCC;
	pRCC = RCC;
	
	GPIO_TypeDef *pGPIOA;
	pGPIOA = GPIOA;
	
	USART_TypeDef *pUART2;
	pUART2 = USART2;
	
//1. UART Perioheral i�in clock etkinlestirilir.
	pRCC->APB1ENR |= (1 << 17);
	
//2. uart_tx ve uart_rx i�in GPIO pinler konfig�re edilir.
	//2.1 GPIOA peripheral i�in clock etkinlestirilir.
	pRCC->AHB1ENR |= (1 << 0);
	//PA2 TX olarak PA3 RX olarak konfig�re edilir.
	//PA2'nin TX olarak konfig�rasyonu su sekildedir:
	//2.2 PA2 modu alternate fonksiyon moda degistirilir.
	pGPIOA->MODER  &= ~(3 << 4);
	pGPIOA->MODER  |=  (2 << 4);
	pGPIOA->AFR[0] &= ~(15 << 8);
	pGPIOA->AFR[0] |=  (7 << 8);
	//2.3 pull-up direnci ihtiyaca g�re etkinlestirilir yada etkinlestirilmez.
	pGPIOA->PUPDR  &= ~(3 << 4);
	pGPIOA->PUPDR  |=  (1 << 4);
	//PA3'�n RX olarak konfig�re edilmesi ise su sekildedir:
	//2.4 PA3 modu alternate fonksiyon moda ge�irilir.
	pGPIOA->MODER  &= ~(3 << 6);
	pGPIOA->MODER  |=  (2 << 6);
	pGPIOA->AFR[0] &= ~(15 << 12);
	pGPIOA->AFR[0] |=  (7 << 12);
	//2.5 pull-up direnci ihtiyaca g�re etkinlestirilir yada etkinlestirilmez.
	pGPIOA->PUPDR  &= ~(3 << 6);
	pGPIOA->PUPDR  |=  (1 << 6);
	
//3. Baudrate konfig�re edilir.
	pUART2->BRR = 0x8B;
	
//4. Data width, no of stop bits gibi �zellikler set edilir.
	//Burada konfig�rasyon yapmiyor varsayilan degerleri kullaniyoruz.
	
//5. Uart aray�z�n�n Tx engine etkinlestirilir.
	pUART2->CR1 |= (1 << 3);

//6. Uart peripheral etkinlestirilir.
	pUART2->CR1 |= (1 << 13);
	
}

void dma1_init(void) {

}
void send_some_data(void) {
	char some_data[] = "Hello World\n\r";
	USART_TypeDef *pUART2;
	pUART2 = USART2;
	uint32_t len = sizeof(some_data);
	
	for(uint32_t i = 0; i < len; i++) {
		while(!(pUART2->SR & (1 << 7)));
		pUART2->DR = some_data[i];
	}
	
}

