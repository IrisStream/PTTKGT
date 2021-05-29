#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int sumMax(int * a,int L,int R, int& i, int& j){
    if(L == R)
        return max(a[L], 0);

    int mid = (L + R) / 2;
    int iL, jL;
    int maxLeft = sumMax(a, L, mid, iL, jL);
    int ans = maxLeft;
    i = iL;
    j = jL;

    int iR, jR;
    int maxRight = sumMax(a, mid + 1, R, iR, jR);
    if(maxRight > ans){
        ans = maxRight;
        i = iR;
        j = jR;
    }

    int iM, jM;
    int tmp = 0;
    int maxLpartS = 0;
    for(int t = mid;t>=0;t--){
        tmp += a[t];
        if(maxLpartS < tmp){
            maxLpartS = tmp;
            iM = t;
        }
    }

    tmp = 0;
    int maxRpartS = 0;
    for(int t = mid + 1;t <= R;t++){
        tmp += a[t];
        if(maxRpartS < tmp){
            maxRpartS = tmp;
            jM = t;
        }
    }

    if(maxLpartS + maxRpartS > 0 && maxLpartS + maxRpartS > ans){
        ans = maxLpartS + maxRpartS;
        i = iM;
        j = jM;
    }
    return ans;
}

int main(){
    ifstream input("input_3.txt");
    int n;
    input >> n;
    int * a = new int[n];
    for(int i = 0;i<n;i++) input >> a[i];
    input.close();

    int L, R;
    int ans = sumMax(a, 0, n - 1, L, R);
    for(int i = L;i<=R;i++){
        cout << a[i] << " ";
    }
    cout << endl << L << " " << R << endl;
    cout << ans << endl;
    return 0;
}
