// Problem : CCO '03 P5 - Longest Substring
// Contest : DMOJ
// URL : https://dmoj.ca/problem/cco03p5
// Memory Limit : 3 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <cstdio>

const int M = 65536;
unsigned short ans[M];
bool tkn[M];
unsigned short arr[M];
int i;

int main(){
	int l = 1, r = 0;
	int al = 0, ar = -1;
	int ptrl = 1, ptrr = 0;
	while(1){
		r++;
		//cin >> arr[r%M];
		scanf("%d", &arr[r%M]);
		if(!arr[r%M]){
			break;
		}
		while(tkn[arr[r%M]]){
			tkn[arr[l%M]] = 0;
			l++;
		}
		tkn[arr[r%M]] = 1;
		if(r - l + 1 > ar - al + 1){
			if(ar < l){
				ptrl = 1;
				ptrr = 0;
				for(i = l; i<=r; i++){
					ans[++ptrr] = arr[i%M];
				}
			}
			else{
				i = l - al;
				while(i--){
					ptrl++;
				}
				for(i = ar+1; i<=r; i++){
					ptrr++;
					ans[ptrr%M] = arr[i%M];
				}
			}
			al = l;
			ar = r;
		}
	}
	for(i = ptrl; i<=ptrr; i++){
		printf("%d\n", ans[i%M]);
	}
}