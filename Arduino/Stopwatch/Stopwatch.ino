/*STOPWATCH
 * Managing a stopwatch [min:sec:mil]
 * Showing to 7 segment displays
 * Enrique Garcia, 2017
*/

#include <avr/io.h>
#include <avr/interrupt.h>

// Time storage
volatile uint8_t thous;
volatile uint8_t digit_0;
volatile uint8_t digit_1;
volatile uint8_t digit_2;
volatile uint8_t digit_3;
volatile uint8_t digit_4;
volatile uint8_t digit_5;

uint8_t digits[] = {digit_0,
                    digit_1,
                    digit_2,
                    digit_3,
                    digit_4,
                    digit_5};

volatile bool counting = false;
volatile uint8_t digitIterator;
// Pin definitions for 7448
#define in48_a 8
#define in48_b 9
#define in48_c 10
#define in48_d 11
//Values for portB as number, lowet nibble
byte codedNumber[] = {B00000000,
                      B00000001,
                      B00000010,
                      B00000011,
                      B00000100,
                      B00000101,
                      B00000110,
                      B00000111,
                      B00001000,
                      B00001001};

//Pin definitions for 74138
#define in138_0 5
#define in138_1 6
#define in138_2 7
//Values for portD as catodes, upper 3 bits
byte cathodes[] = {B00000000,
                   B00100000,
                   B01000000,
                   B01100000,
                   B10000000,
                   B10100000};

#define honk 3
#define start 2
//Test section



void setup() {
  // Init Variables
  thous=0;
  //Init timer at 0
  digit_0, digit_1, digit_2, digit_3, digit_4, digit_5 = 0;
  digitIterator =0;
  //Set port B as output
  DDRB = 0xFF;
  //Set port D as output
  DDRD = 0xFF;
  //Enable inpnut with pullup
  pinMode(start, INPUT);
  digitalWrite(start, HIGH);
  
  pinMode(honk, OUTPUT);
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
  //EIMSK |= (1<< INT0);  //Enable  external interrupt INT0
  //EICRA |= (1<< ISC01); //Triger on falling edge

  //Test section
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  counting=true;
}

ISR(TIMER2_COMPA_vect){
  //Here goes the code for timer interrupt
  thous++;
  if(thous == 10 && counting == true){
    thous = 0;
    _incrementTime();
    digitalWrite(13, !digitalRead(13));
  }
  UpdateDisplays();
  
  
}

ISR(INT0_vect){
  //External interrupt code here
  digitalWrite(13, LOW);
}

void _incrementTime(){
  //Increment miliseconds
  digit_0 ++;
  if(digit_0 == 10){
    //Increment ten miliseconds
    digit_0 = 0;
    digit_1 ++;
    if(digit_1 == 10){
      //Increment second
      digit_1 =0;
      digit_2 ++;
      if(digit_2 ==10){
        //Increment ten seconds
        digit_2=0;
        digit_3 ++;
        if(digit_3 ==6){
          //Increment minute
          digit_3 = 0;
          digit_4 ++;
          if(digit_4 ==10){
            digit_4 =0;
            digit_5 ++;
          }
        }
      }
    }
  }
}
void UpdateDisplays()
{
  digitIterator ++;
  if (digitIterator == 6){
    digitIterator=0;
  }
  //Turn off current digit
  PORTD = PORTD & 0x0F;
  PORTB = PORTB & 0xF0;
  //Replace digit
  //Read current digit Value
  uint8_t number = _getValue(digitIterator);
  //Display new digit
  PORTB = codedNumber[number];
  //Enable current digit
  PORTD = cathodes[digitIterator] | PORTD;
}

uint8_t _getValue(uint8_t index){
  if(index == 0){
    return digit_0;
  }
  
  if(index == 1){
    return digit_1;
  }
  
  if(index == 2){
    return digit_2;
  }
  
  if(index == 3){
    return digit_3;
  }
  
  if(index == 4){
    return digit_4;
  }
  
  if(index == 5){
    return digit_5;
  }
  
}
  
