#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int N = 101;

bool isStar(int * deg, int n);
bool isRing(int * deg, int n);
bool isFullyConnected(int * deg, int n);
int * getDeg(int a[N][N], int n);
void DetectGraphType(int a[N][N], int n);


int main(){
    int a[N][N] = {};
    int n = 10;

    // Ring 
    // for(int i = 0;i<n;i++){
    //     a[i][(i + 1) % n] = 1;
    //     a[(i + 1) % n][i] = 1;
    // }

    //Star (center is Node 0)
    for(int i = 1;i<n;i++){
        a[i][0] = 1;
        a[0][i] = 1;
    }

    //Fully Connected
    // for(int i = 0;i<n;i++){
    //     for(int j = 0;j<i;j++){
    //         a[i][j] = 1;
    //         a[j][i] = 1;
    //     }
    // }

    //Random Graph
    // srand(time(NULL));
    // for(int i = 0;i<n;i++){
    //     for(int j = 0;j<i;j++){
    //         int random = rand() % 2;
    //         a[i][j] = random;
    //         a[j][i] = random;
    //     }
    // }

    DetectGraphType(a, n);
    return 0;
}

//----------------------------------------------------------------

void DetectGraphType(int a[N][N], int n){
    int * deg = getDeg(a, n); //Get degree of each node
    cout << "Do thi: ";
    if(isFullyConnected(deg ,n)){
        cout << "dang luoi day du" << endl;
    }
    else if(isRing(deg,n)){
        cout << "dang vong" << endl;
    }
    else if(isStar(deg, n)){
        cout << "dang sao" << endl;
    }
    else{
        cout << "khong co dang" << endl;
    }
}

int * getDeg(int a[N][N], int n){
    int * deg = new int[n];
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            deg[i] += a[i][j];
        }
    }
    return deg;
}

bool isFullyConnected(int * deg, int n){
    for(int i = 0;i<n;i++){
        if(deg[i] == n - 1){
            continue;
        }
        return false;
    }
    return true;
}

bool isRing(int * deg, int n){
    for(int i = 0;i<n;i++){
        if(deg[i] == 2){
            continue;
        }
        return false;
    }
    return true;
}

bool isStar(int * deg, int n){
    int countFullyConnectedNode = 0;
    for(int i = 0;i<n;i++){
        if(deg[i] == 1) 
            continue;
        if(deg[i] == n - 1){
            countFullyConnectedNode++;
            if(countFullyConnectedNode > 1){
                return false;
            }
        }
        else{
            return false;
        }
    }
    if(countFullyConnectedNode == 1){
        return true;
    }
    return false;
}
