const byte LED_PIN = 13;
const byte METER_PIN = A4;
volatile byte ledstate = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
      
  Serial.begin(9600);
  
  startTimer();
}

void loop()
{ 
}

void startTimer(){
  /* 
  Calculations (for 2s):
  System clock 16 Mhz and Prescalar 1024;
  Timer1 speed = 16Mhz/1024 = 15625Hz
  Count for 2s = 2s * 15625Hz = 31250
*/
  noInterrupts();
  
  TCCR1A = 0; // Reset entire TCCR1A to 0
  TCCR1B = 0; // Reset entire TCCR1B to 0

  /*2. Setting prescaler by changig bits */
  TCCR1B |= B00000101; // CS12 to 1 so prescalar 1024

  /*3. Enabling compare match mode on register A*/
  TIMSK1 |= B00000010;
  /*4. Set the value of register A to 31250*/
  OCR1A = 31250; // Finally we set compare register A to this value
  
  interrupts();
}

ISR(TIMER1_COMPA_vect){
  TCNT1 = 0;    // Timer back to 0 so it resets for next interrupt
  ledstate = !ledstate; // Invert LED state
  digitalWrite(LED_PIN, ledstate);
}
