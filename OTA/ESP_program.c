/***********************************************************************/
/* Author	:	Mahmoud Alaa                                           */
/* Date		:	6 FEB 2022                                             */
/* Version	:	V01											           */
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

u8 u8Response[100];

void HESP_voidInit(void)
{
	u8 Local_u8Result = 0;
	
	/* Clear Response Buffer */
	voidEspClearBuffer();

	/* Disable ECHO */
	while(Local_u8Result == 0)
	{
		/* Send Disable ECHO Command */
		MUSART1_voidTransmit( (u8*) "ATE0\r\n");
		/* Validate Response */
		Local_u8Result = u8EspValidateCmd(ECHO_TIMEOUT);
	}
	
	Local_u8Result = 0;
	
	/* Set Station Mode */
	while(Local_u8Result == 0)
	{
		/* Send Station Mode Command */
		MUSART1_voidTransmit( (u8*) "AT+CWMODE=1\r\n");
		/* Validate Response */
		Local_u8Result = u8EspValidateCmd(MODE_TIMEOUT);
	}
}

void HESP_voidConnectToWiFi(u8* Copy_u8Ssid, u8* Copy_u8Password)
{
	u8 Local_u8Result = 0;
	
	/* Connect to WiFi */
	while(Local_u8Result == 0)
	{
		/* Send WiFi Network Data Command */
		MUSART1_voidTransmit( (u8*) "AT+CWJAP_CUR=\"");
		MUSART1_voidTransmit( (u8*) Copy_u8Ssid);
		MUSART1_voidTransmit( (u8*) "\",\"");
		MUSART1_voidTransmit( (u8*) Copy_u8Password);
		MUSART1_voidTransmit( (u8*) "\"\r\n");
		/* Validate Response */
		Local_u8Result = u8EspValidateCmd(WIFI_TIMEOUT);
	}
}

void HESP_voidConnectToServerTcp(u8* Copy_u8IP)
{
	u8 Local_u8Result = 0;
	
	/* Connect to Server */
	while(Local_u8Result == 0)
	{
		/* Send Server IP Command */
		MUSART1_voidTransmit( (u8*) "AT+CIPSTART=\"TCP\",\"");
		MUSART1_voidTransmit( (u8*) Copy_u8IP);
		MUSART1_voidTransmit( (u8*) "\",80\r\n");
		/* Validate Response */
		Local_u8Result = u8EspValidateCmd(SERVER_TIMEOUT);
	}
}

u8 HESP_u8ExecuteRequest(u8* Copy_u8Length, u8* Copy_u8Link)
{
	u8 Local_u8Result = 0;
	u8 Local_u8Temp = 0;
	
	while(Local_u8Result == 0)
	{
		/* Send Data Length */
		MUSART1_voidTransmit( (u8*) "AT+CIPSEND=");
		MUSART1_voidTransmit( (u8*) Copy_u8Length);
		MUSART1_voidTransmit( (u8*) "\r\n");
		/* Validate Response */
		Local_u8Result = u8EspValidateCmd(PREREQUEST_TIMEOUT);
	}
	
	Local_u8Result = 0;
	
	while(Local_u8Result == 0)
	{
		/* Send Data */
		MUSART1_voidTransmit( (u8*) "GET ");
		MUSART1_voidTransmit( (u8*) Copy_u8Link);
		MUSART1_voidTransmit( (u8*) "\r\n");
		Local_u8Result = u8EspValidateCmd(REQUEST_TIMEOUT);
	}

	for(u8 Local_u8Iindex = 0;Local_u8Iindex<100;Local_u8Iindex++)
	{
		if( (u8Response[Local_u8Iindex] == '+') && (u8Response[Local_u8Iindex+1] == 'I') && (u8Response[Local_u8Iindex+2] == 'P') && (u8Response[Local_u8Iindex+3] == 'D'))
		{
			Local_u8Temp = u8Response[Local_u8Iindex+7];
		}
	}

	return Local_u8Temp;
}

//u8* HESP_u8ReceiveData(void)
//{
//	u8 Local_u8Temp = 0;
//	volatile u8 Local_u8Response[8];
//	u8 Local_u8Index = 0;
//
//	while(Local_u8Temp != 255)
//	{
//		Local_u8Temp = MUSART1_u8Receive();
//		Local_u8Response[Local_u8Index] = Local_u8Temp;
//		Local_u8Index++;
//	}
//
//	return Local_u8Response;
//}

static u8 u8EspValidateCmd(u32 Copy_u32Timout)
{
	u8 Local_u8Index = 0;
	u8 Local_u8Temp = 0;
	u8 Local_u8Result = 0;
	u8 Local_u8Iterator = 0;

	/* Stop Receiving when ESP stops sending */
	while(Local_u8Temp != 255)
	{
		/* Receive a char from ESP */
		Local_u8Temp = MUSART1_u8Receive(Copy_u32Timout);
		/* Store it in buffer */
		u8Response[Local_u8Index] = Local_u8Temp;
		/* Increment Counter */
		Local_u8Index++;
	}

	/* Check if "OK" is sent */
	for(Local_u8Iterator=0;Local_u8Iterator<Local_u8Index-2;Local_u8Iterator++)
	{
		if(u8Response[Local_u8Iterator] == 'O' && u8Response[Local_u8Iterator+1] == 'K')
			{
				Local_u8Result = 1;
				break;
			}
	}

	return Local_u8Result;
}

static void voidEspClearBuffer(void)
{
	for(u8 Local_u8Iterator=0;Local_u8Iterator<100;Local_u8Iterator++)
	{
		u8Response[Local_u8Iterator] = 0;
	}
}
