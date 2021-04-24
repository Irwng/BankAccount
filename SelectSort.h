#ifndef CHAPTER9_SELECTSORT_H
#define CHAPTER9_SELECTSORT_H

template <class T>
void Swap(T &a, T &b){
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
}

template <class T>
void SelectSort(T a[], int n){
    for(int i = 0;i<n;i++){
        int leastindex = i;
        for(int j = i;j<n;j++)
            if(a[j]<a[leastindex])
                leastindex = j;
        Swap(a[i],a[leastindex]);
    }
}

//交换（冒泡）排序的第一种写法（自己写的）
template <class T>
void SwapSort(T a[],int n){
    for(int i = n;i>0;i--){
        int count = 0;
        for(int j = 0;j<i;j++){
            if(a[j]>a[j+1]){
                Swap(a[j],a[j+1]);
                count++;
            }
        }
        if(count==0){
            cout<<"Already sorted after "<<n-i<<"th swapsort."<<endl;
            return;
        }
    }
}

//交换（冒泡）排序的第二种写法（教学视频）
template <class T>
void BubbleSort(T a[],int n){
    int i = n-1;
    while(i>0){
        int lastExchageIndex = 0;
        for(int j = 0;j<i;j++)
            if(a[j]>a[j+1]){
                Swap(a[j],a[j+1]);
                lastExchageIndex=j;
            }
        i = lastExchageIndex;
    }
}

#endif //CHAPTER9_SELECTSORT_H
