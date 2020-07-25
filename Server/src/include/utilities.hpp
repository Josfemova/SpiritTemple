#ifndef SPIRITTEMPLE_UTILITIES_HPP
#define SPIRITTEMPLE_UTILITIES_HPP
#include <iostream>
namespace ce
{

    template <class T>
    void log(T message, bool condition)
    {
        if (condition)
            std::cout << message << std::endl;
    }
    /**
     * @brief logger for relevant game information
     * 
     * @tparam T 
     * @param message 
     */
    template <class T>
    void log(T message)
    {
        std::cout << message << std::endl;
    }
    /**
     * @brief logger for relevant game information
     * @tparam T
     * @tparam T
     * @param messag
     */
    template <class T, class E>
    void log(T message, E message2)
    {
        std::cout << message << message2 << std::endl;
    }
    /**
     * @brief logger for relevant game information
     * 
     * @tparam T 
     * @tparam T 
     * @tparam T 
     * @param message 
     */
    template <class T, class E, class J>
    void log(T message, E message2, J message3)
    {
        std::cout << message << message2 << message3 << std::endl;
    }
    /**
     * @brief logger for debugging sessions
     * 
     * @tparam T 
     * @param message 
     */
    template <class T>
    void debuglog(T message)
    {
        std::cout << message << std::endl;
    }
    /**
     * @brief logger for debugging sessions
     * 
     * @tparam T
     * @tparam T 
     * @param message 
     */
    template <class T, class E>
    void debuglog(T message, E message2)
    {
        std::cout << message << message2 << std::endl;
    }
    /**
     * @brief logger for debugging sessions
     * 
     * @tparam T
     * @tparam T
     * @tparam T 
     * @param message 
     */
    template <class T, class E, class J>
    void debuglog(T message, E message2, J message3)
    {
        std::cout << message << message2 << message3 << std::endl;
    }
    /**
     * @brief LAUNCHES AN ERROR AND PAUSES EXECUTION WITH A MESSAGE
     * 
     * @tparam T 
     * @param message 
     */
    template <class T>
    void errorlog(T message)
    {
        std::cerr << "Error, aborting process. Cause: " << message << std::endl;
        exit(EXIT_FAILURE);
    }
    /**
     * @brief LAUNCHES AN ERROR AND PAUSES EXECUTION WITH A MESSAGE
     * 
     * @tparam T
     * @tparam T
     * @param message 
     */
    template <class T, class E>
    void errorlog(T message, E message2)
    {
        std::cout << message << message2 << std::endl;
        exit(EXIT_FAILURE);
    }
    /**
     * @brief LAUNCHES AN ERROR AND PAUSES EXECUTION WITH A MESSAGE
     * 
     * @tparam T
     * @tparam T
     * @tparam T 
     * @param message 
     */
    template <class T, class E, class J>
    void errorlog(T message, E message2, J message3)
    {
        std::cout << message << message2 << message3 << std::endl;
        exit(EXIT_FAILURE);
    }

}; // namespace ce

#endif