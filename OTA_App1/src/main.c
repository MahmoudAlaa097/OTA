/*
 * main.c
 *
 *  Created on: Feb 25, 2022
 *      Author: Mahmoud Alaa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

void main(void)
{
	/* Initialize System Clock => HSE Crystal */
	MRCC_voidInitSysClock();
	/* Enable PortA Clock */
	MRCC_voidEnableClock(MRCC_APB2,MRCC_APB2_GPIOA);

	/* Pin Direction */
	/* Red LED : A0 => Output Push Pull @ 2 MHz */
	MGPIO_voidSetPinDirection(MGPIOA,PIN0,OUTPUT_SPEED_2MHZ_PP);
	/* Turn on LED */
	MGPIO_voidSetPinValue(MGPIOA,PIN0,HIGH);
	while(1);
}
