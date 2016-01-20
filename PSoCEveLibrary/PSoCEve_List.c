/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "PSoCEve.h"
//#include "PSoCEve_List.h"

//enum LISTTYPE listInProgress = NONE;
uint32 ramPtr;
uint16 ramCMDOffset;

LISTTYPE listInProgress = NONE;

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

void DLListNewItem(uint32 item);
void CMDListNewItem(uint8 *tobesent, uint8 length, unsigned char *string);

extern inline void DLBitmapSource(uint32 address);
extern inline void DLClearColorRGB(uint8 red, uint8 green, uint8 blue);    
extern inline void DLTag(uint8 tag);
extern inline void DLColorRGB(uint8 red, uint8 green, uint8 blue);
extern inline void DLBitmapHandle(uint8 handle);
extern inline void DLCell(uint8 cell);
extern inline void DLBitmapLayout(uint8 format, uint16 linestride, uint16 height);
extern inline void DLBitmapSize(uint8 filter, uint8 wrapx, uint8 wrapy, uint16 width, uint16 height);
extern inline void DLAlphaFunc(uint8 func, uint8 ref);
extern inline void DLStencilFunc(uint8 func, uint8 ref, uint8 mask);
extern inline void DLBlendFunc(uint8 src, uint8 dst);
extern inline void DLStencilOp(uint8 sfail, uint8 spass);
extern inline void DLPointSize(uint32 size);
extern inline void DLLineWidth(uint16 width);
extern inline void DLColorA(uint8 alpha);
extern inline void DLClearStencil(uint8 s);
extern inline void DLClearTag(uint8 t);
extern inline void DLStencilMask(uint8 mask);
extern inline void DLTagMask(uint8 mask);
extern inline void DLBitmapTransformA(uint32 a);
extern inline void DLBitmapTransformB(uint32 b);
extern inline void DLBitmapTransformC(uint32 c);
extern inline void DLBitmapTransformD(uint32 d);
extern inline void DLBitmapTransformE(uint32 e);
extern inline void DLBitmapTransformF(uint32 f);
extern inline void DLScissorXY(uint16 x, uint16 y);
extern inline void DLJump(uint16 address);
extern inline void DLBegin(uint8 primitive);
extern inline void DLCall(uint16 address);
extern inline void DLColorMask(uint8 r, uint8 g, uint8 b, uint8 a);
extern inline void DLEnd();
extern inline void DLSaveContext();
extern inline void DLRestoreContext();
extern inline void DLReturn();
extern inline void DLMacro(uint8 macro);
extern inline void DLClear(uint8 color, uint8 stencil, uint8 tag);
extern inline void DLVertex2F(int16 x, int16 y);
extern inline void DLVertex2II(uint16 x, uint16 y, uint8 handle, uint8 cell);

extern inline void CMDDLStart();
extern inline void CMDSwap();
extern inline void CMDInterrupt(uint32 milliseconds);
extern inline void CMDBgcolor(int8 red, int8 green, int8 blue);
extern inline void CMDFgcolor(int8 red, int8 green, int8 blue);
extern inline void CMDGradient(int16 x0, int16 y0, int8 red0, int8 green0, int8 blue0, int16 x1, int16 y1, int8 red1, int8 green1, int8 blue1);
extern inline void CMDText(int16 x, int16 y, int16 font, int16 options, char* text);
extern inline void CMDButton(int16 x, int16 y, int16 width, int16 height, int16 font, int16 options, char* text);
extern inline void CMDKeys(int16 x, int16 y, int16 width, int16 height, int16 font, int16 options, char* text);
extern inline void CMDProgressBar(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 range);
extern inline void CMDSlider(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 range);
extern inline void CMDScrollBar(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 size, int16 range);
extern inline void CMDToggle(int16 x, int16 y, int16 width, int16 font, int16 options, int16 state, char* text);
extern inline void CMDGauge(int16 x, int16 y, int16 radius, int16 options, int16 major, int16 minor, int16 value, int16 range);
extern inline void CMDClock(int16 x, int16 y, int16 radius, int16 options, int16 hours, int16 minutes, int16 seconds, int16 milliseconds);
extern inline void CMDCalibrate();
extern inline void CMDSpinner(int16 x, int16 y, int16 style, int16 scale);
extern inline void CMDStop();
extern inline void CMDMemSet(int32 ptr, int32 value, int32 size);
extern inline void CMDMemZero(int32 ptr, int32 size);
extern inline void CMDMemCopy(int32 dest, int32 src, int32 size);
extern inline void CMDAppend(int32 ptr, int32 size);
extern inline void CMDSnapshot(int32 ptr);
extern inline void CMDInflate(int32 ptr);
extern inline void CMDLoadIdentity();
extern inline void CMDTranslate(int32 tx, int32 ty);
extern inline void CMDScale(int32 x, int32 y);
extern inline void CMDRotate(int32 angle);
extern inline void CMDSetmatrix();
extern inline void CMDSetfont(int32 font, int32 ptr);
extern inline void CMDTrack(int16 x, int16 y, int16 width, int16 height, int16 tag);
extern inline void CMDDial(int16 x, int16 y, int16 radius, int16 options, int16 value);
extern inline void CMDNumber(int16 x, int16 y, int16 font, int16 options, int32 number);
extern inline void CMDScreenSaver();
extern inline void CMDSketch(int16 x, int16 y, int16 width, int16 height, int32 ptr, int16 format);
extern inline void CMDLogo();
extern inline void CMDColdstart();
extern inline void CMDGradcolor(int16 red, int16 green, int16 blue);


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

/*******************************************************************************
* Function Name: FT_ListStart
********************************************************************************
*
* Summary:
*  Starts a new list. 
*  Can be a DISPLAY list or a COPROCCESSOR list.
*
* Parameters:
*  listtype:    list to start, DISPLAY or COPROCCESOR
*
* Return:
*  Type of error:   OK, if it is ok.
*                   LIST_IN_PROGRESS, if a list has been started previouslly and
*                                     not finished.
*                   UNKNOWN_LIST_TYPE, if value of 'listtype' is unknown.
*
*******************************************************************************/
FTERROR FT_ListStart(LISTTYPE listtype)
{
    if (listInProgress != NONE) return LIST_IN_PROGRESS;
    
    if (listtype == DISPLAY)
    {
        ramPtr = RAM_DL;                                // Display list ram in FT chip.
        FT_Transfer_Start(ramPtr  | MEMORY_WRITE);
        
        listInProgress = DISPLAY;
        return OK;
    } 
    else if (listtype == COPROCESSOR)
    {
        /* Wait until the coproccesor is ready. It have finished proccesing 
           previous commands. */
        while (!FTIsCoproReady(&ramCMDOffset)) {}
    
        FT_Transfer_Start((RAM_CMD + ramCMDOffset) | MEMORY_WRITE);    // Start the display list
        FT_Send_UINT32(CMD_DLSTART);
        ramCMDOffset += 4; CheckCMDOffset();                            // Manage offset to FT RAM.
        
        listInProgress = COPROCESSOR;
        return OK;        
    }
    
    return UNKNOWN_LIST_TYPE;
}

/*******************************************************************************
* Function Name: FT_ListEnd
********************************************************************************
*
* Summary:
*  Finish a list that is in progress.
*
* Parameters:
*  swap:    if = 1, then sends command CMD_SWAP.
*           if = 0, do not send command CMD_SWAP.
*      Sending CMD_SWAP is the usual way of finishing a coproccesor list, but 
*  sometimes we can not send CMD_SWAP command because the command sent 
*  previously to FT chip can not work properly (ex: CMD_SPINNER).
*  This has no effect if the list in progress is a DISPLAY list.
*
* Return:
*  Type of error:   OK, there is no error.
*                   LIST_NOT_IN_PROGRESS, trying to finish a list that has not
*                                         been started.
*******************************************************************************/
FTERROR FT_ListEnd(SWAPACTION swap)
{
    if (listInProgress == NONE) return LIST_NOT_IN_PROGRESS;
    
    if (listInProgress == DISPLAY)
    {
        FT_Send_UINT32(DL_DISPLAY);                     // Send "DL_DISPLAY" command to finish the list.
        FT_Transfer_End();                              // Finish SPI communications.
        FT_Register_Write(REG_DLSWAP, DLSWAP_FRAME);    // Make the list visible in display.        
    }
    else // Then have to be coproccessor list.
    {
        if (swap == END_DL_SWAP)
        {
            FT_Send_UINT32(DL_DISPLAY); 
            ramCMDOffset += 4; CheckCMDOffset();        // Manage offset to FT RAM.
            FT_Send_UINT32(CMD_SWAP); 
            ramCMDOffset += 4; CheckCMDOffset();        // Manage offset to FT RAM.
        }
        
        FT_Transfer_End();
        FT_Register_Write(REG_CMD_WRITE, ramCMDOffset);        
    }
    
    listInProgress = NONE;
    
    return OK;
}

/*******************************************************************************
* Function Name: DLListNewItem
********************************************************************************
*
* Summary:
*  Put new item (new command) inside current display list.
*  If current list is a DISPLAY list,  pointer to FT ram is not incremented in 
*  software. It is incremnted inside FT chip.
*  If current list is a COPROCCESOR list, it takes care of pointer offset.
*
* Parameters:
*  item:    command to be inserted in the list.
*
* Return:
*  none
*
*******************************************************************************/
void DLListNewItem(uint32 item)
{
    FT_Send_ByteArray((uint8*)&item, 4);
    
    /* If current list is a coproccessor list, take care o ram offset. */
    if (listInProgress == DISPLAY) return;
    
    ramCMDOffset += 4; CheckCMDOffset();                
}

/*******************************************************************************
* Function Name: CMDListNewItem
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
void CMDListNewItem(uint8 *tobesent, uint8 length, unsigned char *string)
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

inline void DLBitmapSource(uint32 address)
{
    DLListNewItem(_DLBitmapSource(address));
}

inline void DLClearColorRGB(uint8 red, uint8 green, uint8 blue)
{
    DLListNewItem(_DLClearColorRGB(red, green, blue));
}

inline void DLTag(uint8 tag)
{
    DLListNewItem(_DLTag(tag));
}

inline void DLColorRGB(uint8 red, uint8 green, uint8 blue)
{
    DLListNewItem(_DLColorRGB(red, green, blue));
}

inline void DLBitmapHandle(uint8 handle)
{
    DLListNewItem(_DLBitmapHandle(handle));
}

inline void DLCell(uint8 cell)
{
    DLListNewItem(_DLCell(cell));
}

inline void DLBitmapLayout(uint8 format, uint16 linestride, uint16 height)
{
    DLListNewItem(_DLBitmapLayout(format, linestride, height));
    
    #if defined EVE_FT810
        DLListNewItem(_DLBitmapLayout_H(linestride, height));
    #endif 
}

inline void DLBitmapSize(uint8 filter, uint8 wrapx, uint8 wrapy, uint16 width, uint16 height)
{
    DLListNewItem(_DLBitmapSize(filter, wrapx, wrapy, width, height));
    
    #if defined EVE_FT810
        DLListNewItem(_DLBitmapSize_H(width, height));
    #endif 
}

inline void DLAlphaFunc(uint8 func, uint8 ref)
{
    DLListNewItem(_DLAlphaFunc(func, ref));
}

inline void DLStencilFunc(uint8 func, uint8 ref, uint8 mask)
{
    DLListNewItem(_DLStencilFunc(func, ref, mask));
}

inline void DLBlendFunc(uint8 src, uint8 dst)
{
    DLListNewItem(_DLBlendFunc(src, dst));
}

inline void DLStencilOp(uint8 sfail, uint8 spass)
{
    DLListNewItem(_DLStencilOp(sfail, spass));
}

inline void DLPointSize(uint32 size)
{
    DLListNewItem(_DLPointSize(size));
}

inline void DLLineWidth(uint16 width)
{
    DLListNewItem(_DLLineWidth(width));
}

inline void DLColorA(uint8 alpha)
{
    DLListNewItem(_DLColorA(alpha));
}

inline void DLClearStencil(uint8 s)
{
    DLListNewItem(_DLClearStencil(s));
}

inline void DLClearTag(uint8 t)
{
    DLListNewItem(_DLClearTag(t));
}

inline void DLStencilMask(uint8 mask)
{
    DLListNewItem(_DLStencilMask(mask));
}

inline void DLTagMask(uint8 mask)
{
    DLListNewItem(_DLTagMask(mask));
}

inline void DLBitmapTransformA(uint32 a)
{
    DLListNewItem(_DLBitmapTransformA(a));
}

inline void DLBitmapTransformB(uint32 b)
{
    DLListNewItem(_DLBitmapTransformB(b));
}

inline void DLBitmapTransformC(uint32 c)
{
    DLListNewItem(_DLBitmapTransformC(c));
}

inline void DLBitmapTransformD(uint32 d)
{
    DLListNewItem(_DLBitmapTransformD(d));
}

inline void DLBitmapTransformE(uint32 e)
{
    DLListNewItem(_DLBitmapTransformE(e));
}

inline void DLBitmapTransformF(uint32 f)
{
    DLListNewItem(_DLBitmapTransformF(f));
}

inline void DLScissorXY(uint16 x, uint16 y)
{
    DLListNewItem(_DLScissorXY(x, y));
}

inline void DLScissorSize(uint16 width, uint16 height)
{
    DLListNewItem(_DLScissorSize(width, height));
}

inline void DLJump(uint16 address)
{
    DLListNewItem(_DLJump(address));
}

inline void DLBegin(uint8 primitive)
{
    DLListNewItem(_DLBegin(primitive));
}

inline void DLCall(uint16 address)
{
    DLListNewItem(_DLCall(address));
}

inline void DLColorMask(uint8 r, uint8 g, uint8 b, uint8 a)
{
    DLListNewItem(_DLColorMask(r, g, b, a));
}

inline void DLEnd()
{
    DLListNewItem(_DLEnd());
}

inline void DLSaveContext()
{
    DLListNewItem(_DLSaveContext());
}

inline void DLRestoreContext()
{
    DLListNewItem(_DLRestoreContext());
}

inline void DLReturn()
{
    DLListNewItem(_DLReturn());
}

inline void DLMacro(uint8 macro)
{
    DLListNewItem(_DLMacro(macro));
}

inline void DLClear(uint8 color, uint8 stencil, uint8 tag)
{
    DLListNewItem(_DLClear(color, stencil, tag));
}

inline void DLVertex2F(int16 x, int16 y)
{
    DLListNewItem(_DLVertex2F(x, y));
}

inline void DLVertex2II(uint16 x, uint16 y, uint8 handle, uint8 cell)
{
    DLListNewItem(_DLVertex2II(x, y, handle, cell));
}







inline void CMDDLStart()
{
    CMDListNewItem(_CMDDLStart());
}

inline void CMDSwap()
{
    CMDListNewItem(_CMDSwap());
}

inline void CMDInterrupt(uint32 milliseconds)
{
    CMDListNewItem(_CMDInterrupt(milliseconds));
}

inline void CMDBgcolor(int8 red, int8 green, int8 blue)
{
    CMDListNewItem(_CMDBgcolor(red, green, blue));
}

inline void CMDFgcolor(int8 red, int8 green, int8 blue)
{
    CMDListNewItem(_CMDFgcolor(red, green, blue));
}

inline void CMDGradient(int16 x0, int16 y0, int8 red0, int8 green0, int8 blue0, int16 x1, int16 y1, int8 red1, int8 green1, int8 blue1)
{
    CMDListNewItem(_CMDGradient(x0, y0, red0, green0, blue0, x1, y1, red1, green1, blue1));
}

inline void CMDText(int16 x, int16 y, int16 font, int16 options, char* text)
{
    CMDListNewItem(_CMDTextNew(x, y, font, options, text));
}

inline void CMDButton(int16 x, int16 y, int16 width, int16 height, int16 font, int16 options, char* text)
{
    CMDListNewItem(_CMDButton(x, y, width, height, font, options, text));
}

inline void CMDKeys(int16 x, int16 y, int16 width, int16 height, int16 font, int16 options, char* text)
{
    CMDListNewItem(_CMDKeys(x, y, width, height, font, options, text));
}

inline void CMDProgressBar(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 range)
{
    CMDListNewItem(_CMDProgressBar(x, y, width, height, options, value, range));
}

inline void CMDSlider(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 range)
{
    CMDListNewItem(_CMDSlider(x, y, width, height, options, value, range));
}

inline void CMDScrollBar(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 size, int16 range)
{
    CMDListNewItem(_CMDScrollBar(x, y, width, height, options, value, size, range));
}

inline void CMDToggle(int16 x, int16 y, int16 width,int16 font, int16 options, int16 state, char* text)
{
    CMDListNewItem(_CMDToggle(x, y, width, font, options, state, text));
}

inline void CMDGauge(int16 x, int16 y, int16 radius, int16 options, int16 major, int16 minor, int16 value, int16 range)
{
    CMDListNewItem(_CMDGauge(x, y, radius, options, major, minor, value, range));
}

inline void CMDClock(int16 x, int16 y, int16 radius, int16 options, int16 hours, int16 minutes, int16 seconds, int16 milliseconds)
{
    CMDListNewItem(_CMDClock(x, y, radius, options, hours, minutes, seconds, milliseconds));
}

inline void CMDCalibrate()
{
    CMDListNewItem(_CMDCalibrate());
}

inline void CMDSpinner(int16 x, int16 y, int16 style, int16 scale)
{
    CMDListNewItem(_CMDSpinner(x, y, style, scale)); 
}

inline void CMDStop()
{
    CMDListNewItem(_CMDStop());
}

inline void CMDMemSet(int32 ptr, int32 value, int32 size)
{
    CMDListNewItem(_CMDMemSet(ptr, value, size));
}

inline void CMDMemZero(int32 ptr, int32 size)
{
    CMDListNewItem(_CMDMemZero(ptr, size));
}

inline void CMDMemCopy(int32 dest, int32 src, int32 size)
{
    CMDListNewItem(_CMDMemCopy(dest, src, size));
}

inline void CMDAppend(int32 ptr, int32 size)
{
    CMDListNewItem(_CMDAppend(ptr, size));
}

inline void CMDSnapshot(int32 ptr)
{
    CMDListNewItem(_CMDSnapshot(ptr));
}

inline void CMDInflate(int32 ptr)
{
    CMDListNewItem(_CMDInflate(ptr));
}

inline void CMDLoadIdentity()
{
    CMDListNewItem(_CMDLoadIdentity());
}

inline void CMDTranslate(int32 tx, int32 ty)
{
    CMDListNewItem(_CMDTranslate(tx, ty));
}

inline void CMDScale(int32 x, int32 y)
{
    CMDListNewItem(_CMDScale(x, y));
}

inline void CMDRotate(int32 angle)
{
    CMDListNewItem(_CMDRotate(angle));
}

inline void CMDSetmatrix()
{
    CMDListNewItem(_CMDSetmatrix());
}

inline void CMDSetfont(int32 font, int32 ptr)
{
    CMDListNewItem(_CMDSetfont(font, ptr));
}

inline void CMDTrack(int16 x, int16 y, int16 width, int16 height, int16 tag)
{
    CMDListNewItem(_CMDTrack(x, y, width, height, tag));
}

inline void CMDDial(int16 x, int16 y, int16 radius, int16 options, int16 value)
{
    CMDListNewItem(_CMDDial(x, y, radius, options, value));
}

inline void CMDNumber(int16 x, int16 y, int16 font, int16 options, int32 number)
{
    CMDListNewItem(_CMDNumber(x, y, font, options, number));
}

inline void CMDScreenSaver()
{
    CMDListNewItem(_CMDScreenSaver());
}

inline void CMDSketch(int16 x, int16 y, int16 width, int16 height, int32 ptr, int16 format)
{
    CMDListNewItem(_CMDSketch(x, y, width, height, ptr, format));
}

inline void CMDLogo()
{
    CMDListNewItem(_CMDLogo());
}

inline void CMDColdstart()
{
    CMDListNewItem(_CMDColdstart());
}

inline void CMDGradcolor(int16 red, int16 green, int16 blue)
{
    CMDListNewItem(_CMDGradcolor(red, green, blue));
}



/* [] END OF FILE */
