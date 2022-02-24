#include <string.h>
#include "ex1.h"

/* Returns the number of times LETTER appears in STR.
There are two different ways to iterate through a string.
1st way hint: strlen() may be useful
2nd way hint: all strings end in a null terminator */
int num_occurrences(char *str, char letter) {
    /* TODO: implement num_occurances */
    char *iter = str;
    int cnt = 0;
    while (*iter != '\0')
    {
        if (*iter == letter)
        {
            cnt++;
        }
        iter++;
    }
    return cnt;
}

/* Populates DNA_SEQ with the number of times each nucleotide appears.
Each sequence will end with a NULL terminator and will have up to 20 nucleotides.
All letters will be upper case. */
void compute_nucleotide_occurrences(DNA_sequence *dna_seq) {
    /* TODO: implement compute_nucleotide_occurances */
    // char *iter = dna_seq->sequence;
    // while (*iter != '\0')
    // {
    //     switch (*iter)
    //     {
    //     case 'A':
    //         dna_seq->A_count++;
    //         break;
    //     case 'C':
    //         dna_seq->C_count++;
    //         break;
    //     case 'G':
    //         dna_seq->G_count++;
    //         break;
    //     case 'T':
    //         dna_seq->T_count++;
    //         break;
    //     default:
    //         break;
    //     }
    // }
    char *iter = dna_seq->sequence;
    dna_seq->A_count = num_occurrences(iter, 'A');
    dna_seq->C_count = num_occurrences(iter, 'C');
    dna_seq->G_count = num_occurrences(iter, 'G');
    dna_seq->T_count = num_occurrences(iter, 'T');
    return;
}
