#include <stdio.h>

int sum_to_n(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = sum + i;
    }
    return sum;
}

int main() {
    int n;
    int result;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Error: n must be 1 or greater\n");
    } else {
        result = sum_to_n(n);
        printf("The sum from 1 to %d is %d\n", n, result);
    }

    return 0;
}
