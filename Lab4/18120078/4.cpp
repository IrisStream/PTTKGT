#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int interpolateSearch(double * a,int L, int R,double v){
    if(L >= R)
        return -1;
    int x = L + int(((v - a[L]) * (R - L)) / (a[R] - a[L]));
    if(a[x] == v)
        return x;
    else if(a[x] > v)
        return interpolateSearch(a, L, x - 1, v);
    else 
        return interpolateSearch(a, x + 1, R, v);
}

int main(){
    ifstream input("input_4.txt");
    int n;
    input >> n;
    double * a = new double[n];
    for(int i = 0;i < n;i++)
        input >> a[i];
    double v;
    input >> v;
    input.close();

    cout << interpolateSearch(a, 0, n-1, v) << endl;
    return 0;
}
