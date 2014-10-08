
#ifndef _ARRAY_INTERNAL_H
#define _ARRAY_INTERNAL_H

#include <string.h>
#include <stdlib.h>
#include <new>

#define DEFAULT_INCREMENT_CAPACITY 5

template <class T> inline void callConstructor(T *items, unsigned int num = 1)
{
    for (unsigned int cnt = 0; cnt < num; cnt++)
    {
        ::new ((void *)items) T;
        items++;
    }
}

template <class T> inline void callDestructor(T *items, unsigned int num = 1)
{
    for (unsigned int cnt = 0; cnt < num; cnt++)
    {
        items->~T();
        items++;
    }
}

template <class T> class Array
{
private:
    T *items_;
    unsigned int size_;
    unsigned int capacity_;
    unsigned int inc_capacity_;

public:
    Array();
    Array(unsigned int size);
    ~Array();


    inline bool setSize(unsigned int size);
    inline unsigned int getSize() const;

    inline bool setCapacity(unsigned int size);
    inline unsigned int getCapacity() const;

    inline void setAddCapacity(unsigned int size);
    inline unsigned int getAddCapacity() const;

    inline bool addItem(const T &obj);
    inline bool insertItem(const T &obj, unsigned int index);
//    inline void remove(const T &remove);
    inline bool removeItem(unsigned int index);

    inline void clear();

    inline void sort();

    inline T* operator &();

    inline T operator [](unsigned int index) const;
    inline T &operator [](unsigned int index);
};


template <class T> Array<T>::Array()
{
    items_ = 0;
    size_ = 0;
    capacity_ = 0;
    inc_capacity_ = DEFAULT_INCREMENT_CAPACITY;
}

template <class T> Array<T>::Array(unsigned int size)
{
    items_ = 0;
    size_ = 0;
    capacity_ = 0;
    inc_capacity_ = DEFAULT_INCREMENT_CAPACITY;

    setSize(size);
/*    capacity(size);
    callConstructor(m_items, size);
    m_size = size;*/
}

template <class T> Array<T>::~Array()
{
    clear();
    if (items_ != 0)
        delete [] (unsigned char *)items_;
//    m_capacity = 0;
}


template <class T> bool Array<T>::setSize(unsigned int size)
{
    // se la nuova grandezza è uguale a quella presente esco
    if (size == size_)
        return true;
    // se la nuova è minore della presente devo deallocare gli oggeti in eccesso
    if (size < size_)
    {
        // se la capacità presente supera la nuova grandezza + m_addCapacity diminuisco l'array
        if (capacity_ > size + inc_capacity_)
            if (!setCapacity(size + inc_capacity_))   //capacity aggiorna m_size ma non sarà mai < di size, ok
                return false;           
        callDestructor(&items_[size], (size_ - size));
    } 
    else
    {
        // se la capacità presente è minore della nuova lunghezza aumento
        if (capacity_ < size)
            if (!setCapacity(size + inc_capacity_))
                return false;
        callConstructor(&items_[size_], (size - size_));
    }

    size_ = size;
    return true;
}

template <class T> unsigned int Array<T>::getSize() const
{   
    return size_;
}


template <class T> bool Array<T>::setCapacity(unsigned int size)
{
    if (capacity_ == size)
        return true;

    T *titems;
    
    if (size == 0)
        titems = 0;
    else {
        titems = (T *) new unsigned char[size * sizeof(T)];
        if (titems == 0)
            return false;

        if (size_ != 0)
        {
            if (size_ <= size)
            {
                memcpy(titems, items_, size_ * sizeof(T));
            }
            else
            {
                callDestructor(&items_[size], (size_ - size));
                memcpy(titems, items_, size * sizeof(T));
                size_ = size;
            }
        }
    }

    if (items_ != 0)
        delete [] (unsigned char *)items_;

    items_ = titems;
    capacity_ = size;

    return true;
}

template <class T> unsigned int Array<T>::getCapacity() const
{
    return capacity_;
}


template <class T> void Array<T>::setAddCapacity(unsigned int size)
{
    inc_capacity_ = size;
}


template <class T> unsigned int Array<T>::getAddCapacity() const
{
    return inc_capacity_;
}


template <class T> bool Array<T>::addItem(const T &obj)
{
    if (size_ == capacity_)
    {
        if (!setCapacity(capacity_ + inc_capacity_))
            return false;
    }

    callConstructor(&items_[size_]);
    items_[size_] = obj;
    size_++;

    return true;
}

template <class T> bool Array<T>::insertItem(const T &obj, unsigned int index)
{  
    if (index > size_)
        return false;

    if (size_ == capacity_)
    {
        if (!setCapacity(capacity_ + inc_capacity_))
            return false;
    }

    for (int cnt = 0; cnt < (size_ - index); cnt++)
    {
        memcpy(&items_[size_ - cnt], &items_[(size_ -1) - cnt], sizeof(T));
    }

    callConstructor(&items_[index]);
    items_[index] = obj;
    size_++;

    return true;
}

template <class T> bool Array<T>::removeItem(unsigned int index)
{
    callDestructor(&items_[index]);
    if (index != size_ -1)
        memcpy(&items_[index], &items_[index +1], ((size_ -1) - index) * sizeof(T));
    size_--;

    return true;
}


template <class T> void Array<T>::clear()
{
    if (size_ != 0)
        callDestructor(items_, size_);
    // libero la memoria solo nel distruttore
/*    delete [] (unsigned char *)m_items;
    m_capacity = 0;                       */
    size_ = 0;
}

/*
// sort() with Bubble
template <class T> void Array<T>::sort()
{
    s32 a, b;
    T t;

    for (a = 1; a < m_size; ++a)
    {
        for (b = m_size-1; b >= a; --b)
        {
            if (m_items[b-1]->cmp() > m_items[b]->cmp())
            {
                t = m_items[b-1];
                m_items[b-1] = m_items[b];
                m_items[b] = t;
            }
        }
    }
}*/


// sort() with Shell
template <class T> void Array<T>::sort()
{
    int i, j, increment;
    T temp;

    increment = 5;
    while (increment > 0)
    {    
        for (i = 0; i < size_; i++)
        {
            j = i;
            temp = items_[i];
            while ((j >= increment) && (items_[j-increment]->cmp() > temp->cmp()))
            {
                items_[j] = items_[j - increment];
                j = j - increment;
            }
            items_[j] = temp;
        }
    
        if (increment/2 != 0)
            increment = increment/2;
        else
        {
            if (increment == 1)
                increment = 0;
            else
                increment = 1;
        }
    }
}


template <class T> T* Array<T>::operator &()
{
    return items_;
}


// questo serve per il T = Array<T>; essendo il return un oggetto T const
template <class T> T Array<T>::operator [](unsigned int index) const
{
    // Fare un controllo su m_size per vedere la validità di index (??) lancio un throw
/*    if (index >= getSize())
        throw 1;*/
    return items_[index];
}

// questo serve per il Array<T> = T; essendo il return un & (indirizzo)
template <class T> T &Array<T>::operator [](unsigned int index)
{
    // Fare un controllo su m_size per vedere la validità di index (??) lancio un throw
/*    if (index >= getSize())
        throw 1;*/
    return items_[index];
}

#endif
