
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 1000

int dp[MAX][MAX];

int longestPalindromicSubsequence(char s[], int n) {
    int i, j, length;

    /* Every single character is a palindrome of length 1. */
    for (i = 0; i < n; i++)
        dp[i][i] = 1;

    /* Process substrings in increasing order of length. */
    for (length = 2; length <= n; length++) {
        for (i = 0; i <= n - length; i++) {
            j = i + length - 1;

            if (s[i] == s[j]) {
                if (length == 2)
                    dp[i][j] = 2;
                else
                    dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                int x = dp[i + 1][j];
                int y = dp[i][j - 1];

                dp[i][j] = (x > y) ? x : y;
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    char s[MAX + 1];
    int n, result;
    clock_t start, end;
    double time_taken;

    printf("Enter a string (max %d characters): ", MAX);
    scanf("%1000s", s);

    n = strlen(s);

    if (n == 0) {
        printf("String cannot be empty.\n");
        return 1;
    }

    start = clock();
    result = longestPalindromicSubsequence(s, n);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Length of Longest Palindromic Subsequence = %d\n",
           result);

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}
