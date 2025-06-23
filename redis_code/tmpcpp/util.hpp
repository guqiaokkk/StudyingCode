#pragma once

#include <vector>
#include <string>
#include <iostream>

template <typename T>
inline void PrintContainer(const T &container){
    for(const auto &elem : container){
        std::cout << elem << std::endl;
    }
}

template <typename T>
inline void PrintContainerOptional(const T &container){
    for(const auto &elem : container){
        //此处预期elem是一个optional类型的元素，打印之前先判断是否有效
        if(elem){
            std::cout << elem.value() << std::endl;
        }else{
            std::cout << "no useful" << std::endl;
        }
    }
}
