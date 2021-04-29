volatile unsigned char *myTCCR1A = (unsigned char *) ..
volatile unsigned char *myTCCR1B = (unsigned char *) ..
volatile unsigned char *myTCCR1C = (unsigned char *) ..
volatile unsigned char *myTIMSK1 = (unsigned char *) ..
volatile unsigned int  *myTCNT1  = (unsigned  int *) ..
volatile unsigned char *myTIFR1 =  (unsigned char *) ..
volatile unsigned char *portDDRB = (unsigned char *) ..
volatile unsigned char *portB =    (unsigned char *) ..


void setup()
{
  // set PB6 to output
  // Initialize PB6 to low

  // init timer control registers
  *myTCCR1A = 0x00;
  *myTCCR1B = 0x00;
  *myTCCR1C = 0x00;
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    // Read Input
      // make sure newlines is disabled from the IDE
    // Freq = freq_from_input(Input)
    // ticks = calc_ticks(freq)
      // What if the input is 'q'?
  }

  // Set PB6 to high
  // use YOUR OWN IMPLEMENTATION of the my_delay function. Do NOT use the built-in delay function
  // my_delay(ticks)
  // Set PB6 to low
  // my_delay(ticks)

}

unsigned int freq_from_input(char input){	
  // You can implement it any way you want.
  // Suggested method - 
    // Keep array of characters like - unsigned char letters[] = {'a', 'A', 'b',...}
    // Keep array of frequencies like - unsigned int freq_array[] = {440, 446, 494, 523....}
    // Make sure their indices match
    // Search through the letters arr to the index of the character
    // return that value from that index from the freq_array
}

unsigned int calc_ticks(unsigned int freq) {
  //Given a frequency, calculate the # of ticks
    //use the correct variable types - doubles and floats
    //Do not use integer formats (say 1.0 instead of 1)
  //return unsigned int
}

void my_delay(unsigned int freq)
{
  // stop the timer
  *myTCCR1B &= (????);
  // set the counts
  *myTCNT1 = (unsigned int) (65536 - ticks);
  // start the timer
  * myTCCR1B |= (????);
  // wait for overflow
  while((*myTIFR1 & (????))==0); // 0b 0000 0000
  // stop the timer
  *myTCCR1B &= (????);   // 0b 0000 0000
  // reset TOV - You actually have to set this bit to 1 to reset it, not 0 as would be logical (don't ask)
  *myTIFR1 |= (????);
}
