#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int N = 20;

bool col[N];
bool firstDiag[N * 2];
bool secondDiag[N * 2];
vector<int *> states;


void find(int * curState, int i, int n){
    if(i == n){
        int * newState = new int[n];
        memcpy(newState, curState, n * sizeof(int));
        states.push_back(newState);
    }
    for(int j = 0;j<n;j++){
        if(!(col[j] && firstDiag[i - j + n - 1] && secondDiag[i + j])){
            col[j] = true;
            firstDiag[i - j + n - 1] = true;
            secondDiag[i + j] = true;
            curState[i] = j;
            find(curState, i + 1, n);
            col[j] = false;
            firstDiag[i - j + n - 1] = false;
            secondDiag[i + j] = false;
        }
    }
}

void printResult(int n){
    cout << states.size() << endl;
    for(int i = 0;i<states.size();i++){
        for(int j = 0;j<n;j++){
            cout << states[i][j] + 1 << " ";
        }
        cout << endl;
    }
}

int main(){
    ifstream input("input_1.txt");
    int n;
    input >> n;
    input.close();
    int * curState = new int[n];
    find(curState, 0, n);
    printResult(n);
    return 0;
}