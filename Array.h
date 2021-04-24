#ifndef CHAPTER9_ARRAY_H
#define CHAPTER9_ARRAY_H

#include "Date.h"
#include "SelectSort.h"
/*数组类模板*/
template <class T>
class Array{
private:
    T* list;
    int size;
public:
    Array(int sz = 50);//构造函数
    Array(const Array<T>&a);//复制构造函数
    ~Array();//析构函数

    Array<T> &operator = (const Array<T>&rhs);//重载"="
    T &operator[](int n);//重载"[]"
    const T &operator[](int n)const;//重载"[]"常函数
    operator T*();
    operator T*() const;
    int getSize()const ;
    void resize(int sz);
    void SortbySelect();
    void SortbyBubble();
    void show();
};


template <class T>
void Array<T>::SortbySelect() {
    SelectSort<T>(list, size);
}

template <class T>
void Array<T>::SortbyBubble() {
    BubbleSort<T>(list, size);
}

template <class T>
void Array<T>::show() {
    for(int i = 0;i<size;i++)
        cout<<list[i]<<" ";
}


template <class T>
Array<T>::Array(int sz):size(sz){
    assert(sz >= 0);
    size = sz;
    list = new T[size];
}


template <class T>
Array<T>::~Array() {
    delete list;
}


template <class T>
Array<T>::Array(const Array<T> &a) {
    size = a.size;
    list = new T[size];
    for(int i = 0; i < size; i++)
        list[i] = a.list[i];
}


//重载"="运算符，将对象rhs赋值给本对象，实现对象之间的整体赋值
template <class T>
Array<T> & Array<T>::operator=(const Array<T> &rhs) {
    if(&rhs!=this){
        if(size!=rhs.size){
            delete [] list;
            size = rhs.size;
            list = new T[size];
        }
        for(int i = 0; i < size; i++)
            list[i] = rhs.list[i];
    }
    return *this;//返回当前对象去初始化一个引用
}


//重载下标运算符，实现与普通数组一样通过下标访问元素，具有越界检查功能
template <class T>
T & Array<T>::operator[](int n) {
    assert(n>=0&&n<size);
    return list[n];
}

template <class T>
const T & Array<T>::operator[](int n) const{
    assert(n>=0&&n<size);
    return list[n];
}


//重载指针转换运算符，将Array类的对象名转换为T类型的指针
template <class T>
Array<T>::operator T *() {
    return list;//返回当前对象中私有数组的首地址
}


//重载指针转换运算符，将Array类的对象名转换为T类型的指针
template <class T>
Array<T>::operator T *() const{
    return list;//返回当前对象中私有数组的首地址
}
//取当前数组的大小
template <class T>
int Array<T>::getSize() const {
    return size;
}


//将数组大小修改为sz
template <class T>
void Array<T>::resize(int sz) {
    assert(sz>=0);
    if(size == sz)
        return;
    T* newlist = new T[sz];
    int n = (sz<size)?sz:size;
    //将原有数组中的前n个元素复制到新数组中
    for(int i = 0; i<n;i++)
        newlist[i] = list[i];
    //删除原数组空间
    delete[]list;
    //使list指向新数组
    list = newlist;
    size = sz;
}

#endif //CHAPTER9_ARRAY_H
