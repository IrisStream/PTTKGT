#include <iostream>
#include <fstream>
using namespace std;

const int INF = 1e7;

int ** allocate2DArray(int n){
    int ** a = new int *[n];
    for(int i = 0;i<n;i++){
        a[i] = new int[n];
    }
    return a;
}

void initAdjMatrix(int ** a,int n){
    for(int i = 0;i<n;i++){
        a[i][i] = 0;
        for(int j = 0;j<i;j++){
            a[i][j] = INF;
            a[j][i] = INF;
        }
    }
}

int ** getAdjMatrix(istream& input, int &n){
    input >> n;
    int ** a = allocate2DArray(n);
    initAdjMatrix(a,n);
    int u, v, cost;
    while(true){
        input >> u >> v >> cost;
        if(u == -1) break;
        u--;
        v--;
        a[u][v] = cost;
        a[v][u] = cost;
    }
    return a;
}

int * initPath(int n){
    int * path = new int[n];
    for(int i = 0;i<n;i++){
        path[i] = i;
    }
    return path;
}

void updateMinPath(int * currentPath, int * minPath, int n, int ** a){
    int cost = 0;
    for(int i = 0;i<n;i++){
        cost += a[currentPath[i]][currentPath[(i + 1) % n]];
    }
    if (cost < minPath[n]){
        minPath[n] = cost;
        for(int i = 0;i<n;i++){
            minPath[i] = currentPath[i];
        }
    }
}

void findMinPath(int * currentPath, int pivot, int n, int ** a, int * minPath){
    if(pivot == n){
        updateMinPath(currentPath, minPath, n, a);
        return;
    }
    for(int i = pivot;i<n;i++){
        swap(currentPath[i], currentPath[pivot]);
        findMinPath(currentPath, pivot + 1, n, a, minPath);
        swap(currentPath[i], currentPath[pivot]);
    }
}

void printResult(int * minPath, int n){
    for(int i = 0;i<n;i++){
        cout << minPath[i] + 1 << " ";
    }
    cout << "\n" << minPath[n] << "\n";
}

int main(){
    ifstream input("input_5.txt");
    int n;
    int ** a = getAdjMatrix(input, n);
    input.close();

    int * currentPath = initPath(n);
    int * minPath = new int[n + 1];
    minPath[n] = INF * n;
    findMinPath(currentPath, 0, n, a, minPath);
    printResult(minPath, n);
    return 0;
}