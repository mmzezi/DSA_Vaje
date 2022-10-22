void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop(){ //tukaj loopa štetje po bitih do 256
  for (int stev = 0; stev < 256; stev++) //počasi gre proti 256, recmo 3 je samo prvi dve ledici, 1 samo prva ipd... (128 je polovica vseh ledic)
  {
      led(stev);
      delay(500);
  }
 }

void led(char podatek) {
  // put your main code here, to run repeatedly:

  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  int i = 0;
  for (i=0; i<8; i++){
    if(podatek & B00000001){
        digitalWrite(12, HIGH);
      }
    else{
        digitalWrite(12, LOW);
      }
     digitalWrite(10, HIGH);
     digitalWrite(10, LOW);
     podatek = podatek >> 1;
    }
    digitalWrite(11, HIGH);
    digitalWrite(11, LOW);
}
