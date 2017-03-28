/*
 * Testcase_1_comment1
 *
 *
 */
/*
   Testcase_1_comment2

 */

// Testcase_1_comment3

#pragma source off
int main () 
{
    char a = 'a';

#pragma source on
    double b = 0.01;

#pragma token off
    int i;

#pragma token on
    int c[2];
    for (i = 0; i < 2; i++) {
            c[i] = i;
        }

    printf("c[1]=%d\n", c[1]);
    if (c[0] > 1){ 
            b = b * 99.0e-10; 
        }

    return 0;
}
