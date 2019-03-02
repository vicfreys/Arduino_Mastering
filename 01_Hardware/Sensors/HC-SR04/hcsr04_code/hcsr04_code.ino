#define pinTrig 8
#define pinEcho 2

unsigned long duration;
int distance;
volatile unsigned long lastPulseTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  
  PORTB &= ~(1<<PORTB0);
  
  Serial.begin(9600);

  cli();
  //TIMSK0 &= ~(1<<TOIE0);  // disable interrupts
  sei();
  attachInterrupt(0, echoPinISR, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  PORTB |= (1<<PORTB0);
  delayMicroseconds(10);
  PORTB &= ~(1<<PORTB0);

  //Read the pinEcho
  //duration = pulseInLong(pinEcho, HIGH);
  //distance = duration*0.017;
  //Serial.println(distance);
    
   Serial.println(lastPulseTime*0.017);
    
 
}

void echoPinISR() {
  static unsigned long startTime;

  if ((PIND&(1<<PIND2))==4) // Gone HIGH
    startTime = micros();
  else  // Gone LOW
    lastPulseTime = micros() - startTime;
}
