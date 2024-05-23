/*

Author: Kumar Shubham

Given two strings, S1 and S2, the task is to find the length of the Longest Common Subsequence, i.e. longest subsequence present in both of the strings. 

*/


#include <stdio.h>
#include <string.h>

#define max(a,b) ((a > b) ? a : b)

int tab[100][100];

// using Recursion
int lcs_recursion(char *s1, char *s2, int i, int j) {
    if(i == 0 || j == 0) {
        return 0;
    }

    if(s1[i-1] == s2[j-1]) {
        return 1 + lcs_recursion(s1, s2, i-1, j-1); 
    }

    return max(lcs_recursion(s1, s2, i, j-1), lcs_recursion(s1, s2, i-1, j));
}

// 

int lcs_top_down(char *s1, char *s2, int i, int j) {

    if(i == 0 || j == 0) {
        return 0;
    }

    if(tab[i][j] != -1) {
        return tab[i][j];
    }

    if(s1[i-1] == s2[j-1]) {
        tab[i][j] = 1 + lcs_top_down(s1, s2, i-1, j-1);
        return tab[i][j];
    }

    tab[i][j] = max(lcs_top_down(s1, s2, i-1, j), lcs_top_down(s1, s2, i, j-1));
    return tab[i][j];
}

int lcs_top_up(char *s1, char *s2, int m, int n) {

    int i,j;
    int t[m+1][n+1];

    for(i=0;i<=m;i++) {
        for(j=0;j<=n;j++) {
            if(i==0 || j== 0) {
                t[i][j] = 0;
            }

            else if(s1[i-1] == s2[j-1]) {
                t[i][j] = 1 + t[i-1][j-1];
            }

            else {
                t[i][j] = max(t[i-1][j], t[i][j-1]);
            }
        }
    }

    i=m, j=n;
    int index = t[m][n];
    char lcs[index+1];

    lcs[index] = '\0';

    while(i>0 && j>0) {
        if(s1[i-1] == s2[j-1]){
            lcs[--index] = s1[i-1];
            i--;
            j--; 
        }

        else if(t[i-1][j] > t[i][j-1]){
            i--;
        }
        else{
            j--;
        }
    }
    
    printf("Longest common Sub Sequence %s\n", lcs);
    return t[m][n];
}


int main(int argc, char *argv[]) {

    // char s1[] = "bd";
    // char s2[] = "abcd";

    char s1[] = "AGGTAB";
    char s2[] = "GXTXAYB";

    int m = strlen(s1);
    int n = strlen(s2);

    memset(tab, -1, sizeof(tab));

    printf("Longest common sequence: %i\n", lcs_recursion(s1, s2, m, n));

    printf("Longest common sequence: %i\n", lcs_top_down(s1, s2, m, n));

    printf("Longest common sequence: %i\n", lcs_top_up(s1, s2, m, n));
    return 0;
}