#include <vector>
#include <algorithm>
#include <iostream>

class BinaryHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] > heap[parentIndex]) { 
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int largestIndex = index;

        if (leftChildIndex < heap.size() && heap[leftChildIndex] > heap[largestIndex]) {
            largestIndex = leftChildIndex;
        }
        if (rightChildIndex < heap.size() && heap[rightChildIndex] > heap[largestIndex]) {
            largestIndex = rightChildIndex;
        }

        if (largestIndex != index) {
            std::swap(heap[index], heap[largestIndex]);
            heapifyDown(largestIndex);
        }
    }

public:
    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int peek() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    int pop() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxVal;
    }

    bool empty() const {
        return heap.empty();
    }
};

int main() {
    BinaryHeap maxHeap;
    maxHeap.push(10);
    maxHeap.push(5);
    maxHeap.push(15);
    maxHeap.push(20);

    std::cout << "Max element is: " << maxHeap.peek() << std::endl; 

    while (!maxHeap.empty()) {
        std::cout << maxHeap.pop() << " "; 
    }
    std::cout << std::endl;

    return 0;
}
