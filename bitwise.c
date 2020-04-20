#include <stdio.h>
#include <stdint.h>


union
{
  uint16_t value;
  struct
  {
    uint8_t a: 4;
    uint8_t b: 4;
    uint8_t c: 4;
    uint8_t d: 4;
  };
} int2nib;

/**
* Embedded Systems require use of BITWISE operators to maintain register arrays
* Bit shift, (un)set, toggle & check
*
*/
uint8_t parity_uint8(uint8_t n)
{
  return (((n >> 0) & 1U) + ((n >> 1) & 1U) + ((n >> 2) & 1U)  + ((n >> 3) & 1U) + ((n >> 4) & 1U)  + ((n >> 5) & 1U) + ((n >> 6) & 1U) + ((n >> 7) & 1U)) %2;

}

/**
* In serial data transmission, a common format is 7 data bits, an even parity bit, and one or two stop bits. This format neatly accommodates all the 7-bit ASCII characters in a convenient 8-bit byte.
*/
uint8_t parity_setbit(uint8_t n)
{
  uint8_t p = (((n >> 0) & 1U) + ((n >> 1) & 1U) + ((n >> 2) & 1U)  + ((n >> 3) & 1U) + ((n >> 4) & 1U)  + ((n >> 5) & 1U) + ((n >> 6) & 1U) + ((n >> 7) & 1U)) %2;
  int b = (n >> p) & 1U;
  return n ^= (-b ^ n) & (1UL << 8);
}

int main()
{
  int i = 0;
  printf("%d \n",i);

  // set i.bit[0] = 1
  i |= 1 << 0;
  printf("%d \n",i);

  // i |= 1UL << 0;
  // the << is a "bit shift" operator which will move all the bits in that value above to the left bitno number of times.
  // If it's 1UL<<5, you'll end up with:
  // 00000000000000000000000000100000

  i = 0;
  // toggle nth bit of number
  // number ^= 1UL << n;
  i ^= 1 << 0;
  printf("%d \n",i);

  i ^= 1 << 0;
  printf("%d \n",i);

  // checking a bit
  //bit = (number >> n) & 1U;
  // puts n th bit of number into variable bit
  uint8_t n = 128;
  int bit = (n >> 7) & 1U;
  printf("cb %d \n",bit);

  // changing the n th bit to x (1|0)
  // number ^= (-x ^ number) & (1UL << n);
  n ^= (-0 ^ n) & (1UL << 7);
  bit = (n >> 7) & 1U;
  printf("cb %d \n",bit);


  // OR to set
  uint8_t device_reg;
  device_reg = 0;
  device_reg |= 0x01;    // set bit 0 (0001)
  printf("%X \n",device_reg);

  // check nth bit bit = (device_reg >> n) & 1U;
  device_reg = 1;
  bit = (device_reg >> 1) & 1U;
  printf("%X \n",device_reg);


  // AND to clear
  device_reg &= ~0x01;   // clear bits 1
  //device_reg &= ~0x06;   // clear bits 1 and 2  (0110)
  printf("%X \n",device_reg);


  // Bitwise AND,  extract a set of bits using a mask
  uint8_t mask = 0x0f;   // 00001111b
  uint8_t value = 0x55;  // 01010101b
  uint8_t result = mask & value; // 0000 0101
  printf("%x \n", result);

  // Defining bit masks
  // in c++14 ( supports binary literals )
  const uint8_t mask0 = 0b00000001 ; // represents bit 0
  const uint8_t mask1 = 0b00000010 ; // represents bit 1
  const uint8_t mask2 = 0b00000100 ; // represents bit 2
  const uint8_t mask3 = 0b00001000 ; // represents bit 3
  const uint8_t mask4 = 0b00010000 ; // represents bit 4
  const uint8_t mask5 = 0b00100000 ; // represents bit 5
  const uint8_t mask6 = 0b01000000 ; // represents bit 6

  // hex
  const uint8_t mask10 = 0x1 ; // represents bit 0  0000 0001
  const uint8_t mask11 = 0x2 ; // represents bit 1  0000 0010
  const uint8_t mask12 = 0x4 ; // represents bit 2  0000 0100
  const uint8_t mask13 = 0x8 ; // represents bit 3  0000 1000
  const uint8_t mask14 = 0x10 ; // represents bit 4 0001 0000
  const uint8_t mask15 = 0x20 ; // represents bit 5 0010 0000
  const uint8_t mask16 = 0x40 ; // represents bit 6 0100 0000
  const uint8_t mask17 = 0x80 ; // represents bit 7 1000 0000

  const uint8_t mask20 = 1 << 0 ; // 0000 0001
  const uint8_t mask21 = 1 << 1 ; // 0000 0010
  const uint8_t mask22 = 1 << 2 ; // 0000 0100
  const uint8_t mask23 = 1 << 3 ; // 0000 1000
  const uint8_t mask24 = 1 << 4 ; // ...
  const uint8_t mask25 = 1 << 5 ; //
  const uint8_t mask26 = 1 << 6 ; //
  const uint8_t mask27 = 1 << 7 ; //


  // check if nth bit is set
  //uint8_t result1 = mask13 & value; // 0000 1000 & 0101 0101 = 000 0 0000

  // Arduino example - setting interupt registers
  //    EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
  //    EIMSK |= (1 << INT0);`

   //uint8_t p = ((n >> 1) & 1U) + ((n >> 2) & 1U)  + ((n >> 3) & 1U) + ((n >> 4) & 1U)  + ((n >> 5) & 1U) + ((n >> 6) & 1U) + ((n >> 7) & 1U) + ((n >> 8) & 1U) %2;
  n = 128;
  printf("%d \n",n);
  printf("%d \n",parity_uint8(n));

  n = parity_setbit(n);
  bit = (n >> 7) & 1U;
  printf("cb %d \n",bit);

  n = 126;
  printf("%d \n",n);
  printf("%d \n",parity_uint8(n));

  n = parity_setbit(n);
  bit = (n >> 7) & 1U;
  printf("cb %d \n",bit);


  printf("4bit Nibble Struct\n");

  int2nib.value = 3477;

  char d2h[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  printf("%c",d2h[int2nib.d]);
  printf("%c",d2h[int2nib.c]);
  printf("%c",d2h[int2nib.c]);
  printf("%c",d2h[int2nib.b]);
  printf("%c",d2h[int2nib.a]);

  return 0;
}
