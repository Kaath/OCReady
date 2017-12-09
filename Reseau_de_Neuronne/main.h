#ifndef _NN_MAIN_H_
#define _NN_MAIN_H_

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <err.h>

# include "operations.h"

int learn(float inputs[], char expectedoutput);

char result(float inputs[]);

#endif
