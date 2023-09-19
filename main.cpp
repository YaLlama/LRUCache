#include <iostream>

using namespace std;

void print(int i){
  std::cout << i << std::endl;
}

//Node
class Timekeeper{
    public:
    int key;
    int value;
    Timekeeper * next;
};

class LRUCache {
public:
    explicit LRUCache(int capacity) {
      this->capacity = capacity;
      //creating initial node
      auto * temp = new Timekeeper;
      head = temp;
    }

    //Debugging function
    void print() {
        Timekeeper * currentNode = head;
        //runs through node stack top to bottom
        while(currentNode != nullptr){
            cout << "Key " << currentNode->key << " value " << currentNode->value << endl;
            currentNode = currentNode->next;
        }
    }

    /**
     * Retrieves given value from stack
     * @param key reference key associated with value
     * @return value assigned to key, if key not found returns -1
     */
    int get(int key) {
        Timekeeper * currentNode = head;
        //while not at last node
      while(currentNode != nullptr){
        if(currentNode->key == key){
          return currentNode->value;
        }
        //next node
        currentNode = currentNode->next;
      }
      //default value is -1
      return -1;
    }

    /**
     * Adds a given value to stack based on protocol:
     * If a key already belongs to the stack, remove the node and replace it at the top
     * If a key does not belong to the stack and the stack is at capacity, remove the bottom most (LRU) node and add the new to the top
     * @param key - number used to mark a given value
     * @param value - data being stored and accessed within the stack
     */
    void put(int key, int value) {
        //if no nodes make the new node the head node
        if (currentNodes == 0) {
            head->key = key;
            head->value = value;
            currentNodes = 1;
            return;
        }

        //handles all removing of nodes from stack
        remove(key);

        //place put node at top of stack to indicate its the most recent node
        auto * newHead = new Timekeeper;
        newHead->next = head;
        newHead->key = key;
        newHead->value = value;
        head = newHead;
    }

private:
    //top of node stack
    Timekeeper * head;

    //inputted capacity by user
    int capacity;
    int currentNodes = 0;

    /**
     * Removes a given value to stack based on protocol:
     * If a key already belongs to the stack, remove the node
     * If a key does not belong to the stack and the stack is at capacity, remove the bottom most (LRU) node
     * @param key
     */
    void remove(int key){
      //checks if leading value is what is being "put" into list and handles
     if(key == head->key){

        Timekeeper * temp = head;
        head = head->next;
        delete temp;

        return;
      }

      Timekeeper * previousNode = head;
      Timekeeper * currentNode = head->next;
      //runs through node stack
      while(currentNode != nullptr){
          //if repeat key or stack is at capacity, remove corresponding node
        if(currentNode->key == key || (currentNode->next == nullptr && currentNodes == capacity)){
          previousNode->next = currentNode->next;
          delete currentNode;
          return;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
      }
      //if no node was removed
      currentNodes++;
    }

};

int main() {
  std::cout << "Hello World!\n";
  auto * lRUCache = new LRUCache(2);
lRUCache->put(2, 2); // cache is {2=2}
lRUCache->put(1, 1); // cache is {1=1, 2=2}
//lRUCache->print();
        print(lRUCache->get(1));    // return 1
lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
//lRUCache->print();

        print(lRUCache->get(2));    // returns -1 (not found)
 lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
// lRUCache->print();

    print(lRUCache->get(1));    // return -1 (not found)
        print(lRUCache->get(3));    // return 3
        print(lRUCache->get(4));    // return 4
}

