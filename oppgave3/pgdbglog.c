#include <stdarg.h>
#include <stdio.h>


void debug_logger(
        unsigned long ul_error_type,
        int line_number,
        char *file_name,
        const char *p_format,
        ...
        ) {

    va_list va_args;
    char output_message[256] = {0};
    char *p_mode = (ul_error_type == 1) ? "ERROR":"DEBUG";
    static FILE *fp_log_file = NULL;
    static int call_counter = 1;
    
    
    if(fp_log_file == NULL){
    	fp_log_file = fopen("debug.txt", "w");
    }
    
    
    va_start(va_args, p_format);
    vsnprintf(output_message, 256 - 1, p_format, va_args);
    va_end(va_args);
    
    if(fp_log_file != NULL){
    	fprintf(fp_log_file, "[%s] %03i Line:%i %s\n", p_mode, call_counter, line_number, output_message);
    	fflush(fp_log_file);
    	call_counter++;
    }

    return;
}
