#include "test.h"

int main() {
	float *a = 0;
	TEST("clear empty", buf_size(a) == 0);
    TEST("clear no-op", a == 0);
	return 0;
}
