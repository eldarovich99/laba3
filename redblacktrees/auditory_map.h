#ifndef AUDITORY_MAP_H
#define AUDITORY_MAP_H

#include <iostream>
using namespace std;

/*
 * to-do list:
 * interface */

template <typename Key, typename Value> class Iterator;
template<typename Key, typename Value>
class AuditoryMap
{
    public:
    AuditoryMap() 											//конструктор по умолчанию
    {
        count = 0;
        root = NULL;
    }
    friend class Iterator<Key,Value>;
    //typedef Iterator<Key,Value> const_iterator;
    Value operator[](const Key);
    Iterator<Key, Value> end() {return Iterator<Key, Value>(this->Maximum(root));}
    Iterator<Key, Value> begin() {return Iterator<Key, Value>(this->Minimum(root));}
    template<class T, class N>
    friend std::ostream& operator<< (std::ostream&, AuditoryMap&);

    template<class T, class N>
    friend std::istream& operator>> (std::istream&, AuditoryMap&);

    bool operator== (AuditoryMap&);

    void insert(const Key& key, const Value& value)						// функция вставки
    {
        if (contains(key)) return;
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
            ++count;
        }

        else
        {
            z = new Node;
            z->key = key;
            z->value = value;
            z->colour = RED;
            z->parent = parent;
            z->left = z->right = NULL;
            ++count;
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
        //count++;
    }

 bool contains(const Key& key)                                          //проверка наличия ключа
  {
     Node *node = root;

      while(node && key != node ->key)
      {
          if(key < node->key)
              node = node->left;
          else
              node = node->right;
      }
      if (node!=NULL && key == node->key)return true;
      return false;
  }

  void deleteKey(const Key& key)													//функция удаления
    {
      if (!contains(key)) return;
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

        //if (!node || node->key != key){throw runtime_error("Cannot Delete: value with requested key not found");}

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
        count--;
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

        //throw runtime_error("No value with requested key");
    }

  void displayInfo()
    {
        displayInfo(root, 0);
    }


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

  void cleanup (Node *tn)
  { if(!tn) return;
      if(tn->left){
          cleanup(tn->left);
          delete(tn->left);
      }
      if(tn->right){
          cleanup(tn->right);
          delete(tn->right);
      }
  }

  int size(){
      return count;
  }

  inline void clear()
  {
    cleanup(root);
    root = nullptr;
    //delete(root);
    count = 0;
  }

private:
  int count;
  typename AuditoryMap<Key, Value>::Node*
  findNode(Node *x, Key key)
  {
      while(x != nullptr && key != x->key)
      {
          if(key < x->key)
              x = x->left;
          else
              x = x->right;
      }
      return x;


  }
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

  Node *Maximum(Node *tree)
    {
        while (tree->right)
        {
            tree = tree->right;
        }

        return tree;
    }

  AuditoryMap(const Node &tn)
  { if(!tn) return;
      Node node = new Node();
      if(tn->left){
          node.left = new Node();
          node.left.key = tn.left.key;
          node.left.value = tn.left.value;
          node.left.colour = tn.left.colour;
          AuditoryMap(tn->left);
      }
      if(tn->right){
          node.right = new Node();
          node.right.key = tn.right.key;
          node.right.value = tn.right.value;
          node.right.colour = tn.right.colour;
          AuditoryMap(tn->right);
      }
  }

};

template <typename keyType, typename valueType> valueType AuditoryMap<keyType, valueType>::operator [](keyType key)
{
    Node *pointer = NULL;
    pointer = findNode(root,key);
    if(pointer != NULL)
        return pointer->value;
}

template<typename Key, typename valueType> class Iterator
{
public:
    friend struct AuditoryMap<Key, valueType>::Node;
    Iterator();
    #define NIL &sentinel           /* all leafs are sentinels */
    typename AuditoryMap<Key, valueType>::Node sentinel;
    Iterator(typename AuditoryMap<Key, valueType>::Node *x);
    Iterator next();
    Key key();
    valueType value();
    typename AuditoryMap<Key, valueType>::Node *currNode;

};

template <typename Key, typename valueType>
Iterator<Key, valueType>::Iterator(typename AuditoryMap<Key, valueType>::Node *x)
{
    currNode = x;
    //sentinel = {0,0, nullptr, nullptr, false, NULL};
}


template <typename Key, typename valueType>
Key Iterator<Key, valueType>::key()
{
return currNode->key;
}

template <typename Key, typename valueType>
valueType Iterator<Key, valueType>::value()
{
return currNode->value;
}

template<class T, class N>
Iterator<T,N> Iterator<T,N>::next()
{
    if (currNode->right != nullptr)
    {
        currNode = currNode->right;
        while (currNode->left != nullptr && currNode->left->value != NULL)
                currNode = currNode->left;
    }
    else
    {
        while (currNode != currNode->parent->left)
            currNode = currNode->parent;

        currNode = currNode->parent;
    }

    return *this;
}

template <typename Node_key, typename Node_value>
istream& operator >>(istream& is, AuditoryMap<Node_key, Node_value>& another)
{
    int c;
    Node_key key;
    Node_value value;
    is >> c;
    for (int i = 0; i < c; i++)
    {
        is >> key >> value;
        another.insert(key,value);
    }
    return is;
}
template <typename Node_key, typename Node_value>
ostream& operator <<(ostream& os, AuditoryMap<Node_key, Node_value>& another)
{
    os << another.size() << '\n';

    for (auto i = another.begin(); i.key() != another.end().key() ; i.next())
        os << i.key() << " " << i.value() <<"\n";
    os << another.end().key() <<" "<< another.end().value();
    return os;
}

template<typename Key, typename Value>
bool AuditoryMap<Key, Value>::operator==(AuditoryMap & _other)
{
    if(count != _other.count)
        return false;
    if(count ==  0 &&_other.count==0)
        return true;
    for (auto i = this->begin(); i.key() != _other.end().key(); i.next())
    {
        if (!(i.value() == _other[i.key()]))
            return false;
    }
    return true;
}
#endif // AUDITORY_MAP_H
