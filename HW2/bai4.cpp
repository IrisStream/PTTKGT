#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

const int N = 10;
int a[N][N];

void printResult(int *p, int n);
int computeIndex(int row, int col, int n);
bool validRow(int * p, int n, int sum);
bool validCol(int * p, int n, int sum);
bool validMainDiag(int * p, int n, int sum);
bool validSecondDiag(int * p, int n, int sum);
bool isMagicSquare(int *p, int n);
void magicSquare(int * p, int pivot, int n);

int main(){
    int * p = (int *)a;
    int n = 3;
    for(int i = 0;i<n * n;i++){
        p[i] = i + 1;
    }
    magicSquare(p, 0, n);
    return 0;
}

//----------------------------------------------------------------

void magicSquare(int * p, int pivot, int n){
    int n2 = n * n;
    if(pivot >= n2 && isMagicSquare(p, n)){
        printResult(p, n);
    }
    for(int i = pivot;i<n2;i++){
        swap(p[i], p[pivot]);
        magicSquare(p, pivot + 1, n);
        swap(p[i], p[pivot]);
    }
}

bool isMagicSquare(int *p, int n){
    int sum = (n * (n * n + 1)) / 2;
    if(validRow(p,n, sum) && validCol(p, n, sum) && validMainDiag(p, n, sum) && validSecondDiag(p, n, sum)){
        return true;
    }
    return false;
}

void printResult(int *p, int n){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cout << p[computeIndex(i, j, n)] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


bool validRow(int * p, int n, int sum){
    int rowSum;
    for(int row = 0;row < n; row++){
        rowSum = 0;
        for(int col = 0; col < n;col++){
            rowSum += p[computeIndex(row, col, n)];
        }
        if(rowSum != sum) return false;
    }
    return true;
}

bool validCol(int * p,int n, int sum){
    int colSum;
    for(int col = 0;col < n;col++){
        colSum = 0;
        for(int row = 0;row < n;row++){
            colSum += p[computeIndex(row, col, n)];
        }
        if(colSum != sum) return false;
    }
    return true;
}

bool validMainDiag(int * p, int n, int sum){
    int mainDiagSum = 0;
    for(int row = 0;row < n;row++){
        mainDiagSum += p[computeIndex(row, row, n)];
    }
    return mainDiagSum == sum;
}

bool validSecondDiag(int * p, int n, int sum){
    int secondDiagSum = 0;
    for(int row = 0;row < n;row++){
        secondDiagSum += p[computeIndex(row, n - row - 1, n)];
    }
    return secondDiagSum == sum;
}

int computeIndex(int row, int col, int n){
    return row * n + col;
}
