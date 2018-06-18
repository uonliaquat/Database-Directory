#pragma once
#include <iostream>
#include "treenode.cpp"
#include "linkedlist.cpp"
#include <QDebug>
using namespace std;

class Tree{
private:
    TreeNode * root = nullptr;
public:
    bool AVL_insert(string data[], int no_of_coloumns){

        long long new_data = getHashId(data[0]);
        long long available_data;
        if(!is_full()){
            TreeNode * temp = root;
            TreeNode * newNode = new TreeNode(no_of_coloumns, data);
            newNode->height = 0;
            newNode->bf = 0;
            if(temp == nullptr){
                root = newNode;
                return true;
            }
            while(true){
                available_data = getHashId(temp->data[0]);
                if(new_data < available_data){
                    if(temp->left != nullptr){
                        temp = temp->left;
                    }
                    else{
                        newNode->parent = temp;
                        temp->left = newNode;
                        break;
                    }
                }
                else if(new_data >= available_data){
                    if(temp->right != nullptr){
                        temp = temp->right;
                    }
                    else{
                        newNode->parent = temp;
                        temp->right = newNode;
                        break;
                    }
                }
            }

            TreeNode * temp_parent = newNode;
            while(temp_parent != nullptr){
                temp_parent->height = getheight(temp_parent);
                temp_parent->bf = balance_factor(temp_parent);
                if(temp_parent->bf < -1 || temp_parent->bf > 1){
                    if(getRotation(temp_parent, newNode) == "LL"){
                        temp_parent = Left_Rotation(temp_parent);
                    }
                    else if(getRotation(temp_parent, newNode) == "RR"){
                        temp_parent = Right_Rotation(temp_parent);
                    }
                    else if(getRotation(temp_parent, newNode) == "LR"){
                        temp_parent = Left_Right_Rotation(temp_parent);
                    }
                    else if(getRotation(temp_parent, newNode) == "RL"){
                        temp_parent = Right_Left_Rotation(temp_parent);
                    }
                }
                else{
                     temp_parent = temp_parent->parent;
                }
            }
            return true;
        }
        return false;
    }

    bool BST_insert(string row[], int noOfcoloumns){
        if(!is_full()){
            TreeNode * newTreeNode = new TreeNode(noOfcoloumns, row);
            TreeNode * temp = root;
            if(temp == nullptr){
                root = newTreeNode;
                return true;
            }
            while(temp != nullptr){
                long long data = getHashId(row[0]);
                long long available_data = getHashId(temp->data[0]);
                if(data <= available_data){
                    if(temp->left != nullptr){
                        temp = temp->left;
                    }
                    else{
                        temp->left = newTreeNode;
                        return true;
                    }
                }
                else if(data > available_data){
                    if(temp->right != nullptr){
                        temp = temp->right;
                    }
                    else{
                        temp->right = newTreeNode;
                        return true;
                    }
                }
            }

        }else{
            return false;
        }
    }

    int getheight(TreeNode * temp){
       int height = 0;
       int left_child_h = -1, right_child_h = -1;
       if(temp->left != nullptr){
           left_child_h = temp->left->height;
       }
       if(temp->right != nullptr){
           right_child_h = temp->right->height;
       }
       if(left_child_h > right_child_h){
           return (height = left_child_h + 1);
       }
       else if(left_child_h <= right_child_h){
           return (height = right_child_h + 1);
       }
    }

    int balance_factor(TreeNode * temp){
       int left_b = -1, right_b = -1;
       if(temp->left != nullptr){
           left_b = temp->left->height;
       }
       if(temp->right != nullptr){
           right_b = temp->right->height;
       }
       return (left_b - right_b);
    }

    string getRotation(TreeNode * ancestor, TreeNode * newNode){

       long long ancestor_data = getHashId(ancestor->data[0]);
       long long newNode_data = getHashId(newNode->data[0]);
        string result = "\0";
        for(int i = 0; i < 2; i++){
            if(newNode_data < ancestor_data){
                result = result + "L";
                ancestor = ancestor->left;
                ancestor_data = getHashId(ancestor->data[0]);
            }
            else if(newNode_data > ancestor_data){
                result = result + "R";
                ancestor = ancestor->right;
                ancestor_data = getHashId(ancestor->data[0]);
            }
        }
        return result;
    }

    TreeNode * Left_Rotation(TreeNode * A){
       TreeNode * B = A->left;
       TreeNode * B_right = B->right;

       if(A->parent == nullptr){
           B->parent = nullptr;
           root = B;
       }
       else{
           long long A_parent_data = getHashId(A->parent->data[0]);
           long long A_data = getHashId(A->data[0]);
           if(A_data < A_parent_data){
               A->parent->left = B;
               B->parent = A->parent;
           }
           else{
               A->parent->right = B;
               B->parent = A->parent;
           }
       }
       B->right = A;
       A->parent =B;
       A->left = B_right;
       if(B_right != nullptr){
            B_right->parent = A;
       }
       if(B_right != nullptr){
        return B_right;
       }
       else if(A->right != nullptr){
           return (A->right);
       }
       return A;
    }

    TreeNode * Right_Rotation(TreeNode * A){
       TreeNode * B = A->right;
       TreeNode * B_left = B->left;

       if(A->parent == nullptr){
           B->parent = nullptr;
           root = B;
       }
       else{
           long long A_parent_data = getHashId(A->parent->data[0]);
           long long A_data = getHashId(A->data[0]);
           if(A_data > A_parent_data){
               A->parent->right = B;
               B->parent = A->parent;
           }
           else{
               A->parent->left = B;
               B->parent = A->parent;
           }
       }
       B->left = A;
       A->parent = B;
       A->right = B_left;
       if(B_left != nullptr){
            B_left->parent = A;
       }
       if(B_left != nullptr){
            return B_left;
       }
       else if(A->left != nullptr){
           return (A->left);
       }
       return A;
    }

    TreeNode * Left_Right_Rotation(TreeNode * A){
       TreeNode * B = A->left;
       TreeNode * C = B->right;
       TreeNode * C_left = C->left;
       C->parent = A;
       A->left = C;
       B->parent = C;
       C->left = B;
       B->right = C_left;
       return Right_Rotation(A);
    }

    TreeNode * Right_Left_Rotation(TreeNode * A){
       TreeNode * B = A->right;
       TreeNode * C = B->left;
       TreeNode * C_right = C->right;
       C->parent = A;
       A->right = C;
       B->parent = C;
       C->right = B;
       B->left = C_right;
       return Left_Rotation(A);
    }

    bool delete_data(string table_name, string id_s, TreeNode * head){
       int check_l_r = 0;
       long long id = getHashId(id_s);
       TreeNode * temp = head;
       long long compare_id;
       while(temp != nullptr){
           compare_id = getHashId(temp->data[0]);
           if(id < compare_id){
               temp = temp->left;
               check_l_r = 0;
           }
           else if(id > compare_id){
               temp = temp->right;
                 check_l_r = 1;
           }
           else if(id == compare_id){
               if(temp->left == nullptr && temp->right == nullptr){
                   //no child
                   if(check_l_r == 0){
                       temp->parent->left = nullptr;
                   }
                   else if(check_l_r == 1){
                       temp->parent->right = nullptr;
                   }
                   delete temp;
               }
               else if(temp->left != nullptr && temp->right != nullptr){
                   //two childs
                   TreeNode * temp2 = temp;
                   if(temp2->right->left != nullptr){
                       temp2 = temp2->right->left;
                       while(temp2->left != nullptr){
                           temp2 = temp2->left;
                       }
                       //operator overloading required
                       temp2->parent->left = nullptr;
                       temp->data = temp2->data;
                       delete temp2;
                   }
                   else {
                       temp2 = temp->right;
                       //operator overloading required
                       temp->data = temp2->data;

                       if(temp2->right != nullptr){
                           temp2->right->parent = temp;
                       }
                       temp->right = temp2->right;
                       delete temp2;
                   }

               }
               else{
                   //one child
                   if(temp->left != nullptr){
                       if(check_l_r == 0){
                           temp->left->parent = temp->parent;
                           temp->parent->left = temp->left;
                       }
                       else if(check_l_r == 1){
                           temp->left->parent = temp->parent;
                           temp->parent->right = temp->left;
                       }
                   }
                   else if(temp->right != nullptr){
                       if(check_l_r == 0){
                           temp->right->parent = temp->parent;
                           temp->parent->left = temp->right;
                       }
                       else if(check_l_r == 1){
                           temp->right->parent = temp->parent;
                           temp->parent->right = temp->right;
                       }
                   }
                   delete temp;

               }

           }
       }
       string * str = new string[1];
       str[0] = "NO_ID";
       return str;

    }

    void getRowData(TreeNode * temp, string ** row, int noOfColoumns, int noOfRows, int * index){
        if(temp == nullptr){
            return;
        }
        getRowData(temp->left, row, noOfColoumns, noOfRows, index);
        row[(*index)++] = temp->data;
        getRowData(temp->right, row, noOfColoumns, noOfRows, index);

    }

    void getPreOrder(TreeNode * temp, string ** row, int noOfColoumns, int noOfRows, int * index){
        if(temp == nullptr){
            return;
        }
        row[(*index)++] = temp->data;
        getRowData(temp->left, row, noOfColoumns, noOfRows, index);
        getRowData(temp->right, row, noOfColoumns, noOfRows, index);

    }

    string * search(string id_s, TreeNode * head){
        TreeNode * temp = head;
        long long id = getHashId(id_s);
        long long compare_id;
        while(temp != nullptr){
            compare_id = getHashId(temp->data[0]);
            if(id < compare_id){
                temp = temp->left;
            }
            else if(id > compare_id){
                temp = temp->right;
            }
            else if(id == compare_id){
                return temp->data;
            }
        }
        string * str = new string[1];
        str[0] = "NO_ID";
        return str;
    }

    void update(string id_s, string * data, int no_of_coloumns ,TreeNode * head ){
        TreeNode * temp = head;
        long long id = getHashId(id_s);
        long long compare_id;
        while(temp != nullptr){
            compare_id = getHashId(temp->data[0]);
            if(id < compare_id){
                temp = temp->left;
            }
            else if(id > compare_id){
                temp = temp->right;
            }
            else if(id == compare_id){
                for(int i = 0; i < no_of_coloumns; i++){
                    temp->data[i] = data[i];
                }
                break;
            }
        }
    }

    long long getHashId(string id_s){
        long long key = 0;
        key = 0;
        for(int i = 0; i < id_s.length(); i++){
            key = (key + (id_s[i] * i));
        }
        return key;
    }

    TreeNode * getStart(){
        return root;
    }

    bool is_empty(){
        if(root == nullptr){
            return true;
        }
        return false;
    }

    bool is_full(){
        try{
            TreeNode * test = new TreeNode(0, NULL);
            delete test;
            return false;
        }catch(exception e){
            return true;
        }
    }

    int key(string str){
        int key = 0;
        for(int i = 0; i < str.length(); i++){
            key = (str[i] * i) + key;
        }
        key = key % 10000;
        return key;
    }
};
