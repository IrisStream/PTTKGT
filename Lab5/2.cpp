#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

int main(){
    ifstream input("input_2.txt");
    vector<int> coins;
    while(true){
        int value;
        input >> value;
        coins.push_back(value);
        if(value == 1) 
            break;
    }
    int sum;
    input >> sum;
    input.close();

    vector<int> F(sum + 1, 0);
    vector<int> T(sum + 1, 0);
    for(int i = 1;i<=sum;i++){
        F[i] = i;
        for(int j = SZ(coins) - 1;j >= 0;j--){
            if(i < coins[j]) break;
            if(F[i] > F[i - coins[j]] + 1){
                F[i] = F[i - coins[j]] + 1;
                T[i] = j;
            }
        }
    }
    vector<int> count(SZ(coins), 0);
    int tmp = sum;
    while(tmp > 0){
        count[T[tmp]]++;
        tmp = tmp - coins[T[tmp]];
    }
    for(int i = 0;i < SZ(coins);i++){
        printf("%d: %d\n", coins[i], count[i]);
    }
    return 0;
}
