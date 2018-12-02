#ifndef MYMAP_H
#define MYMAP_H

#include <iostream>
using namespace std;
#define NIL &sentinel

template<typename Key, typename Value> // T is key
class AuditoryMap{
public:
    struct node
       {
           Key _key;
           Value _value;
           node *left;
           node *right;
           bool red;
           node *p;
       };

    AuditoryMap();
    AuditoryMap(const AuditoryMap &map);
    void insert(Key key, Value value);
    bool contains(Key key);
    bool deleteKey(Key key);
    bool clear();
    node sentinel;
    node *root;
    class Iterator{
    };
    Iterator getFirst();
    Iterator getLast();
    int getSize();
    Value operator [](Key key);
    void operator <<(AuditoryMap &bk);
    //Book operator >>(stream);
    bool operator ==(AuditoryMap secondBook);
    // operators == for keys and values; and []; and << and >>
private:
    int _size;
    void leftRotate(node* x);
    void rightRotate(node* y);
    void insertFixUp(node* z);
    void treeWalk(node* x);
};


template <typename Key, typename Value> AuditoryMap<Key, Value>::AuditoryMap()
{
    sentinel = {0,0, NIL, NIL, false, nullptr};
    this->root = NIL;
    _size = 0;
}


template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::leftRotate(node* x)
{
    node *y = x->right;
    x->right = y->left;
    if(y->left != NIL)
        y->left->p = x;
    y->p = x->p;
    if(x->p == NIL)
        this->root = y;
    if(x == x->p->left)
            x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::rightRotate(node* y)
{
    node *x = y->left;
    y->left = x->right;
    if(x->right != NIL)
        x->right->p = y;
    x->p = y->p;
    if(y->p == NIL)
        this->root = x;
    if(y == y->p->right)
        y->p->right = x;
    else
        y->p->left = x;
    x->right = y;

    y->p = x;
}

template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::insertFixUp(node* z)
{
    while(z->p->red)
    {
        if(z->p == z->p->p->left)
        {
            node *y = z->p->p->right;
            if(y->red)
            {
                z->p->red = false;
                y->red = false;
                z->p->p->red = true;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    leftRotate(z);
                }
                z->p->red = false;
                z->p->p->red = true;
                rightRotate(z->p->p);
            }
        }
        else
        {
            node *y = z->p->p->left;
            if(y->red)
            {
                z->p->red = false;
                y->red = false;
                z->p->p->red = true;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z = z->p;
                    rightRotate(z);
                }
                z->p->red = false;
                z->p->p->red = true;
                leftRotate(z->p->p);
            }
        }
    }
    this->root->red = false;

}

template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::insert(keyType key, valueType value)
{
    node *x, *y, *z;
    y = NIL;
    x = this->root;
    z = new node();
    z->_key = key;
    z->_value = value;
    while(x != NIL)
    {
        y = x;
        if(z->_key < x->_key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == NIL)
        this->root = z;
    if(z->_key < y->_key)
        y->left = z;
    else
        y->right = z;
    z->left = NIL;
    z->right = NIL;
    z->red = true;
    insertFixUp(z);

    _size++;
}

template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::treeWalk(node* x)
{
    if(x != NIL)
//        cout << "no";
//    else
    {

        treeWalk(x->left);
        cout << x->_key;
        treeWalk(x->right);
    }
}



template <typename keyType, typename valueType> valueType AuditoryMap<keyType, valueType>::operator [](keyType key)
{
    node *pointer = NULL;
    pointer = isKey(root, key);
    if(pointer != NULL)
        return pointer->_value;
}

//template <typename keyType, typename valueType>
//typename Book<keyType, valueType>::node*
//Book<keyType, valueType>::(node* x, keyType key)
//{

//}

template <typename keyType, typename valueType>
typename AuditoryMap<keyType, valueType>::node*
AuditoryMap<keyType, valueType>::isKey(node *x, keyType key)
{
    while(x != NIL && key != x->_key)
    {
        if(key < x->_key)
            x = x->left;
        else
            x = x->right;
    }
    if (key == x->_key)return true;
    return false;
}

template <typename keyType, typename valueType>
typename AuditoryMap<keyType, valueType>::node*
AuditoryMap<keyType, valueType>::treeMin(node *x)
{
    while(x->left != NIL)
        x = x->left;
    return x;
}

template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::popFixUp(node *x)
{
    node *w;
    while(x != root && x->red == false)
    {
        if(x == x->p->left)
        {
            w = x->p->right;
            if(w->red == true)
            {
                w->red == false;
                x->p->red = true;
                this->leftRotate(x->p);
                w = x->p->right;
            }
            if(w->left->red == false && w->right->red == false)
            {
                w->red = true;
                x = x->p;
            }
            else
            {
                if(w->right->red == false)
                {
                    w->left->red = false;
                    w->red = true;
                    this->rightRotate(w);
                    w = x->p->right;
                }
                w->red = x->p->red;
                x->p->red = false;
                w->right->red = false;
                this->leftRotate(x->p);
                x = root;
            }
        }
        else
        {
            w = x->p->left;
            if(w->red == true)
            {
                w->red == false;
                x->p->red = true;
                this->rightRotate(x->p);
                w = x->p->left;
            }
            if(w->right->red == false && w->left->red == false)
            {
                w->red = true;
                x = x->p;
            }
            else
            {
                if(w->left->red == false)
                {
                    w->right->red = false;
                    w->red = true;
                    this->leftRotate(w);
                    w = x->p->left;
                }
                w->red = x->p->red;
                x->p->red = false;
                w->left->red = false;
                this->rightRotate(x->p);
                x = root;
            }
        }
    }
    x->red = false;
}


template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::pop(keyType key)
{
    node *x, *y, *z; bool yOriginalRed;
    z = this->isKey(root, key);
    if(!z || z == NIL)
        return;
    else
    {
        y = z;
        yOriginalRed = y->red;
        if(z->left == NIL)
        {
            x = z->left;
            this->transplant(z, z->right);
        }
        if(z->right == NIL)
        {
            x = z->left;
            this->transplant(z, z->left);
        }
        else
        {
            y = this->treeMin(z->right);
            yOriginalRed = y->red;
            x = y->right;
            if(y->p == z)
                x->p = y;
            else
            {
                this->transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            this->transplant(z,y);
            y->left = z->left;
            y->left->p = y;
            y->red = z->red;
        }
        if(yOriginalRed == false)
            this->popFixUp(x);
    }

}

template <typename keyType, typename valueType> void AuditoryMap<keyType, valueType>::transplant(node *x, node *y)
{
    if(x->p == NIL)
        root = y;
    if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->p = x->p;
}

template <typename keyType, typename valueType> int AuditoryMap<keyType, valueType>::getSize()
{
    return _size;
}

template <typename keyType, typename valueType> bool AuditoryMap<keyType, valueType>::operator ==(AuditoryMap secondBook)
{

}


#endif // MYMAP_H
