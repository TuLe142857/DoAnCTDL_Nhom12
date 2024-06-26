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

struct Node {
    PNode *pNode;
    Node *next;
    
    Node(PNode *pNode) : pNode(pNode), next(NULL) {}
};

class Queue {
private:
    Node *front;
    Node *rear;
    
public:
    Queue() : front(NULL), rear(NULL) {}
    
    bool isEmpty() {
        return front == NULL;
    }
    
    void enqueue(PNode *pNode) {
        Node *temp = new Node(pNode);
        if (rear == NULL) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }
    
    PNode *dequeue() {
        if (isEmpty()) {
            cout <<("Queue is empty");
        }
        Node *temp = front;
        front = front->next;
        
        if (front == NULL) {
            rear = NULL;
        }
        
        PNode *pNode = temp->pNode;
        delete temp;
        return pNode;
    }
    
    PNode *peek() {
        if (isEmpty()) {
            cout << ("Queue is empty");
        }
        return front->pNode;
    }
    
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

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

PNode *singleRotateLeft(PNode *x) {
	cout << "single rotate" << endl;
    PNode *w = x->left;
    x->left = w->right;
    w->right = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    w->height = max(x->height, height(w->left)) + 1;
    
    return w;
}

PNode *singleRotateRight(PNode *x) {
	cout << "single rotate" << endl;
    PNode *w = x->right;
    x->right = w->left;
    w->left = x;
    x->height;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    w->height = max(x->height, height(w->right)) + 1;
     
    return  w;
}

PNode *doubleRotateLeft(PNode *z) {
	cout << "double rotate" << endl;
    z->left = singleRotateRight(z->left);
    return singleRotateLeft(z);
}

PNode *doubleRotateRight(PNode *z) {
	cout << "double rotate" << endl;
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

void loadTreeData(PNode *&root) {
	Passenger pas; 
	//fstream f("passengers.dat", ios::binary |ios::out|ios::in);
    fstream f("Data\\Passengers.dat", ios::binary |ios::out|ios::in);
	while(f.read(reinterpret_cast<char*>(& pas), sizeof(Passenger))) {
		root = insert(root, pas);
	}
	f.close();
}

void save(PNode *root, fstream &f) {
	PNode *temp;
	Queue queue;
	
	if(!root) {
		return;
	}
	
	queue.enqueue(root);
	while(!queue.isEmpty()) {
		temp = queue.dequeue();
		if (!f.write(reinterpret_cast<char*>(&(temp->pas)), sizeof(Passenger))) {
            cerr << "Error writing to file." << endl;
            return;
        }
        
        if(temp->left) {
        	queue.enqueue(temp->left);
		}
		
		if(temp->right) {
        	queue.enqueue(temp->right);
		}
	}
}

void saveData(PNode *root) {
    fstream f("Data\\Passengers.dat", ios::binary | ios::out | ios::trunc);
    if (!f) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    f.seekp(0, ios::beg);
    save(root, f);
    f.close();
}

void deleteTree(PNode *&node) {
	if (node == NULL) {
		return;
	}
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

PNode* search(PNode* root, char* target_id) {
    if (root == NULL || strcmp(root->pas.getCccd(), target_id) == 0)
        return root;
    
    if (atoll(root->pas.getCccd()) < atoll(target_id))
        return search(root->right, target_id);
    
    return search(root->left, target_id);
}




#endif
