/*
    Activity 4.2: "Grafos: Algoritmos complementarios"
    Carlos César Rodríguez García A00344666

    This program lets the user enter a Graph consisting of its nodes and connections.
    It will determine whether the Graph is a tree or not.

    USAGE:
        (Input):
            3 3   ---> First number, n, represents the number of nodes and second number, m, represents the number of connections
            0 1   ---> Each connection is listed 
            1 2 
            0 2
        
        (Output):
            1     ---> true
*/

#include <bits/stdc++.h>

using namespace std;

struct Graph 
{
    int n;                                     // Number of vertices
    int m;                                     // Numer of edges
    vector<int> *adjList;                      // Adjacency list 

    /** loadGraph()
    * Sets the values for a new Graph struct. 
    * Time Complexity: O(1)
    * 
    * @param n The number of vertices in the graph
    * @param m The number edges
    * @param list The adjacency list received from the user
    */
    void loadGraph(int n, int m, vector<int> *list) 
    {
        this->n = n;
        this->m = m;
        this->adjList = list;
    }

    /** hasCycleDFS()
    * Utility function that performs Depth First Search 
    * on the graph in order to find a cycle starting from 
    * an specified node.
    * 
    * @param index The index for the node present in the adjacency list
    * @param visited A boolean vector initially with all values as false
    * @param recStack Boolean vector determining whether node has been visited by current function call
    * @return Whether a cycle exists in the graph
    */
    bool hasCycleDFS(int index, vector<bool> visited, vector<bool> recStack) 
    {
        // If node has already been visited and is present
        // in stack, return true
        if(recStack[index])
            return true;

        // Visited but not in stack means 
        // that a node is not formed
        if(visited[index])
            return false;
    
        visited[index] = recStack[index] = true; 

        for(int connection : adjList[index])
            if(hasCycleDFS(connection, visited, recStack))
                return true;

        recStack[index] = false;
        return false;
    }

    /** isTree()
    * Calls hasCycleDFS for each node in the adjacency list
    * if a cycle is found then the graph isn't be a tree 
    * 
    * @return Whether the graph is a tree
    */
    bool isTree()
    {
        vector<bool> visited(n, false), recStack(n, false);

        for(int i=0 ; i < n ; i++) {
            if (hasCycleDFS(i, visited, recStack))
                return false;
        }

        return true; 
    }

    /** printGraph()
    * This does what you think it does.
    * Time Complexity: O(n+m)
    */
    void printGraph() 
    {
        for(int i=0 ; i < n ; i++) {
            cout << "\t\t" << i << ": "; 
            for(int connection : adjList[i])
                cout << connection << " ";
            cout << "\n";
        }
    }
};

int main() {

    /* The testCases.txt file contains 4 different test cases.
    *  The expected outputs for each case are:
    *       - Case 1: true  --> 3 nodes and 3 connections
    *       - Case 2: false --> 3 nodes and 3 connections
    *       - Case 3: true  --> 7 nodes and 6 connections
    *       - Case 4: false --> 5 nodes and 5 connections
    */

    freopen("testCases.txt", "r", stdin);

    int t_cases;
    cin >> t_cases;
    
    for(int t=0 ; t<t_cases ; t++) {

        cout << "\nCase " << t+1 << ": \n";

        // ADJACENCY LIST BUILDING AND RETRIEVAL
        int n, m;
        cin >> n >> m;

        vector<int> list[n]; // adjacency list of nodes

        // Receiving connections from user input    
        for(int i=0 ; i < m ; i++) {
            int p, q;
            cin >> p >> q;
            if(p < n && q < n)
                list[p].push_back(q);
        }

        // Create graph
        Graph myGraph = Graph();

        // Graph Loading
        cout << "\t1. Loading Graph...\n";
        myGraph.loadGraph(n, m, list);
        
        // Print Graph
        cout << "\t2. Graph successfully loaded. Adjacency list is:\n";
        cout << "\t   {\n"; 
        myGraph.printGraph();
        cout << "\t   }\n";

        // Check if graph has cycle
        cout << "\n\t3. Graph is Tree (Case " << t+1 << "): " << myGraph.isTree() << "\n";
    }

}