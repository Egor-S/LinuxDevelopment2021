#include <stdio.h>
#include <stdlib.h>

typedef struct range {
    int start;
    int stop;
    int step;
    int iter;
} range;

void argparse(int argc, char *argv[], int *start, int *stop, int *step) {
    *start = 0;
    *step = 1;
    switch (argc) {
        case 2:  // N
            *stop = atoi(argv[1]);
            break;
        case 4:  // M N S
            *step = atoi(argv[3]);
        case 3:  // M N
            *start = atoi(argv[1]);
            *stop = atoi(argv[2]);
            break;
        default:
            printf("Usage:\n  %s stop\n  %s start stop [step]\n", argv[0], argv[0]);
            exit(1);
            break;
    }
}

int range_get(range *I) {
    return I->start + I->iter * I->step;
}

void range_init(range *I) {
    I->iter = 0;
}

int range_run(range *I) {
    int value = range_get(I);
    return (I->step > 0) ? (value < I->stop) : (value > I->stop);
}

void range_next(range *I) {
    I->iter += 1;
}

int main(int argc, char *argv[]) {
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for(range_init(&I); range_run(&I); range_next(&I))
        printf("%d\n", range_get(&I));
    return 0;
}
