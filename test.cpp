#include <iostream>
#include <memory.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    int * a = new int[n];
    memset(a, 255, sizeof(int) * n);
    for(int i = 0;i<n;i++){
        cout << a[i] << " ";
    }
    return 0;
}
