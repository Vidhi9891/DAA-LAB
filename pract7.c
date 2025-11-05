#include <stdio.h>
#include <float.h>

#define MAX 100

int main(){
    int n;

    printf("Enter number of book IDs: ");
    scanf("%d", &n);

    int keys[MAX];
    printf("Enter %d sorted book IDs (keys) :\n", n);
    for(int i = 0; i < n; i++){
        scanf("%d", &keys[i]);
    }

    double p[MAX], q[MAX];
    printf("Enter %d probabilities of successful searches (p[i]):\n", n);
    for(int i = 0; i < n; i++){
        scanf("%lf", &p[i]);
    }

    printf("Enter %d probabilities of unsuccessful searches (q[i]):\n", n + 1);
    for(int i = 0; i <= n; i++){
        scanf("%lf", &q[i]);
    }

    double e[MAX + 2][MAX + 1];
    double w[MAX + 2][MAX + 1];

    for(int i = 1; i <= n + 1; i++){
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for(int length = 1; length <= n; length++){
        for(int i = 1; i <= n - length + 1; i++){
            int j = i + length - 1;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

            e[i][j] = DBL_MAX;

            for(int r = i; r <= j; r++){
                double cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if(cost < e[i][j]){
                    e[i][j] = cost;
                }
            }
        }
    }

    printf("Minimum expected search cost of the Optimal Binary Search Tree: %.4lf\n", e[1][n]);

    return 0;
}
