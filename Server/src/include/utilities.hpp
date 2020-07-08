#ifndef SPIRITTEMPLE_UTILITIES_HPP
#define SPIRITTEMPLE_UTILITIES_HPP
#include <iostream>

namespace ce{
    template <class T>
    void log(T message){
        std::cout<<message<<std::endl;
    }
    template <class T>
    void debuglog(T message){
        std::cout<<message<<std::endl;
    }
    template <class T>
    void errorlog(T message){
        std::cerr<<"Error, aborting process. Cause: "<<message<<std::endl;
        exit(EXIT_FAILURE);
    }
};

#endif