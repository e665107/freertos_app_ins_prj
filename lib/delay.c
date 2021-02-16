#include "delay.h"


void delayus(uint32_t n)  //M/
{
    uint32_t  temp;

    while (n--)
        for (temp = 0; temp < 8 ; temp++)
            ;
}


void delayms(uint32_t n)        //M/
{
    uint8_t i;

    for (i = 0; i < n; i++)
    {
        delayus(803);  //1000us @72M
    }
}
