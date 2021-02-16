#include "common.h"



/* c为0-9 */
uint8_t n_to_ascii(int8_t c)
{
    return (uint8_t)(0x30 + c);
}


void clear_buff(char *buff, uint32_t buff_len)
{
    uint32_t i;
    for (i = 0; i < buff_len; i++)
        buff[i] = 0;
}


/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void error_handler(void)
{
    while (1)
    {
    }
}
