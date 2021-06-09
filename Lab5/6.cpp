#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

bool ** alloc(int nRow, int nCol){
    bool ** a = new bool*[nRow];
    for(int i = 0;i<nRow;i++){
        a[i] = new bool[nCol];
    }
    return a;
}

vector<int> ans;

void trace(bool ** F, bool ** isLast,int * a, int n,int k){
    if(k == 0){
        for(int i = SZ(ans) - 1;i>=0;i--){
            cout << ans[i] << " ";
        }
        cout << endl;
        return;
    }
    for(int i = 1;i<=n;i++){
        if(isLast[i][k]){
            ans.push_back(a[i]);
            trace(F, isLast, a, i - 1, k - a[i]); 
            ans.resize(SZ(ans) - 1);
        }
    }
}

int main(){
    ifstream input("input_6.txt");
    int n;
    input >> n;
    int * a = new int[n + 1];
    for(int i = 1; i<=n;i++)
        input >> a[i];
    int k;
    input >> k;
    input.close();

    bool ** F = alloc(n + 1, k + 1);
    for(int i = 0;i<=n;i++){
        F[i][0] = true;
    }
    for(int j = 1;j<=k;j++){
        F[0][j] = false;
    }

    bool ** isLast = alloc(n + 1, k + 1);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j <= k;j++){
            int tmp = 0;
            if(j >= a[i]){
                tmp  = F[i-1][j - a[i]]; 
            }
            F[i][j] = F[i-1][j] || tmp;
            isLast[i][j] = tmp;
        }
    }
    trace(F, isLast, a, n, k);
    return 0;
}
