/*
    Act 3.4 - Actividad Integral de BST
    Luis David López Magaña A00344656
    Brandon Josué Magaña Mendoza  A01640162
    Carlos César Rodríguez García A00344666

    Programa que lee el reporte generado por el código de la Actividad
    2.3 y guarda la cantidad de accesos por IP en un Binary Search Tree donde la llave
    es el número de accesos y el valor la dirección IP.

    El programa, además, registra cuáles son las 5 IPs que más se repiten.

    EJEMPLO DE LÍNEA EN ARCHIVO DE ENTRADA (generado por Actividad 2.3):

        * "Oct 9 423.2.230.77:6166 3"

*/
#include <bits/stdc++.h>

using namespace std;

// Nodo básico del árbol
struct Node {

    string ip;
    int freq; // número de ocurrencias de la IP

    Node *left, *right; // apuntadores a hijos

    // Constructor parametrizado (los hijos se declaran como NULL)
    Node(string ip, int freq) {
        this->freq = freq;
        this->ip=ip;
        this->left = NULL;
        this->right = NULL;
    }    
};

// Estructura principal de BST
struct BinarySearchTree{
    Node *root; 
    vector<Node *> fiveLargest; // array dinámico que almacena los 5 nodos con key de mayor valor

    //-- INSERCIÓN --//

    // Método para insertar un nuevo nodo, en el árbol.
    // en caso de que el árbol sea vacío, se crea la root. 
    // En caso contrario, se llama a insertUtil, que buscará el lugar del nuevo nodo
    // :Argumentos: 
    //      * string ip -> dirección ip del registro
    //      * int freq -> número de ocurrencias del registro
    // :Complejidad:
    //      * O(log(n)) / O(h), pues normalmente llama a insertUtil.
    void insert(string ip, int freq){
        if (this->root == NULL){
            this->root = new Node(ip, freq);
            return;
        }    
        this->root = this->insertUtil(this->root, ip, freq);
        this->findFiveLargest(); // actualización de los 5 nodos con mayor frequencia
    }

    // Método para buscar posición de un nuevo nodo e insertarlo
    // en el árbol. Se recorre hasta encontrar una hoja del árbol y se inserta
    // el nuevo nodo como un hijo.
    // :Argumentos: 
    //      * Node* currentNode -> nodo actual
    //      * string ip -> dirección ip del registro
    //      * int freq -> número de ocurrencias del registro
    // :Complejidad:
    //      * O(log(n)) / O(h), pues se recorre normalmente la altura del árbol
    Node* insertUtil(Node* currentNode, string ip, int freq){

        // Si no existe el nodo (se llega a la posición deseada) se crea.
        if (currentNode == NULL) {
            currentNode = new Node(ip, freq);
            return currentNode;
        }


        if (freq < currentNode->freq) {
            // Inserción a la izquierda, si el valor de la frecuencia 
            // es menor que la frecuencia del nodo actual

            // Procesamiento de nodo izquierdo
            currentNode->left = insertUtil(currentNode->left, ip, freq);
        } else {

            // Inserción a la derecha, si el valor de la frecuencia 
            // es mayor que la frecuencia del nodo actual

            // Procesamiento de nodo derecho
            currentNode->right = insertUtil(currentNode->right, ip, freq);
        }

        // Retorno de nodo (en la llamada principal, regresa "root")
        return currentNode;
    }

    //-- NODOS CON MAYOR VALOR --//

    // Crea un nuevo vector y llama a fiveLargestUtil para llenarlo con los 5 nodos 
    // de valor más alto. Retorna el nuevo vector
    // :Complejidad:
    //      O(n) debido al traversal de fiveLargestUtil.
    vector<Node*> findFiveLargest(){
        this->fiveLargest = vector<Node *>();
        fiveLargestUtil(this->root);
        return fiveLargest;
    }

    // Encuentra los 5 nodos con mayor frecuencia utilizando un Reverse Inorder Traversal
    // :Argumentos: 
    //      * Node* root -> nodo actual
    // :Complejidad:
    //      Debido a que en esencia utilizamos un Inorder Traversal, podemos asumir que la mayor
    //      parte de los nodos serán visitados. En el peor de los casos la complejidad será O(n), 
    //      aunque en la mayoría de los casos será menor que esto.
	void fiveLargestUtil(Node *root) {
		if(root){
            fiveLargestUtil(root->right);
            if(fiveLargest.size() <= 5) {
                fiveLargest.push_back(root);
                fiveLargestUtil(root->left);
            }
        }
	}
	
    // Imprime los valores en el vector de fiveLargest
    // :Complejidad:
    //      O(5), pues siempre imprime 5 valores
    void printFiveLargest(){
        for(int i=0; i < 5; i++){
            cout << "  --> IP: " << fiveLargest[i]->ip << ", FREQ: " << fiveLargest[i]->freq <<endl;
        }
    }

    //-- IMPRESIÓN DE DATOS -- //

    void printPreorder() {
        preorderUtil(this->root);
    }

    // Imprime las frequencias de todos los nodos en el árbol. 
    // :Complejidad:
    //      O(n), debido a que en traversal se visitan todos los nodos.
    void preorderUtil(Node *root){
        if(root){
            cout << "  --> IP: " << root->ip << ", FREQ: " << root->freq <<endl;
            preorderUtil(root->right);
            preorderUtil(root->left);
        }
    }
};

// Crea nodos para cada par en el unordered_map y los agrega a un BST
// que es regresado. 
// :Argumentos:
//      * unodedered_map ocurrencies -> mapa que almacena las ocurrencias de cada IP.
//                                      Las keys son las IPs y los valores son la frecuencia
// :Complejidad:
//      O(nlogn), para cada par (hay N pares) se realiza una inserción en el BST y la inserción es O(logn)
BinarySearchTree createTree(unordered_map<string, int> ocurrencies) {

    // Creación de objeto BST
    BinarySearchTree tree = BinarySearchTree();

    for (auto &pair : ocurrencies) {
        // Para cada par, llama a insert con el key y el value
        tree.insert(pair.first, pair.second);
    }

    // Retorno del BST
    return tree;
}

int main(){

    cout << "--------------------------------------\n";
    cout << "--------| Actividad 3.4: BST |--------\n";
    cout << "--------------------------------------\n";

    //-- Lectura de reporte --//
   
	ifstream file("bitacora.txt"); // se abre archivo
    
    string line; //Jun 1 746.6.283.33:4659 1

    // Datos a obtener
    string month, day, ip, freq_str;
    int freq; 

    unordered_map<string, int> ocurrencies;
    while (getline(file, line)) {
		// Almacenamiento de los datos separados por espacios
        stringstream ss(line);
        getline(ss, month, ' ');
        getline(ss, day, ' ');
		getline(ss, ip, ' ');
        getline(ss, freq_str, ' ');
        freq = stoi(freq_str);        

        // Adición a pair cuya key tiene es la ip (cálculo de ocurrencias)
        ocurrencies[ip] += freq;
    }

    file.close(); // Se cierra archivo

    //-- Creación de BST --//
    BinarySearchTree tree = createTree(ocurrencies);

    // Imprimir los valores en Preorder
    cout << "\n__PreOrder Traversal__: \n";
    tree.printPreorder();
    // Imprimir las 5 IPs con mayores ocurrencias
    cout << "\n__5 IPs con mayores ocurrencias__: \n";
    tree.printFiveLargest();

}