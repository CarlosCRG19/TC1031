/* Act 5.1 - Implementación individual de operaciones sobre conjuntos */
/* Alumno: Carlos César Rodríguez García */
/* Matrícula: A00344666 */

#include <bits/stdc++.h>

using namespace std;

/* Basic Node struct */
struct Node
{
    char key;           // A character to identify the pair
    int  value;         // The value associated with the character
    Node *next;         // Reference to next node. In case of using Chainning

    // Node constructor
    Node(char key, int value) : key(key), value(value){}
};

#define MAGIC_TABLE_SIZE 100 // Size of table. We expect to insert a number of nodes less than this.

/* Hash table main class */
class HashTable
{
private:
    vector<Node*> table;    // A list of nodes to store each `pair`
    int collisionHandler;   // 0 represents chainning and 1 represents quadratic as the strategy for collisions

    /* hashCode 
    * This is the hashing function for the key. 
    * Here just a modulo is being used to process a the hash code.
    *
    * Time Complexity: O(1)
    * 
    * @param key The key character for a specific node
    * @return The hash code computed with the key
    */
    int hashCode(int key) 
    {
        return key % MAGIC_TABLE_SIZE;
    }

    /* idxChainning 
    * Determines which will be the index of the new node (or of an existing one)
    * following a chainning approach for collisions. It just calls 
    * the hashCode function.
    *
    * Time Complexity: O(1)
    * 
    * @param key The key character for a specific node
    * @return The index of the node in the hash table
    */
    int idxChainning(int key)
    {
        return hashCode(key);
    }

    /* idxQuadratic
    * Determines which will be the index of the new node (or of an existing one)
    * following a quadratic approach for collisions. Calculates an index, if it is
    * occupied, looks for another one; this means that each slot in the table array
    * will just store one node...therefore, there is a limit for the number of nodes
    * that can be inserted.
    * 
    * Time Complexity: O(m) // where m is the size of the hash table
    *
    * @param key The key character for a specific node
    * @return The index of the node in the hash table
    */
    int idxQuadratic(int key)
    {
        int idx = -1, i = 0;
        vector<bool> visited(MAGIC_TABLE_SIZE, false);  // Boolean array to check if we have visited all of slots in table

        while(1)
        {
            int idxCandidate = hashCode(key + i*i); // hash code calculated with quadratic strategy
            
            if (!this->table.at(idxCandidate)) {
                // if the is not a node in this slot 
                // then return the index 
                idx = idxCandidate;
                break;
            } else {
                if (visited[idx]) 
                    // if there is a node in this slot, and we have visited
                    // it, then return the index, since it means that
                    // the table is full
                    break;
                
                visited[idx] = true; // mark this position as visited
                i++;
            }
        }

        // If there is no space the new node
        // the value to be returned is -1
        return idx;
    }

    void printChainning()
    {
        for (int i = 0 ; i < MAGIC_TABLE_SIZE ; i++) {
            if(this->table[i]) {
                Node *dummy = this->table[i];
                
                while (dummy) {
                    cout << "\t" << dummy->key << ": " << dummy->value << ",\n";
                    dummy = dummy->next;
                }
            }
        } 
    } 

    void printQuadratic()
    {
        for (int i = 0 ; i < MAGIC_TABLE_SIZE ; i++)
            if (table[i]) 
                cout << "\t" << this->table[i]->key << ": " << this->table[i]->value << ",\n";
    }

public:
    // Main constructor
    HashTable(int collisionHandler)
    {
        this->collisionHandler = collisionHandler;
        this->table = vector<Node*>(MAGIC_TABLE_SIZE);  // initialize table as an array of MAGIC_TABLE_SIZE null nodes
    }

    /* put
    * Inserts a new key pair as a node into the table.
    * It uses stratefy specified by the field collisionHandler
    *
    * Time Complexity: O(n) or O(m) - where n is the number of nodes and m is the size of the table
    *                                 It depends on wheter it is using chainning or quadratic, respectively.
    * 
    * @param key The key character for a specific node
    * @param value The value associated with the key 
    * @return None
    */
    void put(char key, int value)
    {
        Node *newNode = new Node(key, value); // new node to be inserted is created

        if (this->collisionHandler == 0) {
            // if collisionHandler is 0, it means 
            // chainning is being used as the strategy for collisions
            int idx = idxChainning(key);
            

            if (this->table.at(idx)) {
                // if there is already a node, traverse the linked list
                // until the new node can be placed
                Node *head = table.at(idx);
                
                while(head->next) {
                    head = head->next;
                }

                head->next = newNode;
            } else 
                // if there is nothing in this position
                // start the linked list
                this->table[idx] = newNode;
                
        } else if (this->collisionHandler == 1) {
            // if collisionHandler is 1, 
            // quadratic approach is used
            int idx = idxQuadratic(key);
            this->table.at(idx) = newNode;
        } else {
            // if collisionHandler is different from 0 or 1
            // then there is no valid strategy
            printf("ERROR: Invalid collision handler %d\n", this->collisionHandler);
            exit(EXIT_FAILURE);
        }
    }

    /* get
    * Looks for the node with the given key and returns its value.
    *
    * Time Complexity: O(1) or O(m) - where m is the size of the table in case of using quadratic technique.
    * 
    * @param key The key character for a specific node
    * @return value The value associated with the key 
    */
    int get(char key)
    {
        if (this->collisionHandler == 0) {
            int idx = idxChainning(key);

            Node *head = this->table[idx];

            while (head) {
                if (head->key == key)
                    return head->value;
            
                head = head->next;
            }

            goto not_found;

        } else if (this->collisionHandler == 1) {
            int idx = idxQuadratic(key);

            if  (idx < 0 || !this->table.at(idx))
                // if `idxQuadratic` returns -1
                // or if there is not a node at this index
                goto not_found;
        } else {
            // if collisionHandler is different from 0 or 1
            // then there is no valid strategy
            printf("ERROR: Invalid collision handler %d\n", this->collisionHandler);
            exit(EXIT_FAILURE);
        }

    not_found:
        printf("ERROR: Pair with key `%c` not found in hash table\n", key);
        return INT_MAX;
    }

    /* printTable   
    * Prints each (key, value) pair present in the table.
    * 
    * Time complexity: O(n*m) - worst case where n is the number of nodes and m is the size of the table
    */
    void printTable()
    {
        cout << "{\n";
        if (this->collisionHandler == 0)
            printChainning();
        else if  (this->collisionHandler == 1)
            printQuadratic();
        else {
            printf("ERROR: Invalid collision handler %d\n", collisionHandler);
            exit(EXIT_FAILURE);
        }
        cout << "}\n";    
    }

};

int main() 
{

    freopen("test.txt", "r", stdin); // open test file

    int t_cases;
    cin >> t_cases;

    for (int i = 0; i < t_cases; i++) 
    {
        cout << "--------------------\n";
        cout << "--| Hash Table " << i+1 << " |--\n";
        cout << "--------------------\n\n";

        /* DECLARATION OF VARIABLES */

        int n;                                      // number of nodes to insert
        HashTable chainningTable = HashTable(0);    // table using chainning technique
        HashTable quadraticTable = HashTable(1);    // table using quadratic technique
        char lookupKey;                             // Key to look for in table

        /* TABLE FILLING */

        cin >> n;
        for (int i = 0; i < n; i++) {
            char key; 
            int value;

            cin >> key >> value;

            chainningTable.put(key, value);
            quadraticTable.put(key, value);
        }

        cin >> lookupKey;

        /* USING CHAINNING FOR COLLISIONS */ 

        cout << "Table with Chainning\n";
        cout << "--------------------\n\n";
        
        cout << "1. Contents of table:\n";
        chainningTable.printTable();
        
        cout << "\n2. Get node with key `" << lookupKey << "`: " << chainningTable.get(lookupKey) << "\n\n";

        /* USING QUADRATIC APPROACH FOR COLLISIONS */ 

        cout << "Table with Quadratic technique\n";
        cout << "------------------------------\n\n";
        
        cout << "1. Contents of table:\n";
        quadraticTable.printTable();
        
        cout << "\n2. Get node with key `" << lookupKey << "`: " << chainningTable.get(lookupKey) << "\n\n";
    }
}