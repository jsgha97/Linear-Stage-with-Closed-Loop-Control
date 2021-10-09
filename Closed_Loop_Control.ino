void setup() {
  pinMode(5,INPUT_PULLUP);  // Button set up to pin 5
  pinMode(7,INPUT);         // Encoder B on pin 7 to read analog voltage
  attachInterrupt(digitalPinToInterrupt(2),count,RISING);  // Set digital pin 2 to trigger interrupt function
                                                           // Count () when a rising flank is detected
                                                           // Encoder A connected to pin 2
  
  pinMode(12,OUTPUT);  // Motor Direction
  pinMode(3,OUTPUT);   // Motor Power
  pinMode(9,OUTPUT);   // Motor Brake

  digitalWrite(9,LOW);
  Serial.begin(115200);

  while(digitalRead(5)==HIGH){}  // Remain idle until program starts and button is pressed
}

volatile long int pulses =0;
double v_motor, current_rpm=0, error=0;
int target1 = 130, target2 = 96, target3 = 70;
void loop() {
  //STEP 1
  while(digitalRead(5)==LOW){}  // Press button
  while(digitalRead(5)==HIGH){  // Move forward until button is pressed
    digitalWrite(12,HIGH);  // Set motor direction
    
    //1) Output voltage to motor, 2) wait for it to respond, 3) measure new speed
    analogWrite(3,int(v_motor));  // Feed voltage to motor, v_motor has to be recast into an integer
    delay(100);                   // Wait for motor to reach new speed
    current_rpm=getSpeed(100000); // Measure speed using 100000 microseconds of data

    // Print out time in milliseconds, Control voltage [0-255], Speed [RPM], and Pulse Count
    Serial.println(String(millis())+"\t"+String(int(v_motor))+"\t"+String(current_rpm)+"\t"+String(pulses));
    error = target1 - current_rpm;  
    v_motor += .1*error;  // Proportional control of v_motor to reach a target RPM value
    }
  Serial.println("STEP 2");
  
  //STEP 2
  for (int counter=0; counter<=10; counter++){  // Retract 10mm at reduced speed
    digitalWrite(12,LOW);  // Set motor in opposite direction
    analogWrite(3,int(v_motor));
    delay(100);
    current_rpm=getSpeed(100000); 
    Serial.println(String(millis())+"\t"+String(int(v_motor))+"\t"+String(current_rpm)+"\t"+String(pulses));
    error = target2 - current_rpm;  
    v_motor += .1*error;
    }
  Serial.println("STEP 3");
  
  //STEP 3
  while(digitalRead(5)==LOW){}  // Move towards button again at reduced speed
  while(digitalRead(5)==HIGH){
    digitalWrite(12,HIGH);
    analogWrite(3,int(v_motor));
    delay(100);
    current_rpm=getSpeed(100000); 
    Serial.println(String(millis())+"\t"+String(int(v_motor))+"\t"+String(current_rpm)+"\t"+String(pulses));
    error = target2 - current_rpm;  
    v_motor += .1*error;
    }
  Serial.println("STEP 4");

  //STEP 4
  for (int counter=0; counter<=35; counter++){  // Retract 30mm at lowest speed possible
    digitalWrite(12,LOW);
    analogWrite(3,int(v_motor));
    delay(100);
    current_rpm=getSpeed(100000); 
    Serial.println(String(millis())+"\t"+String(int(v_motor))+"\t"+String(current_rpm)+"\t"+String(pulses));
    error = target3 - current_rpm;  
    v_motor += .1*error;
    }
  analogWrite(3,0);
  while(true);
}

void count(){
  // This function is executed whenever a rising pulse flank is detected on pin 2 (Encoder A)
  if (digitalRead(7) == LOW)
    pulses++;
  else 
    pulses--;
}

double getSpeed(long int us){
  long int t0=0, initialPulses = 0, delta_pulses=0, delta_t;
  double rpm=0;
  initialPulses=pulses;    // Set initial pulse count
  t0=micros();             // Set initial time in us
  while(micros()-t0<us){}  // Allow sampling time (us) to elapse
  delta_t=us;              // Duration of sample, in microseconds (passed as argument)
  if (pulses>initialPulses){  // Pulse increase or decrease (direction dependent) during sample period
    delta_pulses=pulses-initialPulses; 
  }
  else {delta_pulses=initialPulses-pulses;} 
  rpm=double(delta_pulses)/double(delta_t)*1E+6 /374.0 * 60.0; // w=d(theta)/dt, conver to rpm
                                                               // Encoder gives 374 pulses/rev
  return(rpm);
}
