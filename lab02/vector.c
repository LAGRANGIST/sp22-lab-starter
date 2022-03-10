/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval; // v will not be accessible after the return statement
}

/* Another suboptimal way of creating a vector */
vector_t also_bad_vector_new() {
    /* Create the vector */
    vector_t v;

    /* Initialize attributes */
    v.size = 1;
    v.data = malloc(sizeof(int));
    if (v.data == NULL) {
        allocation_failed();
    }
    v.data[0] = 0;
    return v; // returning a whole struct could be slow
}

/* Create a new vector with a size (length) of 1 and set its single component to zero... the
   right way */
/* TODO: uncomment the code that is preceded by // */
vector_t *vector_new() {
    /* Declare what this function will return */
    vector_t *retval;

    /* First, we need to allocate memory on the heap for the struct */
    retval = malloc(sizeof(vector_t));

    /* Check our return value to make sure we got memory */
    if (retval == NULL) {
        allocation_failed();
    }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
    retval->size = 1;
    retval->data = malloc(retval->size * sizeof(int));

    /* Check the data attribute of our vector to make sure we got memory */
    if (retval -> data == NULL) {
        free(retval);				//Why is this line necessary? Because if we miss it, there will be a memory leak here for unfreed allocated memory 
        allocation_failed();
    }

    /* Complete the initialization by setting the single component to zero */
    retval->data[0] = 0;

    /* and return... */
    return retval; /* UPDATE RETURN VALUE */
}

/* Return the value at the specified location/component "loc" of the vector */
int vector_get(vector_t *v, size_t loc) {

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    if (loc < v->size)
    {
        return v->data[loc];
    }
    return 0;
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
void vector_delete(vector_t *v) {
    // TODO
    if(!v)
    {
        return;
    }

    // if there is a free(v->data) here, it will be a double free
    free (v);

    return;
}

/* Set a value in the vector. If the extra memory allocation fails, call
   allocation_failed(). */
void vector_set(vector_t *v, size_t loc, int value) {
    /* What do you need to do if the location is greater than the size we have
     * allocated?  Remember that unset locations should contain a value of 0.
     */
    if(loc < v->size)
    {
        v->data[loc] = value;
        return;
    }
    // loc is >= size
    int *new_data = malloc((loc - 1) * sizeof(int));
    if(!new_data)
    {
        allocation_failed();
        exit(-1);
    }
    // FIXME
    // Don't use memcpy, it adds a null terminator at the end which may cause mistakes
    // memcpy(new_data, v->data, v->size); // copy the value of the original vector to new_data
    for (int i = 0; i < v->size; i++)
    {
        new_data[i] = v->data[i];
    }
    v->size = loc + 1; // update the size 
    new_data[loc] = value;
    int *temp = v->data; // incase we cannot free the original vector later
    v->data = new_data; // point v->data to the new vector
    free(temp);
    return;
}