// Address of the Data Direction Register B
#define DDRB  (*(volatile unsigned char *)(0x24)) 

// Address of the PORTB register (for output)
#define PORTB (*(volatile unsigned char *)(0x25))

// Bit definitions
#define DDB5  5
#define PORTB5 5