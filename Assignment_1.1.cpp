#include<iostream>

using namespace std;

int **square;
int n;

bool init(){
    if(n % 2 == 0)
        return false;
    square = new int* [n];
    for(int i = 0;i < n;i++){
        square[i] = new int [n];
        for(int j = 0;j < n;j++)
            square[i][j] = 0;
    }
    //cout << square;
    return true;
}

void recursion(int first, int x, int y){
    square[x][y] = first;
    if(first != n * n){
        int new_x = (x - 1 < 0)?x + n - 1:x - 1;
        int new_y = (y - 1 < 0)?y + n - 1:y - 1;
        //cout << new_x << new_y << endl;
        if(square[new_x][new_y] == 0)
            recursion(first + 1, new_x, new_y);
        else{
            int new_x = (x + 1 == n)?x - n + 1:x + 1;
            recursion(first + 1, new_x, y);
        }
    }
}


int main(){
    while(cin >> n){
        if(init()){
            recursion(1,0,(n / 2));
            for(int i = 0;i < n;i++){
                for(int j = 0;j < n;j++)
                    cout << square[i][j] << " ";
                cout << endl;
            }
        }
        else
            break;
    }
}
