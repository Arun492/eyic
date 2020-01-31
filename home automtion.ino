#include<LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11);
#define Fan 3
#define Light 4
#define Charger 5
int temp=0,i=0;
void touchcaller();
void pircaller();
 void vibratecaller();

char str[15];
int touch_Sensor = 2;
int pir_Sensor =  12;
int vibration_Sensor = 13;
int present_conditionoftouch =    0;
int previous_conditionoftouch =   0;
int present_conditionofpir =      0;
int previous_conditionofpir =     0;
int present_conditionofvibrate =   0;
int previous_conditionofvibrate = 0;
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
pinMode(touch_Sensor, INPUT);
pinMode(pir_Sensor, INPUT);
//pinMode(vibration_Sensor, INPUT);
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(Charger, OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("GSM Control Home");
  lcd.setCursor(0,1);
  lcd.print("   Automaton    ");
  delay(2000);
  lcd.clear();
  lcd.print("SVIET");
  delay(1000);
  lcd.setCursor(0,1);
  
  lcd.print("System Ready");
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fan   Light  Charger ");
  lcd.setCursor(0,1);
  lcd.print("OFF    OFF   OFF "); 
}
void loop()
{
present_conditionoftouch = previous_conditionoftouch;
present_conditionofpir= previous_conditionofpir;
present_conditionofvibrate= previous_conditionofvibrate;
present_conditionoftouch = digitalRead(touch_Sensor);
present_conditionofpir = digitalRead(pir_Sensor);
present_conditionofvibrate = digitalRead(vibration_Sensor);
if (present_conditionoftouch!= previous_conditionoftouch) 
{
touchcaller();
present_conditionoftouch;

}

if (present_conditionofpir!= previous_conditionofpir) 
   {
  pircaller();
present_conditionofpir=0;
}
 



if (present_conditionofvibrate!= previous_conditionofvibrate) 
{
vibratecaller();
present_conditionofvibrate=0;

}
 

  lcd.setCursor(0,0);
  lcd.print("Fan   Light  Charger");
  if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }
}
 void serialEvent() 
 {
  while(Serial.available()) 
  {
    if(Serial.find("#A."))
    {
 
      delay(1000);

      while (Serial.available()) 
      {
      char inChar=Serial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 

      } 
    }
   }
 }
void check()
{
   if(!(strncmp(str,"Charger on",10)))
    {
      digitalWrite(Charger, HIGH);
      lcd.setCursor(13,1); 
      lcd.print("ON    ");
      delay(200);
    }  
   
   else if(!(strncmp(str,"Charger off",11)))
    {
      digitalWrite(Charger, LOW);
      lcd.setCursor(13,1); 
      lcd.print("OFF    ");
      delay(200);
    }
  
    else if(!(strncmp(str,"fan on",6)))
    {
      digitalWrite(Fan, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON   ");
      delay(200);
    }
 
    else if(!(strncmp(str,"fan off",7)))
    {
      digitalWrite(Fan, LOW);
      lcd.setCursor(0,1); 
      lcd.print("OFF    ");
      delay(200);
    }
 
    else if(!(strncmp(str,"light on",8)))
    {
      digitalWrite(Light, HIGH);
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(200);
    }
 
    else if(!(strncmp(str,"light off",9)))
    {
      digitalWrite(Light, LOW);
      lcd.setCursor(7,1); 
      lcd.print("OFF    ");
      delay(200);
    } 
    
    else if(!(strncmp(str,"all on",6)))
    {
      digitalWrite(Light, HIGH);
      digitalWrite(Fan, HIGH);
      digitalWrite(Charger, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON     ON    ON  ");
      delay(200);
    }
 
    else if(!(strncmp(str,"all off",7)))
    {
      digitalWrite(Light, LOW);
      digitalWrite(Fan, LOW);
      digitalWrite(Charger, LOW);
      lcd.setCursor(0,1); 
      lcd.print("OFF   OFF    OFF  ");
      delay(200);
    }     
}

void vibratecaller()
{
   Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");
    delay(1000);
    Serial.print("AT+CMGS=\"+918919735145\"\r");
    delay(1000);
   
    Serial.print("Someone tried to open your Locker");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
}
void pircaller()
{
    Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");
    delay(1000);
  
    Serial.print("AT+CMGS=\"+918919735145\"\r");
    delay(1000);
    //The text of the message to be sent.
    Serial.print("Someone Entered into your home");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
}
void touchcaller()
{
      Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");
    delay(1000);
    /*Replace XXXXXXXXXX to 10 digit mobile number & ZZ to 2 digit country code*/
    Serial.print("AT+CMGS=\"+918919735145\"\r");
    delay(1000);
    //The text of the message to be sent.
    Serial.print("Someone tried to open your home door");
    delay(1000);
    Serial.write(0x1A);
    delay(1000);
}
