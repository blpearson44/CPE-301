// Code by Ben Pearson
// Revision 3 on 3/31/21
#define RDA 0x80
#define TBE 0x20
volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0; // control and status registers
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int *myUBRR0 = (unsigned int *)0x00C4;  // sets baud rate
volatile unsigned char *myUDR0 = (unsigned char *)0x00C6; // used to send and receive data
//
// main()
//
void setup()
{
  // initialize the serial port on USART0:
  U0init(9600);
}
void loop()
{
  unsigned char cs1;
  while (!U0kbhit())
  {
  }                  // wait for RDA = true
  cs1 = U0getchar(); // read character
  U0putchar('0');    // to display hex
  U0putchar('x');
  U0putchar(((cs1 & 0xF0) >> 4) + 0x30); // 0x30 is an int 48 offset to get to ascii values, this is for the 4 most significant bits
  U0putchar((cs1 & 0x0F) + 0x30);        // this is for the 4 least significant bits
  U0putchar((unsigned char)0x0A);        // new line character
}
//
// function to initialize USART0 to "int" Baud, 8 data bits,
// no parity, and one stop bit. Assume FCPU = 16MHz.
//
void U0init(unsigned long U0baud)
{
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  *myUCSR0A = 0x20;
  *myUCSR0B = 0x18;
  *myUCSR0C = 0x06;
  *myUBRR0 = tbaud;
}
//
// Read USART0 RDA status bit and return non-zero true if set
//
unsigned char U0kbhit()
{
  return *myUCSR0A & RDA;
}
//
// Read input character from USART0 input buffer
//
unsigned char U0getchar()
{
  return *myUDR0;
}
//
// Wait for USART0 TBE to be set then write character to
// transmit buffer
//
void U0putchar(unsigned char U0pdata)
{
  while ((*myUCSR0A & TBE) == 0)
  {
  }                  // check for an update in the control register
  *myUDR0 = U0pdata; // after update, send data
}
