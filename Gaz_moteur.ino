
int mvt =13;
int led =7; 
int lum = A0;
void setup()
{ Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(lum,INPUT);
 pinMode(mvt,INPUT);
}

void loop()
{ 
 int mvt;
 mvt = digitalRead(mvt);
  Serial.println(mvt);
  int l;
  l= analogRead(lum);
  Serial.println(l);
 if(l <55 )
 { 
   if ( mvt == 1)
   {digitalWrite(led,HIGH);
    
   }
  else {  digitalWrite(led,LOW);}
       
 }
 else
 { 
   digitalWrite(led,LOW);
 }
   
  
}
