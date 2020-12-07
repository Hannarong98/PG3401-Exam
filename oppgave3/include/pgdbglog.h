#ifndef PGDBGLOG_H
#define PGDBGLOG_H

#define log_debug(...) debug_logger(0, __LINE__, __FILE__, __VA_ARGS__)
#define log_error(...) debug_logger(1, __LINE__, __FILE__, __VA_ARGS__)


void debug_logger(unsigned long ul_error_type, int line_number, const char *file_name, char *p_format, ...);

#endif //PGDBGLOG_H
