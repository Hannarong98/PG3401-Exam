#ifndef OPPGAVE4_H

#include <stdint.h>
#include <time.h>

#define YEAR_OFFSET 100

#pragma pack(1)
typedef struct _CCD {
    char digit[5];
    int convert;
    struct _CCD* p;
} CCD;
#pragma pack()

int Backendprocesspayment(int a, int64_t c, CCD* p, const char* n, int b);

int ProcessCreditcardPayment(int a, char* c, char* e, char* n);

int CheckExpiryDate(time_t card_expiry_date, time_t current_time);

#endif // OPPGAVE4_H
