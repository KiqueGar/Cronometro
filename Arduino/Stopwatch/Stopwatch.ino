/*STOPWATCH
 * Managing a stopwatch [min:sec:mil]
 * Showing to 7 segment displays
 * Enrique Garcia, 2017
*/
// Time storage
volatile uint32_t current_time;

void setup() {
  //Init timer at 0
  current_time = 0;
  cli();  //Disable interrupts
  TCCR2A =0; //Set timer registers to 0
  TCCR2B =0;
  //Set compare match register to timer count 240:
  OCR2A = 240;
  //Turn on CTC (Clear Timer on Match)
  TCCR2B |= (1 << WGM21);
  //Prescaler:64
  TCCR2B |= (1 << CS22);
  //Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE2A);
}

void loop() {
  // put your main code here, to run repeatedly:

}

ISR(TIMER2_COMPA_vect){
  //Here goes the code for interrupt
}

