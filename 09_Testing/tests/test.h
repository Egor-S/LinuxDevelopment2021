#include <stdio.h>
#include "../buf.h"

#define TEST(s, x) if (!(x)) { printf("failed: %s\n", s); return 1; } 
