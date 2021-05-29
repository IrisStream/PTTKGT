#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define SZ(x) (int)x.size()

class BigInt{
private:
    vector<bool> bits;
public:
    BigInt(){}
    
    void toBits(string n);

    BigInt(string n){
        toBits(n);
    }

    BigInt(int len, bool value = false){
        bits = vector<bool>(len, value);
    }

    int size(){
        return bits.size();
    }

    bool isZero(){
        for(int i = 0;i<SZ(bits);i++){
            if(bits[i]) 
                return false;
        }
        return true;
    }

    void printBit();

    string toNum();
    friend BigInt operator+(BigInt a, BigInt b);
    friend BigInt operator-(BigInt a, BigInt b);
    friend BigInt operator*(BigInt a, BigInt b);
    BigInt mod2(int p); // x mod 2^p
    BigInt div2(int p); // x div 2^p
    BigInt shl(int p);  // x << p;
};

BigInt BigInt::mod2(int p){
    BigInt ans(p);
    for(int i = 0;i<p;i++){
        ans.bits[i] = this->bits[i];
    }
    return ans;
}

BigInt BigInt::div2(int p){
    BigInt ans(this->size() - p);
    for(int i = 0;i < ans.size();i++){
        ans.bits[i] = this->bits[p+i];
    }
    return ans;
}

BigInt BigInt::shl(int p){
    BigInt ans(p + this->size());
    for(int i = 0;i < this->size();i++){
        ans.bits[p + i] = this->bits[i];
    }
    return ans;
}

BigInt operator+(BigInt a, BigInt b){
    BigInt c;
    if(a.size() < b.size()) c = b;
    else c = a;
    int memo = 0;
    int len = min(a.size(), b.size());
    for(int i = 0;i < len;i++){
        memo += a.bits[i] + b.bits[i];
        c.bits[i] = memo % 2;
        memo /= 2;
    }
    for(int i = len;i < c.size();i++){
        memo += c.bits[i];
        c.bits[i] = memo % 2;
        memo /= 2;
    }
    if(memo > 0){
        c.bits.push_back(memo);
    }
    return c;
}

BigInt operator-(BigInt a, BigInt b){
    BigInt c = a;
    int memo = 0;
    for(int i = 0;i < b.size();i++){
        memo = a.bits[i] - b.bits[i] - memo;
        if(memo >= 0){
            c.bits[i] = memo;
            memo = 0;
        }
        else {
            c.bits[i] = memo + 2;
            memo = 1;
        }
    }
    for(int i = b.size();i < c.size();i++){
        memo = c.bits[i] - memo;
        if(memo >= 0){
            c.bits[i] = memo;
            memo = 0;
        }
        else {
            c.bits[i] = memo + 2;
            memo = 1;
        }
    }
    int len = c.size();
    while(len > 1 && c.bits[len - 1] == 0) len--;
    c.bits.resize(len);
    return c;
}

BigInt operator*(BigInt a, BigInt b){
    int len = max(a.size(), b.size());
    if(a.isZero() || b.isZero()){
        return BigInt(1); // the Ctor return one bool with value false
    }
    if(len == 1){
        return BigInt(1, a.bits[0] & b.bits[0]);
    }
    int m = len / 2;
    BigInt x = a.div2(m);
    BigInt y = a.mod2(m);
    BigInt w = b.div2(m);
    BigInt z = b.mod2(m);
    BigInt r = (x + y) * (w + z);
    BigInt p = x * w;
    BigInt q = y * z;
    return p.shl(m * 2) + (r - p - q).shl(m) + q;
}

bool mod(string& n){
    int res = 0;
    int len = (int)n.size();
    for(int i = len-1;i>=0;i--){
        res = res * 10 + (n[i] - '0');
        n[i] = res / 2 + '0';
        res = res % 2;
    }
    while(len > 1 && n[len-1] == '0'){
        n.resize(--len);
    }
    return res;
}


void BigInt::toBits(string n){
    reverse(n.begin(), n.end());
    while(n.size() > 1 || n[0] != '0'){
        bits.push_back(mod(n));
    }
}

string add(const string& a, const string& b){
    string c;
    if(SZ(a) > SZ(b)) c = a;
    else c = b;
    int memo = 0;
    int len = min(SZ(a), SZ(b));
    for(int i = 0;i < len;i++){
        memo += (a[i] - '0') + (b[i] - '0');
        c[i] = (memo % 10) + '0';
        memo /= 10;
    }
    for(int i = len;i < SZ(c);i++){
        memo += c[i] - '0';
        c[i] = (memo % 10) + '0';
        memo /= 10;
    }
    if(memo > 0){
        c = c + char(memo + '0');
    }
    return c;
}

string BigInt::toNum(){
    string ans = "0";
    string cur = "1";
    for(int i = 0;i<SZ(bits);i++){
        if(bits[i]) ans = add(ans, cur);
        cur = add(cur, cur);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void BigInt::printBit(){
    for(int i = SZ(bits) - 1;i>=0;i--){
        cout << bits[i];
    }
    cout << endl;
}


int main(){
    ifstream input("input_1.txt");
    string a,b;
    input >> a >> b;
    input.close();

    BigInt x(a);
    BigInt y(b);

    cout << (y * x).toNum() << endl;
    return 0;
}
