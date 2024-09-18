#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#define SPEAKER_PIN   (*((volatile uint32_t *)0x40025008))  // PF1
#define SPEAKER_PIN_MASK 0x02  // Mask for PF1

void Sound_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;             // 1) Enable clock for Port F
  while((SYSCTL_PRGPIO_R & 0x0020) == 0);// Wait until Port F is ready
  
  GPIO_PORTF_AMSEL_R &= ~SPEAKER_PIN_MASK;   // 3) Disable analog functionality on PF1
  GPIO_PORTF_PCTL_R &= ~0x000000F0;          // 4) Configure PF1 as GPIO
  GPIO_PORTF_DIR_R |= SPEAKER_PIN_MASK;      // 5) Set PF1 as output
  GPIO_PORTF_AFSEL_R &= ~SPEAKER_PIN_MASK;   // 6) Disable alternate functions on PF1
  GPIO_PORTF_DEN_R |= SPEAKER_PIN_MASK;      // 7) Enable digital I/O on PF1
  SPEAKER_PIN = 0x00;                        // Initialize the speaker pin to off
}

void Sound_AlarmOn(void){
  while(1){
    SPEAKER_PIN ^= SPEAKER_PIN_MASK;        // Toggle PF1
    for(int i = 0; i < 500000; i++){}       // Adjust the delay for frequency control
  }
}

void Sound_AlarmOff(void){
  SPEAKER_PIN = 0x00;                       // Set PF1 to low (no sound)
}