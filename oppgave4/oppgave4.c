#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "include/oppgave4.h"

int main(int argc, char *argv[]){

    ProcessCreditcardPayment(1231, "42421232", "12/22", "something"); // Valid with cashback
    ProcessCreditcardPayment(1231, "42421233", "04/19", "something"); // Valid but expired
    ProcessCreditcardPayment(1231, "42429932", "12/21", "something"); // Valid with no cashback
    ProcessCreditcardPayment(1231, "43218181", "04/23", "something"); // Invalid

}

int Backendprocesspayment(int a, int64_t c, CCD *p, const char *n, int b){
    printf("Successfully processed card information.\n");
    return 0;
}

int CheckExpiryDate(time_t card_expiry_date, time_t current_time){
    if(card_expiry_date < current_time){
        printf("This card has been expired please renew your card.\n");
        return 1;
    }
    return 0;
}

int ProcessCreditcardPayment(int a, char* c, char* e, char* p) {

    int64_t llCreditcard = 0; /* C99 type, our compiler supports this... */
    char *i = (char*)c;
    int j = 0; // for the loop
    char month[3];
    char year[3];
    struct tm *card_expiry_date = malloc(sizeof(struct tm));
    time_t raw_time;
    time(&raw_time);
    CCD *pc, *cc = malloc(sizeof(CCD));


    if (!cc)
        exit(1);
    else
        pc = cc;


    memset(cc, 0, sizeof(CCD));
    memset(month, 0, sizeof(month));
    memset(year, 0, sizeof(year));
    memset(card_expiry_date, 0, sizeof(struct tm));
    /* Create 4 linked structures that holds one 4 digit
       segment of cardnumber: */

    while (i[0]) {
        pc->digit[j++] = i++[0];
        if (strlen(pc->digit) == 4) {
            pc->p = (CCD*)malloc(sizeof(CCD));
            if (!pc->p) exit(1);
            else {
                memset(pc->p, 0, sizeof(CCD));
                pc = pc->p;
                j=0;
            }
        }
    }

    /* Check that card starts with 4242, if not card is from
       another bank so we fail: */
    if (strcmp(cc->digit, "4242") != 0) {
        printf("This card is not from this bank!\n");
        // not free-ing everything
        // free(cc);
        while(cc != NULL){
            CCD *next_p = cc->p;
            free(cc);
            cc = next_p;
        }
        free(card_expiry_date);
        return 6;
    }

    memcpy(&month, &e[0], 2);
    memcpy(&year, &e[3], 2);

    // This wont apply to year, because it can be 00
    if(atoi(month) == 0){
        printf("Invalid month\n");

        while(cc != NULL){
            CCD *next_p = cc->p;
            free(cc);
            cc = next_p;
        }

        free(card_expiry_date);
        return 1;
    }



    card_expiry_date->tm_mday = 1;
    card_expiry_date->tm_mon = atoi(month) - 1;
    // tm_year is year since 1900.
    // Offset with 100 + year_input.
    // Not very flexible :( but it will have to do
    card_expiry_date->tm_year = atoi(year) + YEAR_OFFSET;

    time_t converted_card_expiry_date = mktime(card_expiry_date);

    if(CheckExpiryDate(converted_card_expiry_date, raw_time) == 1){

        while(cc != NULL){
            CCD *next_p = cc->p;
            free(cc);
            cc = next_p;
        }

        free(card_expiry_date);
        return 1;
    };

    /* Calculate the cardnumber as a 64 bit integer: */
    for (j = 12, pc = cc; pc; pc = pc->p, j-=4) {
        pc->convert = atoi(pc->digit);
        llCreditcard += ((int64_t)pc->convert) * pow(10, j);
    }
    /* If next section is 123x it is a bonus card with cash-back, we
       send type (x) to backend below: Set j to the type of bonus card */


   
    if (strncmp(cc->p->digit, "123", 3) == 0) {
        // This line can either cause SIGFPE or undefined behaviour since it can read something out of bound
        // The latter happends when denominator is not 0
        //j = cc->p->digit[cc-p->digit[3] / ((cc->p->digit[3]-'0') % 9)];
        j = cc->p->digit[3]-'0';
    } else {
        printf("This card does not have cash-back.\n");
    }

    /* Call backend function: */

    // Calling free(cc); is not enough
    // We have to free the whole list to deallocate all memory that were allocated in the loop
    Backendprocesspayment(a, llCreditcard, cc, e, j);
    while(cc != NULL){
        CCD *next_p = cc->p;
        free(cc);
        cc = next_p;
    }

    free(card_expiry_date);
    return 0;
}

