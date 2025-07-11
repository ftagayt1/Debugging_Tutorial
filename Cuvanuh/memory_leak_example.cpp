#include <iostream>
#include <vector>
#include <string>

// Class with a memory leak - destructor doesn't delete allocated memory
class MemoryLeakClass {
private:
    int* data;
    int size;
    
public:
    MemoryLeakClass(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
        std::cout << "MemoryLeakClass: Allocated " << size << " integers" << std::endl;
    }
    
    // BUG: Missing destructor! This will cause a memory leak
    // Should have: ~MemoryLeakClass() { delete[] data; }
    
    void printData() {
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Function that creates a memory leak by not deleting allocated memory
void createMemoryLeak() {
    std::cout << "Creating memory leak..." << std::endl;
    
    // BUG: Allocating memory but never deleting it
    int* leakyArray = new int[1000];
    for (int i = 0; i < 1000; i++) {
        leakyArray[i] = i * 2;
    }
    
    // Memory is used but never freed
    std::cout << "First element: " << leakyArray[0] << std::endl;
    std::cout << "Last element: " << leakyArray[999] << std::endl;
    
    // BUG: Should have: delete[] leakyArray;
}

// Function with another type of memory leak - early return without cleanup
int* createAnotherLeak(bool shouldReturn) {
    int* ptr = new int(42);
    
    if (shouldReturn) {
        // BUG: Returning without deleting the allocated memory
        return ptr;
    }
    
    delete ptr;
    return nullptr;
}

// Function that leaks memory in a loop
void leakInLoop(int iterations) {
    std::cout << "Creating " << iterations << " memory leaks in a loop..." << std::endl;
    
    for (int i = 0; i < iterations; i++) {
        // BUG: Allocating memory in each iteration but never freeing it
        double* tempArray = new double[100];
        for (int j = 0; j < 100; j++) {
            tempArray[j] = i * j * 0.1;
        }
        
        // Use the array but don't delete it
        std::cout << "Iteration " << i << ": " << tempArray[0] << std::endl;
        
        // BUG: Should have: delete[] tempArray;
    }
}

// Function with a double-free bug (will be caught by Valgrind)
void doubleFreeBug() {
    std::cout << "Demonstrating double-free bug..." << std::endl;
    
    int* ptr = new int(123);
    std::cout << "Value: " << *ptr << std::endl;
    
    delete ptr;  // First delete - correct
    delete ptr;  // BUG: Second delete - double free!
}

// Function with use-after-free bug
void useAfterFreeBug() {
    std::cout << "Demonstrating use-after-free bug..." << std::endl;
    
    int* ptr = new int(456);
    std::cout << "Original value: " << *ptr << std::endl;
    
    delete ptr;  // Memory is freed
    
    // BUG: Using memory after it's been freed
    std::cout << "Value after free: " << *ptr << std::endl;
}

int main() {
    std::cout << "=== Memory Leak Debugging Example ===" << std::endl;
    
    // Test 1: Class with missing destructor
    std::cout << "\n--- Test 1: Class memory leak ---" << std::endl;
    {
        MemoryLeakClass obj(10);
        obj.printData();
        // Object goes out of scope, but destructor doesn't free memory
    }
    
    // Test 2: Function with memory leak
    std::cout << "\n--- Test 2: Function memory leak ---" << std::endl;
    createMemoryLeak();
    
    // Test 3: Early return memory leak
    std::cout << "\n--- Test 3: Early return memory leak ---" << std::endl;
    int* leakedPtr = createAnotherLeak(true);
    if (leakedPtr) {
        std::cout << "Got pointer: " << *leakedPtr << std::endl;
        // BUG: Should delete leakedPtr here
    }
    
    // Test 4: Loop memory leak
    std::cout << "\n--- Test 4: Loop memory leak ---" << std::endl;
    leakInLoop(5);
    
    // Test 5: Double free bug (commented out to avoid crash)
    // std::cout << "\n--- Test 5: Double free bug ---" << std::endl;
    // doubleFreeBug();
    
    // Test 6: Use after free bug (commented out to avoid crash)
    // std::cout << "\n--- Test 6: Use after free bug ---" << std::endl;
    // useAfterFreeBug();
    
    std::cout << "\n=== Program finished ===" << std::endl;
    std::cout << "Run with: valgrind --leak-check=full --show-leak-kinds=all ./memory_leak_example" << std::endl;
    
    return 0;
} 