/*
Actividad 1.3: Conceptos Básicos y Algoritmos Fundamentales
Carlos César Rodríguez García A00344666
Brandon Josué Magaña Mendoza A01640162
Luis David López Magaña A00344656

Programa que lee una bitácora de fallas desde un archivo .txt, guarda cada evento
en un vector de objetos de clase Falla  y lo ordena por fecha mediante la implementación 
del algoritmo de Quick Sort. Posteriormente pide al usuario que ingrese un intervalo de
tiempo para mostrar las fallas en el mismo y ofrece la posibilidad de guardarlas en
un nuevo archivo .txt.
*/


#include <bits/stdc++.h>

using namespace std;

class Falla {
    private:

        int fecha;  // Entero que representa a la fecha en formato MESDIAHORA (e.g. 12311200 -> 31 de diciembre a las 12:00)
        string falla; // El mensaje de falla que se le muestra al usuario


        /* 
            Utiliza métodos estáticos para formatear cada componente de la fecha y retorna
            la fecha para ese día formateada como entero. Esta única función tiene complejidad constante

            :Argumentos:
                mes -> string 
                dia -> string
                hora -> string en formato de 24 horas

            :Return:
                una hora en tipo entero
        */
        static int formateaFecha(string mes, string dia, string hora) {
            string fechaFormateada = formateaMes(mes) + formateaDia(dia) +  formateaHora(hora);
            // Formateo de string a entero
            return stoi(fechaFormateada);

        } 

        /*
            Formatea una hora escrita en estructura de 24 horas (23:59:59). 
            Elimina los dos puntos usando sub strings.

            :Argumentos:
                hora -> string

            :Return:
                una hora sin : en tipo de dato de string

        */    
        static string formateaHora(string hora) {
            return hora.substr(0, 2) + hora.substr(3, 2) + hora.substr(6, 2);
        }
    
    public:

        //-- GETTERS Y SETTERS --//
        
        void setFalla(string _falla) { 
            this->falla = _falla;
        }

        string getFalla() {
            return this->falla;
        } 
    
        int getFecha(){
            return this->fecha;
        }
        
        
        // Constructor parametrizado de objetos Falla.  
        Falla(string mes, string dia, string hora, string falla) {
            this->fecha = formateaFecha(mes, dia, hora); // las fallas se comparan con base a este atributo
            this->falla = mes + " " + dia + " "+ hora  + " " + falla; 
        }
        
        /* 
            Agrega un 0 si un día tiene únicamente un dígito
            
            :Argumentos: 
                dia -> string de 1 a 31
            :Return:
                un string de dos caracteres representando el día
        */
        static string formateaDia(string dia) {
            return dia.size() > 1 ? dia : "0" + dia;
        }

        /*
            Utiliza un diccionario para relacionar el mes con su número en dos dígitos (e.g. Enero -> 01).
            
            :Argumentos:
                mes -> string 
            :Return:
                un string que representa al mes en dos dígitos
        */
        static string formateaMes(string mes) {
            
            map<string, string> meses
            {
                {"Jan", "01"},
                {"Feb", "02"},
                {"Mar", "03"},
                {"Apr", "04"},
                {"May", "05"},
                {"Jun", "06"},
                {"Jul", "07"},
                {"Aug", "08"},
                {"Sep", "09"},
                {"Oct", "10"},
                {"Nov", "11"},
                {"Dec", "12"}
            };
            
            // Si el mes sí se encuentra en el diccionario, regresa dicho mes
            if (meses.find(mes) != meses.cend()){
                return meses[mes];
            }
            // En caso contrario, regresa un string vacio
            return "";
        }


        

};

class FallaSorter {
    private:

        /* 
            Método de apoyo que intercambia dos elementos del array de fallas. 
            Esta operarción es inplace.

            Debido a que solo se hace un intercambio de valores (igualaciones),
            la complejidad es O(1). Se realiza en tiempo constante.

            :Argumentos:
                x -> primer elemento a intercambiar
                y -> segundo elemento a intercambiar
        */
        static void fallaSwap(Falla& x, Falla& y) {
            Falla temp = y;
            y = x;
            x = temp;
        }

        /*
            Toma el último elemento del vector como un pivote, lo coloca en su
            posición correcta con respecto al array sorteado, y coloca los elementos
            menores (más pequeños que el pivote) a la izquierda y a los elementos más
            grandes a la derecha. 
            
            Debido a que esta función recorre todo el array, su complejidad será O(n).

            :Argumentos:
            
                fallas -> un vector de fallas
                low -> un entero que representa el índice del primer elemento del subarray en el array 
                principal 
                high -> un entero que representa el índice del último elemento del subarray

            :Return: un entero que representa la posición correcta del pivote en el array 

        */
        static int particion(vector<Falla>& fallas, int low, int high) {

            int valorPivote;
            // Obtener fecha del pivote (último valor en el array)
            valorPivote = fallas[high].getFecha();

            int i;
            // Obtener índice del elemento más pequeño
            i = low - 1;

            for(int j=low ; j <= high ; j++) {

                // Obtener la fecha del elemento actual para comparar
                int valorComparacion = fallas[j].getFecha();
                
                // Comparar el valor actual con el pivote
                if (valorComparacion < valorPivote) {  
                    // Si la fecha actual es menor, 
                    // mover el índice del menor elemento
                    i++;
                    fallaSwap(fallas[i], fallas[j]);

                }
                
            }

            fallaSwap(fallas[i+1], fallas[high]);
            return i+1;
        }

    
    public:

        /*
            Función principal que implementa el QuickSort. 
            Debido a que este algoritmo divide el array cada vez en 2 y 
            a realiza una operación de O(n) a cada subarray, su complejidad total es de O(nlogn) 

            :Argumentos:
                fallas -> un vector de objetos Falla
                low -> el índice inicial del vector
                high -> el índice final del vector
        */
        static void quickSort(vector<Falla>& fallas,int low, int high) {

            if(low < high) {
                // Llamada a la función partición, que colocará a fallas[p] en su posición correcta.
                int pi = particion(fallas, low, high);

                // Realiza el mismo proceso para ordenar el subarray a la derecha de pi
                // y el subarray a la izquierda de pi
                quickSort(fallas, low, pi-1);
                quickSort(fallas, pi+1, high);
            } 
        }

};

class FallaSearcher{
    public:

		/*
			Función que implementa la búsqueda binaria.
			Tomando un vector ordenado de forma ascendente, identifica si el punto medio
			del mismo es superior o inferior al elemento deseado para determinar el siguiente
			punto medio a checar hasta que se encuentre el elemento.
		*/
        static int binSearch(vector<Falla> fallas, int target){
            int inicio = 0;
            int fin = fallas.size() - 1;
            
            while(inicio <= fin){
            	int mitad = inicio + (fin - inicio) / 2;

                if(target == fallas[mitad].getFecha()) {
					return mitad;
				}
                else if(target < fallas[mitad].getFecha()) {
                    fin = mitad-1;
            	}
				else{
                    inicio = mitad + 1;
                }
            }
            return inicio;
        }
};


int main() {

	// Creación de vector de fallas.
	vector<Falla> fallas;

	// Lectura del archivo de eventos de falla
	ifstream lector("bitacora.txt");
    string linea, mes, dia, hora, falla; 
    while (getline(lector, linea)) {
		// Almacenamiento de los datos separados por espacios
        stringstream ss(linea);
        getline(ss, mes, ' ');
        getline(ss, dia, ' ');
        getline(ss, hora, ' ');
        getline(ss, falla, '\n');

		// Creación de nueva falla y almacenamiento en el vector
        Falla nuevaFalla = Falla(mes,dia,hora,falla);
        fallas.push_back(nuevaFalla);
    }
    lector.close();

	// Implementación de Quick Sort e impresión de fallas ordenadas por fecha    
    cout << "//-- FALLAS SORTEADAS: \n";

    FallaSorter::quickSort(fallas, 0, fallas.size() - 1);
    for(Falla f : fallas) {
        cout << f.getFalla() << "\n";
    }
    //Se guarda el vector de fallas ordenado en bitacoraordenada.txt
    ofstream escritor("bitacoraordenada.txt");
    if (escritor.is_open()) {
        for (int i = 0 ; i < fallas.size() ; i++) {
            escritor << fallas[i].getFalla() << "\n";
        }
        escritor.close();
		cout << "Las fallas ordenadas se han guardado en \"bitacoraordenada.txt\"." << endl;
	}

    // Input del Usuario
    cout << "//-- INPUT DEL USUARIO --// \n"; 
    
	// Mes y día de límite inferior
    string mesInicioStr, diaInicioStr;
    cout << "Ingrese primeras tres letras del mes (e.g. Aug): ";
    cin >> mesInicioStr;
    cout << "Ingrese día : ";
    cin >> diaInicioStr;

	// Almacenamiento con hora 12:00 AM
    int fechaInicio = stoi(Falla::formateaMes(mesInicioStr) + Falla::formateaDia(diaInicioStr) + "000000");

	// Mes y día del límite superior
    string mesFinalStr, diaFinalStr;
    cout << "Ingrese primeras tres letras del mes (e.g. Aug): ";
    cin >> mesFinalStr;
    cout << "Ingrese día : ";
    cin >> diaFinalStr;
	
	// Almacenamiento con hora 23:59 PM
    int fechaFinal = stoi(Falla::formateaMes(mesFinalStr) + Falla::formateaDia(diaFinalStr) + "235959");

	// Búsqueda e impresión de índices de inicio y final
    int indiceInicio = FallaSearcher::binSearch(fallas, fechaInicio);
    int indiceFinal = FallaSearcher::binSearch(fallas, fechaFinal);
    cout << "Fecha inicio: " << fechaInicio << " Índice: " << indiceInicio << endl;
    cout << "Fecha final: " << fechaFinal << " Índice: " << indiceFinal << endl;
    cout << endl;

    // Imprime Reporte
    cout << "//-- IMPRESIÓN DE REPORTE --// \n";
    cout << endl;
    for (int i = indiceInicio ; i < indiceFinal ; i++) {
        cout << fallas[i].getFalla() << "\n";
    }

	// Guarda Reporte
    string respuesta;
    cout << "¿Desea guardar los resultados en un archivo? (Si/No): ";
    cin >> respuesta;
    if (respuesta == "Si") {
        ofstream escritor("reporte.txt");
        if (escritor.is_open()) {
            for (int i = indiceInicio ; i < indiceFinal ; i++) {
                escritor << fallas[i].getFalla() << "\n";
            }
        	escritor.close();
			cout << "El intervalo de fallas fue guardado en \"reporte.txt\"." << endl;
		}
	}
}