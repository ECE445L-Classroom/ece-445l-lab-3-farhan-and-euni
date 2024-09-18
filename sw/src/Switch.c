#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void Switch_Init(void){
    SYSCTL_RCGCGPIO_R |= 0x20;            // 1) Enable clock for Port F
    while((SYSCTL_PRGPIO_R & 0x20) == 0); // Wait until Port F is ready

    GPIO_PORTF_AMSEL_R &= ~0x07;          // 3) Disable analog on PF0, PF1, PF2
    GPIO_PORTF_PCTL_R &= ~0x00000FFF;     // 4) Configure PF0, PF1, PF2 as GPIO
    GPIO_PORTF_DIR_R &= ~0x07;            // 5) Set PF0, PF1, PF2 as inputs
    GPIO_PORTF_AFSEL_R &= ~0x07;          // 6) Disable alternate functions on PF0, PF1, PF2
    GPIO_PORTF_DEN_R |= 0x07;             // 7) Enable digital I/O on PF0, PF1, PF2
}

uint32_t Switch_In_PF0(void){
    return (GPIO_PORTF_DATA_R & 0x01);    // Return 0x01 if PF0 is pressed, 0x00 if not
}

uint32_t Switch_In_PF1(void){
    return (GPIO_PORTF_DATA_R & 0x02);    // Return 0x02 if PF1 is pressed, 0x00 if not
}

uint32_t Switch_In_PF2(void){
    return (GPIO_PORTF_DATA_R & 0x04);    // Return 0x04 if PF2 is pressed, 0x00 if not
}