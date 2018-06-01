#include "stm32f446xx.h"

void clear_exti_pending_bit(void) {
	EXTI_TypeDef *pEXTI;
	pEXTI = EXTI;
	
	if(pEXTI->PR & (1 << 13)) {
		pEXTI->PR |= (1 << 13);
	}
	
}

void EXTI15_10_IRQHandler(void) {
		clear_exti_pending_bit();
	
}