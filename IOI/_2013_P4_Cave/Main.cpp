
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5001;
int doorsOpened[MAXN];
int placement[MAXN];
int state[MAXN];
int N;
int numTries = 0;

void answer(int S[], int D[]) {
    for(int i = 0; i<N; i++){
        cout << S[i] << " " << D[i] << endl;
    }
        for (int a = 0; a < N; a++) {
                if (S[a] != state[a] || D[a] != placement[a]) {
                        printf("INCORRECT TRY USING %i TRIES\n", numTries);
                        exit(0);
                }
        }
        printf("ANSWER CORRECT USING %i TRIES\n", numTries);
        exit(0);
}


int tryCombination(int S[]) {
    for(int i =0; i<N; i++){
        cout << S[i] << " ";
    }
    cout << endl;
        std::fill(doorsOpened, doorsOpened + MAXN, 0);

        for (int a = 0; a < N; a++) {
                //printf("%i ", S[a]);
                doorsOpened[placement[a]] = (S[a] == state[a]);
        }
        //printf("\n");
        for (int a = 0; a < N; a++) {
                //printf("%i ", doorsOpened[a]);
        }
        //printf("\n");

        numTries++;
        for (int a = 0; a < N; a++) {
                if (!doorsOpened[a]) {
                        //printf("ret @ %i\n", a);
                        return a;
                }
        }
        //printf("ret >%i\n", N);
        return -1;
}

void exploreCave(int N){
    int pos[N], on[N], sol[N];
    fill(pos, pos+N, -1);
    fill(on, on+N, 0);
    for(int i = 0; i<N; i++){
        int times = tryCombination(on);
//        cout << " " << times << endl;
        int delta = 1;
        if(times == -1 || times > i){
            delta = 0;
            for(int j = 0; j<N; j++){
                if(pos[j] == -1){
                    on[j] = 1;
                }
            }
        }
        else{
            for(int j = 0; j<N; j++){
                if(pos[j] == -1){
                    on[j] = 0;
                }
            }
        }
        int l = 1, r = N-i, ans = 0;
        while(l <= r){
            int mid = (l+r)/2, idx = 0;
            for(int j = 0, cnt = 0; j<N && cnt < mid; j++){
                if(pos[j] == -1){
//                    cout << "  " << j << " " << mid << endl;
                    on[j] = delta;
                    cnt++;
                    idx = j;
                }
            }
            times = tryCombination(on);
//            cout << times << endl;
            if(times == -1 || times > i){
                r = mid - 1;
                ans = idx;
                for(int j = 0, cnt = 0; j<N && cnt < mid; j++){
                    if(pos[j] == -1){
                        on[j] = (delta+1)%2;
                        cnt++;
                    }
                }
            }
            else{
                l = mid + 1;
            }
        }
        pos[ans] = i;
        sol[i] = ans;
        on[ans] = delta;
        for(int j = 0; j<N; j++){
            if(pos[j] == -1){
                on[j] = 0;
            }
        }
    }
    answer(on, pos);
}

int main() {
        scanf("%i", &N);
        for (int a = 0; a < N; a++) {
                scanf("%i", &placement[a]); //enter order of switches from 0...N - 1
        }
        for (int a = 0; a < N; a++) {
                scanf("%i", &state[a]); //please only enter 1 or 0 here, otherwise you screw yourself up
        }
        exploreCave(N);
        printf("Your program forgot to call answer(int S[], int D[])");
}
