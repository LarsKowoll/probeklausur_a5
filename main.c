/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
  *          	Labor für technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    23.05.2013
  * @brief   Main program body
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "TI_Lib.h"
#include "tft.h"

//--- For GPIOs -----------------------------
//Include instead of "stm32f4xx.h" for
//compatibility between Simulation and Board
//#include "TI_memory_map.h"

//--- For Touch Keypad ----------------------
//#include "keypad.h"

//--- For Timer -----------------------------
//#include "timer.h"

/**
  * @brief  Main program
  * @param  None
  */
int main(void)
{
	
  Init_TI_Board();
    
  printf("Hallo TI-Labor.\n\r");

  TFT_cls();
  TFT_puts("Hallo TI-Labor\n\r");
  
   float werte[480];
   for (int i = 0; i < 240; i++) {
           float temp;
           temp = (400) * ((float)i/48000) - 1;
           werte[i] = (temp + 1) * 2047.5;
       } 
       
    for (int i = 0; i < 240; i++) {
           float temp;
           temp =  -(400) * ((float)i/48000) + 1;
           werte[i + 240] = (temp + 1) * 2047.5;
       }
    
      RCC->APB1ENR = RCC_APB1ENR_TIM2EN | RCC_APB1ENR_DACEN;
      TIM2->CR1 = 0;
      TIM2->CR2 = 0;
      TIM2->PSC = 4 - 1;
      TIM2->ARR = 438 - 1;
       
      TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
      
     
      DAC->CR |= 1;
       
       DAC->DHR12R1 = 2050;
       DAC->DHR12R1 = 0;
      
      int i = 0;
      while(1) {
          while ((TIM2->SR & TIM_SR_UIF) == 0) {
          }
          TIM2->SR = ~TIM_SR_UIF;
          DAC->DHR12R1 = werte[i];    
          i++;
          if (i == 481) {
              i=0;
          }

      }
       
  return 0;

}
// EOF
