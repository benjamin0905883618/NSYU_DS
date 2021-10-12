#include<iostream>

using namespace std;

struct leaf_node{
    int content;
    leaf_node *left, *right;
    leaf_node(int c,leaf_node *l,leaf_node *r):content(c),left(l),right(r){}

    void push(int value){
        if(value > content){
            leaf_node *temp = new leaf_node(value,nullptr,nullptr);
            this->right = temp;
        }
        else{
            leaf_node *temp = new leaf_node(value,nullptr,nullptr);
            this->left = temp;
        }
    }
    void pop(){
        if(this->right == nullptr && this->left == nullptr){
            //cout << "case 1 : double null" << endl;
            delete this;
        }
        else if(this->left != nullptr && this->right != nullptr){
            //cout << "case 2 : double full" << endl;
            leaf_node *temp = this->left;
            while(temp->left != nullptr){temp = temp->left;}
            this->content = temp->content;
            delete temp;

            leaf_node *t = this->right;
            this->right = this->left;
            leaf_node *cursor = this;
            while(cursor->right != nullptr){cursor = cursor->right;}
            cursor->right = t;
        }
        else{
            //cout << "case 3 : one side null" << endl;
            leaf_node *temp = (this->left == nullptr)?this->right:this->left;
            this->content = temp->content;
            this->left = temp->left;
            this->right = temp->right;
            delete temp;
        }
    }
};


class Tree{
public:
    Tree(int c){root = new leaf_node(c,nullptr,nullptr);}
    void search_tree(int value){
        leaf_node *cursor = root;
        while(true){
            //cout << "tree content : " << cursor->content << " value is : " << value << endl;
            if(cursor->content == value){
                //cout << "delete root" << endl;
                if(cursor->left == nullptr && cursor->right == nullptr)
                    cursor->content = 0;
                else
                    cursor->pop();
                break;
            }
            else if(cursor->content > value){
                if(cursor->left == nullptr){
                    cursor->push(value);
                    break;
                }
                else if(cursor->left->content == value){
                    leaf_node *temp = cursor->left;
                    if(temp->left == nullptr && temp->right == nullptr)
                        cursor->left = nullptr;
                    else
                        cursor->left->pop();
                    break;
                }
                else
                    cursor = cursor->left;

            }
            else{
                if(cursor->right == nullptr){
                    cursor->push(value);
                    break;
                }
                else if(cursor->right->content == value){
                    leaf_node *temp = cursor->right;
                    if(temp->left == nullptr && temp->right == nullptr)
                        cursor->right = nullptr;
                    else
                        cursor->right->pop();
                    break;
                }
                else
                    cursor = cursor->right;
            }

        }
    }
    bool empty(){return (root->content == 0);}
    leaf_node* r(){return root;}
private:
    leaf_node *root;
};

void output_tree(leaf_node *root){
    if(root->left != nullptr)
        output_tree(root->left);
    cout << root->content << " ";
    if(root->right != nullptr)
        output_tree(root->right);
    return;
}

int main(){
    int input[6] = {10,7,12,8,11,4};
    Tree t(input[0]);
    for(int i = 1;i < 6;i++){
        //cout << input[i] << endl;
        if(t.empty())
            t.r()->content = input[i];
        else
            t.search_tree(input[i]);
    }
    output_tree(t.r());
}
