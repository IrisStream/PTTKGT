#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

int main(){
    ifstream input("input_4.txt");
    int n;
    input >> n;
    int * a = new int[n + 1];
    for(int i = 1;i<=n;i++) 
        input >> a[i];
    input.close();
    int * F = new int[n + 1];
    int * T = new int[n + 1];
    F[0] = 0;
    for(int i = 1;i<=n;i++){
        int jmax = 0;
        for(int j = 1;j<i;j++){
            if(a[i] > a[j] && (jmax == 0 || F[j] > F[jmax])){
                jmax = j;
            }
        }
        F[i] = F[jmax] + 1;
        T[i] = jmax;
    }
    int v = 0;
    for(int i = 1;i<n;i++){
        if(F[i] > F[v])
            v = i;
    }
    
    vector<int> ans;
    while(v > 0){
        ans.push_back(a[v]);
        v = T[v];
    }
    for(int i = SZ(ans) - 1;i>=0;i--)
        cout << ans[i] << " ";
    cout << endl << SZ(ans) << endl;
    return 0;
}
