#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

//Stdout colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//Modes
#define LOGGER_INFO 0
#define LOGGER_WARN 1
#define LOGGER_SETUP 2
#define LOGGER_ERROR 3 

#define max_inf_len 63
#define max_len 255
#define tot_len 318

void cwlog(const char* Source, int mode, const char *format, ...);

struct Logger {
    const char* name;
    int prints;
    
};
#endif
