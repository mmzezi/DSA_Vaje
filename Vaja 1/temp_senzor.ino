// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


// the loop routine runs over and over again forever:
void loop() {
  getTemp(A1);
}

float getTemp(int vhodAD){
  // read the input on analog pin 0:
  float sensorValue = (analogRead(vhodAD) + 20.0); //A0 - svetloba, A1 - temperatura, +20 je za kalibracijo temperature
  // print out the value you read:
  float napetost = sensorValue * (5000/1023);
  float temp = napetost - 400;
  temp = temp / 19.5;
  Serial.println(temp);
  delay(250);        // delay in between reads for stability
  }
