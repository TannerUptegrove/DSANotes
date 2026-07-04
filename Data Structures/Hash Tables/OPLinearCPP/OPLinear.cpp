#include <iostream>
#include <climits>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;

class HashTable {
    // Object used to simulate a key-pair entry in the hash table.
    struct Entry {
        int key;
        int value;

        Entry(int k, int v) {
            key = k;
            value = v;
        }
    };

    int capacity;
    int size;

    // A vector, where each index represents a bucket.
    // This is acceptable since this hashtable does not allow multiple
    // pairs to exist in the same bucket.
    vector<Entry*> table;

    int Hash(int key) {
        return abs(key % capacity);
    }

    void IncreaseCapacity() {
        // Creates a new hashtable with double the old one's capacity.
        cout << endl << "Increasing capacity" << endl;
        HashTable newHashTable(capacity * 2);

        // For each bucket, each pair is inserted into the new hashtable using
        // its Insert function.
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                newHashTable.Insert(table[i]->key, table[i]->value);
            }
        }

        capacity *= 2;
        table = newHashTable.table;
    }

    void DecreaseCapacity() {
        // Creates a new hashtable with half the old one's capacity.
        cout << endl << "Decreasing capacity..." << endl;
        HashTable newHashTable(capacity / 2);

        // For each bucket, each pair is inserted into the new hashtable using
        // its Insert function.
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                newHashTable.Insert(table[i]->key, table[i]->value);
            }
        }
        capacity /= 2;
        table = newHashTable.table;
    }

    public:
    HashTable(int buckets) {
        capacity = buckets;
        size = 0;
        table.resize(capacity);
    }

    ~HashTable() {
        table.clear();
        table.shrink_to_fit();
    }

    void Insert(int key, int value) {
        int bucket = Hash(key);

        // Checks if the key was already inserted into the hashtable.
        // If so, then the value of its pair is updated.
        //
        // If the key is -1, that means that spot once held a pair, but is
        // now empty.
        while (table[bucket] != nullptr) {
            if (table[bucket]->key == key) {
                table[bucket]->value = value;
                return;
            }
            if (table[bucket]->key == -1) {
                table[bucket] = new Entry(key, value);
                size++;
                return;
            }
            else {
                // Retries the hash function to find the next available bucket.
                bucket = Hash(1 + key);
            }
        }

        // Inserts a new key-value pair at that bucket.
        table[bucket] = new Entry(key, value);
        size++;

        if (size / capacity >= 0.75) {
            IncreaseCapacity();
        }
    }

    void Delete(int key) {
        int bucket = Hash(key);

        // Checks if the pair exists in the hashtable.
        // If it does, then the key is replaced with -1 and the value with INT_MIN.
        while (table[bucket] != nullptr) {
            if (table[bucket]->key == key) {
                
                table[bucket]->key = -1;
                table[bucket]->value = INT_MIN;
                size--;

                if (size / capacity <= 0.25) {
                    DecreaseCapacity();
                }
                return;
            }
            else {
                // Retries the Hash function to find the next possible bucket
                // the pair could be in.
                bucket = Hash(key + 1);
            }
        }

        cout << "The entry could not be found...";
        return;
    }

    int LookUp(int key) {
        int bucket = Hash(key);

        while (table[bucket] != nullptr) {
            if (table[bucket]->key == key) {
                return table[bucket]->value;
            }
            else {
                bucket = Hash(key + 1);
            }
        }
        cout << "The entry could not be found...";
        return INT_MIN;
    }

    void Display() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            if (table[i] != nullptr && table[i]->key != -1) {
                cout << "(" << table[i]->key << " : " << table[i]->value << ")";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable table(23);
    
    table.Insert(50, 67);
    table.Insert(500, 67);
    table.Insert(890, 67);
    table.Insert(10, 67);
    table.Insert(2, 67);
    table.Display();
    table.~HashTable();
    return 0;
}