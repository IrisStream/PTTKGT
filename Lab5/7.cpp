#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

int ** alloc(int nRow, int nCol){
    int ** a = new int*[nRow];
    for(int i = 0;i < nRow;i++){
        a[i] = new int[nCol];
    }
    return a;
}

void trace(int ** F,int ** last, int * w, int n, int W){
    if(W == 0) return;
    trace(F, last, w, last[n][W] - 1, W - w[last[n][W]]);
    cout << last[n][W] - 1 << " ";
}

int main(){
    ifstream input("input_7.txt");
    int W, n;
    input >> W >> n;
    int * w = new int[n + 1];
    int * v = new int[n + 1];
    for(int i = 1;i<=n;i++){
        input >> w[i] >> v[i];
    }
    input.close();

    int ** F = alloc(n + 1, W + 1);
    int ** last = alloc(n + 1, W + 1);
    for(int i = 0;i <= n;i++) F[i][0] = 0;
    for(int j = 0;j <= W;j++) F[0][j] = 0;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=W;j++){
            F[i][j] = F[i-1][j];
            last[i][j] = last[i-1][j];
            if(j >= w[i] && F[i][j] < F[i-1][j - w[i]] + v[i]){
                F[i][j] = F[i-1][j- w[i]] + v[i];
                last[i][j] = i;
            }
        }
    }
    trace(F, last, w, n, W);
    cout << endl << F[n][W] << endl;
    return 0;
}
