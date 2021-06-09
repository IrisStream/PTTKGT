#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

int ** Alloc(int nRow, int nCol){
    int ** a = new int*[nRow];
    for(int i = 0;i < nRow;i++){
        a[i] = new int[nCol];
    }
    return a;
}

void trace(string a, int i, string b, int j, int ** F){
    if(a[i] == b[j]){
        trace(a, i - 1, b, j - 1, F);
        cout << a[i];
    }
    else if(F[i][j-1] > F[i-1][j]){
        trace(a, i, b, j - 1, F);
    }
    else if(F[i-1][j] > F[i][j-1]){
        trace(a, i - 1, b, j, F);
    }
}

int main(){
    ifstream input("input_3.txt");
    string a, b;
    input >> a >> b;
    input.close();
    int nA = SZ(a);
    int nB = SZ(b);
    a = " " + a;
    b = " " + b;

    int ** F = Alloc(nA + 1, nB + 1);

    for(int i = 1;i<=nA;i++){
        for(int j = 1;j<=nB;j++){
            if(a[i] == b[j]){
                F[i][j] = F[i-1][j-1] + 1;
            }
            else{
                F[i][j] = max(F[i-1][j], F[i][j-1]);
            }
        }
    }
    trace(a, nA, b, nB, F);
    cout << endl;
    return 0;
}
