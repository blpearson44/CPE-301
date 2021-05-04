volatile unsigned char *myTCCR1A = (unsigned char *)0x80;
volatile unsigned char *myTCCR1B = (unsigned char *)0x81;
volatile unsigned char *myTCCR1C = (unsigned char *)0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *)0x6F;
volatile unsigned int *myTCNT1 = (unsigned int *)0x84;
volatile unsigned char *myTIFR1 = (unsigned char *)0x36;
volatile unsigned char *portDDRB = (unsigned char *)0x24;
volatile unsigned char *portB = (unsigned char *)0x25;
unsigned int freq = 0;
unsigned int ticks;
unsigned char notes[] = {'q', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'a', 'c', 'd', 'f', 'g'};
unsigned int frequencies[] = {0, 440, 494, 523, 587, 659, 698, 784, 466, 554, 624, 740, 831};
void setup()
{
  // set PB6 to output
  *portDDRB |= 0x40;
  // Initialize PB6 to low
  *portB &= 0xBF;
  // init timer control registers
  *myTCCR1A = 0x00;
  *myTCCR1B = 0x00;
  *myTCCR1C = 0x00;
  // this is so we don't run into issues with the overflow flag
  *myTIFR1 = 0x01;
  Serial.begin(9600);
}

void loop()
{
  // if the UART received a character
  if (Serial.available())
  {
    // read in the character
    unsigned char in_char = Serial.read();
    freq = calc_freq(in_char);
    ticks = calc_ticks(freq);
  }
  if (ticks != 0)
  {
    *portB |= 0x40;
    my_delay(ticks);
    *portB &= 0xBF;
    my_delay(ticks);
  }
}

unsigned int calc_freq(unsigned char note)
{
  for (size_t i = 0; i < 13; i++)
  {
    if (note == notes[i])
    {
      return frequencies[i];
    }
  }
}

unsigned int calc_ticks(unsigned int x)
{
  
  if (x == 0)
  {
    return 0;
  }
  float duty_cycle = (1.0 / freq) / 2.0;
 
  float t_clk = 1.0 / 16000000; // 16,000,000 is the frequency of the Arduino Mega 2560
  
  float temp = duty_cycle / t_clk;
  
  return temp;
}
void my_delay(unsigned int freq)
{
  *myTCNT1 = (unsigned int)(65536 - ticks);
  // set normal mode
  *myTCCR1A = 0;

  // start the timer with prescaler of 1 because min freq is > 245Hz
  *myTCCR1B = 0x01;
  // wait for overflow flag
  while ((*myTIFR1 & 0x01) == 0)
  {
  }
  myTCCR1B = 0x00;
  *myTIFR1 = 0x01;
}
