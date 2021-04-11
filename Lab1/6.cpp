#include <iostream>
#include <fstream>
using namespace std;

struct obj{
    int weight;
    int value;
};

obj * getObjs(istream& input, int &W, int& n){
    input >> W >> n;
    obj * objects = new obj[n];
    for(int i = 0;i<n;i++){
        input >> objects[i].weight >> objects[i].value;
    }
    return objects;
}

bool getBit(int x, int pos){
    return (x >> pos) & 1;
}

int Knapsack(obj * objects, int W, int n){
    int bestState = 0;
    int maxValue = 0;
    for(int state = 1;state < (1 << n);state++){
        int curValue = 0;
        int curWeight = 0;
        for(int i = 0;i<n;i++){
            if(getBit(state,i) == true){
                curValue += objects[i].value;
                curWeight += objects[i].weight;
            }
        }
        if(curWeight <= W && curValue > maxValue){
            maxValue = curValue;
            bestState = state;
        }
    }
    return bestState;
}

void printResult(obj * objects, int n, int bestState){
    int maxValue = 0;
    for(int i = 0;i<n;i++){
        if(getBit(bestState, i) == true){
            cout << i << " ";
            maxValue += objects[i].value;
        }
    }
    cout << "\n" << maxValue << "\n";
}

int main(){
    ifstream input("input_6.txt");
    int W,n;
    obj * objects = getObjs(input, W, n);
    input.close();
    int bestState = Knapsack(objects, W, n);
    printResult(objects, n, bestState);
    return 0;
}