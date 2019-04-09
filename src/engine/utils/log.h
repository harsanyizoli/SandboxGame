#include <iostream>

template<class T>
void log(T var){
    std::cout << var << std::endl;
}
# if 0
void log(const char* message){
    std::cout << message << std::endl;
}
#endif