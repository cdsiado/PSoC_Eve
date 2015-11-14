/*******************************************************************************
* File Name: Test.h  
* Version 0.1 Alpha
*
* Description:
*  This file belongs to the PSoCEve library project.
*
* Note:
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#if !defined(TEST_H)
#define TEST_H

    
/* *** GENERAL *** */ 
    
void T_Init();


/* *** DISPLAY LIST *** */

void T_DL_A();
void T_DL_PRIMITIVE_POINT();
void T_DL_PRIMITIVE_LINE();
void T_PRIMITIVE_EDGESTRIP();
void T_PRIMITIVE_RECTANGLE();
void T_PRIMITIVE_BITMAP();
void T_DL_B();
void T_DL_SCISSOR();
void T_DL_TAG_AND_MASK();

/* *** COPROCESSOR *** */

void T_CMD_GRADIENT();
void T_CMD_TEXT();
void T_CMD_BUTTON();
void T_CMD_KEYS();
void T_CMD_PROGRESS();
void T_CMD_SLIDER();
void T_CMD_SCROLLBAR();
void T_CMD_TOGGLE();
void T_CMD_GAUGE();
void T_CMD_CLOCK();
void T_CMD_CALIBRATE();
void T_CMD_SPINNER();
void T_CMD_DIAL();
void T_CMD_NUMBER();
void T_CMD_SKETCH();
void T_CMD_LOGO();
void T_CMD_SCREENSAVER();
void T_CMD_COLDSTART();
void T_CMD_INFLATE();

/* *** SOUND *** */

void T_SOUND();
    
#endif /* End TEST_H */    

/* [] END OF FILE */
