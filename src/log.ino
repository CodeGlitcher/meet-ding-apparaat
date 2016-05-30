bool log_enabled = true;

inline void log_init()
{
  
  digitalWrite(LOG_PIN,HIGH);
  if(digitalRead(LOG_PIN) == HIGH){
   log_disable();
  }

  
  Serial.begin(baud, SERIAL_8N1);
}

void log_print(char* msg)
{
  if (log_enabled) {
    Serial.print(msg);
  }
}

void log_println(char* msg)
{
  if (log_enabled) {
    Serial.println(msg);
  }
}

void log_println(String msg)
{
  if (log_enabled) {
    Serial.println(msg);
  }
}

void log_enable()
{
  log_enabled = true;
}

void log_disable()
{
  log_enabled = false;
}
