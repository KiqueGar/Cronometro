/*STOPWATCH
 * Managing a stopwatch [min:sec:mil]
 * Showing to 7 segment displays
 * Enrique Garcia, 2017
*/

#include <avr/io.h>
#include <avr/interrupt.h>

// Time storage
volatile uint32_t thous;
volatile uint32_t pair_1;
volatile uint32_t pair_2;
volatile uint32_t pair_3;
volatile bool counting = false;
//Test section


void setup() {
  // Init Variables
  thous=0;
  //Init timer at 0
  pair_1 = 0;
  pair_2 = 0;
  pair_3 = 0;
  cli();  //Disable interrupts
  TCCR2A =0; //Set timer registers to 0
  TCCR2B =0;
  //Set compare match register to timer count 240:
  OCR2A = 240;
  //Turn on CTC (Clear Timer on Match)
  TCCR2A |= (1 << WGM21);
  //Prescaler:64
  TCCR2B |= (1 << CS22);
  //Enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  // Enable Interrupts
  sei();

  //Test section
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

ISR(TIMER2_COMPA_vect){
  thous++;
  if(thous == 10 && counting == true){
    thous = 0;
    _incrementTime();
    digitalWrite(13, !digitalRead(13));
  }
  UpdateDisplays();
  //Here goes the code for interrupt
  
  //Display update goes here
  
}
void _incrementTime(){
  pair_3 ++;
  if(pair_3 == 100){
    pair_3 = 0;
    pair_2 ++;
    if(pair_2 == 60){
      pair_2 =0;
      pair_3 ++;
    }
  }
}
void UpdateDisplays()
{
  
}


