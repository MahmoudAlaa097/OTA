/***********************************************************************/
/* Author	:	Mahmoud Alaa                                           */
/* Date		:	6 FEB 2022                                             */
/* Version	:	V01											           */
/***********************************************************************/

#ifndef ESP_INTERFACE_H
#define	ESP_INTERFACE_H

/* Functions Prototypes */
void HESP_voidInit(void);
void HESP_voidConnectToWiFi(u8* Copy_u8Ssid, u8* Copy_u8Password);
void HESP_voidConnectToServerTcp(u8* Copy_u8IP);
u8* HESP_u8ExecuteRequest(u8* Copy_u8Length, u8* Copy_u8Link);
u8* HESP_u8ReceiveData(void);

#endif
