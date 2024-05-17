#include <iostream>
#include "vector.h" // Include the vector class header file

int main() {
    // Create a vector of integers
    g3::vector<int> v1;

    // Push some elements into the vector
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);

       // Test copy constructor and assignment operator
    g3::vector<int> v2 = v1;
    g3::vector<int> v3;
    v3 = v1;

    // Test comparison operators
    if (v1 == v2) {
        std::cout << "v1 is equal to v2" << std::endl;
    } else {
        std::cout << "v1 is not equal to v2" << std::endl;
    }

    if (v1 != v3) {
        std::cout << "v1 is not equal to v3" << std::endl;
    } else {
        std::cout << "v1 is equal to v3" << std::endl;
    }

    if (v1 < v3) {
        std::cout << "v1 is less than v3" << std::endl;
    } else {
        std::cout << "v1 is not less than v3" << std::endl;
    }

    // Test resize and comparison using resize
    v1.resize(5, 50); // Resize v1 to size 5, filling new elements with value 50

    if (v1 >= v2) {
        std::cout << "v1 is greater than or equal to v2" << std::endl;
    } else {
        std::cout << "v1 is not greater than or equal to v2" << std::endl;
    }
    v1.pop_back(); // Remove the last element

    return 0;
}
