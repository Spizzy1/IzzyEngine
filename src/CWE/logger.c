#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "logger.h"
void cwlog(const char* Source, int mode, const char *format, ...){
    int cx = 0;
    const int max_len = 255;
    const int max_inf_len = 64;
    char buffer [max_inf_len+max_len];
    va_list args;
    va_start(args, format);
    char InfoStr [max_inf_len];  
    int cix = 0;
    switch (mode){
        case LOGGER_INFO:
            cix = snprintf(InfoStr, max_inf_len, GRN "[INFO/%s]:" RESET, Source);
            break;
        case LOGGER_WARN:
            cix = snprintf(InfoStr, max_inf_len, YEL "[WARNING/%s]:" RESET, Source);
            break;
        case LOGGER_SETUP:
            cix = snprintf(InfoStr, max_inf_len, BLU "[SETUP/%s]:" RESET, Source);
            break;
        case LOGGER_ERROR:
            cix = snprintf(InfoStr, max_inf_len, RED "[ERROR/%s]:" RESET, Source);
            break;
        default:
            printf(RED "Invalid logger mode" RESET ": max value is %x got %x\n", LOGGER_ERROR, mode);
            return;
    }
    
    if (cix < 0 || cix >= max_inf_len){
        printf(RED "Invalid info string, maybe your source string was too large? (%x characters max you tried to output: %x (including formatting characters))\n" RESET, max_inf_len, cix); 
        return;

    }
    memcpy(buffer, InfoStr, cix*sizeof(char));
    cx = snprintf(buffer+cix, max_len, format, args);

    if (cx < 0 || cix >= max_inf_len){
        printf(RED "Error message buffer overflow (outputting too much data? Max data string size: %x, this string size: %x)\n" RESET, max_len, cx); 
        return;
    }
    puts(buffer);

}
