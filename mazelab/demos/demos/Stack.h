#ifndef DEMOS_STACK_H
#define DEMOS_STACK_H
#include<stack>
template<typename T>
class Stack:public  std::stack<T>{
public:
    T pop(){
        T temp;
        temp=std::stack<T>::top();
        std::stack<T>::pop();
        return temp;
    }
};
#endif //DEMOS_STACK_H
