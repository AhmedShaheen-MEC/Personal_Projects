#include <stdint.h>
#include<stdio.h>
 void waitDelay (int x)
{
    uint16_t x;
 for ( x = 0; x < 16000000 ; x--) 
{
asm volatile ( "nop" ); 
}

}
int main()
{
    shortDelay();
}