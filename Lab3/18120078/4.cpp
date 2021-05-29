#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define SZ(x) (int)x.size()

struct coord{
    int x,y;
};

istream& operator>>(istream& in, coord& p){
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const coord& p){
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

bool operator <(const coord& a, const coord& b){
    return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

bool operator==(const coord& a, const coord& b){
    return (a.x == b.x && a.y == b.y);
}

#define cc pair<coord, coord>
#define fi first
#define se second
#define mp make_pair

int dict(coord a, coord b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool cmpX(coord a, coord b){
    return a.x < b.x;
}

bool cmpY(coord a, coord b){
    return a.y < b.y;
}

void quicksort(coord * points,int L,int R, bool (*cmp)(coord, coord)){
    if(L>=R) return;
    int i = L;
    int j = R;
    coord v = points[L + rand() % (R - L + 1)];
    while(i<=j){
        while(cmp(points[i], v)) i++;
        while(cmp(v, points[j])) j--;
        if(i<=j){
            swap(points[i], points[j]);
            i++;
            j--;
        }
    }
    quicksort(points, L, j, cmp);
    quicksort(points, i, R, cmp);
}

void add(vector<cc> &a, int& pos, cc value){
    if(pos < SZ(a))
        a[pos] = value;
    else 
        a.push_back(value);
    pos++;
}

vector<cc> bruteForce(coord * P, int n){
    int minDict = dict(P[0], P[1]);
    vector<cc> ans;
    int len = 0;
    for(int i = 0;i<n - 1;i++){
        for(int j = i + 1;j < n;j++){
            if(minDict > dict(P[i], P[j])){
                len = 0;
                add(ans, len, mp(P[i], P[j]));
            }
            else if(minDict == dict(P[i], P[j])){
                add(ans, len, mp(P[i], P[j]));
            }
        } 
    }

    return ans;
}

vector<cc> stripClosest(coord * P, int n,int minDict){
    quicksort(P, 0, n - 1, cmpY);
    vector<cc> ans;
    int len = 0;
    for(int i = 0;i<n - 1;i++){
        for(int j = i+1;j < n;j++){
            int d = P[j].y - P[i].y;
            if(d*d > minDict) break;
            if(minDict > dict(P[i], P[j])){
                len = 0;
                add(ans, len, mp(P[i], P[j]));
            }
            else if(minDict == dict(P[i], P[j])){
                add(ans, len, mp(P[i], P[j]));
            }
        }
    }
    return ans;
}

vector<cc> min(vector<cc> a, vector<cc> b){
    int da = dict(a[0].fi, a[0].se);
    int db = dict(b[0].fi, b[0].se);

    vector<cc> ans;
    if(da < db){
        ans = a;
    }
    else if(da > db){
        ans = b;
    }
    else{
        ans = a;
        ans.insert(ans.end(), b.begin(), b.end());
    }
    return ans;
}

vector<cc> closestPairRec(coord * P, int n){
    if(n <= 3)
        return bruteForce(P, n);

    int mid = n / 2;
    coord median = P[mid];

    vector<cc> closestPairLeft = closestPairRec(P, mid);
    vector<cc> closestPairRight = closestPairRec(P + mid, n - mid);

    vector<cc> closestSet = min(closestPairLeft, closestPairRight);
    int minDict = dict(closestSet[0].fi, closestSet[0].se);

    coord * strip = new coord[n];
    int len = 0;
    for(int i = 0;i<n;i++){
        int d = P[i].x - median.x;
        if(d * d <= minDict){
            strip[len] = P[i];
            len++;
        }
    }

    vector<cc> stripClosestSet = stripClosest(strip, len, minDict);
    if(stripClosestSet.size() == 0){
        return closestSet;
    }
    else{
        return min(closestSet, stripClosestSet);
    }
}

vector<cc> closestPair(coord * P, int n){
    quicksort(P, 0, n-1, cmpX);
    return closestPairRec(P, n); 
}

int main(){
    ifstream input("input_4.txt");
    int n;
    input >> n;
    coord * points = new coord[n];
    for(int i = 0;i<n;i++){
        input >> points[i];
    }
    input.close();
    
    vector<cc> ans = closestPair(points, n);
    for(int i = 0;i < SZ(ans);i++){
        if(ans[i].se < ans[i].fi){
            swap(ans[i].fi, ans[i].se);
        }
    }
    sort(ans.begin(), ans.end());


    cout << ans[0].fi << " " << ans[0].se << endl;
    for(int i = 1;i<SZ(ans);i++){
        if(ans[i].fi == ans[i-1].fi && ans[i].se == ans[i-1].se)
            continue;
        cout << ans[i].fi << " " << ans[i].se << endl;
    }
    return 0;
}
