#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

template<typename T>
T ** alloc(int n){
    T ** a = new T*[n];
    for(int i = 0;i < n;i++){
        a[i] = new T[n];
        for(int j = 0;j < n;j++){
            a[i][j] = 0;
        }
    }
    return a;
}

void inorder(int ** root, int * key, int left, int right){
    if(left > right) return;
    int k = root[left][right];
    inorder(root, key, left, k - 1);
    cout << key[k] << " ";
    inorder(root, key, k + 1, right);
}

int main(){
    ifstream input("input_5.txt");
    int n;
    input >> n;
    int * key = new int[n + 1];
    double * prob = new double[n + 1];
    double * sum = new double[n + 1];
    for(int i = 1;i <= n;i++){
        input >> key[i] >> prob[i];
    }
    input.close();

    sum[0] = 0.0;
    for(int i = 1;i <= n;i++){
        sum[i] = sum[i - 1] + prob[i];
    }

    double ** F = alloc<double>(n + 2);
    int ** root = alloc<int>(n + 2);

    for(int len = 0;len < n;len++){
        for(int i = 1;i<=n - len;i++){
            int j = i + len;
            int kMin = -1;
            for(int k = i;k<=j;k++){
                if(kMin == -1 || F[i][kMin - 1] + F[kMin + 1][j] > F[i][k - 1] + F[k + 1][j]){
                    kMin = k;
                }
            }
            F[i][j] = F[i][kMin - 1] + F[kMin + 1][j] + sum[j] - sum[i-1];
            root[i][j] = kMin;
        }
    }
    cout << root[1][n] << endl;
    inorder(root, key, 1, n);
    return 0;
}
