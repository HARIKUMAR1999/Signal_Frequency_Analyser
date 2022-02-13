#include "stm32l476xx.h"
#include <uart.h>

void get_timer_data(int llp) {
	int i = 0, j, n, data[2000], temp, value, count = 0;
	uint32_t buffer[100], current_state, previous_state = 0;
	n = sprintf((char*) buffer,
			"\n The lower limit : %d The upper limit: %d \r\n\n\n\n", llp,
			llp + 100);
	USART_Write(USART2, buffer, n);

	while (i < 1001)														//This is the main loop where for 1000 time interval values within the specified limit is considered
	{

		if (TIM2->SR & 0x2)													//Checking whether any input is sensed by timer
				{
			current_state = TIM2->CCR1;										//Storing the timer value when an input is sensed inside Current_State
			int x = current_state - previous_state;							//Calculating the time interval by finding difference between current state and previous state
			previous_state = current_state;									//once the time interval is calculated setting the new previous state as current state prepping for the next input capture
			if (x >= llp && x <= (llp + 100)) {								//checking whether the time interval lies between the limits set by the user

				data[i] = x;												//storing the time interval in an array

				i++;
			}

		}
	}

	i = 0;

	//Sorting the array using selection sort

	for (i = 0; i < 1001; i++) {
		for (j = i + 1; j < 1001; j++) {
			if (data[i] > data[j]) {
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}

	n = sprintf((char*) buffer, "\r Time Interval         Count \r\n", value,
			count);
	USART_Write(USART2, buffer, n);
	value = data[0];
	i = 0;

	// counting and printing the time intervals in ascending order

	while (i < 1000) {

		if (value != data[i]) {
			n = sprintf((char*) buffer, "\r %d     		%d\r\n", value, count);
			USART_Write(USART2, buffer, n);
			value = data[i];

			count = 0;

		} else {
			count++;
			i++;
		}

	}
	n = sprintf((char*) buffer, "\r %d     		%d\r\n", value, count);
	USART_Write(USART2, buffer, n);
}
