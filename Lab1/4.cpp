#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
using namespace std;

#define PI 3.14
#define EPS 0.000000001
#define ii pair<int,int>

pair<int,int> * getPoints(istream& input, int & n){
    input >> n;
    pair<int, int> * points = new pair<int,int>[n];
    for(int i = 0;i<n;i++){
        input >> points[i].first >> points[i].second;
    }
    return points;
}

float computeAngle(ii p1, ii p2){
    float angle = atan2(p2.second - p1.second, p2.first - p1.first);
    if(angle < 0){
        angle += PI * 2;
    }
    return angle;
}

int findNextExtremePoint(ii * points, int n, int curExtremePoint, int curAngle){
    float minAngle = 2 * PI;
    int nextExtremePoint;
    for(int i = 0;i<n;i++){
        if(i == curExtremePoint) continue;
        float angle = computeAngle(points[curExtremePoint], points[i]);
        if(angle >= curAngle && angle < minAngle){
            minAngle = angle;
            nextExtremePoint = i;
        }
    }
    return nextExtremePoint;
}

int findFirstExtremePoint(ii * points, int n){
    int firstExtremePoint = 0;
    for(int i = 1;i<n;i++){
        if(points[i].second < points[firstExtremePoint].second || 
            (points[i].second == points[firstExtremePoint].second && points[i].first < points[firstExtremePoint].first)){
                firstExtremePoint = i;
            }
    }
    return firstExtremePoint;
}

int findConvexHull(pair<int,int> * points, int n){
    swap(points[0], points[findFirstExtremePoint(points,n)]);
    int curExtremePoint = 0;
    float curAngle = 0;
    while(true){
        int nextExtremePoint = findNextExtremePoint(points, n, curExtremePoint, curAngle);
        if(nextExtremePoint == 0){
            break;
        }
        curAngle = computeAngle(points[curExtremePoint], points[nextExtremePoint]);
        curExtremePoint++;
        swap(points[curExtremePoint], points[nextExtremePoint]);
    }
    return curExtremePoint;
}

void printResult(ii * points, int n){
    for(int i = 0;i<=n;i++){
        printf("(%d, %d) ", points[i].first, points[i].second);
    }
    printf("\n");
}

int main(){
    ifstream input("input_4.txt");
    int n;
    pair<int, int> * points = getPoints(input, n);
    input.close();
    int numExtremePoints = findConvexHull(points, n);
    printResult(points, numExtremePoints);
    return 0;
}