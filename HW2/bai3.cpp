#include <iostream>
using namespace std;

bool getBit(int x, int pos);
void printResult(int * a,int n, int state);
void partition(int * a,int n);

int main(){
    int a[] = {1, 2, 3, 4};
    int n = sizeof(a)/sizeof(int);
    partition(a, n);
    return 0;
}

//--------------------------------

void partition(int * a,int n){
    int sum = 0;
    for(int i = 0;i < n;i++){
        sum += a[i];
    }
    int currentSum = 0;
    for(int state = 1;state <= (1 << n);state++){
        currentSum = 0;
        for(int i = 0;i<n;i++){
            if(getBit(state, i) == true){
                currentSum += a[i];
            }
        }
        if(currentSum * 2 == sum){
            printResult(a, n, state);
        }
    }
}

void printResult(int * a,int n, int state){
    for(int i = 0;i < n;i++){
        if(getBit(state, i) == true) cout << a[i] << " ";
    }
    cout << " <---> ";
    for(int i = 0;i < n;i++){
        if(getBit(state, i) == false) cout << a[i] << " ";
    }
    cout << endl;
}

bool getBit(int x, int pos){
    return (x >> pos) & 1;
}

