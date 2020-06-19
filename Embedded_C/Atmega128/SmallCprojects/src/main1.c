   #include<stdint.h>
    uint8_t setBits  (uint8_t var)
{
    /* Left shift 1, n times and perform bitwise OR with number */

    var = (1 << 4) | var;
    var = (1 << 6) | var;

    printf(" \nBit set successfully.\n");

    printf("Number after setting %dth bit and %dth bit: %d (in decimal)\n", 4,6, var);
    return var;
    }

uint8_t clearBits  (uint8_t var)
{
    /* Left shift 1, n times and perform bitwise AND NOT with number */

    var =var & (~(1 << 2)) ;
    var =var & (~(1 << 7)) ;

    printf("Bit set successfully.\n");

    printf("Number after clearing %dth bit and %dth bit: %d (in decimal)\n", 2,7, var);
    return var;
    }

    uint8_t toggleBits  (uint8_t var)
{
    /* Left shift 1, n times and perform bitwise XOR with number */

    var = (1 << 3) ^ var;
   

    printf("Bit set successfully.\n");

    printf("Number after toggling %dth bit: %d (in decimal)\n", 3, var);
    return var;
    }

  uint8_t mirroring (uint8_t number)
 {  
    uint8_t reversed = 0;
    int i = 0;
    for(i = 0; i < 8; i++)//loop to 8 for 8 bits 
    {
        if((1 << i) & number)//doesn't work if changed to == 1, only checks 'true'
        {
            reversed |= (1 << ((8 -1)-i)) ;
        }
    }
    printf("Number after mirroring: %d",reversed); 
    
    return reversed;
}
int main()
{
   uint8_t x;
  
   scanf("%d",&x);
  
   setBits(x);
  

    return 0;
}