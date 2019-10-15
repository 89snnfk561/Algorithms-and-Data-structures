#include <stdio.h>
#include <stdlib.h>
#define LEN 100
//  k = a + b + c  -> 	k - a = b + c  ->	k - a - b = c

int main (){
	int n, k;
	printf("輸入資料個數: ");
	scanf("%d", &n);
	printf("輸入目標值: ");
	scanf("%d", &k);
	
	int A[n+10], B[LEN];
	int C[LEN][LEN];
	int i, j;
	int check = 0;
	for(i = 0; i < n; i++){
		scanf("%d", &A[i]);
		B[A[i]] = k - A[i];
	}
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			C[B[A[i]]][A[j]] = B[A[i]] - A[j];
			if(C[B[A[i]]][B[A[i]]-A[j]] == A[j]){
				if(C[B[A[i]]][A[j]] != B[A[j]] - C[B[A[i]]][A[j]] && C[B[A[i]]][A[j]] != A[j] && B[A[j]] - C[B[A[i]]][A[j]] != A[j]){
					printf("%d %d %d\n", C[B[A[i]]][A[j]], B[A[j]] - C[B[A[i]]][A[j]], A[j]);
					check = 1;
				}
			}
		}
	}
	if(check == 0){
		printf("NO.\n");
	}
	
	return 0;
}
