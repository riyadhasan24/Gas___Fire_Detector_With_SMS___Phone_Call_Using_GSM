#include <SoftwareSerial.h>
SoftwareSerial MY_Serial(8, 9);

char Phone_No[] = "+8801730288553";
int Buzzer = A0;
int GAS_Sensor = A3;
int Buzzer_Delay = 7000;
int Flame_Sensor = 2;
int GAS_Sensor_Value;
int Flame_Sensor_Value;

String Message_Body_Gas = "Gas Leaking..! Do Something..!";
String Message_Body_Fire = "Fire Detected..! Do Something..!";
String Message_Body_Thief = "Thief Detected..! Do Something..!";


void setup() 
{
 Serial.begin(9600);
 MY_Serial.begin(9600);
 pinMode(Buzzer, OUTPUT);
 pinMode(GAS_Sensor, INPUT); 
}

void loop() 
{   
  Flame_Sensor_Value = digitalRead(Flame_Sensor);
  GAS_Sensor_Value = analogRead(GAS_Sensor);
  
  if (GAS_Sensor_Value >= 320)
    {
      digitalWrite(Buzzer, HIGH);
      Make_Call(Phone_No);
      Send_Message_Gas();
      delay(Buzzer_Delay);
      digitalWrite(Buzzer, LOW);
    }

  if (Flame_Sensor_Value == LOW)
    {
      digitalWrite(Buzzer, HIGH);
      Make_Call(Phone_No);
      Send_Message_Fire();
      delay(Buzzer_Delay);
      digitalWrite(Buzzer, LOW);
    }
}

void Make_Call(char *number) 
{
  MY_Serial.print("ATD + "); 
  MY_Serial.print(number); 
  MY_Serial.println(";");
  delay(20000);       // wait for 20 seconds...
  MY_Serial.println("ATH"); //hang up
  delay(100);
}

void Send_Message_Fire()
{
  MY_Serial.println("AT+CMGF=1");
  delay(1000);
  MY_Serial.println("AT+CMGS=\"+8801730288553\"\r"); // Change the number as you need
  delay(1000);
  MY_Serial.println(Message_Body_Fire);//the content of the message
  delay(200);
  MY_Serial.println((char)26);
  delay(1000);
}


void Send_Message_Gas()
{
  MY_Serial.println("AT+CMGF=1");
  delay(1000);
  MY_Serial.println("AT+CMGS=\"+8801730288553\"\r"); // Change the number as you need
  delay(1000);
  MY_Serial.println(Message_Body_Gas);//the content of the message
  delay(200);
  MY_Serial.println((char)26);
  delay(1000);
}
