/*******************************************************************************
* File Name: PSoCEve_Hal.c  
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

#include <project.h>
#include "PSoCEve_Hal.h"

// FT800 Memory Commands
#define MEMORY_WRITE    0x80			// FT800 Host Memory Write 
#define MEMORY_READ		0x00			// FT800 Host Memory Read  

#define mSPI_EVE_WAIT_TXDONE()      while(0u == (SPI_EVE_GetMasterInterruptSource() & SPI_EVE_INTR_MASTER_SPI_DONE)) {} \
                                    SPI_EVE_ClearMasterInterruptSource(SPI_EVE_INTR_MASTER_SPI_DONE);

unsigned char spiTransferInProgress = 0;


void SPI_Transfer_Start(unsigned long address)
{
    unsigned char tobesent[] =  { (address >> 16), (address >> 8), address };
        
    SPI_EVE_SS_Write(0);
    CyDelay(5);

    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(tobesent, 3);
    
    mSPI_EVE_WAIT_TXDONE();    
}

void SPI_Transfer_Write_Long(unsigned long data)
{
    unsigned char tranferprogressflag = 0;
    unsigned char tobesent[4] =  { data, (data >> 8), (data >> 16), (data >> 24) };
        

    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(tobesent, 4);
    
    mSPI_EVE_WAIT_TXDONE();    
    
}

void SPI_Transfer_End()
{
    CyDelay(5);
    SPI_EVE_SS_Write(1);
}


void SPI_TransferL_Write_Byte(unsigned char data)
{
    unsigned char tranferprogressflag = 0;
    unsigned char tobesent[4] = { data };
    
    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartWriteTxData(data);  //   SpiUartPutArray(tobesent, 4);
    
    mSPI_EVE_WAIT_TXDONE();
}

void SPI_TransferL_Write_ByteArray(const unsigned char *data, unsigned long size)
{
    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(data, size);
        
    mSPI_EVE_WAIT_TXDONE();     
}

void SPI_TransferS_Write_Long(unsigned long address, unsigned long data)
{
    unsigned char tranferprogressflag = 0;
    unsigned char tobesent[7] =  { (address >> 16), (address >> 8), address,  data, (data >> 8), (data >> 16), (data >> 24) };
        
    SPI_EVE_SS_Write(0);
    CyDelay(5);

    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(tobesent, 7);
    
    mSPI_EVE_WAIT_TXDONE();    

    CyDelay(5);
    SPI_EVE_SS_Write(1);
}

unsigned long SPI_TransferS_Read_Long(unsigned long address)
{
    unsigned char tranferprogressflag = 0;
    uint32 data = 0x00000000;
    unsigned char tobesent[7] = 
         { (address >> 16), (address >> 8), address,  0x00 };;
        
    SPI_EVE_SS_Write(0);
    CyDelay(5);

    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(tobesent, 7);
    mSPI_EVE_WAIT_TXDONE();  
    
    SPI_EVE_SpiUartClearRxBuffer();
    SPI_EVE_SpiUartWriteTxData(0x00);
    SPI_EVE_SpiUartWriteTxData(0x00); 
    SPI_EVE_SpiUartWriteTxData(0x00);
    SPI_EVE_SpiUartWriteTxData(0x00);
    mSPI_EVE_WAIT_TXDONE();  
    CyDelay(5);
    SPI_EVE_SS_Write(1);

    
    data = SPI_EVE_SpiUartReadRxData() | (SPI_EVE_SpiUartReadRxData() << 8)| (SPI_EVE_SpiUartReadRxData() << 16)| (SPI_EVE_SpiUartReadRxData() << 24);

    return data;
}


void FTCommandWrite(unsigned char command)
{
    unsigned char tranferprogressflag = 0;
    unsigned char tobesent[3] = {command, 0x00, 0x00};
    
    SPI_EVE_SS_Write(0);
    CyDelay(5);

    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(tobesent, 3);
    
    mSPI_EVE_WAIT_TXDONE();
    CyDelay(5);
    SPI_EVE_SS_Write(1);
}

void EVE_Memory_Write_Word(unsigned long address, unsigned int data)
{
    unsigned char tranferprogressflag = 0;
    unsigned char tobesent[5] = { (address >> 16) | MEMORY_WRITE, (address >> 8), address, data, (data >> 8) };
    
    SPI_EVE_SS_Write(0);
    CyDelay(5);

    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(tobesent, 5);
    
    mSPI_EVE_WAIT_TXDONE();    

    CyDelay(5);
    SPI_EVE_SS_Write(1);
}

unsigned char EVE_Memory_Read_Byte(unsigned long address)
{
    unsigned char tranferprogressflag = 0;
    unsigned char data = 0x00;
    unsigned char tobesent[4] = { (address >> 16) | MEMORY_READ, (address >> 8), address,  0x00 };
    uint32 sizer;
    unsigned char data1, data2, data3, data4, data5;
    

    SPI_EVE_SS_Write(0);
    CyDelay(5);

    SPI_EVE_SpiUartClearTxBuffer();
    
    SPI_EVE_SpiUartPutArray(tobesent, 4);
    mSPI_EVE_WAIT_TXDONE();
    
    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartClearRxBuffer();
    SPI_EVE_SpiUartWriteTxData(0x00);
    mSPI_EVE_WAIT_TXDONE();
        
    data = SPI_EVE_SpiUartReadRxData();

    CyDelay(5);
    SPI_EVE_SS_Write(1);
        
    return data;
}

unsigned int EVE_Memory_Read_Word(unsigned long address)
{
    unsigned char tranferprogressflag = 0;
    uint16 data = 0x0000;
    unsigned char tobesent[4] = { (address >> 16) | MEMORY_READ, (address >> 8), address,  0x00 };
    
    SPI_EVE_SS_Write(0);
    CyDelay(5);

    SPI_EVE_SpiUartClearTxBuffer();
    SPI_EVE_SpiUartPutArray(tobesent, 4);
    mSPI_EVE_WAIT_TXDONE();  
    
    SPI_EVE_SpiUartClearRxBuffer();
    SPI_EVE_SpiUartWriteTxData(0x00);
    SPI_EVE_SpiUartWriteTxData(0x00);
    mSPI_EVE_WAIT_TXDONE();  
    CyDelay(5);
    SPI_EVE_SS_Write(1);

    data = SPI_EVE_SpiUartReadRxData() | (SPI_EVE_SpiUartReadRxData() << 8);
    
    return data;
}




/* [] END OF FILE */
