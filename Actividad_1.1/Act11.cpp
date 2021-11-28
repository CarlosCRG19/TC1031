/*
ACT 1.1 - Funciones Iterativas, Recursivas y su análisis de Complejidad

- AUTOR: Carlos César Rodríguez García
- MATRÍCULA: A00344666
- FECHA DE CREACIÓN: 19/08/2021

- DESCRIPCIÓN: Este programa calcula la sumatoria desde 1 hasta n utilizando tres métodos
	distintos. Al final, se prueban los tres métodos con cuatro casos distintos.
*/

#include <bits/stdc++.h>

using namespace std;

//-- FUNCIONES--//

/**
    Utiliza un ciclo for para generar todos los números desde 1 hasta n.
	Por cada iteración, donde genera los elementos, agrega el nuevo número
	a un acumulador. Debido a que atraviesa todos los números de 1 hasta n, 
	la complejidad del algoritmo en esta función es O(n).

	:Argumentos: un entero "n" que describe hasta dónde se desea la suma.
	:Return: un entero "suma" que representa la sumatoria de 1 hasta n	

*/
int sumaIterativa(int n) {
	// Acumulador a retornar
	int suma = 0;

	// Crear loop for y sumar cada valor al acumulador
	for (int i = 1 ; i <= n ; i++) {
		suma += i;
	}

	// Retornar el valor de la suma
	return suma;
}


/**
    La función genera la suma desde 1 hasta n llamándose a sí misma con el valor 
	de n-1 y sumando esto al valor inicial de n. De esta forma la función "itera" 
	n veces hasta llegar al caso base (0) cuando retorna 0. Con lo anterior, su complejidad
	sería O(N).

	:Argumentos: un entero "n" que describe hasta dónde se desea la suma.
	:Return: un entero "suma" que representa la sumatoria de 1 hasta n	

*/
int sumaRecursiva(int n) {
	// Checar base case en el que n es 0
	if (n == 0) {
		return 0;
	}
	// Retornar la suma de n y la función recursiva 	
	return n + sumaRecursiva(n - 1);
}


/**
    Utiliza la fórmula de la Suma de Gauss para calcular la sumatoria
	desde 1 hasta n. Debido a que solo se sustituyen los valores en la fórmula (estatuto base), 
	el cálculo es directo y la complejidad O(1).

	:Argumentos: un entero "n" que describe hasta dónde se desea la suma.
	:Return: un entero "suma" que representa la sumatoria de 1 hasta n	

*/
int sumaDirecta(int n) {
	return n * (n + 1) / 2;
}


int main() {
	
	// Valores de N para casos prueba
	int prueba1 = 6, prueba2 = 15, prueba3 = 1000, prueba4 = 0;

	cout << "CASOS PRUEBA" << endl;
	cout << "------------" << endl;

	// Caso prueba 1: debe retornar 21
	cout << "1. n = 6 -> suma = 21" << endl;
	cout << "Iterativa: " << sumaIterativa(prueba1) << ", Recursiva: " << sumaRecursiva(prueba1) << ", Directa: " << sumaDirecta(prueba1) << endl;  
	cout << endl;

	// Caso prueba 2: debe retornar 120
	cout << "2. n = 15 -> suma = 120" << endl;
	cout << "Iterativa: " << sumaIterativa(prueba2) << ", Recursiva: " << sumaRecursiva(prueba2) << ", Directa: " << sumaDirecta(prueba2) << endl;  
	cout << endl;

	// Caso prueba 3: debe retornar 1000
	cout << "3. n = 1000 -> suma = 500500" << endl;
	cout << "Iterativa: " << sumaIterativa(prueba3) << ", Recursiva: " << sumaRecursiva(prueba3) << ", Directa: " << sumaDirecta(prueba3) << endl;  
	cout << endl;

	// Caso prueba 4: debe retornar 0
	cout << "4. n = 0 -> suma = 0" << endl;
	cout << "Iterativa: " << sumaIterativa(prueba4) << ", Recursiva: " << sumaRecursiva(prueba4) << ", Directa: " << sumaDirecta(prueba4) << endl;  

	return 0;

}
