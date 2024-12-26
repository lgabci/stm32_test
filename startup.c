#include <stdint.h>

#define STM32F103xB
#define __PROGRAM_START
#include "stm32f1xx.h"

#define SRAM_BASE       0x20000000UL
#define SRAM_SIZE       0x5000UL
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)
#define STACK_PT_INIT   SRAM_END

#define ISR_V_SZ_W      67

extern int main(void);

void reset_handler(void);
void default_handler(void) __attribute__((noreturn));
void nmi_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void mmu_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void bus_fault_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void debug_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, noreturn, alias("default_handler")));
void systick_handler(void) __attribute__((weak, noreturn, alias("default_handler")));

uint32_t isr_vector[ISR_V_SZ_W] __attribute__((section(".isr_vector"))) = {
  STACK_PT_INIT,
  (uint32_t)&reset_handler,
  (uint32_t)&nmi_handler,
  (uint32_t)&hard_fault_handler,
  (uint32_t)&mmu_handler,
  (uint32_t)&bus_fault_handler,
  (uint32_t)&usage_fault_handler,
  0,
  0,
  0,
  0,
  (uint32_t)&svcall_handler,
  (uint32_t)&debug_handler,
  0,
  (uint32_t)&pendsv_handler,
  (uint32_t)&systick_handler
};

__attribute__((noreturn)) void default_handler(void) {
  while (1) ;
}

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;


void reset_handler(void) {
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t *)&_etext;
  uint8_t *sram_data = (uint8_t *)&_sdata;

  for (uint32_t i = 0; i < data_size; i ++) {
    sram_data[i] = flash_data[i];
  }

  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t *)&_sbss;

  for (uint32_t i = 0; i < bss_size; i ++) {
    bss[i] = 0;
  }

  main();
}
