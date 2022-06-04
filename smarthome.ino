#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
Servo servo_9;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 
int pos = 0;
int buzzer=2;
int ledRouge=7;
int ledvert=4;
int gaz= A0;
int mouvement =3;
int led =8; 
int lum = A1;
int moteur=5;


void setup()
{ servo_9.attach(9);
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();
  pinMode (buzzer,OUTPUT);
  pinMode(ledRouge,OUTPUT);
  pinMode(ledvert,OUTPUT);
  pinMode(gaz,INPUT);
  pinMode(led, OUTPUT);
  pinMode(lum,INPUT);
  pinMode(mouvement,INPUT);
  pinMode(moteur, OUTPUT);
}

void loop()
{int G=analogRead(gaz);
     Serial.println(G);
 int mvt;
     mvt = digitalRead(mouvement);
     Serial.println(mvt);
 int l;
  l= analogRead(lum);
  Serial.println(l);
 if(l <55 )
 { 
   if ( mvt == 1)
   
    { digitalWrite(led,HIGH);}
   
 
  else 
   
    { digitalWrite(led,LOW);}
 }

  
 else
 { 
   digitalWrite(led,LOW);
 }
 
  
  if (G > 110)
  {   digitalWrite(ledRouge,HIGH);
     digitalWrite(ledvert,LOW);
     delay(2000); 
    tone(buzzer,1200);
          digitalWrite(moteur, HIGH);
       delay(1000);                  
   
  }
  else{
     digitalWrite(ledRouge,LOW);
     digitalWrite(ledvert,HIGH);
        noTone(buzzer);
        digitalWrite(moteur, LOW);
        delay(1000);
}

   
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  
  }
  if ( !mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  
  Serial.println();
  }
  Serial.print("Message : ");
  content.toUpperCase();
   if (content.substring(1) == "23 87 68 0D") 
  {
    for (pos = 90; pos >= 0; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    delay(15); // Wait for 15 millisecond(s)
  };
  delay(3000);
    for (pos = 0; pos <= 90; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    delay(15); // Wait for 15 millisecond(s)
  };
  delay(500);
    Serial.println("Authorized access");
    Serial.println();
    
    delay(400);
  }
 
 else   {
    Serial.println(" Access denied");
  }
}
