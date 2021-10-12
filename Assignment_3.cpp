#include<iostream>
#include<vector>

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

struct _stack_{
    coor* _list_;
    int* method;
    int length;
    _stack_(int n){
        _list_ = new coor [n * n];
        method = new int [n * n];
        length = 0;
    }
    void push(coor l,int m){
        _list_[length] = l;
        method[length] = m;
        length++;
        cout << "push " << l << " with " << m  << " and length is " << length << endl;
    }
    coor top_c(){return _list_[length-1];}
    int top_m(){return method[length-1];}
    void pop(){length--;}
    bool empty(){return (length == 0);}
};

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


int main(){
    n = 5;
    coor init(1,1,n);
    _stack_ s(n);
    _map_ = new int* [n+1];
    for(int i = 0;i < n + 1;i++){
        _map_[i] = new int [n+1];
        for(int j = 0;j < n + 1;j++){
            _map_[i][j] = 0;
        }
    }
    _map_[1][1] = 1;
    int idx = 2;
    cout << init << endl;
    while(idx < n*n || (s.top_c() == init && s.top_m() == 8)){
        cout << "write number : " << idx << endl;
        coor prev = (s.empty())?init:s.top_c();
        int prev_method = (s.empty())?1:s.top_m();
        cout << "prev position is : " << prev << "by method : " << prev_method << endl;

        coor new_c = prev + method(prev_method);
        cout << "position is : " << new_c << endl;
        bool flag = false;
        for(int i = 1;i <= 8;i++){
            coor temp = new_c + method(i);
            cout << "next position is : " << temp << endl;
            if(_map_[temp.i][temp.j] == 0){
                cout << "push " << new_c  << " with method " << i << endl;
                s.push(new_c, i);
                _map_[new_c.i][new_c.j] = idx;
                idx++;
                flag = true;
                break;
            }
        }
        if(flag == false){
            idx--;
            _map_[prev.i][prev.j] = 0;
            s.pop();
            s.push(prev,prev_method + 1);
        }
    }
    if(idx == n*n){
        coor new_c = s.top_c() + method(s.top_m());
        _map_[new_c.i][new_c.j] = idx;
        for(int i = 1;i < n+1 ;i++){
            for(int j = 1;j < n+1;j++)
                cout << _map_[i][j] << " ";
            cout << endl;
        }
    }

}
