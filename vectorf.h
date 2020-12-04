#ifndef VECTORF_H
#define VECTORF_H

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class vectoRF{
    private:
        
        int capacity, current;
    public:
        T* arr;
        vectoRF()
        {
            arr = new T[1];
            capacity=1;
            current=0;
        }
        void push(T data)
        {
            if(current==capacity)
            {
                
                T* temp = new T[capacity++];
                for(int i=0; i<capacity-1;i++)
                {
                    temp[i]=arr[i];
                }
                delete[] arr;
                arr=temp;
            }
            arr[current]=data;
            current++;
            
        }
        void insert(T data, int index)
        {
            
            if(index==capacity)
                push(data);
            else
                arr[index]=data;
            
        }
        T get(int index){return arr[index];}
        void pop(){current--;}
        int size(){return current;}
        int getCapacity(){return capacity;}
        void print()
        {
            for(int i=0; i<current-1; i++)
            {
                cout<<arr[0]<<endl;
            }
            cout<<endl;
        }

};
#endif