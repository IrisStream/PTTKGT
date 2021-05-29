#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define SZ(x) (int)x.size()

bool ** alloc2d(int n){
    bool ** a = new bool*[n];
    for(int i = 0;i<n;i++){
        a[i] = new bool[n];
    }
    return a;
}

class DAG{
private:
    int n;
    bool ** adj;
    int * degIn;
public:
    DAG(){
        n = 0;
        adj = NULL;
        degIn = NULL;
    }

    DAG(int size){
        this->n = size;
        adj = alloc2d(n);
        degIn = new int[n];
        reset();
    }

    DAG(int size,istream& input) :DAG(size){
        string line;
        while(true){
            getline(input, line);
            if(line == "0") break;
            stringstream ss(line);
            int curNode = 0;
            int prevNode = 0;
            ss >> curNode;
            while(!ss.eof()){
                ss >> prevNode;
                adj[prevNode-1][curNode-1] = true;
                degIn[curNode - 1]++;
            }
        }
    }

    void reset(){
        for(int i = 0;i<n;i++){
            degIn[i] = 0;
            for(int j = 0;j<n;j++){
                adj[i][j] = false;
            }
        }
    }


    vector<int> topo(){
        vector<int> res;
        queue<int> q;
        for(int i = 0;i<n;i++){
            if(degIn[i] == 0) 
                q.push(i);
        }

        while(!q.empty()){
            int u = q.front();
            res.push_back(u + 1);
            q.pop();
            for(int i = 0;i<n;i++){
                if(adj[u][i]){
                    degIn[i]--;
                    if(degIn[i] == 0) 
                        q.push(i);
                }
            }
        }
        return res;
    }
};

int main(){
    int n;
    ifstream input("input_1.txt");
    input >> n;
    DAG graph(n, input);
    input.close();

    vector<int> ans = graph.topo();
    for(int i = 0;i < SZ(ans);i++){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
