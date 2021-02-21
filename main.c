#include "stm32f030x8.h"
#include "stm32f0xx.h"
#include "system_stm32f0xx.h"
// Create function to wait for a specified amount of time
void WaitForAMoment(int Moment) {
  volatile int i, j;
  for (i=0; i < Moment; i++) {
    j ++;
  }
}

int main(void) {
// Enable the GPIO Clock for Port C using the AHB and RCC
RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
// Mode register set
GPIOB->MODER &= ~GPIO_MODER_MODER6_0;
GPIOB->MODER |= GPIO_MODER_MODER6_1;
GPIOB->MODER &= ~GPIO_MODER_MODER7_0;
GPIOB->MODER |= GPIO_MODER_MODER7_1;
// Typer register, open drain
GPIOB->OTYPER |= GPIO_OTYPER_OT_6;
GPIOB->OTYPER |= GPIO_OTYPER_OT_7;
// O speed of register
GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR6_0;
GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR7_0;
// No PUPDR
GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;
GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7;
// Set alt function for pin 6 and 7
// 0b00010001000000000000000000000000
GPIOB->AFR[0] = (1 << 24) | (1 << 28);//0b00010001000000000000000000000000; //(1 << 24) | (1 << 28);

// Enable I2C
RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
// timing configuration: used tool at https://www.st.com/en/embedded-software/stsw-stm32126.html#get-software
I2C1->TIMINGR = (uint32_t) 0x0010020A; //0x00201D2B
// enable per control
I2C1->CR1 |= I2C_CR1_PE;

// Asset slave ID, room for RW
I2C1->CR2 |= (0x60 << 1); //(0x60 << 1)
// Set R/W bit 0 = W 1= R
I2C1->CR2 &= ~I2C_CR2_RD_WRN;
// How many bytes we are wrintg
I2C1->CR2 |= (3 << 16);
// start bit
I2C1->CR2 |= I2C_CR2_START;
// confirm start condition
while(I2C1->CR2 & I2C_CR2_START);

// write a byte to the Transmit Data register
 //I2C1->TXDR = 0b11000000; //0x60;
 I2C1->TXDR = 0x40; //0b10000000; //
 I2C1->TXDR = 0xFF; //0b00000000; //
 I2C1->TXDR = 0xF0; // 0b11110000; //

// Confirm transmit by making sure TXDR is empty
 while(!(I2C1->ISR & I2C_ISR_TXE));

// Establish stop condition
I2C1->CR2 |= I2C_CR2_STOP;
// Confirm stop
while(I2C1->CR2 & I2C_CR2_STOP);

while(1) {}

// Mode, TYPE, Speed, ALt Function
// RCC ->AHBENR |= RCC_AHBENR_GPIOCEN;
// // Set any Control Registers for PortC Pin 6
// // Moder
// GPIOC ->MODER |= GPIO_MODER_MODER6_0;
// // OTyper
// GPIOC ->OTYPER &= ~(GPIO_OTYPER_OT_6);
// //OSpeedr
// GPIOC ->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR6;
// // PUPDr
// GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR6);
//
// while(1) {
//
//   // Turn on the LED (BSRR)
//   GPIOC ->BSRR |= GPIO_BSRR_BS_6;
//   // Wait
//   WaitForAMoment(200000);
//   // Turn off the LED (BRR)
//   GPIOC ->BRR |= GPIO_BRR_BR_6;
//   // Wait
//   WaitForAMoment(100000);
//
//   }
}
