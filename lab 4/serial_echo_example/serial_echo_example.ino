// Serial Echo Example
void setup() 
{
  // setup the UART
  Serial.begin(9600);
}
void loop() 
{
  // if the UART received a character
  if(Serial.available())
  {
    // read in the character
    unsigned char in_char = Serial.read();
    // write the character back to the Serial Port
    Serial.write(in_char);
  }
}
