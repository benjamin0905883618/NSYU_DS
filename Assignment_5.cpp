#include<iostream>

using namespace std;

struct Node{
    int coefficient;
    int exponent;
    Node* next = nullptr;
    Node(int c, int e) : coefficient(c),exponent(e){}
    friend ostream& operator<<(ostream& os, const Node& n);
};

ostream& operator<<(ostream& os, const Node* n){
    if(n->exponent == 0)
        os << n->coefficient;
    else
        os << n->coefficient << "x^" << n->exponent;
    return os;
}

class Poly{
public:
    Poly(Node* h = nullptr){
        if(h == nullptr){
            head = new Node(-1,-1);
        }
        else
            head = h;
    }
    bool empty(){return (head->next == nullptr);}
    Node* h(){return head;}
    void push(Node* new_n){
        //cout << new_n << endl;
        if(empty())
            head->next = new_n;
        else{
            Node* cursor = head;
            while(cursor->next != nullptr && cursor->next->exponent > new_n->exponent){
                cursor = cursor->next;
            }
            if(cursor->next == nullptr)
                cursor->next = new_n;
            else if(cursor->next->exponent == new_n->exponent){
                cursor->next->coefficient += new_n->coefficient;
            }
            else{
                new_n->next = cursor->next;
                cursor->next = new_n;
            }

        }
    }
    Poly operator+(Poly& that){
        Node* cursor_self = head->next;
        Node* cursor_other = that.h()->next;
        Node* new_l = new Node(-1,-1);
        Node* cursor = new_l;
        while(true){
            //cout << cursor_self << endl;
            //cout << cursor_other <<endl;
            if(cursor_self == nullptr && cursor_other == nullptr)
                break;
            else if(cursor_other == nullptr || cursor_self->exponent > cursor_other->exponent){
                cursor->next = cursor_self;
                cursor_self = cursor_self->next;
                cursor = cursor->next;
            }
            else if(cursor_self == nullptr || cursor_self->exponent < cursor_other->exponent){
                cursor->next = cursor_other;
                cursor_other = cursor_other->next;
                cursor = cursor->next;
            }
            else if(cursor_self->exponent == cursor_other->exponent){
                if(cursor_self->coefficient + cursor_other->coefficient == 0){
                    cursor_self = cursor_self->next;
                    cursor_other = cursor_other->next;
                }
                else{
                    Node* temp = new Node(cursor_self->coefficient + cursor_other->coefficient,cursor_self->exponent);
                    cursor->next = temp;
                    cursor_self = cursor_self->next;
                    cursor_other = cursor_other->next;
                    cursor = cursor->next;
                }
            }
        }
        return Poly(new_l);
    }
    Poly operator*(Poly& that){
        Node* cursor_self = head->next;
        Poly p;
        while(cursor_self != nullptr){
            Node* cursor_other = that.h()->next;
            while(cursor_other != nullptr){
                //cout << cursor_self << " , " << cursor_other << endl;
                if(cursor_self->coefficient * cursor_other->coefficient == 0){
                    cursor_other = cursor_other->next;
                }
                else{
                    Node* temp = new Node(cursor_self->coefficient * cursor_other->coefficient,cursor_self->exponent + cursor_other->exponent);
                    p.push(temp);
                    cursor_other = cursor_other->next;
                }
            }
            cursor_self = cursor_self->next;
        }
        return p;
    }
    void output_list(){
        if(empty()){
            cout << 0 << endl;
            return;
        }
        Node *cursor = head->next;
        while(cursor->next != nullptr){
            if(cursor->coefficient != 0){
                cout << cursor << " + ";
            }
            cursor = cursor->next;
        }
        cout << cursor;
        cout << endl;
    }

protected:
    Node *head;
};

int main(){
    Node* f1 = new Node(2,2);
    Poly p1;
    p1.push(f1);
    p1.output_list();
    Node* f4 = new Node(1,2);
    Node* f5 = new Node(1,1);
    Node* f6 = new Node(1,0);
    Poly p2;
    p2.push(f4);
    p2.push(f5);
    p2.push(f6);
    p2.output_list();
    Poly p3 = p1 * p2;
    p3.output_list();
}
