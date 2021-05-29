#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int ** alloc(int n){
    int ** a = new int*[n];
    for(int i = 0;i<n;i++){
        a[i] = new int[n];
    }
    return a;
}

void dealloc(int ** a, int n){
    for(int i = 0;i<n;i++){
        delete[] a[i];
    } 
    delete[] a;
}

class Matrix{
private:
    int ** m;
    int size;
public:
    Matrix(){
        size = 0;
        m = NULL;
    }

    Matrix(int n){
        m = alloc(n);
        size = n;
    }

    Matrix(const Matrix& src){
        m = alloc(src.size);
        size = src.size;
        for(int i = 0;i < size;i++){
            for(int j = 0;j < size;j++){
                m[i][j] = src.m[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& src){
        if(m != NULL) 
            dealloc(m, size);
        m = alloc(src.size);
        size = src.size;
        for(int i = 0;i < size;i++){
            for(int j = 0;j < size;j++){
                m[i][j] = src.m[i][j];
            }
        }
        return *this;
    }

    Matrix(int ** A, int n){
        m = A;
        size = n;
    }

    ~Matrix(){
        dealloc(m, size);
    }

    int get(int i,int j){
        if(i < size && j < size)
            return m[i][j];
        return 0;
    }

    void set(int i,int j,int value){
        if(i < size && j < size)
            m[i][j] = value;
    }

    void print(){
        for(int i = 0;i < size;i++){
            for(int j = 0;j < size;j++){
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    static Matrix mul(Matrix a, Matrix b);

    static Matrix combine(Matrix A11, Matrix A12, Matrix A21, Matrix A22, int n);

    friend Matrix operator+(Matrix a, Matrix b);
    friend Matrix operator-(Matrix a, Matrix b);
    friend Matrix operator*(Matrix a, Matrix b);
};

Matrix Matrix::mul(Matrix a, Matrix b){
    Matrix c(a.size);
    for(int i = 0;i < a.size;i++){
        for(int j = 0;j<b.size;j++){
            c.m[i][j] = 0;
            for(int k = 0;k<a.size;k++){
                c.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return c;
}

Matrix Matrix::combine(Matrix A11, Matrix A12, Matrix A21, Matrix A22, int n){
    Matrix A(n);
    int sub_size = A11.size;
    for(int i = 0;i<sub_size;i++){
        for(int j = 0;j<sub_size;j++){
            A.m[i][j] = A11.m[i][j];
            A.set(i, j + sub_size, A12.m[i][j]);
            A.set(i + sub_size, j, A21.m[i][j]);
            A.set(i + sub_size, j + sub_size, A22.m[i][j]);
        }
    }
    return A;
}

Matrix operator+(Matrix a, Matrix b){
    Matrix c(a.size);
    for(int i = 0; i < a.size; i++){
        for(int j = 0; j < a.size; j++){
            c.m[i][j] = a.m[i][j] + b.m[i][j];
        }
    }
    return c;
}

Matrix operator-(Matrix a, Matrix b){
    Matrix c(a.size);
    for(int i = 0; i < a.size; i++){
        for(int j = 0; j < a.size; j++){
            c.m[i][j] = a.m[i][j] - b.m[i][j];
        }
    }
    return c;
}

Matrix operator*(Matrix a, Matrix b){
    if(a.size == 2){
        return Matrix::mul(a,b);
    }
    int mid = (a.size + 1) / 2;
    Matrix A11(mid);
    Matrix A12(mid);
    Matrix A21(mid);
    Matrix A22(mid);
    Matrix B11(mid);
    Matrix B12(mid);
    Matrix B21(mid);
    Matrix B22(mid);
    for(int i = 0;i < mid;i++){
        for(int j = 0;j< mid;j++){
            A11.m[i][j] = a.m[i][j];
            A12.m[i][j] = a.get(i,j + mid);
            A21.m[i][j] = a.get(i + mid, j);
            A22.m[i][j] = a.get(i + mid, j + mid);


            B11.m[i][j] = b.m[i][j];
            B12.m[i][j] = b.get(i,j + mid);
            B21.m[i][j] = b.get(i + mid, j);
            B22.m[i][j] = b.get(i + mid, j + mid);
        }
    }
    Matrix M1 = (A11 + A22) * (B11 + B22);
    Matrix M2 = (A21 + A22) * B11;
    Matrix M3 = A11 * (B12 - B22);
    Matrix M4 = A22 * (B21 - B11);
    Matrix M5 = (A11 + A12) * B22;
    Matrix M6 = (A21 - A11) * (B11 + B12);
    Matrix M7 = (A12 - A22) * (B21 + B22);

    Matrix C11 = M1 + M4 - M5 + M7;
    Matrix C12 = M3 + M5;
    Matrix C21 = M2 + M4;
    Matrix C22 = M1 + M3 - M2 + M6;
    Matrix C = Matrix::combine(C11, C12, C21, C22, a.size);
    return C;
}

int ** inputMatrix(istream& input, int n){
    int ** a = alloc(n);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            input >> a[i][j];
        }
    }
    return a;
}

int main(){
    ifstream input("input_2.txt");
    int n;
    input >> n;
    int ** a = inputMatrix(input, n);
    int ** b = inputMatrix(input, n);
    input.close();

    Matrix A(a, n);
    Matrix B(b, n);
    (A * B).print();
    return 0;
}
