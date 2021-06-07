#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

int ** Alloc(int n){
    int ** a = new int*[n];
    for(int i = 0;i<n;i++){
        a[i] = new int[n];
    }
    return a;
}

void track(int ** a,int ** F, int row, int col){
    if(row == 1){
        cout << a[row][col];
        return;
    }
    if(F[row - 1][col] > F[row - 1][col - 1]){
        track(a, F, row - 1, col);
    }
    else{
        track(a, F, row - 1, col - 1);
    }
    cout << " " << a[row][col];
}

int main(){
    ifstream input("input_1.txt"); 
    int n;
    input >> n;
    int ** a = Alloc(n + 1);
    int ** F = Alloc(n + 1);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=i;j++){
            input >> a[i][j];
            F[i][j] = a[i][j] + max(F[i-1][j-1], F[i-1][j]);
        }
    }
    input.close();

    int v = 1;
    for(int i = 1;i<=n;i++){
        if(F[n][i] > F[n][v])
            v = i;
    }
    cout << F[n][v] << endl;
    track(a, F, n, v);
    cout << endl;
    return 0;
}
