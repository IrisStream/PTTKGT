#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int J(int n){
    if(n == 1)
        return 1;
    if(n & 1)
        return 2 * J(n >> 1) + 1;
    else
        return 2 * J(n >> 1) - 1;
}

int main(){
    ifstream input("input_2.txt");
    int n;
    input >> n;
    input.close();

    queue<int> q;
    for(int i = 0;i<n;i++)
        q.push(i + 1);

    while(q.size() > 1){
        int killer = q.front(); q.pop();
        int deadth = q.front(); q.pop();
        q.push(killer);
        cout << deadth << " ";
    }
    cout << endl << J(n) << endl;
    return 0;
}
