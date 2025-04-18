#include <stdio.h>

#define SIZE 1024

int main() {
    float V[SIZE][3], S[8], U[3];
    int k, i, j;

    // Assuming V, S, and U are initialized elsewhere in the code
    for (k = 0; k < SIZE; k += 8) {  // equivalent to DO K=1,1024,8
        for (i = 0; i < 8; i++) {  // equivalent to DO I=0,7
            S[i] = U[0] * V[k + i][0] + U[1] * V[k + i][1] + U[2] * V[k + i][2];  // S(I) calculation
        }

        for (i = 0; i < 8; i++) {  // equivalent to DO I=0,7
            for (j = 0; j < 3; j++) {  // equivalent to DO J=1,3
                V[k + i][j] = S[i] * U[j];  // V(I+K,J) update
            }
        }
    }

    return 0;
}
