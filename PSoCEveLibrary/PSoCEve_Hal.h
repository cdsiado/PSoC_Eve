/*******************************************************************************
* File Name: PSoCEve_Hal.h  
* Version 0.1 Alpha
*
* Description:
*  PSoCEveLibrary project.
*  Library to easy the use of the FT EVE graphic chips from FTDI.
*  Actually in development and in a very early stage there is support only
*  for the FT800 chip with Cypress PSOC4 family microcontrollers.
*  It is planned to had support for FT801 and newer TF81x chips, also for
*  other PSOC families (PSOC3 and PSCO5).
*
* Note:
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#if !defined(PSOC_EVE_HAL_H)
#define PSOC_EVE_HAL_H
    
#include <cytypes.h>    
    
    
void SPI_Transfer_Start(unsigned long address);
void SPI_Transfer_Write_Long(unsigned long data);
void SPI_Transfer_End();    
void EVE_Memory_Write_Byte(unsigned long address, uint8 data);

void SPI_TransferL_Write_Byte(unsigned char data);
void SPI_TransferL_Write_ByteArray(const unsigned char *data, unsigned long size);   
void SPI_Write_ByteArray_4(const unsigned char *data, unsigned long size);
void SPI_TransferS_Write_Long(unsigned long address, unsigned long data);    
unsigned long SPI_TransferS_Read_Long(unsigned long address);    
void FTCommandWrite(unsigned char command);    
void EVE_Memory_Write_Word(unsigned long address, unsigned int data);
unsigned char EVE_Memory_Read_Byte(unsigned long address);
unsigned int EVE_Memory_Read_Word(unsigned long address); 

uint32 FTMemoryReadUint32(uint32 address);

    
#endif /* End PSOC_EVE_HAL_H */    

/* [] END OF FILE */
