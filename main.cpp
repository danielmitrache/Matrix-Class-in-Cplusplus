#include <iostream>

using namespace std;

class Matrix{
private:
    int n, m, a[101][101];
    int calculDeterminant(Matrix A){
        int n = A.n;
        if(n == 1)
            return A.a[1][1];
        else{
            int det = 0;
            for(int i = 1; i <= n; i ++){
                int p = i % 2 == 0 ? -1 : 1, caux;
                Matrix aux(n - 1, n - 1);
                for(int l = 2; l <= n; l ++){
                    caux = 0;
                    for(int c = 1; c <= n; c ++){
                        if(c != i)
                            aux.setElement(l - 1, ++ caux, A.a[l][c]);
                    }
                }
                det += p * A.a[1][i] * calculDeterminant(aux);
            }
            return det;
        }
    }
    void setElement(int i, int j, int x){
        a[i][j] = x;
    }
    friend Matrix multiply(const Matrix&, const Matrix&);
public:
    Matrix(int l = 2, int c = 2, int x = 0){
        n = l;
        m = c;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                if(i == j)
                    a[i][j] = x;
                else a[i][j] = 0;
    }
    ~Matrix(){}
    Matrix operator= (const Matrix &A){
        this -> n = A.n;
        this -> m = A.m;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                this -> a[i][j] = A.a[i][j];
        return *this;
    }
    int getNrLinii(){
        return n;
    }
    int getNrColoane(){
        return m;
    }
    void transpusa(){
        Matrix T(m, n);
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++)
                T.setElement(j, i, a[i][j]);
        *this = T;
    }
    int determinant(){
        if(n != m){
            cout << "Nu se poate calcula determinantul - matricea nu este patratica.\n";
            return 0;
        }
        else return calculDeterminant(*this);
    }
    Matrix operator* (const Matrix &A){
        Matrix rez = multiply(A, *this);
        return rez;
    }
    Matrix operator+ (const Matrix &A){
        if(this -> n != A.n || this -> m != A.m)
            throw invalid_argument("Dimensiunile nu sunt compatibile pentru adunare!");
        else{
            Matrix rez(A.n, A.m, 0);
            for(int i = 1; i <= A.n; i ++)
                for(int j = 1; j <= A.m; j ++)
                    rez.setElement(i, j, A.a[i][j] + this -> a[i][j]);
            return rez;
        }
    }
    Matrix operator- (const Matrix &A){
        if(this -> n != A.n || this -> m != A.m)
            throw invalid_argument("Dimensiunile nu sunt compatibile pentru scadere!");
        else{
            Matrix rez(A.n, A.m, 0);
            for(int i = 1; i <= A.n; i ++)
                for(int j = 1; j <= A.m; j ++)
                    rez.setElement(i, j, this -> a[i][j] - A.a[i][j]);
            return rez;
        }
    }
    int* operator[] (int i){
        if(i < 1 || i > n)
            return nullptr;
        else
            return a[i];
    }
    void Fill(int x1, int y1, int x2, int y2, int val){
        for(int i = x1; i <= x2; i ++)
            for(int j = y1; j <= y2; j ++)
                a[i][j] = val;
    }
    bool operator== (const Matrix& A){
        if(this -> n != A.n || this -> m != A.m)
            return false;
        for(int i = 1; i <= A.n; i ++)
            for(int j = 1; j <= A.m; j ++)
                if(this -> a[i][j] != A.a[i][j])
                    return false;
        return true;
    }
    friend ostream & operator<< (ostream & out, const Matrix& A){
        for(int i = 1; i <= A.n; i ++, out << "\n")
            for(int j = 1; j <= A.m; j ++)
                out << A.a[i][j] << " ";
        return out;
    }
    friend istream & operator>> (istream & in, Matrix& A){
        cout << "Introduceti valorile matricei (" << A.n << "x" << A.m << ")\n";
        for(int i = 1; i <= A.n; i ++)
            for(int j = 1; j <= A.m; j ++)
                in >> A.a[i][j];
        return in;
    }
    int trace(){
        if(n != m)
            throw invalid_argument("Nu se poate calcula trace-ul!");
        else{
            int s = 0;
            for(int i = 1; i <= n; i ++)
                s += a[i][i];
            return s;
        }
    }
};

Matrix multiply(const Matrix& A, const Matrix& B){
    int ca = A.m, lb = B.n, cb = B.m, la = A.n;
    Matrix rez(la, cb);
    int n = la, m = cb;
    if(ca != lb)
        throw invalid_argument("Dimensiunile nu sunt compatibile pentru inmultire!");
    else{
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= m; j ++){
                int x = 0;
                for(int k = 1; k <= ca; k ++)
                    x += A.a[i][k] * B.a[k][j];
                rez.setElement(i, j, x);
            }
        return rez;
    }
}

int main() {
    return 0;
}