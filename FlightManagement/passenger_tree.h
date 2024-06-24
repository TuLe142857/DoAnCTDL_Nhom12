#ifndef PASSENGER_TREE_H
#define PASSENGER_TREE_H

#include"passengers.h"

#include<math.h>
#include<cstring>
#include<iostream>
#include <fstream>

using namespace std;

// fstream f("passenger_db.dat", ios::binary |ios::out|ios::in); 

struct PNode {
    Passenger pas;
    PNode *left;
    PNode *right;
    int height;
    
    PNode() : pas("", "", "", ""), left(NULL), right(NULL), height(0) {}
};

// STRUCT HERE



PNode * minValueNode(PNode* node) 
{ 
    PNode* current = node; 
 
  
    while (current->left != NULL) 
        current = current->left; 
 
    return current; 
}



void print(Passenger p) {
    cout << p.getCccd() << " : " << p.getHo() << " : " << p.getTen() << " : " << p.getSex() <<endl;
}

int height(PNode *root) {
    if (!root) {
        return -1;
    } else {
        return root->height;
    }
}

int getBalance(PNode *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - 
           height(N->right); 
}

PNode *singleRotateLeft(PNode *x) {
    PNode *w = x->left;
    x->left = w->right;
    w->right = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    w->height = max(x->height, height(w->left)) + 1;
    
    return w;
}

PNode *singleRotateRight(PNode *x) {
    PNode *w = x->right;
    x->right = w->left;
    w->left = x;
    x->height;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    w->height = max(x->height, height(w->right)) + 1;
     
    return  w;
}

PNode *doubleRotateLeft(PNode *z) {
    z->left = singleRotateRight(z->left);
    return singleRotateLeft(z);
}

PNode *doubleRotateRight(PNode *z) {
    z->right = singleRotateLeft(z->right);
    return singleRotateRight(z);
}

PNode *insert(PNode *root, Passenger pas) {
    if (!root) {
        root = new PNode;
        if (!root) {
            return NULL;
        } else {
            root->pas = pas;
            root->height = 0;
            root->left = root->right = NULL;
        }
    } else if (atoll(pas.getCccd()) < atoll(root->pas.getCccd())) {
        root->left = insert(root->left, pas);
        if (height(root->left) - height(root->right) == 2) {
            if (atoll(pas.getCccd()) < atoll(root->left->pas.getCccd())) {
                root = singleRotateLeft(root);
            } else {
                root = doubleRotateLeft(root);
            }
        }
    } else if (atoll(pas.getCccd()) > atoll(root->pas.getCccd())) {
        root->right = insert(root->right, pas);
        if (height(root->right) - height(root->left) == 2) {
            if (atoll(pas.getCccd()) > atoll(root->right->pas.getCccd())) {
                root = singleRotateRight(root);
            } else {
                root = doubleRotateRight(root);
            }
        }
    } 

    root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

PNode *findByCccd(PNode *root, char* cccd) {
	if(root == NULL) {
		return NULL;
	}
	
	if(atoll(cccd)< atoll(root->pas.getCccd())) {
		return findByCccd(root->left, cccd);
	}else if(atoll(cccd )> atoll(root->pas.getCccd()) ){
		return findByCccd(root->right, cccd);
	}
	
	return root;
}

int countNodes(PNode* root) {
    if (!root)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void traverTree_ltl(PNode *root, PNode **Plist, int& n) {
    if (root) {
        traverTree_ltl(root->left, Plist, n);
		Plist[n++] = root;
		traverTree_ltl(root->right, Plist, n);
	} else {
        return; 
    }
}

void traverTree(PNode *root) {
    if (root) {
        traverTree(root->left);
		print(root->pas);
		traverTree(root->right);
	} 
}


void loadTreeData(PNode *&root) {
	Passenger pas; 
	//fstream f("passengers.dat", ios::binary |ios::out|ios::in);
    fstream f("Data\\Passengers.dat", ios::binary |ios::out|ios::in);
	while(f.read(reinterpret_cast<char*>(& pas), sizeof(Passenger))) {
		root = insert(root, pas);
	}
	f.close();
}
  
// start load data

int countObjects() {
    //ifstream file("passengers.dat", ios::binary);
    ifstream file("Data//Passengers.dat", ios::binary |ios::in |ios::out);
    if (!file) {
        cerr << "Could not open file." << endl;
        return -1;
    }

    Passenger temp;
    int count = 0;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Passenger))) {
        count++;
    }
    
    return count;
}

Passenger *buildArrayData(int count){
    ifstream file("Data\\Passengers.dat", ios::binary|ios::in |ios::out);
    if (!file) {
        cerr << "Could not open file." << endl;
    }

    Passenger temp;

    Passenger *pas_arr = new Passenger[count];
    int index = 0;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Passenger))) {
        pas_arr[index] = temp;
        index++;
    }
    
    file.close();
    return pas_arr;
}

PNode *build(int start, int end, Passenger* data) {
	  if (start > end) {
            return NULL;
        }

        int mid = start + (end - start) / 2;
        PNode *node = new PNode;
        
        node->pas = data[mid];

        node->left = build(start, mid - 1, data);
        node->right = build(mid + 1, end, data);

        node->height = 1 + max(height(node->left), height(node->right));

        return node;
}

PNode *buildAVLTree(){
	int count = countObjects();
	Passenger *passenger_array = buildArrayData(count);
	int start = 0;
	PNode *root = build(start, count-1, passenger_array);
	delete[] passenger_array;
	return root;
}

// end load data

void save(PNode *root, fstream &f) {
    if (root) {
        save(root->left, f);
        if (!f.write(reinterpret_cast<char*>(&(root->pas)), sizeof(Passenger))) {
            cerr << "Error writing to file." << endl;
            return;
        }
        save(root->right, f);
    }
}

void saveData(PNode *root) {
    //fstream f("passengers.dat", ios::binary | ios::out | ios::trunc); 
    fstream f("Data\\Passengers.dat", ios::binary | ios::out | ios::trunc);
    if (!f) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    f.seekp(0, ios::beg);
    save(root, f);
    f.close();
}
  

PNode* deleteNode(PNode* root, Passenger pas) 
{ 
    if (root == NULL) 
        return root; 
 
    if ( atoll(pas.getCccd()) < atoll(root->pas.getCccd() ) )
        root->left = deleteNode(root->left, pas); 
 
    else if( atoll(pas.getCccd()) > atoll(root->pas.getCccd()) )
        root->right = deleteNode(root->right, pas); 

    else
    { 
  
        if( (root->left == NULL) ||
            (root->right == NULL) ) 
        { 
            PNode *temp = root->left ? 
                         root->left : 
                         root->right; 
 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else 
            *root = *temp; 
                          
            delete(temp); 
        } 
        else
        { 

            PNode* temp = minValueNode(root->right); 
 
         
            root->pas.setCccd(temp->pas.getCccd()); 
 
            root->right = deleteNode(root->right, 
                              temp->pas); 
        } 
    } 
 

    if (root == NULL) 
    return root; 
 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
 

    int balance = getBalance(root); 
 

    if (balance > 1 && 
        getBalance(root->left) >= 0) 
        return singleRotateLeft(root); 
 

    if (balance > 1 && 
        getBalance(root->left) < 0) 
    { 
        root->left = singleRotateRight(root->left); 
        return singleRotateLeft(root); 
    } 
 
    if (balance < -1 && 
        getBalance(root->right) <= 0) 
        return singleRotateRight(root); 
 
  
    if (balance < -1 && 
        getBalance(root->right) > 0) 
    { 
        root->right = singleRotateLeft(root->right); 
        return singleRotateRight(root); 
    } 
 
    return root; 
} 

PNode* search(PNode* root, char* target_id) {
    if (root == NULL || strcmp(root->pas.getCccd(), target_id) == 0)
        return root;
    
    if (atoll(root->pas.getCccd()) < atoll(target_id))
        return search(root->right, target_id);
    
    return search(root->left, target_id);
}

int deleteTree(PNode* &node) {
    if (node == nullptr)
        return 0;

    int numDeleted = 1 + deleteTree(node->left) + deleteTree(node->right);
    
    delete node;

    node = nullptr;
    
    return numDeleted;
}




#endif
