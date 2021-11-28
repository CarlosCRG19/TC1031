/*
    Act 2.3 - Actividad Integral estructura de datos lineales
    Luis David López Magaña A00344656
    Carlos César Rodríguez García A00344666
    Brandon Josué Magaña Mendoza  A01640162

    Programa que lee una bitácora de fallas desde un archivo .txt, 
    guardando en primera instancia cada una de las ocurrencias de las 
    IPs en un map donde su key es la propia IP junto con su fecha. 

    Posterior a ello cada uno de los valores guardados en el map se 
    encapsularan en Nodos, mismos que procederan a añadirse a una 
    PriorityQueue donde la key es el numero de ocurrencias de la IP.

    Finalmente se guarda al reporte ordenado y se pide al usuario que
    ingrese un intervalo de tiempo para mostrar las fallas en el mismo 
    organizadas por numero de ocurrencias de dirección IP.
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
    int dateInt; // Entero que representa la fecha
    int frequency;//Entero que representa la frecuencia con la que aparece una IP en la bitacora
    string message;//String que contiene el registro 
    
    Node *next;//Apuntador al Nodo Siguiente
    
	// Constructor con parámetros
    Node(int dateInt, int frequency, string message) {
        this->dateInt = dateInt;
        this->frequency = frequency;
        this->message = message;
        this->next = NULL;
    }
};

class PriorityQueue{
    public:
        Node *head, *tail;
		
        //Método que agrega la información en el lugar correspondiente de la PriorityQueue
        //Complejidad: O(n)
        void enqueue(Node *node){
            
            // Caso de queue nulo
            if(this->head == NULL){//Si nuestra PriorityQueue esta vacia, la inicializamos con la información del nodo recibido
                this->head = this->tail = node;
                return;
            }
            
            Node *currentNode = this->head; // Asigna al nodo actual como head
            
            // Insercion al inicio 
            if (node->dateInt < currentNode->dateInt || (node->dateInt == currentNode->dateInt && node->frequency > currentNode->frequency)) {         
                node->next = currentNode; //no tenemos que hacer el siguiente del nodo anterior a currnent node el node?
                this->head = node;
            } else {
                // Encontrar prioridad
                while(currentNode->next && node->dateInt > currentNode->next->dateInt){
                    currentNode = currentNode->next;
                }
				
                while(currentNode->next && node->dateInt == currentNode->next->dateInt && node->frequency < currentNode->next->frequency) {
                    currentNode = currentNode->next;
                }

                if (!currentNode->next){
                    // añadir al final
                    this->tail->next = node;
                    this->tail = node;
                    return;
                }
                node->next = currentNode->next;
                currentNode->next = node;
            }
        }

        // Impresion de todos los nodos
        //Complejidad: O(n)
        void printlist(){
            Node *currentNode = this->head;  

            while(currentNode != NULL){
                cout << currentNode->message << " " << currentNode->frequency << "\n";
                currentNode = currentNode->next;
            }
            cout << endl;
        } 

		// Impresion del reporte 
        //Complejidad: O(n);
        void printReporte(int date){
            Node *currentNode=this->head;
            while(currentNode->dateInt < date){
                    currentNode = currentNode->next;
            }
            
            if(currentNode->dateInt > date){
                 cout << "No se han encontrado registros en este intervalo." << endl;
                 return;
            }
            
            while(currentNode != NULL && currentNode->dateInt == date){
                cout << currentNode->message << " " << currentNode->frequency << "\n";
                currentNode = currentNode->next;
            }
            return;
        }
    
        // Sobrecarga de función printReporte
        //  Utilizada para obtener un reporte en un determinado intervalo 
        // Complejidad: O(n);
        void printReporte(int date1, int date2){
            Node *currentNode=this->head;
            int min = date1;
            int max = date2;

            if(date1 < currentNode->dateInt && date2 < currentNode->dateInt){
                cout << "No se han encontrado registros en este intervalo." << endl;
                return;
            }   

            if(date1 > this->tail->dateInt && date2 > this->tail->dateInt){
                cout << "No se han encontrado registros en este intervalo." << endl;
			    return;
            }
		
            if(date1==date2){
                printReporte(date1);
                return;
            }    
        
            if(date2 < date1){
                min=date2;
                max=date1;
            }
		
            while(currentNode != NULL && currentNode->dateInt <= max){
                if(currentNode->dateInt >= min){
                    cout << currentNode->message << " " << currentNode->frequency << "\n";
                }
                currentNode = currentNode->next;
            }
        }

        //Método para almacenar la información en archivo de texto reporte.txt
        //Complejidad O(n)
		void saveReport() {	
			Node *currentNode=this->head;
			ofstream escritor("reporte.txt");
			if (escritor.is_open()) {
				while (currentNode) {
					escritor << currentNode->message << " " << currentNode->frequency << "\n";
					currentNode = currentNode->next;
				}
				escritor.close();
            }
				cout << "El intervalo de fallas fue guardado en \"reporte.txt\"." << endl;
		}
};

class DateFormatter {
    public:
        /* 
            Utiliza métodos estáticos para formatear cada componente de la fecha y retorna
            la fecha para ese día formateada como entero. Esta única función tiene complejidad constante

            :Argumentos:
                mes -> string 
                day -> string
                hora -> string en formato de 24 horas

            :Return:
                una hora en tipo entero
        */
        static int formatDate(string month, string day) {
            string formattedDate = formatMonth(month) + formatDay(day);
            // Formateo de string a entero
            return stoi(formattedDate);
        }
        
        /* 
            Agrega un 0 si un día tiene únicamente un dígito
            
            :Argumentos: 
                day -> string de 1 a 31
            :Return:
                un string de dos caracteres representando el día
        */
        static string formatDay(string day) {
            return day.size() > 1 ? day : "0" + day;
        }

        /*
            Utiliza un diccionario para relacionar el month con su número en dos dígitos (e.g. Enero -> 01).
            
            :Argumentos:
                month -> string 
            :Return:
                un string que representa al month en dos dígitos
        */
        static string formatMonth(string month) {
            
            map<string, string> months
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
            
            // Si el month sí se encuentra en el diccionario, regresa dicho month
            if (months.find(month) != months.cend()){
                return months[month];
            }
            // En caso contrario, regresa un string vacio
            return "";
        }
};


/*
    :Argumentos:
        ocurrencies -> Mapa desordenado<string, int>
    :Return:
        PriorityQueue con Nodos ordenados
    Complejidad: O(n^2) 
*/
PriorityQueue createNodes(unordered_map<string, int> ocurrencies) {
    
    PriorityQueue queue = PriorityQueue();

    string month, day;
    for (auto &pair : ocurrencies) {

        stringstream ss(pair.first);
        getline(ss, month, ' ');
        getline(ss, day, ' ');

        int dateInt = DateFormatter::formatDate(month, day);
        queue.enqueue(new Node(dateInt, pair.second, pair.first));
    }
    return queue;
}





int main() {
    // Lectura del archivo de eventos de falla
    unordered_map<string, int> ocurrencies;
	ifstream file("bitacora copy.txt");
    string linea, month, day, hora, falla, ip; 
    while (getline(file, linea)) {
		// Almacenamiento de los datos separados por espacios
        stringstream ss(linea);
        getline(ss, month, ' ');
        getline(ss, day, ' ');
        getline(ss, hora, ' ');
		getline(ss, ip, ' ');
        
		string key = month + " " + day + " " + ip;
        // cout << key << endl;
        ++ocurrencies[key];

    }
    file.close();

    PriorityQueue queue = createNodes(ocurrencies);

	// Guarda Reporte
	queue.saveReport();
	
	// Input del Usuario
    cout << "//-- INPUT DEL USUARIO --// \n"; 
    
	// Mes y día de límite inferior
    string mesInicioStr, diaInicioStr;
    cout << "Ingrese primeras tres letras del mes (e.g. Aug): ";
    cin >> mesInicioStr;
    cout << "Ingrese día : ";
    cin >> diaInicioStr;

	// Almacenamiento 
    int fechaInicio = (DateFormatter::formatDate(mesInicioStr, diaInicioStr));

	char answer;
	cout << "¿Deseas establecer un intervalo de búsqueda? (Y/N): ";
	cin >> answer;
    
	if (answer == 'Y' || answer == 'y') {
		// Mes y día del límite superior
		string mesFinalStr, diaFinalStr;
		cout << "Ingrese primeras tres letras del mes (e.g. Aug): ";
		cin >> mesFinalStr;
		cout << "Ingrese día : ";
		cin >> diaFinalStr;
		
		// Almacenamiento 
		int fechaFinal = (DateFormatter::formatDate(mesFinalStr, diaFinalStr));

		cout << "\n//---REPORTE DE FALLAS POR FRECUENCIA DE DIRECCION IP---\\\\" << endl;
        queue.printReporte(fechaInicio,fechaFinal);
	}
	else {
		cout << "\n//---REPORTE DE FALLAS POR FRECUENCIA DE DIRECCION IP---\\\\" << endl;
        queue.printReporte(fechaInicio);
	}
}