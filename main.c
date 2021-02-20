#include "stm32f030x8.h"
#include "stm32f0xx.h"

//#include "system_stm32f0xx.c"
#include "system_stm32f0xx.h"
// Create function to wait for a specified amount of time
void WaitForAMoment(int Moment) {
  volatile int i, j;
  for (i=0; i < Moment; i++) {
    j ++;
  }
}
//tm32f030x8.h
int main(void) {
// Enable the GPIO Clock for Port C using the AHB and RCC
RCC ->AHBENR |= RCC_AHBENR_GPIOCEN;
// Set any Control Registers for PortC Pin 6
// Moder
GPIOC ->MODER |= GPIO_MODER_MODER6_0;
// OTyper
GPIOC ->OTYPER &= ~(GPIO_OTYPER_OT_6);
//OSpeedr
GPIOC ->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR6;
// PUPDr
GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR6);

while(1) {

  // Turn on the LED (BSRR)
  GPIOC ->BSRR |= GPIO_BSRR_BS_6;
  // Wait
  WaitForAMoment(200000);
  // Turn off the LED (BRR)
  GPIOC ->BRR |= GPIO_BRR_BR_6;
  // Wait
  WaitForAMoment(100000);

  }
}
