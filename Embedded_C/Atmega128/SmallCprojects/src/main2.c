   #include<stdint.h>
    int setBits  (uint8_t var)
{
    /* Left shift 1, n times and perform bitwise OR with number */

    var = (1 << 4) | var;
    var = (1 << 6) | var;

  

    printf("%d\n", var);
    return var;
    }

int clearBits  (uint8_t var)
{
    /* Left shift 1, n times and perform bitwise AND NOT with number */

    var =var & (~(1 << 2)) ;
    var =var & (~(1 << 7)) ;

    

    printf("%d\n",var);
    return var;
    }

    int toggleBits  (uint8_t var)
{
    /* Left shift 1, n times and perform bitwise XOR with number */

    var = (1 << 3) ^ var;
   

   

    printf("%d\n", var);
    return var;
    }

  unsigned int mirroring (uint8_t number)
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
    printf("%d\n",reversed); 
    
    return reversed;
}
int main()
{
   unsigned int x;
  
   scanf("%d",&x);
   mirroring(x);
   setBits(x);
   clearBits(x);
   toggleBits(x);
  

    return 0;
}