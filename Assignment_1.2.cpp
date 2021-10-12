#include<iostream>

using namespace std;

int array_[100] = {0};

void init(){
    array_[0] = 1;
}

int Fib(int n, int i = 1, int num = 0){
    //cout << i << endl;
    if(n > i){
        for(int j = 0;j < 100;j++)
            array_[j] *= (i + 1);
        for(int j = 0;j < 100;j++){
            if(array_[j] >= 10){
                array_[j+1] += array_[j] / 10;
                array_[j] = array_[j] % 10;
                if(num < j+1)
                    num = j+1;
            }
        }
        Fib(n, i + 1, num);
    }
    else
        return num;
}

int main(){
    init();
    int num = Fib(50);
    //cout << num;
    for(int i = num;i >= 0; i--){
        cout << array_[i];
    }
    cout << endl;
}
