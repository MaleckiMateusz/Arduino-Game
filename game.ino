int iloscSzans = 2;
boolean czerwona = false, zolta = false, zielona = false;
int napisanaLiczba = 0, potnLiczba = 0;

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT); //Wyjście diody czerwonej
  digitalWrite(11, LOW);
  pinMode(10, OUTPUT); //Wyjście diody żółtej
  digitalWrite(10, LOW);
  pinMode(9, OUTPUT); //Wyjście diody zielonej
  digitalWrite(9, LOW);
  pinMode(7, INPUT_PULLUP); //Przycisk
}

void loop() {
  potnLiczba = analogRead(A4); // odczytanie liczby z potencjometru
  
  while(digitalRead(7) == LOW){
    Serial.println("Podaj liczbę:");
    delay(1000);
  }
  
  if(Serial.available() > 0) {
    napisanaLiczba = Serial.readStringUntil('\n').toInt();
    Serial.print("Twoja liczba to: ");
    Serial.println(napisanaLiczba);

    if((napisanaLiczba < (potnLiczba+50)) && (napisanaLiczba > (potnLiczba-50))) {
      czerwona = false;
      zolta = false;
      zielona = true; // zielona dioda
      Serial.print("Potencjometr wskazywał na : ");
      Serial.println(potnLiczba);
    } else { 
      czerwona = false;
      zolta = true; // żółta dioda
      zielona = false;
      iloscSzans--;
    }
    if(iloscSzans < 0) { // przegrana
    czerwona = true; // czerwona dioda
    zolta = false; 
    zielona = false;
    Serial.print("Potencjometr wskazywał na : ");
    Serial.println(potnLiczba);
    }
  }

  if(czerwona) digitalWrite(11, HIGH);
  else digitalWrite(11, LOW);
  if(zolta) digitalWrite(10, HIGH);
  else digitalWrite(10, LOW);
  if(zielona) digitalWrite(9, HIGH);
  else digitalWrite(9, LOW);
}
