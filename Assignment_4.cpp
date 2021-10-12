#include<iostream>

using namespace std;

struct coor{
    int i, j;
    int n;
    coor(int i = 0,int j = 0,int n = 0):i(i),j(j),n(n) {}
    friend ostream& operator << (ostream& os, const coor& c);

    coor operator+(const coor& that){
        int new_i = that.i;
        int new_j = that.j;
        if(that.i < 0){new_i = that.i + n;}
        if(that.j < 0){new_j = that.j + n;}
        new_i = (new_i + i > n)?new_i + i - n:new_i + i;
        new_j = (new_j + j > n)?new_j + j - n:new_j + j;
        return coor(new_i, new_j, n);

    }
    bool operator==(const coor& that){
        return (i == that.i && j == that.j);
    }

};

ostream& operator<<(ostream& os, const coor& c){
    os << "(" <<  c.i << "," << c.j << ")" ;
    return os;
}

int n;
coor K1(-2,1,n);
coor K2(-1,2,n);
coor K3(1,2,n);
coor K4(2,1,n);
coor K5(2,-1,n);
coor K6(1,-2,n);
coor K7(-1,-2,n);
coor K8(-2,-1,n);
coor method(int i){
    switch(i){
        case 1:
            return K1;
        case 2:
            return K2;
        case 3:
            return K3;
        case 4:
            return K4;
        case 5:
            return K5;
        case 6:
            return K6;
        case 7:
            return K7;
        case 8:
            return K8;
        }
}
int** _map_;

bool backtracking(int idx, int prev_method, coor prev){
    if(idx == n*n){
        cout << "find" << endl;
        coor new_c = prev + method(prev_method);
        _map_[new_c.i][new_c.j] = idx;
        return true;
    }
    else{
        cout << "write number : " << idx << endl;
        coor new_c = prev + method(prev_method);
        _map_[new_c.i][new_c.j] = idx;
        for(int i = 1;i <= 8;i++){
            coor temp = new_c + method(i);
            if(_map_[temp.i][temp.j] == 0){
                if(backtracking(idx + 1, i, new_c))
                    return true;
                else
                    continue;
            }
        }
        cout << "not found" << endl;
        _map_[new_c.i][new_c.j] = 0;
        return false;
    }
}


int main(){
    n = 5;
    coor init(1,1,n);
    _map_ = new int* [n+1];
    for(int i = 0;i < n + 1;i++){
        _map_[i] = new int [n+1];
        for(int j = 0;j < n + 1;j++){
            _map_[i][j] = 0;
        }
    }
    _map_[1][1] = 1;
    if(backtracking(2, 1, init)){
        for(int i = 1;i < n+1 ;i++){
            for(int j = 1;j < n+1;j++)
                cout << _map_[i][j] << " ";
            cout << endl;
        }
    }
    else
        cout << "No solution " << endl;
}
