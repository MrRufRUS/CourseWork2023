#ifndef AVLTREE_H
#define AVLTREE_H
#define SPACE 10
#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>
#include <fstream>

class Node {
public:
    QVector<QString> data;
    Node* next;
    Node() {
        data.push_back(" ");
        data.push_back(" ");
        data.push_back(" ");
        data.push_back(" ");
        data.push_back(" ");
        next = this;
    }
    Node(QVector<QString> in) {
        data = in;
        next = this;
    }
};
class TreeNode {
public:
    Node* list;
    TreeNode* left;
    TreeNode* right;
    int bal;

    TreeNode() {
        list = new Node();
        bal = 0;
        left = nullptr;
        right = nullptr;
    }
    TreeNode(QVector<QString> in) {
        list = new Node(in);
        bal = 0;
        left = nullptr;
        right = nullptr;
    }
};
class AVLTree {
private:
    int index;
    TreeNode* p;
    TreeNode* p1;
    TreeNode* p2;
    bool h;
    void insertAtTail(QVector<QString> in, Node*& head) {
        Node* n = new Node(in);
        if (head == nullptr) {
            n->next = n;
            head = n;
        }
        else {
            Node* temp = head;

            while (temp->next != head) {
                temp = temp->next;
            }

            temp->next = n;
            n->next = head;
        }
    }
    void insert(QVector<QString> in, TreeNode* &p, bool &h) {

        if (p == nullptr) {
            p = new TreeNode(in);
            h = true;
        }
        else if (p->list->data.at(index) > in.at(index)) {
            insert(in, p->left, h);
            if (h) {
                if (p->bal == 1) {
                    p->bal = 0;
                    h = false;
                }
                else if (p->bal == 0) {
                    p->bal = -1;
                }
                else {
                    p1 = p->left;

                    if (p1->bal == -1) {
                        p->left = p1->right;
                        p1->right = p;
                        p->bal = 0;
                        p = p1;
                    }
                    else {
                        p2 = p1->right;
                        p1->right = p2->left;
                        p2->left = p1;
                        p->left = p2->right;
                        p2->right = p;
                        if (p2->bal == -1)
                            p->bal = 1;
                        else
                            p->bal = 0;

                        if (p2->bal == 1)
                            p1->bal = -1;
                        else
                            p1->bal = 0;
                        p = p2;
                    }
                    p->bal = 0;
                    h = false;
                }
            }
        }
        else if (p->list->data.at(index) < in.at(index)) {
            insert(in, p->right, h);
            if (h) {
                if (p->bal == -1) {
                    p->bal = 0;
                    h = false;
                }
                else if (p->bal == 0)
                    p->bal = 1;
                else {
                    p1 = p->right;
                    if (p1->bal == 1) {
                        p->right = p1->left;
                        p1->left = p;
                        p->bal = 0;
                        p = p1;
                    }
                    else {
                        p2 = p1->left;
                        p1->left = p2->right;
                        p2->right = p1;
                        p->right = p2->left;
                        p2->left = p;

                        if (p2->bal == 1)
                            p->bal = -1;
                        else
                            p->bal = 0;

                        if (p2->bal == -1)
                            p1->bal = 1;
                        else
                            p1->bal = 0;
                        p = p2;
                    }
                    p->bal = 0;
                    h = false;
                }
            }
        }
        else {
            insertAtTail(in, p->list);
        }
    }
    int countOfRepeats(Node* head) {
        int count = 0;
        if (head != nullptr) {

            Node* temp = head;
            do
            {
                count++;
                temp = temp->next;
            } while (temp != head);
        }
        return count;
    }
    void balanceL(TreeNode*& p, bool& h) {
        TreeNode* p1;
        TreeNode* p2;

        if (p->bal == -1)
            p->bal = 0;
        else if (p->bal == 0) {
            p->bal = 1;
            h = false;
        }
        else {
            p1 = p->right;
            if (p1->bal >= 0) {
                //cout << "LL\n";// one LL-rotation
                p->right = p1->left; p1->left = p;
                if (p1->bal == 0) {
                    p->bal = 1; p1->bal = -1; h = false;
                }
                else {
                    p->bal = 0; p1->bal = 0;
                }
                p = p1;
            }
            else {
                //cout << "RL\n";// double RL-rotation
                p2 = p1->left;
                p1->left = p2->right; p2->right = p1;
                p->right = p2->left; p2->left = p;
                if (p2->bal == 1)
                    p->bal = -1;
                else
                    p->bal = 0;
                if (p2->bal == -1)
                    p1->bal = 1;
                else
                    p1->bal = 0;
                p = p2; p2->bal = 0;
            }
        }
    }
    void balanceR(TreeNode*& p, bool& h) {
        TreeNode* p1;
        TreeNode* p2;

        if (p->bal == 1)
            p->bal = 0;
        else if (p->bal == 0) {
            p->bal = -1;
            h = false;
        }
        else {
            p1 = p->left;
            if (p1->bal <= 0) {
                //cout << "RR\n";// one RR-rotation
                p->left = p1->right; p1->right = p;
                if (p1->bal == 0) {
                    p->bal = -1; p1->bal = 1; h = false;
                }
                else {
                    p->bal = 0; p1->bal = 0;
                }
                p = p1;
            }
            else {
                //cout << "LR\n";// double LR-rotation
                p2 = p1->right;
                p1->right = p2->left; p2->left = p1;
                p->left = p2->right; p2->right = p;
                if (p2->bal == -1)
                    p->bal = 1;
                else
                    p->bal = 0;
                if (p2->bal == 1)
                    p1->bal = -1;
                else
                    p1->bal = 0;
                p = p2;
                p2->bal = 0;
            }
        }
    }
    void deleteAtTail(Node* head) {
        Node* temp = head;
        while (temp->next->next != head) {
            temp = temp->next;
        }

        Node* todelete = temp->next;
        temp->next = head;

        delete todelete;
    }
    void del(TreeNode*& r, TreeNode*& q, bool& h) {
        if (r->right != nullptr) {
            del(r->right, q, h);
            if (h)
                balanceR(r, h);
        }
        else {
            q->list->data = r->list->data;
            q->list = r->list;
            q = r; r = r->left; h = true;
        }
    }
    void deleteElem(QVector<QString> in, TreeNode*& p, bool& h) {
        TreeNode* q;
        if (p == nullptr) {
            return;
        }
        else if (p->list->data.at(index) > in.at(index)) {
            deleteElem(in, p->left, h);
            if (h)
                balanceL(p, h);
        }
        else if (p->list->data.at(index) < in.at(index)) {
            deleteElem(in, p->right, h);
            if (h)
                balanceR(p, h);
        }
        else
        {

            if (countOfRepeats(p->list) - 1 != 0)
                deleteAtTail(p->list);
            else {
                q = p;
                if (q->right == nullptr) {
                    p = q->left; h = true;
                }
                else if (q->left == nullptr) {
                    p = q->right; h = true;
                }
                else {
                    del(q->left, q, h);
                    if (h)
                        balanceL(p, h);
                }
                //delete q;
            }
        }
    }
    void printList(Node* head) {

        if (head != nullptr) {

            Node* temp = head;
            do
            {
                for (int i = 0; i < temp->data.size(); i++)
                    std::cout << temp->data.at(i).toStdString() << " ";
                temp = temp->next;
            } while (temp != head);
            std::cout << std::endl;

        }
    }
    void printTree(TreeNode* head, int space) {
        if (head == nullptr)
            return;
        space += SPACE;
        printTree(head->right, space);
        std::cout << std::endl;
        for (int i = SPACE; i < space; i++)
            std::cout << " ";
        printList(head->list);
        printTree(head->left, space);
    }
    QVector<QVector<QString>> search(Node*& head) {
        QVector<QVector<QString>> found;
        Node* temp = head;
        while (temp->next != head) {
            found.push_back(head->data);
        }
        return found;
    }

    TreeNode* recursiveSearch(TreeNode*& head, QString strToSearch) {
        if (head == nullptr)
            return head;
        if (head->list->data.at(index) == strToSearch) {
            return head;
        }
        else if (strToSearch < head->list->data.at(index))
            return recursiveSearch(head->left, strToSearch);

        else
            return recursiveSearch(head->right, strToSearch);
    }
    int count(TreeNode* head) {
        if (head == nullptr) {
            return 0;
        }
        return countOfRepeats(head->list) +  count(head->left) + count(head->right);
    }
    void dispose(TreeNode* head) {
        if (head == nullptr) {
            return;
        }

        dispose(head->left);
        dispose(head->right);
        delete head;
        head = nullptr;
    }
public:

    AVLTree(int i) {
        index = i;
        p = nullptr;
        h = false;
    }
    void insert(QVector<QString> in) {
        insert(in, p, h);
        //print();
    }
    void print() {
        //std::cout << "========================================================\n";
        printTree(p, 5);
        //std::cout << "\n========================================================\n";
    }
    void deleteElem(QVector<QString> in) {
        deleteElem(in, p, h);
    }
    QVector<QVector<QString>> recursiveSearch(QString strToSearch) {
        TreeNode *q = recursiveSearch(p, strToSearch);
        if (q != nullptr) {
            auto searched = search(q->list);
            return searched;
        }
        else {
            return QVector<QVector<QString>> (1, QVector<QString> (1, "Empty>"));
        }
    }
    void dispose() {
        dispose(p);
    }
};

#endif // AVLTREE_H
