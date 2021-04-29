// CPE 301 Lab 7
// Ben Pearson
// Due 4/7/21
// 7 segment display config
volatile unsigned char* ddr_k  = (unsigned char*) 0x107;
volatile unsigned char* port_k = (unsigned char*) 0x108;
volatile unsigned char* pin_k  = (unsigned char*) 0x106;

// button config
volatile unsigned char* portB = (unsigned char *)0x25;
volatile unsigned char* portDDRB = (unsigned char *)0x24;
volatile unsigned char* pinB = (unsigned char *)0x23;

// from the eeprom_demo
// this is the character array, mapped such that the first element displays a '0' on the 7-segment
unsigned char chr_array[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
// get a pointer to the EEPROM ADDRESS REGISTER (16-bit)
volatile unsigned int* EEPROM_ADDR_REG = (unsigned int*) 0x41;
// get a pointer to the EEPROM Data Register (8-bit)
volatile unsigned char* EEPROM_DATA_REG = (unsigned char*) 0x40;
// get a pointer to the EEPROM Control Register (8-bit)
volatile unsigned char* EEPROM_CNTRL_REG = (unsigned char*) 0x3F;

unsigned int counter = 0;
unsigned int address = 0x0025;

void setup()
{
  // 7 segment display set all pins as output
  *ddr_k |= 0xFF;

  // Button
  // set PB7 to input;
  *portDDRB &= 0x7F;
  // enable pullup resistor on PB7
  *portB |= 0x80;

  // set display to be saved display
  *pin_k = eeprom_read(address);
}
void loop()
{
  if (!(*pinB & 0x80)) // check for button press
  {
    while (!(*pinB & 0x80)); // wait until release
    *pin_k = chr_array[counter]; // write character to display
    eeprom_write(address, chr_array[counter++]); // save character to memory
    if (counter==0) // check for counter overflow
    {
      counter = 16;
    }
  }  
  
  delay(50); // to debounce add delay of 50ms
}

void eeprom_write(unsigned int address, unsigned char data_in)
{
  /* Wait for completion of previous write */
  while(*EEPROM_CNTRL_REG & 0x02);
  /* Set up address and Data Registers */
  *EEPROM_ADDR_REG = address;
  *EEPROM_DATA_REG = data_in;
  /* Write logical one to EEMPE */
  *EEPROM_CNTRL_REG |= 0x04;
  /* Write logical zero to EEPE */
  *EEPROM_CNTRL_REG &= ~(0x02);
  /* Write logical one to EEPE */
  *EEPROM_CNTRL_REG |= 0x02;
}
unsigned char eeprom_read(unsigned int address)
{
  /* Wait for completion of previous write */
  while(*EEPROM_CNTRL_REG & 0x02);
  /* Set up address register */
  *EEPROM_ADDR_REG = address;
  /* Start eeprom read by writing EERE */
  *EEPROM_CNTRL_REG |= 0x01;
  /* Return data from Data Register */
  return *EEPROM_DATA_REG;
}
