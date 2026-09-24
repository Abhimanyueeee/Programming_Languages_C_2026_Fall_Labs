#include <stdio.h>

int is_prime(int n) {
    int i;

    if (n < 2) {
        return 0;
    }

    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Error: n must be 2 or greater\n");
    } else {
        printf("Primes up to %d:\n", n);
        for (int i = 2; i <= n; i++) {
            if (is_prime(i) == 1) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}
