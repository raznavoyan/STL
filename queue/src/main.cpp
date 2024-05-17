#include "queue.h"
#include <iostream>
#include <string>

int main() {
    // Create a queue of integers
    g3::queue<int> intQueue;
    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);

    // Test size and element access
    std::cout << "Front element: " << intQueue.front() << std::endl; // Should be 10
    std::cout << "Back element: " << intQueue.back() << std::endl;  // Should be 30
    std::cout << "Size: " << intQueue.size() << std::endl;          // Should be 3

    // Test copy constructor
    g3::queue<int> copiedQueue = intQueue;
    std::cout << "Copied queue front: " << copiedQueue.front() << std::endl; // Should be 10

    // Test move constructor
    g3::queue<int> movedQueue = std::move(copiedQueue);
    std::cout << "Moved queue front: " << movedQueue.front() << std::endl; // Should be 10
    std::cout << "Copied queue size (after move): " << copiedQueue.size() << std::endl; // Might be 0 or undefined

    // Test popping elements
    intQueue.pop();
    std::cout << "Front after pop: " << intQueue.front() << std::endl; // Should be 20

    // Test comparison operators
    g3::queue<int> queue1;
    queue1.push(1);
    queue1.push(2);

    g3::queue<int> queue2;
    queue2.push(1);
    queue2.push(2);

    g3::queue<int> queue3;
    queue3.push(2);
    queue3.push(3);

    std::cout << "Queue1 == Queue2: " << (queue1 == queue2 ? "True" : "False") << std::endl; // True
    std::cout << "Queue1 == Queue3: " << (queue1 == queue3 ? "True" : "False") << std::endl; // False
    std::cout << "Queue1 < Queue3: " << (queue1 < queue3 ? "True" : "False") << std::endl;   // True

    return 0;
}
