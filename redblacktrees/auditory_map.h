#ifndef AUDITORY_MAP_H
#define AUDITORY_MAP_H

#include <iostream>
using namespace std;

template<typename Key, typename Value>
class AuditoryMap
{
    public:
    AuditoryMap() 											//конструктор по умолчанию
    {
        root = NULL;
    }
    class iterator;

    typedef iterator const_iterator;

    iterator begin();
    iterator end();
    template<class T, class N>
    friend std::ostream& operator<< (std::ostream&, AuditoryMap&);

    template<class T, class N>
    friend std::istream& operator>> (std::istream&, AuditoryMap&);

    bool operator== (AuditoryMap&);

    void insert(const Key& key, const Value& value)						// функция вставки
    {
        Node *node, *parent, *z, *u;
        parent = NULL;
        node = root;

        while (node)
        {
            parent = node;
            if (key < node->key)
            {
                node = node->left;
            }
            else if (key > node->key)
            {
                node = node->right;
            }
        }

        if (!parent)																	//при отсутствии родительского узла будет произведена вставка в корень
        {
            z = root = new Node;
            z->key = key;
            z->value = value;
            z->colour = BLACK;
            z->parent = z->left = z->right = NULL;
        }

        else
        {
            z = new Node;
            z->key = key;
            z->value = value;
            z->colour = RED;
            z->parent = parent;
            z->left = z->right = NULL;

            if (z->key < parent->key)
            {
                parent->left = z;
            }
            else
            {
                parent->right = z;
            }
         }

        while (z->parent && z->parent->colour == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                u = z->parent->parent->right;

                if (u && u->colour == RED)
                {
                    z->parent->colour = BLACK;
                    u->colour = BLACK;
                    z->parent->parent->colour = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }

                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                rightRotate(z->parent->parent);
                }

            }

            else
            {
                u = z->parent->parent->left;

                if (u && u->colour == RED)
                {
                    z->parent->colour = BLACK;
                    u->colour = BLACK;
                    z->parent->parent->colour = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->colour = BLACK;
                    z->parent->parent->colour = RED;
                    leftRotate(z->parent->parent);
                }

            }

            root->colour = BLACK;
        }

    }

 bool contains(const Key& key)
  {
     Node *node = root;

      while(node && key != node ->_key)
      {
          if(key < node->_key)
              node = node->left;
          else
              node = node->right;
      }
      if (key == node->_key)return true;
      return false;
  }

  void deleteKey(const Key& key)													//функция удаления
    {
        Node *node = root;
        Node *y, *x;

        while (node)
        {
            if (key < node->key)
            {
                node = node->left;
            }
            else if (key > node->key)
            {
                node = node->right;
            }
            else
            {
                break;
            }
        }

        if (!node || node->key != key)
        {
            throw runtime_error("Cannot Delete: value with requested key not found");
        }

        if (!node->left || !node->right )
        {
            y=node;
        }

        else
        {
            y = TreeSuccessor(node);
            y->colour = node->colour;
        }

        if (y->left)
        {
            x = y->left;
        }

        else
        {
            x = y->right;
        }

        if(x)
            x->parent = y->parent;

        if(!y->parent)
        {
            root = x;
        }

        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }

        else
        {
            y->parent->right = x;
        }

        if(y!= node)
        {
            node->key = y->key;
            node->colour = y->colour;
            node->value = y->value;
        }

        if (y->colour == BLACK && x!=NULL)
        {
            Node *w;
            while (x != root && x->colour == BLACK)
            {
                if (x == x->parent->left)
                {
                    w = x->parent->right;

                    if (w->colour == RED)
                    {
                        w->colour = BLACK;
                        x->parent->colour = RED;
                        leftRotate(x->parent);
                        w =  x->parent->right;
                    }

                    if (w->left->colour == BLACK && w->right->colour == BLACK)
                    {
                        w->colour = RED;
                        x = x->parent;
                    }

                    else if (w->right->colour == BLACK)
                    {
                        w->left->colour = BLACK;
                        w->colour = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }

                    w->colour = x->parent->colour;
                    x->parent->colour = BLACK;
                    w->right->colour = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
                else
                {
                    w = x->parent->left;

                    if (w->colour == RED)
                    {
                        w->colour = BLACK;
                        x->parent->colour = RED;
                        rightRotate(x->parent) ;
                        w =  x->parent->left;
                    }

                    if (w->right->colour == BLACK && w->left->colour == BLACK)
                    {
                        w->colour = RED;
                        x = x->parent;
                    }

                    else if (w->left->colour == BLACK)
                    {
                        w->right->colour = BLACK;
                        w->colour = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    w->colour = x->parent->colour;
                    x->parent->colour = BLACK;
                    w->left->colour = BLACK;
                    rightRotate(x->parent);

                    x = root;

                }

                x->colour = BLACK;

            }
        }

    }


  Value& getValue(const Key& key)
    {
        Node *node = root;

        while (node)
        {
            if (key < node->key  )
            {
                node = node->left;
            }
            else if (key > node->key )
            {
                node = node->right;
            }

           else
           {
                return node->value;
           }

        }

        throw runtime_error("No value with requested key");
    }


  Value minimumValue ()
    {
        Node *x =root;
        while (x->left)
        {
            x = x->left;
        }

        return x->key;
    }

  Value maximumValue ()
    {
        Node *x =root;

        while (x->right)
        {
            x = x->right;
        }

        return x->key;
    }

  void displayInfo()
    {
        displayInfo(root, 0);
    }






public:
  enum NodeColour
    {
        RED,
        BLACK
    };

  struct Node
    {
        NodeColour colour;
        Key key;
        Value value;
        Node *parent;
        Node *left;
        Node *right;
    };
    Node *root;
    /*
template<class T, class N>
class MyMap<T, N>::Node
{

public:

    Node();
    Node(T, N);
    Node(Node&);
    Node(Node*);
    ~Node();

    T* key;
    N* value;

    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    bool color = true;

    Node* grandparent();
    Node* uncle();
    Node* sibling();
    void free();
    bool is_leaf();

    Node operator->();
    Node& operator= (Node&);
};Node *root;
     */

  void leftRotate(Node *x)
    {
        Node *y;

        y = x->right;
        x->right = y->left;

        if (y->left)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

 void rightRotate(Node *x)
    {
        Node *y;

        y = x->left;
        x->left = y->right;

        if (y->right)
        {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
  }

 Node *TreeSuccessor(Node *x) 															//Поиск потомка узла
    {
        Node *y;

        if(x->right)
        {
            return Minimum(x->right);
        }

        y = x->parent;

        while(y && x==y->right)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

  Node *Minimum(Node *tree)
    {
        while (tree->left)
        {
            tree = tree->left;
        }

        return tree;
    }


  void displayInfo(Node *node, int spaces)
    {
        if (!node)
        {
            return;
        }

        displayInfo(node->left, spaces + 1);

        for (int i = 0; i < spaces; ++i)
        {
            cout << "\t";
        }

        cout << node->key << (node->colour ? "B" : "R") << endl;						//отображение ключа вместе с цветом

        displayInfo(node->right, spaces + 1);
    }

  void clear(){}

};

template<class T, class N>
class AuditoryMap<T, N>::iterator : std::iterator< std::input_iterator_tag, AuditoryMap<T, N>::Node>
{
    friend AuditoryMap<T, N>;
public:
    iterator(const iterator&);
    iterator& next();
    iterator& operator=(const iterator&);
    bool operator!= (const iterator&) const;
    Node& operator*() const;
    Node& operator->() const;

private:
    int count = 0;
    iterator(Node*);
    Node* _pointer;
};

template<class T, class N>
inline typename AuditoryMap<T, N>::iterator AuditoryMap<T, N>::begin()
{

    if (!root->key)                  //some doubtful changes here
        return iterator(root);

    auto _point = root;

    while (_point->left)
        _point = _point->left;

    return iterator(_point);
}

template<class T, class N>
typename AuditoryMap<T, N>::iterator AuditoryMap<T, N>::end()
{
    if (!root->key)               // it was root->key == nullptr
        return iterator(root);

    auto _point = root;

    while (_point->right)       //_point->right->key != nullptr
        _point = _point->right;
    //if(!_point->right)         //_point->right->value == nullptr
       // _point = _point->left; // _point->right->value = new N;

    return iterator(_point); // return iterator(_point->right);
}


template<class T, class N>
inline AuditoryMap<T, N>::iterator::iterator(const iterator & _other)
{
    _pointer = _other._pointer;
}

template<class T, class N>
inline AuditoryMap<T, N>::iterator::iterator(AuditoryMap<T, N>::Node* _point)
{
    _pointer = _point;
}

template<class T, class N>
typename AuditoryMap<T, N>::iterator & AuditoryMap<T, N>::iterator::next()
{
    if (_pointer->right != nullptr)      //_pointer->right->value != nullptr
    {
        _pointer = _pointer->right;
        while (_pointer->left != nullptr && _pointer->left->value != NULL)       //(_pointer->left != nullptr && _pointer->left->value != nullptr)
                _pointer = _pointer->left;
    }
    else
    {
        while (_pointer != _pointer->parent->left)
            _pointer = _pointer->parent;

        _pointer = _pointer->parent;
    }

    return *this;
}

template<class T, class N>
bool AuditoryMap<T, N>::operator==(AuditoryMap & _other)
{
    if(this->count != _other.count)
        return false;

    AuditoryMap<T, N>::iterator i1 = begin();
    AuditoryMap<T, N>::iterator i2 = _other.begin();
    for (;i1 != end(), i2 != _other.end(); ++i1, ++i2)
        if (*(*i1).key != *(*i2).key || *(*i1).value != *(*i2).value)
            return false;

    return true;
}

template<class T, class N>
typename AuditoryMap<T, N>::iterator & AuditoryMap<T, N>::iterator::operator=(const iterator &_other)
{
    _pointer = _other._pointer;
}


template<class T, class N>
bool AuditoryMap<T, N>::iterator::operator!= (const iterator & _other) const
{
    return _pointer != _other._pointer;
}

template<class T, class N>
inline typename AuditoryMap<T, N>::Node& AuditoryMap<T, N>::iterator::operator*() const
{
    return *_pointer;
}

template<class T, class N>
inline typename AuditoryMap<T, N>::Node& AuditoryMap<T, N>::iterator::operator->() const
{
    return *_pointer;
}

#endif // AUDITORY_MAP_H