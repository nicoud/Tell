// Tell.h  Blocking function to write 16 bits to DiTell.
//#include "Tell.h"  before calling Tell(nb16);
#include <Arduino.h>
#define bS1 5 // pin 13  
#define S1On  bitClear (PORTB,bS1)
#define S1Off  bitSet  (PORTB,bS1)
#define S1dirOut bitSet (DDRB,bS1)

volatile byte qz;
volatile int qqz;
#define Delt qz=95; while (qz--) {}  // 60us à 16 MHz
#define Deltt  qqz=600; while (qqz--) {}  // 600us à 16 MHz

void Tell (int dd) { 
  byte cc=0, sd; 
      sd = PORTB;  S1Off;  // save , set high  // optional recovery
      Deltt;   // min 600 us                   // instructions
  //  cli();  //remove jitter interrupt if required (>5us)

  while (cc++ < 16) { 
    S1On;
    Delt; if (!(dd&0x8000)) { S1Off;}
    Delt; S1Off; 
    Delt;
    dd <<=1;
  }
  if (!(sd & (1<<bS1))) { S1On; }  // 2 bytes!!
  //  sei();  //restore interrupts
}

