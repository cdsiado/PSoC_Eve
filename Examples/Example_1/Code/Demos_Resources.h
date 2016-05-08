/*******************************************************************************
* File Name: Demos_Resources.h  
* Version 0.1 Alpha
*
* Description:
*  This file belongs to the PSoCEve library project.
*  Used for testing features of PSocEve library during development.
*  It contains some resources such as graphics and sounds.
*
* Note:
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#if !defined(DEMOS_RESOURCES_H) /* Pins SPI_EVE_miso_s_H */
#define DEMOS_RESOURCES_H
    
#include <cytypes.h>    

/* HackingChips bitmap: converted with FTDI tool. 64x64, RGB565,  */
extern const uint8 testbitmap[8192];

/* HackingChips bitmap: converted with FTDI tool. 64x64, RGB565, ZLIB, to be used with CMD_INFLATE */
const uint8 testbitmapzlib[2030];


#endif /* End DEMOS_RESOURCES_H */

/* [] END OF FILE */
