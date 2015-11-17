/*******************************************************************************
* File Name: PSoCEve.c 
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
#include "PSoCEve.h"
#include "PSoCEve_Hal.h"

//enum LISTTYPE listInProgress = NONE;
uint32 ramPtr;
uint16 ramCMDOffset;

uint8 listInProgress = NONE;

/*******************************************************************************
*   Macros.
*******************************************************************************/

/* Macro name : CheckCMDOffset
   Description: Control roll-over to command list ram in FT chip.
*/
#define CheckCMDOffset() if (ramCMDOffset > 4095) { ramCMDOffset = (ramCMDOffset - 4096); }

/*******************************************************************************
*   Function prototypes.
*******************************************************************************/

uint8 FTIsCoproReady(uint16 *newoffset);

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
* Function Name: FT_Init
********************************************************************************
*
* Summary:
*  Initializes the FT chip with values from PSoCEve_Config.h file.
*  After initialization, display is off, touch panel is disabled and audio
*  is disabled.
*  To enable display, touch panel and audio call proper functions.
*  As stated in FT datasheet, until the FT chip is initializad, maximun SPI bus
*  speed is 12Mhz. After initializacion, SPI bus speed can be incremented up to
*  30Mhz. This functions doesn´t change the SPI bus communication speed. 
*
* Parameters:
*  None
*
* Return:
*  0 if initialization fails. 1 if initialization is OK.
*
*******************************************************************************/

uint8 FT_Init()
{
    uint8 t = 0;
    
    // Force a hardware reset of EVE chip using PD_N pin.
    PD_N_Write(0); CyDelay(10); PD_N_Write(1); CyDelay(20);
    
    // Initialize EVE chip. Max SPI speed before the chip is initialized is 11Mhz.
    FTCommandWrite(FT800_ACTIVE);            // Start FT800
    CyDelay(5);	
    FTCommandWrite(FT800_CLKEXT);			// Set FT800 for external clock
    CyDelay(5);	
    FTCommandWrite(FT800_CLK48M);			// Set FT800 for 48MHz PLL
    CyDelay(5);	
    FTCommandWrite(FT800_CORERST);			// Set FT800 for 48MHz PLL
    CyDelay(5);
    
    // Read ID register. If we don¨t get 0x7C something is bad.
    //if (EVE_Memory_Read_Byte(REG_ID) != 0x7C) return 0;
    if (FT_Register_Read(REG_ID) != 0x7C) return 0;
    
    // At startup, PCLK (pixel clock) and PWM_DUTY (used for backlight) are programmed to 0.
    //      Display is off until user turns it on.
    FT_Register_Write(REG_PCLK, 0);
    FT_Register_Write(REG_PWM_DUTY, 0);	
    
    // Continue initializing registers with values from configuration header file.
    FT_Register_Write(REG_HSIZE, LCDWIDTH);	
    FT_Register_Write(REG_VSIZE, LCDHEIGHT);
    FT_Register_Write(REG_HCYCLE, LCDHCYCLE);
    FT_Register_Write(REG_HOFFSET, LCDHOFFSET);
    FT_Register_Write(REG_HSYNC0, LCDHSYNC0);
    FT_Register_Write(REG_HSYNC1, LCDHSYNC1);
    FT_Register_Write(REG_VCYCLE, LCDVCYCLE);
    FT_Register_Write(REG_VOFFSET, LCDVOFFSET);
    FT_Register_Write(REG_VSYNC0, LCDVSYNC0);
    FT_Register_Write(REG_VSYNC1, LCDVSYNC1);
    FT_Register_Write(REG_SWIZZLE, LCDSWIZZLE);
    FT_Register_Write(REG_PCLK_POL, LCDPCLKPOL);
    
    FT_Register_Write(REG_VOL_PB, 0);               // turn recorded audio volume down
    FT_Register_Write(REG_VOL_SOUND, 0);            // turn synthesizer volume down
    FT_Register_Write(REG_SOUND, 0x0060);           // set synthesizer to mute
    
    /* Configure GPIO1 to control audio amplifier chip. */
    #ifdef USE_GPIO1_AUDIO
        t = FT_Register_Read(REG_GPIO_DIR);   
        t |= 0x02;                                  // GIPO1, as output.
        FT_Register_Write(REG_GPIO_DIR, t);
        
        t = FT_Register_Read(REG_GPIO);             
        t &= 0xFD;                                  // = 0, shutdown amplifier.
        FT_Register_Write(REG_GPIO, t);
    #endif
              
    return 1;
}

/*******************************************************************************
* Function Name: FT_Display_ON
********************************************************************************
*
* Summary:
*  Enable display. Put DISP signal high and start the FT clock. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void FT_Display_ON()
{
    unsigned char gpio = FT_Register_Read(REG_GPIO);        // Read actual value of GPIO register.

    FT_Register_Write(REG_GPIO, (gpio | 0x80));			    // Set bit 7 of GPIO register (DISP signal).
    FT_Register_Write(REG_PCLK, LCDPCLK);			        // Start clock.
}

/*******************************************************************************
* Function Name: FT_Display_OFF
********************************************************************************
*
* Summary:
*  Disable display. Put DISP signal low and stop the FT clock. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void FT_Display_OFF()
{
    unsigned char gpio = FT_Register_Read(REG_GPIO);        // Read actual value of GPIO register.
    
    FT_Register_Write(REG_GPIO, (gpio & 0x70));			    // Clear bit 7 of GPIO register (DISP signal).
    FT_Register_Write(REG_PCLK, LCDPCLK);			        // Stop clock.
}

/*******************************************************************************
* Function Name: FT_Touch_Enable
********************************************************************************
*
* Summary:
*  Enable the touch panel.
*  Value of REG_TOUCH_RZTHRESH depends on touch panel requirement and is derived 
*  by experimentation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void FT_Touch_Enable()
{
    FT_Register_Write(REG_TOUCH_MODE, TOUCHMODE_FRAME);
    FT_Register_Write(REG_TOUCH_RZTHRESH, 1200);    
}

/*******************************************************************************
* Function Name: FT_Touch_Disable
********************************************************************************
*
* Summary:
*  Disable the touch panel. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void FT_Touch_Disable()
{
    FT_Register_Write(REG_TOUCH_MODE, 0);
    FT_Register_Write(REG_TOUCH_RZTHRESH, 0);    
}

/*******************************************************************************
* Function Name: FT_Touch_Calibrate
********************************************************************************
*
* Summary:
*  Start touch calibration procedure.
*  FT chip doesn´t permanently store calibration values internally, so they are
*  lost every time the FT chip is power cycle or reseted.
*  Look at FT_Touch_ReadCalibrationValues and FT_Touch_WriteCalibrationValues.
*
* Parameters:
*  None
*
* Return:
*  0, if can not start calibration because there is a list (display or 
*     coprocessor in progress).
*  1, for successful calibration. 
*
*******************************************************************************/

uint8 FT_Touch_Calibrate()
{
    if (listInProgress != NONE) return 0;
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDCalibrate());
    CMDEndList(END_DL_SWAP);  
    
    while (!FTIsCoproccesorReady()) {};
    
    return 1;
}

/*******************************************************************************
* Function Name: FT_Touch_ReadCalibrationValues
********************************************************************************
*
* Summary:
*  This function reads touch calibration values from registers in FT chip.
*  Then you can store those values in flash rom so they can be used in
*  future.
*  Until now, this library doesn´t store values in flash, you have to implement
*  it by yourself.
*
* Parameters:
*  values: pointer to variable where to store calibration values.
*          Look at definition of "TouchCalibrationValues" enum in PSocEve.h
*
* Return:
*  none
*
*******************************************************************************/

void FT_Touch_ReadCalibrationValues(TouchCalibrationValues* values)
{
    uint8 loop;
    uint32 ptr = REG_TOUCH_TRANSFORM_A;
        
    for (loop = 0; loop < 6; loop++)
    {
        values->TouchTransform_X[loop] = FTMemoryReadUint32(ptr);
        ptr += 4;
    }
}

/*******************************************************************************
* Function Name: FT_Touch_WriteCalibrationValues
********************************************************************************
*
* Summary:
*  This function writes touch calibration values to registers in FT chip.
*  Can be used to write previouly stored values.
*  Until now, this library doesn´t store value in flash, you have to implement
*  it by yourself.
*
* Parameters:
*  values: pointer to variable where to calibration values are stored.
*          Look at definition of "TouchCalibrationValues" enum in PSocEve.h
*
* Return:
*  none
*
*******************************************************************************/

void FT_Touch_WriteCalibrationValues(TouchCalibrationValues* values)
{
    uint8 loop;
    uint32 ptr = REG_TOUCH_TRANSFORM_A;
    
    for (loop = 0; loop < 6; loop++)
    {
        FT_Register_Write(ptr, values->TouchTransform_X[loop]);
        ptr += 4;
    }
}

    /* Conditional compilation. For more info look at PSoCEve_config.h */
#ifdef USE_GPIO1_AUDIO
    
    
    /*******************************************************************************
    * Function Name: FT_Audio_Mute
    ********************************************************************************
    *
    * Summary:
    *  Put GPIO1 pin of FT chip to low state. This puts the audio amplifier in FTDI
    *  development kits in shutdown condition.
    *
    * Parameters:
    *  none
    *
    * Return:
    *  none
    *
    *******************************************************************************/    
    void FT_Audio_Mute()
    {
        uint8 t = 0;
        
        t = FT_Register_Read(REG_GPIO);             
        t &= 0xFD;                                  
        FT_Register_Write(REG_GPIO, t); 
    }
    
    /*******************************************************************************
    * Function Name: FT_Audio_Unmute
    ********************************************************************************
    *
    * Summary:
    *  Put GPIO1 pin of FT chip to high state. This puts the audio amplifier in FTDI
    *  development kits in poer on  condition.
    *
    * Parameters:
    *  none
    *
    * Return:
    *  none
    *
    *******************************************************************************/      
    void FT_Audio_Unmute()
    {
        uint8 t = 0;
        
        t = FT_Register_Read(REG_GPIO);             
        t |= 0x02;                                  
        FT_Register_Write(REG_GPIO, t);    
    }
    
#endif

/*******************************************************************************
* Function Name: FT_Sound_Volume
********************************************************************************
*
* Summary:
*  Set volume level for sounds.
*
* Parameters:
*  volume:  volume level. Maximun 255.
*
* Return:
*  none
*
*******************************************************************************/
void FT_Sound_Volume(uint8 volume)
{
    FT_Register_Write(REG_VOL_SOUND, volume);
}

/*******************************************************************************
* Function Name: FT_Sound_Play
********************************************************************************
*
* Summary:
*  Play sound.
*
* Parameters:
*  sound:   sound to be played.
*  pitch:   pitch. 
*  Look at FT datsheet for more info.
*
* Return:
*  none
*
*******************************************************************************/
void FT_Sound_Play(uint8 sound, uint8 pitch)
{
    FT_Register_Write(REG_SOUND, sound | (pitch << 16));
    FT_Register_Write(REG_PLAY, 1);
}

/*******************************************************************************
* Function Name: FT_Sound_Stop
********************************************************************************
*
* Summary:
*  Stops sound.
*
* Parameters:
*  none
*
* Return:
*  none
*
*******************************************************************************/
void FT_Sound_Stop()
{
    FT_Register_Write(REG_SOUND, 0x60);
    FT_Register_Write(REG_PLAY, 1);    
}
    
/*******************************************************************************
* Function Name: DLStartList
********************************************************************************
*
* Summary:
*  Function used to start a new "Display" list.
*
* Parameters:
*  none
*
* Return:
*  none
*
*******************************************************************************/
void DLStartList()
{
    ramPtr = RAM_DL;                                // Display list ram in FT chip.
    FT_Transfer_Start(ramPtr  | MEMORY_WRITE);
}

/*******************************************************************************
* Function Name: DLListNewItem
********************************************************************************
*
* Summary:
*  Put new item (new command) inside current display list.
*  During display list, pointer to FT ram is not incremented in software.
*  It is incremnted inside FT chip.
*
* Parameters:
*  item:    command to be inserted in the list.
*
* Return:
*  none
*
*******************************************************************************/
void DLListNewItem(unsigned long item)
{
    FT_Send_UINT32(item);                  // All display list commands are 32 bits long.
}

/*******************************************************************************
* Function Name: DLEndList
********************************************************************************
*
* Summary:
*  Finish a display list.
*
* Parameters:
*  none
*
* Return:
*  none
*
*******************************************************************************/
void DLEndList()
{
    FT_Send_UINT32(DL_DISPLAY);            // Send "DL_DISPLAY" command to finish the list.
    FT_Transfer_End();                             // Finish SPI communications.
    FT_Register_Write(REG_DLSWAP, DLSWAP_FRAME);    // Make the list visible in display.
}

/*******************************************************************************
* Function Name: CMDStartList
********************************************************************************
*
* Summary:
*  Function used to start a new "Coproccesor" list.
*
* Parameters:
*  none
*
* Return:
*  none
*
*******************************************************************************/
void CMDStartList()
{
    /* Fist wait until the coproccesor is ready. It have finished proccesing 
       previous commands. */
    while (!FTIsCoproReady(&ramCMDOffset)) {}
    
    FT_Transfer_Start((RAM_CMD + ramCMDOffset) | MEMORY_WRITE);    // Start the display list
    FT_Send_UINT32(CMD_DLSTART);
    ramCMDOffset += 4; CheckCMDOffset();                            // Manage offset to FT RAM.
}

/*******************************************************************************
* Function Name: CMDEndList
********************************************************************************
*
* Summary:
*  Function used to start a new "Coproccesor" list.
*
* Parameters:
*  swap:    if = 1, then sends command CMD_SWAP.
*           if = 0, do not send command CMD_SWAP.
*      Sending CMD_SWAP is the usual way of finishing a coproccesor list, but 
*  sometimes we can not send CMD_SWAP command because the command sent 
*  previously to FT chip can work properly (ex: CMD_SPINNER).
*
* Return:
*  none
*
*******************************************************************************/
void CMDEndList(unsigned char swap)
{
    if (swap)
    {
        FT_Send_UINT32(DL_DISPLAY); 
        ramCMDOffset += 4; CheckCMDOffset();                            // Manage offset to FT RAM.
        FT_Send_UINT32(CMD_SWAP); 
        ramCMDOffset += 4; CheckCMDOffset();                            // Manage offset to FT RAM.
    }
    
    FT_Transfer_End();
    FT_Register_Write(REG_CMD_WRITE, ramCMDOffset);
}

/*******************************************************************************
* Function Name: CMDListAddItem
********************************************************************************
*
* Summary:
*  Put new item inside current coproccesor list.
*
* Parameters:
*  tobesent:    pointer to the item to be sent to FT chip.
*  length:      length (in bytes) to be sent.
*  string:      for commands with strings (like CMD_BUTTON or CMD_TEXT) this is
*               a pointer to the string. For command that don´t use strings this
*               have to take value 0.
*
* Return:
*  none
*
*******************************************************************************/
void CMDListAddItem(uint8 *tobesent, uint8 length, unsigned char *string)
{
    unsigned char *cptr = string;
    
    FT_Send_ByteArray(tobesent, length);                // Send all command parameters. 
    ramCMDOffset += length; CheckCMDOffset();           // Manage offset to FT RAM. 
    
    // Send the string if pointer to string is not zero.
    if (string != 0)                            
    {
        // Last byte of the string to be sent have to be equal to 0.
        // So, send bytes until we find byte = 0. 
        while (*cptr != 0)
        {
            FT_Send_Byte(*cptr);
            ramCMDOffset++;  CheckCMDOffset();          // Manage offset to FT RAM.
            cptr++;
        } 
    
        // Send last byte (byte = 0) to FT chip.
        FT_Send_Byte(0);
        ramCMDOffset++; CheckCMDOffset();               // Manage offset to FT RAM.
    
        // Every time we send a string to FT chip, its lenght have be multiple of 4.
        // If the length of the string is shorter than that, the we send 0 bytes until it is
        // a multiple of 4.
        while ((ramCMDOffset % 4) != 0)
        {
            FT_Send_Byte(0);
            ramCMDOffset++; CheckCMDOffset();           // Manage offset to FT RAM.
        }
    }
}

/*******************************************************************************
* Function Name: CMDListAddDLItem
********************************************************************************
*
* Summary:
*  Put a "Display" list item in a coproccesor command list.
*
* Parameters:
*  item:    display list item.    
*
* Return:
*  none
*
*******************************************************************************/
void CMDListAddDLItem(uint32 item)
{
    FT_Send_UINT32(item); 
    ramCMDOffset += 4; CheckCMDOffset();                // Manage offset to FT RAM.
}

/*******************************************************************************
* Function Name: FTIsCoproccesorReady
********************************************************************************
*
* Summary:
*  Wrapper to FTIsCoproReady function.
*  Used with commands like CMD_CALIBRATE to know when command work have finished.
*
* Parameters:
*  none
*
* Return:
*  1, if coprocessor have finished proccesing commands list.
*  0, if coprocessor is busy.
*
*******************************************************************************/

uint8 FTIsCoproccesorReady()
{
    return FTIsCoproReady(&ramCMDOffset);
}

/*******************************************************************************
* Function Name: FTIsCoproReady
********************************************************************************
*
* Summary:
*  Check if coproccesor is ready to proccess a new commands list.
*
* Parameters:
*  newoffset:   pointer to variable to store offset to command list.
*
* Return:
*  1, if coproccesor is ready.
*  0, if coproccesor is busy proccessing a commands list.
*
*******************************************************************************/
uint8 FTIsCoproReady(uint16 *newoffset)
{
    unsigned int cmdbufferrd, cmdbufferwr;

    cmdbufferrd = FT_Register_Read(REG_CMD_READ);		    // Read the graphics processor read pointer.
	cmdbufferwr = FT_Register_Read(REG_CMD_WRITE); 	        // Read the graphics processor write pointer.
    
    if (cmdbufferrd != cmdbufferwr) return 0;               // If both are equal, processor have finished
    else                                                    //    processing previous list.
    {
        *newoffset = cmdbufferwr;
        return 1;                  
    }
}

/*******************************************************************************
* Function Name: FT_Write_ByteArray_4
********************************************************************************
*
* Summary:
*  Send an array of bytes to FT chip.
*  Used when bytes to send have to be multiple of four but possibly they are not.
*  This functions, if the array to be send is not multiple of 4; sends 0 bytes
*  until it is multiple.
*
* Parameters:
*  data:    pointer to array of bytes to be sent.
*  length:  length of the array.
*
* Return:
*  none
*
*******************************************************************************/
void FT_Write_ByteArray_4(const uint8 *data, uint32 length)
{
    FT_Send_ByteArray(data, length);
    ramCMDOffset += length; CheckCMDOffset();           // Manage offset to FT RAM.
    
    while ((ramCMDOffset % 4) != 0)
    {
        FT_Send_Byte(0);
        ramCMDOffset++; CheckCMDOffset();               // Manage offset to FT RAM.
    }
}

