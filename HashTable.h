#ifndef HASHTABLE_H
#define HASHTABLE_H

#define KKK 2
#include <QVector>
#include <QString>
#include <iostream>
#include <fstream>
class Data{
public:

    int key;
    QVector<QString> d;
    Data(QVector<QString> in) {
        d = in;
        key = getKey();
    }

    Data() {
        d.push_back("");
        d.push_back("");
        d.push_back("");
        d.push_back("");
        d.push_back("");
    };
    ~Data() = default;
    int getKey() {
        int key = 0;
        for (auto ch : d[0]) {
            key = (ch.unicode() <= 57 && ch.unicode() >= 48) ? (key + ch.unicode() - 48) : (key + ch.unicode());
        }
        return key;
    }

    bool operator==(Data r) {
        return d.at(0) == r.d.at(0);
    }
    bool operator!=(Data r) {
        return d.at(0) != r.d.at(0);
    }
};

class HashTable {
    int defaultSize;
    int size;
    int busyNodes;
    double resizeGreater = 0.7;
    double resizeLower = 0.3;
    struct Node {
        bool isHere;
        Data d;
        Node() {
            isHere = false;
            d = Data();
        }
        Node(Data dtr) {
            isHere = true;
            d = dtr;
        }
        Node(QVector<QString> in) {
            isHere = true;
            d = Data(in);
        }
        ~Node() = default;
    };
    QVector <Node> nodes;

    int hashFunction1(int key) {
        return key % size;
    }
    int hashFunction2(int oldKey, int i, int k) {
        //std::cout << "z " << key + i * k;
        int key = (oldKey + i * k) % size;
        return key;
    }
    int resolutionOfСollisions(int key, int k, Data toAdd) {
        int oldKey = key;
    bool isFound = false;
    int i = 0;
    while (i <= (size / k) && !isFound) {
        key = hashFunction2(oldKey, i, k);
        if (nodes[key].d == toAdd && nodes[key].isHere)
            return -2;
        if (!nodes[key].isHere) {
            isFound = true;
        }
        i++;
        //std::cout << key << " ";
    }
    //std::cout << endl;
    if (isFound) {
        int check = key;
        oldKey = key;
        i = 0;
        while(i <= (size / k) && nodes[check].d != Data()){
            check = hashFunction2(oldKey, i, k);
            if (nodes[check].d == toAdd && nodes[check].isHere)
                return -2;
            i++;
        }
        return key;
    }
    return -1;
}
void resize(double mulResize) {
    if (size == defaultSize)
        return;
    int newSize = int(size * mulResize);
    if (defaultSize >= newSize)
        newSize = defaultSize;
    QVector<Node> newNodes(newSize);
    int pastSize = size;
    size = newSize;
    busyNodes = 0;
    std::swap(nodes, newNodes); // новое становится старым, старое становится новым
    for (int i = 0; i < pastSize; i++) {
        if(newNodes[i].isHere)
            add(newNodes[i].d);
    }
    newNodes.clear();

}

void add(Data& d) {
    if (busyNodes + 1 >= int(resizeGreater * size)) {
        resize(2);
    }
    int position = hashFunction1(d.key); // тут выбираю куда вставлять элемент
    if (!nodes[position].isHere) {
        int check = find(position, KKK, d);
        if (check < 0) {
            nodes[position] = Node(d);
            busyNodes++;
        }
        else
            std::cout << "Cannot add same element\n";
    }
    else {
        position = resolutionOfСollisions(position, KKK, d);
            if (position >= 0) {
            nodes[position].d = d;
            nodes[position].isHere = true;
            busyNodes++;
        }
        else if (position == -2) {
            std::cout << "Cannot add same element\n";
        }
        else {
            resize(2);
            add(d);
        };
    }
}
int find(int key, int k, Data& d) {
    int oldKey = key;
    bool isFound = false;
    int i = 0;
    while (i <= (size / k) && !isFound && nodes[key].d != Data()) {
        //std::cout << key << " \n";
        key = hashFunction2(oldKey, i, k);
        //std::cout << key << " \n";
        if (nodes[key].isHere && nodes[key].d == d) {
            return key;
        }
        i++;
    }
    //std::cout << endl;
    return -1;
}
void remove(Data& d) {
    if (busyNodes - 1 <= int(resizeLower * size)) {
        resize(0.5);
    }
    int position = hashFunction1(d.key); // тут выбираю куда вставлять элемент
    if (nodes[position].isHere && nodes[position].d == d) {
        nodes[position].isHere = false;
        busyNodes--;
    }
    else {
        position = find(position, KKK, d);
        if (position >= 0) {
            nodes[position].isHere = false;
            busyNodes--;
        }
        else {
            std::cout << "Cannot find them\n";
        };
    }
}

public:
void add(QVector<QString> in) {
    Data newEl = Data(in);
    add(newEl);
}
QVector<QVector<QString>> find(QString str) {
    QVector<QString> in;
    QVector<QVector<QString>> out;
    in.push_back(str);
    Data findEl = Data(in);
    int position = hashFunction1(findEl.key);
    position = find(position, KKK, findEl);
    if (position >= 0) {
        out.push_back(nodes[position].d.d);
        std::cout << "Element is on position: " << position << std::endl;
    }
    return out;
}
void remove(QString str) {
    QVector<QString> in;
    in.push_back(str);
    Data remEl = Data(in);
    remove(remEl);
}
void print() {
    int i = 0;
    std::ofstream ofs;
    ofs.open("hashtable.txt", std::ios::out);
//    std::cout << "###########################\n";
    for (auto el : nodes) {
        //if (el.isHere)
        ofs << i << ". " << hashFunction1(el.d.key) << " [" << el.isHere << "] "<< el.d.d.at(0).toStdString() << " "<< el.d.d.at(1).toStdString() << " " << el.d.d.at(2).toStdString() << " " << el.d.d.at(3).toStdString()<< " " <<  el.d.d.at(4).toStdString() << std::endl;
        // else
        //   std::cout << i << ". [" << el.isHere << "]\n";
        i++;
    }
//    std::cout << "###########################\n";
    ofs.close();
}
HashTable(int s) {
    size = s;
    defaultSize = s;
    for (int i = 0; i < size; i++) {
        nodes.push_back(Node());
    }
    busyNodes = 0;
}
~HashTable() = default;
};



#endif // HASHTABLE_H
