#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define SZ(x) (int)x.size()

int main(){
    string line;
    getline(cin, line);
    stringstream input(line);
    vector<int> coins;
    while(!input.eof()){
        int cur;
        cin >> cur;
        coins.push_back(cur);
    }
    int s;
    cin >> s;
    return 0;
}
