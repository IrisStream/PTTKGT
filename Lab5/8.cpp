#include <iostream>
#include <fstream>
#include <vector>
#include <memory.h>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()
#define oo 1000000000
#define next somerandomthing

int n;
int ** a;
int ** F;
int ** next;

int ** alloc(int nRow, int nCol){
    int ** w = new int*[nRow];
    for(int i = 0;i<nRow;i++){
        w[i] = new int[nCol];
        memset(w[i], 255, sizeof(int) * nCol);
    }
    return w;
}

int calc(int last, int passed){
    if(F[last][passed] != -1){
        return F[last][passed];
    }

    if(passed == 0){
        F[last][passed] = a[last][0]; 
        next[last][passed] = 0;
        return F[last][passed];
    }
    int ans = oo;
    int tmp = -1;
    for(int i = 1; i < n;i++){
        if(((passed >> i) & 1) && (a[last][i] != oo)){
            if(ans > calc(i, passed ^ (1 << i)) + a[last][i]){
                ans = calc(i, passed ^ (1 << i)) + a[last][i];
                tmp = i;
            }
        }
    }
    F[last][passed] = ans;
    next[last][passed] = tmp;
    return F[last][passed];
}

void trace(int cur, int passed){
    if(cur == 0){
        cout << "1 ";
        return;
    }
    int tmp = next[cur][passed];
    trace(tmp, passed ^ (1 << tmp));
    cout << cur + 1 << " ";
}

int main(){
    ifstream input("input_8.txt");
    input >> n;
    a = alloc(n + 1, n + 1);
    F = alloc(n + 1, 1 << n);
    next = alloc(n + 1, 1 << n);
    for(int i = 0;i<n;i++){
        a[i][i] = 0;
        for(int j = 0;j<i;j++){
            a[i][j] = oo;
            a[j][i] = oo;
        }
    }
    while(true){
        int u,v,c;
        input >> u;
        if(u == -1) break;
        input >> v >> c;
        u--;
        v--;
        a[u][v] = c;
        a[v][u] = c;
    }
    input.close();

    int ans = 1;
    int all = (1 << n) - 2;
    for(int i = 1;i<n;i++){
        if(calc(ans, all ^ (1 << ans)) + a[ans][0] > calc(i, all ^ (1 << i)) + a[i][0])
            ans = i;
    }

    trace(ans, all ^ (1 << ans));
    cout << endl << calc(ans, all ^ (1 << ans)) + a[ans][0] << endl;
    return 0;
}
