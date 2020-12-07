#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <string.h>


// Am not sure if we are actually.
// Exchanging task between threads.
// Since the worker thread is not killed til the end of file or outside the loop.
// But am very sure that thread synchronization is in place.


int main(int argc, char *argv[]){

    static sem_t worker_thread;
    char data_buffer[11];
    FILE *file_to_read;
    char file_name[120];

    strcpy(file_name, argv[1]);

    for(int i = 0; i < strlen(argv[1]); i++){
        if((file_name[i] < 0)||(file_name[i] > 127)){
            printf("Non ascii file name allowed\n");
            return 1;
        }
    }

    file_to_read = fopen(argv[1], "r");

    if(file_to_read == NULL){
        printf("Could not open the file\n");
        return 1;
    }

    sem_init(&worker_thread, 1, 1);

    // Offset to fseek, also works as char counter
    int offset = 0;

    while(!feof(file_to_read)){

        // Block other(if any) worker_thread operations until post is called.
        sem_wait(&worker_thread);
        fseek(file_to_read, offset, SEEK_SET);
        // Will always copy max 10 chars 11th index is reserved for zero termination.
        fgets(data_buffer, 10, file_to_read);
        sem_post(&worker_thread);
        offset += strlen(data_buffer);

        if(strlen(data_buffer) > 10){
            printf("Overflowed\n");
            fclose(file_to_read);
            sem_destroy(&worker_thread);
            return 1;
        }

        for(int i = 0; i < strlen(data_buffer); i++){
            if((data_buffer[i] < 0)||(data_buffer[i] > 127)){
                printf("Non ascii content allowed\n");
                fclose(file_to_read);
                sem_destroy(&worker_thread);
                return 1;
            }
        }

        printf("%s\n", data_buffer);
        memset(data_buffer, 0, sizeof(data_buffer));
    }

    sem_destroy(&worker_thread);

    fclose(file_to_read);
    printf("Characters read: %i\n", offset - 1);
    return 0;
}


