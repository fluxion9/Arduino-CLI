String inString;
void setup() {
  Serial.begin(38400);

}

void loop() {
  if(Serial.available())
  {
    inString = Serial.readStringUntil('\\');
    if(inString.length() > 0)
    {
      exeCMD(inString);
      inString = "";
    }
  }

}

void exeCMD(String command)
{
  if(command.startsWith("RFUNC"))
  {
    String function = command.substring(command.indexOf('=') + 1, command.indexOf('('));
    if(function == "digitalRead")
    {
      int pin = command.substring(command.indexOf('(') + 1, command.indexOf(')')).toInt();
      Serial.println(digitalRead(pin));
    }
    else if(function == "analogRead")
    {
      int pin = command.substring(command.indexOf('(') + 1, command.indexOf(')')).toInt();
      Serial.println(analogRead(pin));
    }
    else if(function == "micros")
    {
      Serial.println(micros());
    }
    else if(function == "millis")
    {
      Serial.println(millis());
    }
  }
  else if(command.startsWith("VFUNC")){
    String function = command.substring(command.indexOf('=') + 1, command.indexOf('('));
    if(function == "pinMode")
    {
      int pin = command.substring(command.indexOf('(') + 1, command.indexOf(',')).toInt();
      int val = command.substring(command.indexOf(',') + 1, command.indexOf(')')).toInt();
      pinMode(pin, val);
    }
    else if(function == "digitalWrite")
    {
      int pin = command.substring(command.indexOf('(') + 1, command.indexOf(',')).toInt();
      int val = command.substring(command.indexOf(',') + 1, command.indexOf(')')).toInt();
      digitalWrite(pin, val);
    }
    else if(function == "analogWrite")
    {
      int pin = command.substring(command.indexOf('(') + 1, command.indexOf(',')).toInt();
      int val = command.substring(command.indexOf(',') + 1, command.indexOf(')')).toInt();
      analogWrite(pin, val);
    }
    else if(function == "tone")
    {
      int pin = command.substring(command.indexOf('(') + 1, command.indexOf(',')).toInt();
      int freq = command.substring(command.indexOf(',') + 1, command.indexOf(')')).toInt();
      tone(pin, freq);
    }
    else if(function == "noTone")
    {
      int pin = command.substring(command.indexOf('(') + 1, command.indexOf(')')).toInt();
      noTone(pin);
    }
    else if(function == "shiftOut")
    {
      int dpin = command.substring(command.indexOf('(') + 1, command.indexOf(',')).toInt();
      String other = command.substring(command.indexOf(',') + 1);
      int cpin = other.substring(0, command.indexOf(',')).toInt();
      other = other.substring(other.indexOf(',') + 1);
      int lpin = other.substring(0, command.indexOf(',')).toInt();
      other = other.substring(other.indexOf(',') + 1);
      int d = other.substring(0, command.indexOf(')')).toInt();
      pinMode(dpin, 1);
      pinMode(cpin, 1);
      pinMode(lpin, 1);
      digitalWrite(lpin, 0);
      shiftOut(dpin, cpin, MSBFIRST, d);
      digitalWrite(lpin, 1);
      delay(1);
      digitalWrite(lpin, 0);
    }  
    else if(function == "Serial.println")
    {
      String message = command.substring(command.indexOf('(') + 1, command.indexOf(')'));
      Serial.println(message);
    }  
    else if(function == "Serial.print")
    {
      String message = command.substring(command.indexOf('(') + 1, command.indexOf(')'));
      Serial.print(message);
    }  
  }
}
