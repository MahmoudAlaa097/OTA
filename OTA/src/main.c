/*
 * main.c
 *
 *  Created on: Feb 24, 2022
 *      Author: Mahmoud Alaa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"

#include "ESP_interface.h"

void Parser_voidParseRecord(u8* Copy_u8BufData);

u8  u8BLFlag    = 0		;
u8  u8Counter   = 0	  	;
u8* u8RecBuffer	= NULL	;
u8* u8Record	= NULL	;

typedef void (*Function_t)(void);
Function_t addr_to_call = NULL;

void voidClearBuffer(void)
{
	for(u8 i=0;i<100;i++)
	{
		u8RecBuffer[i] = 0;
	}
}

void voidJmpToApp(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}

void main(void)
{
	/* Initialize System Clock => HSI */
	MRCC_voidInitSysClock();
	/* Enable Port A */
	MRCC_voidEnableClock(MRCC_APB2,MRCC_APB2_GPIOA);
	/* Enable USART1 */
	MRCC_voidEnableClock(MRCC_APB2,MRCC_APB2_USART1);
	/* Enable FPEC   */
	MRCC_voidEnableClock(MRCC_AHB,MRCC_AHB_FPEC);

	/* Pin Directions */
	/* TX: A9 => Output Alternative Function Push Pull @ 10 MHz */
	MGPIO_voidSetPinDirection(MGPIOA,PIN9,OUTPUT_SPEED_10MHZ_AFPP);
	/* RX: A10 => Input Floating */
	MGPIO_voidSetPinDirection(MGPIOA,PIN10,INPUT_FLOATING);

	/* Initialize USART1 => Baud Rate = 115200 */
	MUSART1_voidInit();

	/* Initialize ESP32 */
	HESP_voidInit();

	/* Connect to WiFi */
	HESP_voidConnectToWiFi((u8*)"7oDa",(u8*)"30111997");

	while(1)
	{
		/* Clear Buffer */
		//voidClearBuffer();

		/* Connect to Server */
		HESP_voidConnectToServerTcp((u8*)"162.253.155.226");

		/* Get Received Data */
		u8RecBuffer = HESP_u8ExecuteRequest((u8*)"36",(u8*)"GET http://ota.ueuo.com/buffer.txt");

		/* Get Record */
		for(u8 Local_u8Index = 0;Local_u8Index<100;Local_u8Index++)
		{
			if( (u8RecBuffer[Local_u8Index] == '+') && (u8RecBuffer[Local_u8Index+1] == 'I') && (u8RecBuffer[Local_u8Index+2] == 'P') && (u8RecBuffer[Local_u8Index+3] == 'D'))
			{
				u8Record = &(u8RecBuffer[Local_u8Index+7]);
			}
		}

		/* Check if "done" is sent or not */
		if( (u8Record[0] == 'd') && (u8Record[1] == 'o') && (u8Record[2] == 'n') && (u8Record[3] == 'e') )
		{
			/* Send "ok" */
			u8RecBuffer = HESP_u8ExecuteRequest((u8*)"49",(u8*)"POST http://ota.ueuo.com/script.php?response=ok");

			/* Jump To APP */
			voidJmpToApp();
		}
		else
		{
			/* Check for first record */
			if (u8BLFlag == 0)
			{
				/* Erase APP Area */
				MFPEC_voidEraseAppArea();
				/* Update Flag */
				u8BLFlag = 1;
			}

			/* Parse Record */
			Parser_voidParseRecord(u8Record);

			/* Send "ok" */
			u8RecBuffer = HESP_u8ExecuteRequest((u8*)"49",(u8*)"POST http://ota.ueuo.com/script.php?response=ok");
		}
	}
}
