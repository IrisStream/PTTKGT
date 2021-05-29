#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;


#define SZ(x) (int)x.size()

struct Answer{
    vector<int> cnt;
    int sum;

    Answer(){}

    Answer(int n, int pos, int value){
        cnt = vector<int>(n, 0);
        cnt[pos] = value;
        sum = value;
    }

    friend Answer operator+(const Answer& a, const Answer& b);
    friend bool operator<(const Answer& a, const Answer& b);
};

Answer operator+(const Answer& a, const Answer& b){
    Answer c;
    c.cnt = vector<int>(SZ(a.cnt),0);
    c.sum = a.sum + b.sum;
    for(int i = 0;i < SZ(a.cnt);i++){
        c.cnt[i] = a.cnt[i] + b.cnt[i];
    }
    return c;
}

bool operator<(const Answer& a, const Answer& b){
    return a.sum < b.sum;
}

Answer moneyChange(vector<int> coins, int money){
    for(int i = 0;i < SZ(coins);i++){
        if(coins[i] == money)
            return Answer(SZ(coins), i, 1);
    }
    Answer minCoins = Answer(SZ(coins), SZ(coins) - 1, money);
    for(int i = 0;i < SZ(coins);i++){
        if(money > coins[i]){
            Answer tmpSum = Answer(SZ(coins), i, 1) + moneyChange(coins, money - coins[i]);
            if(tmpSum < minCoins){
                minCoins = tmpSum;
            }
        }
    }
    return minCoins;
}

int main(){
    ifstream input("input_5.txt");
    vector<int> coins;
    while(true){
        int cur;
        input >> cur;
        coins.push_back(cur);
        if(cur == 1) break;
    }
    int money;
    input >> money;
    input.close();

    Answer ans = moneyChange(coins, money);
    for(int i = 0;i < SZ(coins);i++){
        cout << coins[i] << ": " << ans.cnt[i] << endl;
    }
    return 0;
}
