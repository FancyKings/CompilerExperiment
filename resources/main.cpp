#include <stdio.h>

int main() {
    long i, sum = 0;
    while (scanf("%ld", &i) != EOF) {
        while (i--) {
            long k;
            scanf("%ld", &k);
            sum += k;
        }
        printf("%ld", sum);
        sum = 0;
    }
    return 0;
}
