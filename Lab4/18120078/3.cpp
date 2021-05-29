#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int partition(double * a, int L, int R,int pos){
    double pivot = a[pos];
    swap(a[pos], a[L]);
    pos = L;
    for(int i = L + 1;i<=R;i++){
        if(pivot > a[i]){
            pos++;
            swap(a[pos], a[i]);
        }
    }
    swap(a[L], a[pos]);
    return pos;
}

double selection(double * a,int L,int R,int k){
    int h = L + rand() % (R - L + 1);
    int pos = partition(a, L, R, h);
    if(pos == k)
        return a[pos];
    else if(pos < k)
        return selection(a, pos + 1, R, k);
    else
        return selection(a, L, pos - 1, k);
}

int main(){
    ifstream input("input_3.txt");
    int n;
    input >> n;
    double * a = new double[n];
    for(int i = 0;i<n;i++)
        input >> a[i];
    int k;
    input >> k;
    input.close();

    cout << selection(a,0, n - 1, k - 1) << endl;
    return 0;
}
