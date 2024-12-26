#include <stdint.h>

#define STM32F103xB
#define __PROGRAM_START
#include "stm32f1xx.h"

__attribute__((noreturn)) int main(void) {
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk;

  uint32_t temp;
  temp = GPIOA->CRL;
  temp &= ~(GPIO_CRL_MODE5_Msk | GPIO_CRL_CNF5_Msk);
  temp |= GPIO_CRL_MODE5_1;
  GPIOA->CRL = temp;

  while (1) {
    GPIOA->BSRR = GPIO_BSRR_BS5_Msk;
    for (int i = 0; i < 0x100000; i++) ;
    GPIOA->BSRR = GPIO_BSRR_BR5_Msk;
    for (int i = 0; i < 0x100000; i++) ;
  }
}
