/***********************************************************************/
/* Author	:	Mahmoud Alaa                                           */
/* Date		:	13 FEB 2022                                            */
/* Version	:	V01													   */
/***********************************************************************/

#ifndef FPEC_INTERFACE_H
#define FPEC_INTERFACE_H

/* Functions Prototypes */
void MFPEC_voidEraseAppArea(void);
void MFPEC_voidFlashPageErase(u8 Copy_u8PageNumber);
void MFPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);

#endif
