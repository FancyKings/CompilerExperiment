#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    long long i, sum = 0;
    while (scanf("%lld", &i) != EOF) {
        while (i--) {
            long long k;
            scanf("%lld", &k);
            sum += k;
        }
        printf("%lld", sum);
        sum = 0;
    }
    return 0;
}

