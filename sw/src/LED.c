#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/SysTick.h"
#include "../inc/PLL.h"
#include "../inc/LaunchPad.h"

int LED(void){
  PLL_Init(Bus80MHz);         // set system clock to 50 MHz
  SysTick_Init();             // initialize SysTick timer
  LaunchPad_Init();   // activate port F  
  while(1){
    PF3 = PF3^0x08; // toggle PF2
    SysTick80_Wait10ms(10);      // approximately 100 ms
  }
}