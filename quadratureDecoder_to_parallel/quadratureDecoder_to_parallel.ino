volatile long temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder
int timer1_counter;
    
void setup() {
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  //timer1_counter = 65036;   // preload timer 65536-16MHz/64/500Hz
  //timer1_counter = 65203;   // preload timer 65536-16MHz/64/750Hz
  //timer1_counter = 65286;     // preload timer 65536-16MHz/64/1kHz
  
  TCNT1 = timer1_counter;   // preload timer
  //TCCR1B |= (1 << CS11);    // 64 prescaler
  //TCCR1B |= (1 << CS10);    // 64 prescaler 
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
  
  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(3, INPUT_PULLUP); // internal pullup input pin 3
   //Setting up interrupt
  //A rising pulse from encoder activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);
  //B rising pulse from encoder activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
  Serial.begin(250000);
  }
   
void loop() {
  // Loop functions

}

ISR(TIMER1_OVF_vect){
  
  TCNT1 = timer1_counter;   // preload timer
  Serial.println(counter);
}

void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(3)==LOW) {
    counter++;
    }else{
      counter--;
  }
}
   
void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
    counter--;
    }else{
      counter++;
  }
}
