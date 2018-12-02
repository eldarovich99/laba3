#ifndef ITERATOR_H
#define ITERATOR_H
#include <auditory_map.h>
using namespace std;
template<class Key, class Value>
class AuditoryMap<Key, Value>::iterator : std::iterator< std::input_iterator_tag, AuditoryMap<Key, Value>::Node>
{
    friend AuditoryMap<Key, Value>;
public:
    iterator(const iterator&);
    iterator& next();
    inline Key key(){
        return (*this).key;
    }
    inline Value value(){
        return (*this).value;
    }
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

/*template<class T, class N>
int AuditoryMap<T, N>::iterator::value(){

};

template<class Key, class Value>
Key AuditoryMap<Key, Value>::iterator::key()
{/*
    if (!root->key)                  //some doubtful changes here
        return iterator(root);

    auto _point = root;

    while (_point->left)
        _point = _point->left;

    return iterator(root);*/
//}

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

#endif // ITERATOR_H
