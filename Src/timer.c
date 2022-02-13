#include "stm32l476xx.h"

void timer_Init(void){

		RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;					//Enabling Clock for the timer

		TIM2->PSC=15;											//Setting the Prescalar value as 15 so that timer will be running on 1 Mhz clock

		TIM2->EGR |= TIM_EGR_UG;								//Creating an update event

		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;					//Enabling the GPIO pin for taking input from the signal genrator

		GPIOA->MODER &= ~3;										//Setting the gpio pin for input
		GPIOA->MODER |= 2 ;

		GPIOA->AFR[0]|=0x1;										//Setting the alternate function register as well be taking input from the pin for the timer

		TIM2->CCER &= ~(0xFFFFFFFF);							//Turning off the input capture by turning off the output enable

		TIM2->CCMR1|=1;											//setting the

		TIM2->CCER |=1;											//Turning back on the output enable  for functioning of the timer

		TIM2->CR1 |= TIM_CR1_CEN;								//Staring the input capture mode for the timer

}



