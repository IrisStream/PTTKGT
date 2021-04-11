#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

const float eps = 0.000000001f;

float * getArray(istream& input, int& size){
    input >> size;
    float * a = new float[size];
    for(int i = 0;i < size;i++){
        input >> a[i];
    }
    return a;
}

void findMaximumSubSequence(float * a, int size){
    float maxSum = 0.0;
    float curSum = 0.0;
    int left = 0;
    int right = -1;
    for(int i  = 0;i < size;i++){
        curSum += a[i];
        if(curSum > maxSum){
            maxSum = curSum;
            right = i;
        }
        else if(curSum < 0){
            curSum = 0;
        }
    }
    curSum = maxSum;
    for(int i = right;i>=0;i--){
        curSum -= a[i];
        if(curSum <= eps){
            left = i;
            break;
        }
    }
    for(int i = left;i<=right;i++){
        cout << a[i] << " ";
    }
    cout << endl << maxSum << endl;
}

int main(){
    ifstream input;
    input.open("input_2.txt");
    int size = 0;
    float * a = getArray(input, size);
    input.close();
    findMaximumSubSequence(a, size);
    return 0;
}