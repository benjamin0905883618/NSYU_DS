#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

bool compare(char a, char b){
    return int(a) < int(b);
}

class TSet{
    string content;
    int length;

public:
    string check(string test, int mode){
        string new_str = "";
        for(int i = 1;i < test.length();i++){
            if(test[i] == test[i-1]){
                new_str += test[i-1];
                test.erase(i-1,1);
            }
        }
        if(mode == 0)
            return test;
        else
            return new_str;

    }
    TSet(string c) : content(c) {
        length = content.length();
        sort(content.begin(),content.end(),less<char>());
        content = check(content,0);
        //cout << content << endl;
    }
    TSet operator+(const TSet &that){
        string new_str = content + that.content;
        sort(new_str.begin(),new_str.end(),less<char>());
        return TSet(new_str);
    }
    TSet operator*(const TSet &that){
        int new_length = (length < that.length)?length:that.length;
        //cout << "test" << endl;
        string new_str = content + that.content;
        sort(new_str.begin(),new_str.end(),less<char>());
        return TSet(check(new_str, 1));
    }
    TSet operator-(const TSet &that){
        string new_str = content;
        int idx = 0;
        for(int i = 0;i < new_str.length();i++){
            //cout << new_str[i] << " " << that.content[idx] <<endl;
            if(new_str[i] == that.content[idx]){
                new_str.erase(i,1);
                i--;
                idx++;
            }
            else if(int(that.content[idx]) < int(new_str[i]) && idx < that.length){
                idx++;
                i--;
            }
        }
        return TSet(new_str);
    }
    bool operator>=(const TSet &that){
        int new_length = (length < that.length)?length:that.length;
        //cout << "test" << endl;
        string new_str = content + that.content;
        sort(new_str.begin(),new_str.end(),less<char>());

        if(new_str == content)
            return true;
        else
            return false;
    }
    bool belong(char input){
        for(int i = 0;i < length;i++){
            if(content[i] == input)
                return true;
        }
        return false;
    }
    void output(){
        cout << content << endl;
    }
};


int main(){
    TSet A("abcdef");
    A.output();
    TSet B("chfeechi");
    B.output();
    TSet C = A + B;
    C.output();
    TSet D = A * B;
    D.output();
    TSet E = A - B;
    E.output();
    TSet F = B - A;
    F.output();
    bool temp_a = A >= B;
    bool temp_b = B >= A;
    cout << temp_a << endl;
    cout << temp_b << endl;
    cout << A.belong('h') << endl;
    cout << B.belong('h') << endl;
}
