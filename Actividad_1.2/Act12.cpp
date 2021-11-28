/*
ACT 1.2 - Algoritmos de Búsqueda y Ordenamiento

- AUTOR: Carlos César Rodríguez García
- MATRÍCULA: A00344666
- FECHA DE CREACIÓN: 02/02/2021

- DESCRIPCIÓN: Este programa realiza el ordenamiento de vectores con tres algoritmos distintos 
    (Insertion Sort, Bubble Sort y Merge Sort). A su vez, también incluye funciones para 
    encontrar un valor en un array

- INPUT: Primero se recibe un entero T que representa el número de casos de prueba. Para cada T casos, se recibe un
    entero N que representa la longitud de un array; se llena el array con N valores y por último se recibe un valor 
    B que se buscará dentro del array.

    Ejemplo de Input:

        1
        4
        4 3 2 1
        3

- OUTPUT: Para cada caso, se imprime una copia del array ordenada con cada uno de los algoritmos y por último su 
    posición en memoria, esto para comprobar que distintos arrays fueron ordenados. A su vez, se imprime el índice
    del valor buscado

    Ejemplo de Output:

        || CASO 1 ||
        
        Ordenamiento
        ------------
        Insertion Sort: 1 2 3 4 | Posición en Memoria: 1003
        Bubble Sort: 1 2 3 4 | Posición en Memoria: 2003
        Merge Sort: 1 2 3 4 | Posición en Memoria: 4003

        Búsqueda
        -------- 
        Sequential Search: 1
        Binary Search: 1

*/

#include <bits/stdc++.h>

using namespace std;

// Clase que almacena los métodos de ordenamiento y sus auxiliares
// Los distintos algoritmos se escriben como funciones estáticas y modifican directamente el array que reciben
class Ordenador {

    private:

        // -- MÉTODOS AUXILIARES -- //

        /**
            Intercambia la referencia de dos valores dentro de un array. El swap es inplace.
            Esta operación solo involucra igualaciones simples por lo que su complejidad es O(1).

            :Argumentos: dos referencias a valores x y y
        */
        static void swap(int& x, int& y){
                // Almacenar valor de y en una variable temporal
                int temp = y;
                y = x;
                x = temp;
        }


        /**
            Une dos subarrays de un array inicial. Se itera sobre cada subarray, se comparan sus valores
            y se llena el array padre con los valores ordenados ascendentemente. Debido a que la operación
            recorre los dos subarrays y cuenta con un índice k que va de 0 hasta array.size(), la complejidad
            es O(n).

            :Argumentos: un vector de enteros "v". Índices "low", "high" y "mid" que representan el inicio, final
                y mitad del array sobre el cual aplicar el merge
        */
        static void merge(vector<int>& v, int low, int high, int mid){

            // Crear arrays temporales 
            vector<int> left, right;

            // Copiar los valores de ambas mitades
            // del array inicial
            for(int i=low; i<mid; i++) 
                left.push_back(v[i]);
            
            for (int j=mid; j<high; j++) 
                right.push_back(v[j]);
            
            int i, j, k;
            i = j = 0; // índices para recorrer subarrays
            k = low; // índice del array que está siendo unido
            while(i < left.size() && j < right.size()) {
                // Comparar si el valor del primer subarray es menor
                if(left[i] < right[j]) {
                    // Llenar v[k] con el valor en el primer subarray
                    v[k] = left[i];
                    i++;
                } else {
                    // En caso contrario, colocar el valor del segundo subarray
                    // en la posición k del array principal
                    v[k] = right[j];
                    j++;
                }
                k++;
            }

            // Copiar los elementos restantes del 
            // primer subarray en el array principal
            while(i < left.size()) {
                v[k] = left[i];
                i++;
                k++;
            }

            // Copiar los elementos restantes del 
            // segundo subarray en el array principal
            while(j < right.size()) {
                v[k] = right[j];
                j++;
                k++;
            }
        }

    public:
        
        // -- MÉTODOS DE ORDENAMIENTO -- //

        /* 
            Ordena un array inplace usando insertion sort. 
            :Argumentos: un vector de enteros "v"
            
            Complejidad O(n^2). Se recorre el array de 0 a n-1
            y se compara el elemnto actual con sus predecesores para colocarlo en la 
            posición correcta
        */
        static void ordenaIntercambio(vector<int>& v) {
            for (int i = 1; i < v.size(); i++) {
                int j = i;
                while (j > 0 && v[j] < v[j-1]) {
                    Ordenador::swap(v[j], v[j-1]);
                    j--;
                }
            }
        }

        /* 
            Divide el array en dos, se llama a sí mismo en cada uno de los subarrays y utiliza otra
            función para unir los dos subarrays sorteados. Esta es la primera función para aplicar un MergeSort

            Por sí misma, esta función tiene complejidad de O(logn). Pero llama al merge, por lo que la Complejidad
            de todo el algoritmo de MergeSort es O(nlogn).

            :Argumentos: Un vector de enteros "v", el inicio del array y su final.

        */
        static void ordenaMerge(vector<int>& v, int begin, int end) {
            
            if ((end-begin) <= 1)
                return;

            int mid = (end - begin)/2 + begin;
            Ordenador::ordenaMerge(v, begin, mid);
            Ordenador::ordenaMerge(v, mid, end);
            Ordenador::merge(v, begin, end, mid);

        }

        /* 
            Implementa bubbleSort para ordernar un array de manera ascendente.
            Intercambio elementos adyacentes hasta que estén en su lugar.

            Complejidad O(n^2). Ocurre cuando el vector está en orden decendente.
            Aquí el algoritmo se optimiza con el bool "swapped".

            :Argumentos: un array de enteros "v"
        */
        static void ordenaBurbuja(vector<int>& v) {

            for (int i = 0; i < v.size(); i++) {
                bool swapped = false;

                // El último elemento ya está en su lugar
                for (int j = 0; j < v.size()-i-1; j++) {
                    if (v[j] > v[j+1]) 
                        Ordenador::swap(v[j], v[j+1]);
                        swapped = true;
                }
                
                // Si no hubo ningun swap, el array ya está ordenado
                if (!swapped) {
                    return;
                }

            }
        }
};

// Clase que almacena todos los algoritmos de búsqueda. Se implementan como métodos estáticos.
class Buscador {
    public:

        /*
            Recorre todo el array en busca del elemento. SI lo encuentra, regresa su índice.

            La complejidad de este algoritmo es O(n). 

            :Argumentos: un array de enteros v y un entero a buscar "target"
        */
        static int busqSecuencial(vector<int> v, int target) {
            for (int i=0; i<v.size(); i++) {
                if(v[i] == target) 
                    return i;
            }
            return -1;
        }

        /*
            Busca un elemento en un array sorteado. Divide el array en un intervalo de búsqueda
            y según el valor en el medio dividirá este intervalo en dos y realizará el mismo proceso en 
            una de estas mitades. Si el elemento es menor al que está en medio, se toma la mitad inferior;
            si el elemento es igual, se regresa su índice; y si es mayor, se toma la mitad superior.

            Complejidad O(logn). Con un mejor caso de O(1) cuando el elemento a buscar está justo en medio.

            :Argumentos: un array de enteros v, su inicio (int), su final (int) y un entero a buscar "target"


        */
        static int busqBinaria(vector<int>v, int low, int high, int target) {
            
            if(high >= low) {
                int mid = low + (high - low) / 2;

                if(v[mid] == target) 
                    return mid;
                else if(v[mid] > target)
                    return busqBinaria(v, low, mid-1, target);

                return busqBinaria(v, mid+1, high, target);
            }
            return -1;
        }
};

// Complejidad O(n). Recorre todo el array
void imprimeArray(vector<int> v) {
    for(auto &it : v)
        cout << it << " " ;
}

int main() {
        
    freopen("input.txt","r",stdin); // Recibe inputs de archivo txt

    int t_cases;
    cin >> t_cases;

    for(int i = 0; i < t_cases; i++) {
        // Header
        printf("\n|| CASO %d || \n\n", i+1);
        
        // Generación de array base
        int n;
        cin >> n;
        vector<int> arrayBase(n);
        for (auto &it : arrayBase) {
            cin >> it;
        }

        // Otención de número a buscar
        int b;
        cin >> b;

        // Generación de copias de array base 
        // (esto no es óptimo en cuanto a uso de memoria, pero es solo para esta demo)
        vector<int> arrayIntercambio(arrayBase.begin(), arrayBase.end());
        vector<int> arrayMerge(arrayBase.begin(), arrayBase.end());
        vector<int> arrayBurbuja(arrayBase.begin(), arrayBase.end());

        // Ordenamiento de vectores
        Ordenador::ordenaIntercambio(arrayIntercambio);
        Ordenador::ordenaMerge(arrayMerge, 0, arrayMerge.size());
        Ordenador::ordenaBurbuja(arrayBurbuja);

        // Búsqueda de elemento B 
        int iSequentialSearch = Buscador::busqSecuencial(arrayMerge, b);
        int iBinarySearch = Buscador::busqBinaria(arrayMerge, 0, arrayMerge.size()-1, b);
        
        cout << "ARRAY BASE: ";
        imprimeArray(arrayBase);
        cout << "\nELEMENTO A BUSCAR: " << b << "\n\n";

        // Impresión de resultados
        cout << "Ordenamiento \n";
        cout << "------------ \n";


        cout << "Ordena Intercambio: ";
        imprimeArray(arrayIntercambio);
        cout << " | Locación en memoria: " << &arrayIntercambio[0] << "\n";
        cout << "Ordena Merge: ";
        imprimeArray(arrayMerge);
        cout << " | Locación en memoria: " << &arrayMerge[0] << "\n";
        cout << "Ordena Burbuja: ";
        imprimeArray(arrayBurbuja);
        cout << " | Locación en memoria: " << &arrayBurbuja[0] << "\n\n";

        cout << "Búsqueda \n";
        cout << "-------- \n";
        cout << "Búsqueda Secuencial: " << iSequentialSearch << "\n";
        cout << "Búsqueda Binary: " << iBinarySearch << "\n";
    
    }
}

