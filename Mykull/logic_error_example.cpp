#include <iostream>
#include <vector>
#include <string>

int findMax(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        return -1; // Return -1 for empty vector
    }
    
    int max = numbers[1]; 
    

    for (unsigned int i = 1; i < numbers.size(); i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    
    return max;
}


int factorial(int n) {
    if (n <= 0) {
        return 1;
    }
    
    int result = 1;
    for (int i = 1; i < n; i++) {
        result *= i;
    }
    
    return result;
}

int countEvenHelper(const std::vector<int>& arr) {
    int count = 0;
    for (unsigned int i = 0; i < arr.size(); i++) {

        if (arr[i] % 2 == 1) {
            count++;
        }
    }
    return count;
}


int countEven(const std::vector<int>& arr) {
    return countEvenHelper(arr);
}

int main() {
    std::cout << "=== Logic Error Debugging Example ===" << std::endl;
    
    // Test case 1: findMax bug
    std::vector<int> test1 = {9, 2, 8, 1, 5};
    std::cout << "Testing findMax with vector: ";
    for (int num : test1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    int maxResult = findMax(test1);
    std::cout << "findMax result: " << maxResult << std::endl;
    std::cout << "Expected result: 9" << std::endl;
    
    // Test case 2: factorial bug
    int n = 5;
    int factResult = factorial(n);
    std::cout << "\nTesting factorial(" << n << ")" << std::endl;
    std::cout << "factorial result: " << factResult << std::endl;
    std::cout << "Expected result: 120" << std::endl;
    
    // Test case 3: countEven bug (should count even numbers, but counts odd numbers)
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    int evenCount = countEven(nums);
    std::cout << "\nTesting countEven with: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "countEven result: " << evenCount << std::endl;
    std::cout << "Expected result: 3 (number of even numbers)" << std::endl;
    
    // Add a breakpoint here for GDB debugging
    std::cout << "\n=== Set a breakpoint here to start debugging ===" << std::endl;
    
    return 0;
} 