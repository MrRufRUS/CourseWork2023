#include<iostream>
#include<string>
#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>
#include <fstream>
#define SPACE 10

using namespace std;

class Node {
public:
    struct List {
        QVector<QString> value;
        List* next;
        List() {
            value.push_back(" ");
            value.push_back(" ");
            value.push_back(" ");
            value.push_back(" ");
            value.push_back(" ");
            next = this;
        }
        List(QVector<QString> v) {
            value = v;
            next = this;

        }
    };
    List* list;
    Node* left;
    Node* right;
    Node() {
        list = new List();
        left = NULL;
        right = NULL;

    }
    Node(QVector<QString> v) {
        list = new List(v);
        left = NULL;
        right = NULL;

    }

};

class AVLTree {
private:
    int index;

    Node* root;
    bool isTreeEmpty() {
        if (root == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    int height(Node* head) {
        if (head == NULL)
            return -1;
        else {
            int lheight = height(head->left);
            int rheight = height(head->right);

            if (lheight > rheight)
                return (lheight + 1);
            else return (rheight + 1);
        }
    }
    int getBalanceFactor(Node* n) {
        if (n == NULL)
            return -1;
        return height(n->left) - height(n->right);
    }
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }
    void printList(Node* head, std::ofstream& ofs) {

        if (head != NULL) {

            Node::List* temp = head->list;
            do
            {
                for(int i = 0; i < temp->value.size(); i++)
                    ofs << temp->value.at(i).toStdString() << " ";
                temp = temp->next;
                ofs << " | ";
            } while (temp != head->list);

            ofs << endl;
        }
    }

    void insertAtTail(Node*& head, QVector<QString> val) {
        Node::List* n = new Node::List(val);
        if (head == NULL) {
            n->next = n;
            head->list = n;
        }
        else {
            Node::List* temp = head->list;

            while (temp->next != head->list) {
                temp = temp->next;
            }

            temp->next = n;
            n->next = head->list;
        }
    }
    Node* insert(Node* head, QVector<QString> val) {

        Node* new_node = new Node(val);
        if (head == NULL) {
            head = new_node;
            return head;
        }

        if (new_node->list->value.at(index) < head->list->value.at(index)) {
            head->left = insert(head->left, val);
        }
        else if (new_node->list->value.at(index) > head->list->value.at(index)) {
            head->right = insert(head->right, val);
        }
        else if (new_node->list->value.at(index) == head->list->value.at(index)) {
            insertAtTail(head, val);
        }

        int bf = getBalanceFactor(head);
        if (bf > 1 && new_node->list->value.at(index) < head->left->list->value.at(index))
            return rightRotate(head);

        if (bf < -1 && new_node->list->value.at(index) > head->right->list->value.at(index))
            return leftRotate(head);

        if (bf > 1 && new_node->list->value.at(index) > head->left->list->value.at(index)) {
            head->left = leftRotate(head->left);
            return rightRotate(head);
        }

        if (bf < -1 && new_node->list->value.at(index) < head->right->list->value.at(index)) {
            head->right = rightRotate(head->right);
            return leftRotate(head);
        }

        return head;

    }
    Node* maxValueNode(Node* node) {
        Node* current = node;
        while (current->right != NULL) {
            current = current->right;
        }
        return current;
    }
    void deleteAtHead(Node::List* &head){
        Node::List* temp=head;
        while(temp->next!=head){
            temp=temp->next;
        }

        Node::List* todelete=head;
        temp->next=head->next;
        head=head->next;

        delete todelete;
    }
    void deletion(Node::List* &head, QVector<QString> v){

        if(head == nullptr) {
            return;
        }
        if(head->value == v) {
            deleteAtHead(head);
            return;
        }
        Node::List* temp=head;
        while(temp->next->value != v && temp->next != head){
            temp=temp->next;
        }
        if (temp->next->value == v) {
        //qDebug() << "Avl delete";
        Node::List* todelete=temp->next;
        temp->next=temp->next->next;

        delete todelete;
        }
    }
    Node* deleteNode(Node* head, QVector<QString> v) {
        if (head == NULL) {
            return NULL;
        }
        else if (v.at(index) < head->list->value.at(index)) {
            head->left = deleteNode(head->left, v);
        }
        else if (v.at(index) > head->list->value.at(index)) {
            head->right = deleteNode(head->right, v);
        }
        else {
            if (head->list->next != head->list) {
                deletion(head->list, v);
            }
            else {
                Node *r = head->right;
                if (head->right == NULL) {
                    Node *l = head->left;
                    delete (head);
                    head = l;
                } else if (head->left == NULL) {
                    delete (head);
                    head = r;
                } else {
                    while (r->left != NULL) r = r->left;
                    head->list = r->list;       // Переносим значения из мин. левого в удаляемый узел
                    r->list = new Node::List();  // На мин. левом ставим значения гарантированного удаления
                    head->right = deleteNode(head->right, r->list->value);
                }
            }
        }

        int bf = getBalanceFactor(head);
        if (bf == 2 && getBalanceFactor(head->left) >= 0)
            return rightRotate(head);
        else if (bf == 2 && getBalanceFactor(head->left) == -1) {
            head->left = leftRotate(head->left);
            return rightRotate(head);
        }
        else if (bf == -2 && getBalanceFactor(head->right) <= -0)
            return leftRotate(head);
        else if (bf == -2 && getBalanceFactor(head->right) == 1) {
            head->right = rightRotate(head->right);
            return leftRotate(head);
        }

        return head;
    }
    void printTree(Node* head, int space, std::ofstream& ofs) {
        if (head == NULL)
            return;
        space += SPACE;
        printTree(head->right, space, ofs);
        ofs << endl;
        if(head->list->value.at(index) != " ") {
            for (int i = SPACE; i < space; i++)
                ofs << " ";
            printList(head, ofs);
        }
        printTree(head->left, space, ofs);
    }
    Node* recursiveSearch(Node* head, QString val, int& steps) {
        steps++;
        if (head == NULL || head->list->value.at(index) == val)
            return head;

        else if (val < head->list->value.at(index))
            return recursiveSearch(head->left, val, steps);

        else
            return recursiveSearch(head->right, val, steps);
    }
    void dispose(Node* head)
    {
        if (head == NULL) {
            return;
        }

        dispose(head->left);
        dispose(head->right);
        delete head;
        head = NULL;
    }
public:
    AVLTree(int i) {
        index = i;
        root = nullptr;
    }
    void insert(QVector<QString> in) {
        root = insert(root, in);
        //print();
    }
    void print() {
//        std::cout << "========================================================\n";
        std::ofstream ofs;
        ofs.open(("avl"+ std::to_string(index) + ".txt"), ios::out);
        printTree(root, 5, ofs);
//        std::cout << "\n========================================================\n";
        ofs.close();
    }
    void deleteElem(QVector<QString> in) {
        root = deleteNode(root, in);
    }
    QVector<QVector<QString>> recursiveSearch(QString strToSearch, int& steps) {
        QVector<QVector<QString>> searched;
        Node *q;
        q = recursiveSearch(root, strToSearch, steps);
        if (q != nullptr) {

            Node::List* p = q->list;
            do
            {
                searched.push_back(p->value);
                p = p->next;
            } while (p != q->list);
        }
        return searched;
    }
    void dispose() {
        dispose(root);
    }
};
