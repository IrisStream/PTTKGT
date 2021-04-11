#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> getArray(istream& in, int &n){
    string line;
    getline(in, line);
    stringstream s(line);
    vector<int> x;
    while(!s.eof()){
        int cur = 0;
        s >> cur;
        x.push_back(cur);
    }
    in >> n;
    return x;
}

#define vit vector<int>::iterator

void UpdateMinCoin(vit coin, int nVal, vit bestState){
    if(nVal > 1){
        UpdateMinCoin(coin - 1, nVal - 1, bestState - 1);
    }
    *bestState = *coin;
}

void exchange(vit coin,vit val, int nVal, int curSum, int n, int numCoin, int minCoin, vit bestState){
    if(*val == 0){
        if(curSum == n && numCoin < minCoin){
            UpdateMinCoin(coin - 1, nVal, bestState - 1);
        }
        return;
    }
    for(int i = 0;i<=n/(*val);i++){
        *coin = i;
        exchange(coin + 1, val + 1, nVal, curSum + i * (*val), n, numCoin + i, minCoin, bestState);
    }
}

void printResult(vit value, vit coin){
    while(*value != 0){
        cout << *value << ": " << *coin << "\n";
        value += 1;
        coin += 1;
    }
}

int main(){
    ifstream input("input_3.txt");
    int n = 0;
    vector<int> value(getArray(input, n));
    input.close();
    vector<int> coin(value.size());
    vector<int> bestState(value.size());
    exchange(coin.begin(), value.begin(), value.size(), 0, n, 0, n, bestState.end());
    printResult(value.begin(), bestState.begin());
    return 0;
}