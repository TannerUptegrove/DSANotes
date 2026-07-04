#include <iostream>
#include <climits>
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

    // A vector of vectors.
    // The indexes of the outer vector represent buckets.
    vector<vector<Entry*>> table;

    int Hash(int key) { return (key % capacity); }

    void IncreaseCapacity() {
        // Creates a new hashtable with double the old one's capacity.
        HashTable newHT(capacity * 2);
        
        // For each bucket, each pair is inserted into the new hashtable using
        // its Insert function.
        for (int i = 0; i < capacity; i++) {
            for (int j = 0; j < table[i].size(); j++) { 
                newHT.Insert(table[i][j]->key, table[i][j]->value);
            }           
        }

        capacity *= 2;
        table = newHT.table;
    }

     void DecreaseCapacity() {
        // Creates a new hashtable with half the old one's capacity.
        HashTable newHT(capacity / 2);
        
        // For each bucket, each pair is inserted into the new hashtable using
        // its Insert function.
        for (int i = 0; i < capacity; i++) {
            if (!table[i].empty()) {
                 for (int j = 0; j < table[i].size(); j++) { 
                    newHT.Insert(table[i][j]->key, table[i][j]->value);
                }     
            }
             
        }
        capacity /= 2;
        table = newHT.table;
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
        int bucket = abs(Hash(key));

        // Checks if the key was already inserted into the hashtable.
        // If so, then the value of its pair is updated.
        if (table[bucket].size() > 0) {
            for (const auto& e : table[bucket]) {
                if (e->key == key) {
                    e->value = value;
                    return;
                }
            }
        }
        
        // Inserts a new key-value pair at the back of a bucket's vector.
        table[bucket].push_back(new Entry(key, value));
        size++;

        if (size / capacity >= 0.75) {
            IncreaseCapacity();
        }

    }

    void Delete(int key) {
        int bucket = Hash(key);

        for (int i = 0; i < table[bucket].size(); i++) {
            if (table[bucket][i]->key == key) {
                table[bucket].erase(table[bucket].begin() + i);
                size--;

                if (size / capacity <= 0.25) {
                    DecreaseCapacity();
                }

                return;
            }
        }

        cout << "\nEntry could not be found...\n";
    }

    int LookUp(int key) {
        int bucket = Hash(key);

        for (int i = 0; i < table[bucket].size(); i++) {
            if (table[bucket][i]->key == key) {
                return table[bucket][i]->value;
            }
        }

        cout << "\nEntry could not be found...\n";
        return INT_MIN;
    }

    void Display() {

        // For each bucket, their name is displayed, along with each of the
        // pairs, separating them with " -> ".
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            if (table[i].size() > 0) {
                for (int j = 0; j < table[i].size() - 1; j++) {
                    cout << "(" << table[i][j]->key << " : " << table[i][j]->value << ") | ";
                }
                cout << "(" << table[i][table[i].size() - 1]->key << " : " << table[i][table[i].size() - 1]->value << ")";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable hashTable(20);
    hashTable.Insert(10, 50);
    hashTable.Insert(209, 80);
    hashTable.Insert(209, 50);
    hashTable.Display();
    return 0;
}