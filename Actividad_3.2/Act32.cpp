#include <bits/stdc++.h>
using namespace std;

struct MaxHeap { 
        int len=0; // tamaño del heap
        vector<int> MaxHeap; // array dinámico para almacenar heap ordenado
        
        //-- Funciones Auxiliares --//

		// Función auxiliar que intercambia dos nodos
		// Complejidad: O(1)
        void swap(int i1, int i2){
            int temp = MaxHeap[i1];
            MaxHeap[i1] = MaxHeap[i2];
            MaxHeap[i2] = temp;
        }
        
		// Funciones que indican la existencia de nodo izquierdo, derecho o padre
		// Complejidad: O(1)
        bool hasRight(int index){
            return getRightIndex(index)< this->MaxHeap.size();
        }
		
        bool hasLeft(int index) {
            return getLeftIndex(index) < this->MaxHeap.size();
        }
        
        bool hasParent(int index){
            return getParentIndex(index) >= 0;
        }

		// Getters de los índices de nodo padre, izquierdo y derecho
		// Complejidad: O(1)
        int getParentIndex(int index){return (index-1)/2;}
        
        int getLeftIndex(int index){return index*2 + 1;}

        int getRightIndex(int index){return index*2 + 2;}

		// Getters de nodos padre, izquierdo y derecho
		// Complejidad: O(1)
        int getRight(int index){
            return MaxHeap[getRightIndex(index)];
        }

        int getLeft(int index){
            return MaxHeap[getLeftIndex(index)];
        }

        int getParent(int index){
            return MaxHeap[getParentIndex(index)];
        }
    
        //-- Métodos Principales --//

		// Función que ingresa un nodo al heap, llama a la función heapifyUp y aumenta el tamaño del vector
		// Complejidad: 
		void push(int item) {
			MaxHeap.push_back(item);
			len++;
            heapifyUp();
		}

		// Función que elimina y retorna la raíz del heap, llama a la función heapifyDown y disminuye el tamaño del vector
		// Complejidad: O(Log(n))
        int pop(){
            if(len==0) return -1;
            int item = MaxHeap[0];
            MaxHeap[0]= MaxHeap[len-1];
            heapifyDown();
			len--;
            MaxHeap.erase(MaxHeap.begin()+(len));
            return item;
        }
		
		// Función que retorna el nodo raíz
		// Complejidad: O(1)
        int top(){
            if(len==0) return -1;
            return MaxHeap[0];
        }

		// Función que indica si el heap está vacío
		// Complejidad: O(1)		
        bool empty(){
            return len==0;
        }

		// Función que retorna el tamaño del heap
		// Complejidad: O(1)
		int size(){
            return len;
        }

		// Función que organiza el heap cuando se ingresa un nuevo valor
		// Complejidad: O(nlog(n))
        void heapifyUp(){
            int current = len - 1; 
			// Intercambia el nuevo valor con su padre mientras sea mayor al mismo
            while(hasParent(current) && MaxHeap[current] > getParent(current)){
                swap(current, getParentIndex(current)); 
                current = getParentIndex(current);
            }
        }

        // Función que acomoda al nodo en root en su lugar
        // Complejidad: O(h) / O(log(n))
        void heapifyDown(){
            int index = 0;
            while(hasLeft(index)){
                // Si no tiene hijo izquierdo, no tendrá hijo derecho 
                int maxChildIndex = getLeftIndex(index);
                
                if(hasRight(index) && getRight(index) > getLeft(index)){
                    maxChildIndex = getRightIndex(index);
                }
                if(MaxHeap[maxChildIndex] > MaxHeap[index]){
                    swap(maxChildIndex, index);
                }else{
                    break;
                }
                index = maxChildIndex;
            }
        }
        
        //-- Otras funciones --//

        void print(){
            for(auto &it: MaxHeap){
                cout << "     --> " << it << endl;
            }
        }  
};

int main() {

    cout << "---------------------\n";
    cout << "-----| MaxHeap |-----\n";
    cout << "---------------------\n";
    
    // Creación de nuevo heap
    MaxHeap myHeap; 

    //Agregando datos al Heap
    myHeap.push(6);
    myHeap.push(5);
    myHeap.push(3);
    myHeap.push(4);
    myHeap.push(2); 
    myHeap.push(1);  
    
    //Impresión del tamaño de Max Heap
    cout << "1. Tamaño de Heap : "<< myHeap.size()<<endl;

    //Impresión de Max Heap
    cout << "2. Valores acomodados en Heap : \n";
    myHeap.print();

    //Removiendo el elemento con mayor prioridad
    cout<<"3. Valor en Top (previo a pop): "<< myHeap.top()<<endl;
    myHeap.pop(); 
    cout<<"4. Valor en Top (posterior a pop): "<< myHeap.top()<<endl;
    
    //Impresión del tamaño de Max Heap
    cout << "5. Tamaño de Heap (posterior a pop): "<< myHeap.size()<<endl;
    
    //Impresión de Max Heap
    cout << "6. Valores acomodados en Heap (posterior a pop): \n";
    myHeap.print();
}