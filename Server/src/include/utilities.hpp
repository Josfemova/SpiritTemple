#ifndef SPIRITTEMPLE_UTILITIES_HPP
#define SPIRITTEMPLE_UTILITIES_HPP
#include <iostream>
namespace ce{
    template <class T>
    void log(T message){
        std::cout<<message<<std::endl;
    }
    template <class T, class E>
    void log(T message, E message2){
        std::cout<<message<<message2<<std::endl;
    }
    template <class T,class E, class J>
    void log(T message, E message2, J message3){
        std::cout<<message<<message2<<message3<<std::endl;
    }
    template <class T>
    void debuglog(T message){
        std::cout<<message<<std::endl;
    }
    template <class T, class E>
    void debuglog(T message, E message2){
        std::cout<<message<<message2<<std::endl;
    }
    template <class T,class E, class J>
    void debuglog(T message, E message2, J message3){
        std::cout<<message<<message2<<message3<<std::endl;
    }
    template <class T>
    void errorlog(T message){
        std::cerr<<"Error, aborting process. Cause: "<<message<<std::endl;
        exit(EXIT_FAILURE);
    }
    template <class T, class E>
    void errorlog(T message, E message2){
        std::cout<<message<<message2<<std::endl;
        exit(EXIT_FAILURE);
    }
    template <class T,class E, class J>
    void errorlog(T message, E message2, J message3){
        std::cout<<message<<message2<<message3<<std::endl;
        exit(EXIT_FAILURE);
    }
    
};

#endif