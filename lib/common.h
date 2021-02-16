#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

    typedef signed char         s8_t;
    typedef signed short        s16_t;
    typedef signed int          s32_t;
    typedef signed long long    s64_t;

    typedef unsigned char       u8_t;
    typedef unsigned short      u16_t;
    typedef unsigned int        u32_t;
    typedef unsigned long long  u64_t;

#ifdef __cplusplus
}
#endif
typedef unsigned char bool;

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

uint8_t n_to_ascii(int8_t c);
void clear_buff(char *buff, uint32_t buff_len);
void error_handler(void);

#endif /* _COMMON_H */


