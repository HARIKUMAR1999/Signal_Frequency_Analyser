#include "stm32l476xx.h"
#include <uart.h>

int post_check() {
	uint8_t buffer[1000];
	int flag = 0, now,*nowp=&now, n;
	*nowp=0;

	while (1) {

		//checking if there is any input during the first 100 milli seconds
		while ((TIM2->CNT - *nowp) < 1000) {
			if (TIM2->SR & 0x2) {																				//checking whether an input has been captured
				flag = 1;																						//setting flag when the post conditions are met

			}
		}


		if (flag == 1) {
			n = sprintf((char*) buffer, "\n\r Post check Success !!! \n\r");
			USART_Write(USART2, buffer, n);
			return flag;																						//returning the flag=1 when Post check is successful

		} else if (flag == 0) {
			n =sprintf((char*) buffer,"\n\r Post check Failed \n\n\r Please check the connections \n\n\r"		//Printing error when the post check fails
									" Do you want to Rerun the Post Check\n\n\r If Yes press Y or press N ");
			USART_Write(USART2, buffer, n);
			char rxByte = USART_Read(USART2);
			if (rxByte == 'Y') {

				*nowp = TIM2->CNT;																				//Resetting now when rerunning the post check

			} else if (rxByte == 'N') {
				return flag;																					//Breaking out of the loop when user does not want to rerun the post check
			}

		}
	}

}
