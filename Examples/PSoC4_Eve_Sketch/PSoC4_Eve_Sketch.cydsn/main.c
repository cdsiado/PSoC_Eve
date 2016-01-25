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
#include <project.h>
#include "demo_sketch.h"

int main()
{
    /* *** Start leds.
           Be sure both leds are turned off.
    */
    
    Led_Red_Write(1);
    Led_Green_Write(1);
    
    /* *** Start SPI bus. *** 
        In schematic, SPI module is configured to have one SS line.
        Disconects SS0 from HSIOM so it can be controlled by software instead of hardware or API. 
    */

    SPI_Start();
    
    (*(reg32 *)SPI_ss0_m__0__HSIOM) = 
        ((*(reg32 *)SPI_ss0_m__0__HSIOM) & (uint32)~SPI_ss0_m__0__HSIOM_MASK) | (uint32)(SPI_HSIOM_GPIO_SEL << SPI_ss0_m__0__HSIOM_SHIFT);
    
    SPI_ss0_m_Write(1); 
    
    /* Init the demo. */
    Home_Setup();
    
    /* Show info screen. */
    Info();
    
    /* Enter in sketck. */
    Sketch();
    
    //CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
