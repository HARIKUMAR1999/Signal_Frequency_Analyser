#include <uart.h>

uint8_t buffer[100];
int limit_init(void) {
	int n, x;
	n =
			sprintf((char*) buffer,
					"\n\r\n The default lower limit : 950 \r\n The default upper limit : 1050\n\n"
							"\r If you wish to continue press Y if you wish to change the limits press N\r\n\n"
							" The lower limit can be from 50 microseconds to 9950 microseconds\r\n");
	USART_Write(USART2, buffer, n);
	char rxByte = USART_Read(USART2);
	if (rxByte == 'N') {																	//If the user does not want to change the default limits
		return 950;																			//Return the default lower limit which is 950
	} else if (rxByte == 'Y') {																//If the user wants to change the limits used
		n = sprintf((char*) buffer, "\n Enter the new Lower Limit \r\n\n\n\n");
		USART_Write(USART2, buffer, n);
		int i = 0;

		//Getting the input from user and setting the value

		while (1) {
			int rxstring = USART_Read( USART2);
			if (rxstring == 13) {
				break;
			} else {
				n = sprintf((char*) buffer, "%d", rxstring - 48);
				USART_Write(USART2, buffer, n);

				if (i == 0) {
					x = (rxstring - 48);
				} else {
					x = (x * 10) + (rxstring - 48);
				}

			}
			i++;
		}
		if (x >= 50 && x <= 9950) {															//checking whether the inputs taken are valid and returning them
			return x;
		} else {
			n = sprintf((char*) buffer,
					"\n\r Entered Limits are not valid \r\n\n\n\n");						//If the input limit is not valid printing the error message
			USART_Write(USART2, buffer, n);
			return 950;
		}
	}

}
