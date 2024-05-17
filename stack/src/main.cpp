#include "stack.h"
#include <iostream>
#include <string>

using namespace g3;

int main() {
    // Create a stack of integers
    stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    // Display the top element
    std::cout << "The top element is: " << intStack.top() << std::endl;

    // Pop an element
    intStack.pop();
    std::cout << "After popping, the top element is: " << intStack.top() << std::endl;

    // Check the size of the stack
    std::cout << "Current size of stack: " << intStack.size() << std::endl;

    // Create another stack and use copy constructor
    stack<int> anotherStack = intStack;
    std::cout << "Top element of another stack (copied): " << anotherStack.top() << std::endl;

    // Check for equality
    if (intStack == anotherStack) {
        std::cout << "Stacks are equal." << std::endl;
    } else {
        std::cout << "Stacks are not equal." << std::endl;
    }

    // Create a stack using initializer list
    stack<int> initListStack = {1, 2, 3, 4, 5};
    std::cout << "Top element of initializer list stack: " << initListStack.top() << std::endl;
    std::cout << "Size of initializer list stack: " << initListStack.size() << std::endl;

    // Example using a stack of strings
    stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");

    std::cout << "Top string in stack: " << stringStack.top() << std::endl;
    stringStack.pop();
    std::cout << "Top string after pop: " << stringStack.top() << std::endl;

    return 0;
}
