#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

float * getArray(istream& input, int& size){
    input >> size;
    float * a = new float[size];
    for(int i = 0;i < size;i++){
        input >> a[i];
    }
    return a;
}

void shakerSort(float * a, int size){
    bool flag = true;
    int left = 0;
    int right = size - 1;
    bool coin = true;
    while(flag){
        flag = false;
        coin = not coin;
        if(coin){
            left++;
            for(int i = right;i>=left;i--){
                if(a[i] < a[i-1]){
                    swap(a[i],a[i-1]);
                    flag = true;
                }
            }
        }
        else{
            right--;
            for(int i = left;i<=right;i++){
                if(a[i] > a[i + 1]){
                    swap(a[i], a[i+1]);
                    flag = true;
                }
            }
        }
    }
}

void printArray(float * a, int size){
    for(int i = 0;i<size;i++){
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main(){
    ifstream input;
    input.open("input_1.txt");
    int size = 0;
    float * a = getArray(input, size);
    input.close();
    shakerSort(a, size);
    printArray(a, size);
    return 0;
}