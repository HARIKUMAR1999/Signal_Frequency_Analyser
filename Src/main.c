#include "stm32l476xx.h"
#include "clock.h"
#include "uart.h"
#include "timer.h"
#include "Post_Check.h"
#include "Set_Limit.h"
#include "Compute.h"

uint8_t buffer[100];																					//setting the buffer for Uart
int ll,*llp,n;																							//initializing lower limit and integer n for printing
*llp = &ll;

int main(void) {
	clock_init();																						//Initializing Clock
	timer_Init();																						//Initializing Timer
	USART2_Init(115200);																				//Initializing Uart
																										//Getting the flag value whether Post check is Successfull or not
	int flag=post_check();
	while(1){

		if(flag==1){
		n = sprintf((char *)buffer, "\n\r Welcome to Project 1 \n\n\r Press Enter to continue \n\n");
		USART_Write(USART2, buffer, n);
		int rxstring = USART_Read((int) USART2);
		if(rxstring==13){

			*llp = limit_init();																		//Setting the limits
			get_timer_data(*llp);																		//getting the data from timer running on input capture and and printing results

		}
		else{
			n = sprintf((char *)buffer, "\n\r Program has Terminated \n\r");
			USART_Write(USART2, buffer, n);
			break;
		}
	}
		else if(flag==0){
			n = sprintf((char *)buffer, "\n\r Program has Terminated \n\r");
						USART_Write(USART2, buffer, n);
						break;
		}
}



}

