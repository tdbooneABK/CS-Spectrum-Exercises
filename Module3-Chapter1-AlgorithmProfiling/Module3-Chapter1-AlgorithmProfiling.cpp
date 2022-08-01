#include <chrono>
#include <iostream>
#include <string>

uint32_t GetNanos() {
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

enum class sortMethod {
    bubbleSort,
    linkedListSort
};

void evaluateMethod(sortMethod method, int arraySize = 25, bool debug = false);
int* generateData(int arraySize);
void bubbleSort(int* inputData, int arraySize);
void linkedListInsertionSort(int* inputData, int arraySize);

int main()
{
    srand(time(0));
    std::cout << "List size of 25:" << std::endl;
    evaluateMethod(sortMethod::bubbleSort, 25);
    evaluateMethod(sortMethod::linkedListSort, 25);
    std::cout << std::endl << "List size of 250:" << std::endl;
    evaluateMethod(sortMethod::bubbleSort, 250);
    evaluateMethod(sortMethod::linkedListSort, 250);
    std::cout << std::endl << "List size of 2500:" << std::endl;
    evaluateMethod(sortMethod::bubbleSort, 2500);
    evaluateMethod(sortMethod::linkedListSort, 2500);
}

void evaluateMethod(sortMethod method, int arraySize, bool debug) {
    int* dataArray = generateData(arraySize);
    if (debug) {
        std::cout << "Unsorted data: " << std::endl;
        for (int i = 0; i < arraySize; i++) {
            std::cout << dataArray[i] << ' ';
        }
        std::cout << std::endl;
    }

    uint32_t startTime = GetNanos();
    uint32_t endTime = GetNanos();
    std::string sortMethod = "";

    switch (method) {
    case sortMethod::bubbleSort:
        sortMethod = "Bubble Sort";
        startTime = GetNanos();
        bubbleSort(dataArray, arraySize);
        endTime = GetNanos();
        break;
    case sortMethod::linkedListSort:
        sortMethod = "Ordered Linked List Insertion";
        startTime = GetNanos();
        linkedListInsertionSort(dataArray, arraySize);
        endTime = GetNanos();
        break;
    }

    std::cout << sortMethod << " processing time: " << endTime - startTime << "ns." << std::endl;

    if (debug) {
        std::cout << "Sorted data: " << std::endl;
        for (int i = 0; i < arraySize; i++) {
            std::cout << dataArray[i] << ' ';
        }
        std::cout << std::endl;
    }

    delete[] dataArray;
}

int* generateData(int arraySize) {
    int* data = new int[arraySize];
    for (int i = 0; i < arraySize; i++) {
        data[i] = 1 + rand() % 100;
    };
    return data;
}

void bubbleSort(int* inputData, int arraySize) {
    for (int iteration = 0; iteration < arraySize; iteration++) {
        for (int bubbleLocation = 0; bubbleLocation < arraySize - 1; bubbleLocation += 1) {
            if (inputData[bubbleLocation] > inputData[bubbleLocation + 1]) {
                int temp = inputData[bubbleLocation];
                inputData[bubbleLocation] = inputData[bubbleLocation + 1];
                inputData[bubbleLocation + 1] = temp;
            }
        }
    }
}

void linkedListInsertionSort(int* inputData, int arraySize) {
    struct Node {
        int value;
        Node* next;
        Node(int value, Node* next = nullptr)
            : value(value)
            , next(next)
        {}
        ~Node()
        {}
    };

    class LinkedList {
        Node* head;
    public:
        LinkedList()
            : head(nullptr)
        {}
        ~LinkedList()
        {
            Node* currentNode = head;
            while (currentNode != nullptr) {
                Node* nodeToDelete = currentNode;
                currentNode = currentNode->next;
                delete nodeToDelete;
            }
        }
        Node* GetHead() { return head; }
        void AddNode(int value) {
            int position = 1;
            if ((head == nullptr) || (value < head->value)) {
                head = new Node(value, head);
            }
            else {
                Node* currentNode = head;
                while (currentNode != nullptr) {
                    position += 1;
                    if (currentNode->next == nullptr) {
                        currentNode->next = new Node(value);
                        break;
                    }
                    else if (currentNode->next->value >= value) {
                        Node* temp = currentNode->next;
                        currentNode->next = new Node(value, temp);
                        break;
                    }
                    else {
                        currentNode = currentNode->next;
                    }
                }
            }
        };
    };

    LinkedList list = LinkedList();
    for (int i = 0; i < arraySize; i++) {
        list.AddNode(inputData[i]);
    }

    Node* currentNode = list.GetHead();
    for (int i = 0; i < arraySize; i++) {
        if (currentNode) {
            inputData[i] = currentNode->value;
            currentNode = currentNode->next;
        }
    }
}
