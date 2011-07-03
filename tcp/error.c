#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */
#include "error.h"

void tcp_error(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
