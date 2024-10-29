#include <iostream>
#include <string>
#include <locale>

// Clase SocioClub para almacenar la información de un socio
class SocioClub {
private:
    int numeroSocio;
    std::string nombre;
    std::string domicilio;
    int anioIngreso;  // Nuevo campo Año de Ingreso

public:
    // Constructor por defecto
    SocioClub() : numeroSocio(0), nombre(""), domicilio(""), anioIngreso(0) {}

    // Constructor con parámetros
    SocioClub(int numero, std::string nombre, std::string domicilio, int anio)
        : numeroSocio(numero), nombre(nombre), domicilio(domicilio), anioIngreso(anio) {}

    // Sobrecarga del operador << para impresión
    friend std::ostream& operator<<(std::ostream& out, const SocioClub& socio) {
        out << "Numero de Socio: " << socio.numeroSocio
            << ", Nombre: " << socio.nombre
            << ", Domicilio: " << socio.domicilio
            << ", Año de Ingreso: " << socio.anioIngreso;  // Mostrar año de ingreso
        return out;
    }

    // Sobrecarga del operador == para comparar por numeroSocio
    bool operator==(const SocioClub& otro) const {
        return this->numeroSocio == otro.numeroSocio;
    }

    // Obtener el número de socio
    int getNumeroSocio() const {
        return numeroSocio;
    }

    // Obtener el nombre del socio
    std::string getNombre() const {
        return nombre;
    }

    // Obtener el domicilio del socio
    std::string getDomicilio() const {
        return domicilio;
    }

    // Obtener el año de ingreso
    int getAnioIngreso() const {
        return anioIngreso;
    }
};

// Nodo de la lista simplemente ligada
template<class T>
struct Node {
    T data;
    Node<T>* sig;
    Node(T elem) : data(elem), sig(nullptr) {}
};

// Clase de la Lista Simplemente Ligada
template<class T>
class LSLSE {
private:
    Node<T>* lista;

public:
    LSLSE() : lista(nullptr) {}

    // Verifica si la lista está vacía
    bool vacia() const {
        return lista == nullptr;
    }

    // Inserta un elemento en la posición dada (antes de "pos")
    void insertar(Node<T>* pos, T elem) {
        Node<T>* nuevo = new Node<T>(elem);
        if (pos == nullptr) {
            nuevo->sig = lista;
            lista = nuevo;
        } else {
            nuevo->sig = pos->sig;
            pos->sig = nuevo;
        }
    }

    // Elimina un nodo y ajusta los enlaces
    bool eliminar(Node<T>* pos) {
        if (vacia() || pos == nullptr) return false;
        if (pos == lista) {
            lista = lista->sig;
        } else {
            Node<T>* anterior = lista;
            while (anterior->sig != pos) anterior = anterior->sig;
            anterior->sig = pos->sig;
        }
        delete pos;
        return true;
    }

    // Imprime los elementos de la lista
    void imprimir() const {
        Node<T>* aux = lista;
        while (aux != nullptr) {
            std::cout << aux->data << " -> ";
            aux = aux->sig;
        }
        std::cout << "null\n";
    }

    // Devuelve el primer nodo de la lista
    Node<T>* primero() const {
        return lista;
    }
};

// Programa principal con el menú

int main() {
    // Configurar locale para soportar la letra ñ y otros caracteres especiales
    std::setlocale(LC_ALL, "");

    LSLSE<SocioClub> listaSocios;
    int opcion;

    do {
        std::cout << "\nMenu de Opciones:\n";
        std::cout << "1. Registrar un nuevo socio\n";
        std::cout << "2. Dar de baja un socio\n";
        std::cout << "3. Generar reporte de socios\n";
        std::cout << "4. Buscar socio por nombre y domicilio\n";
        std::cout << "5. Calcular total de socios\n";
        std::cout << "6. Salir\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                // Registrar un nuevo socio
                int numero, anioIngreso;
                std::string nombre, domicilio;
                std::cout << "Ingrese el numero de socio: ";
                std::cin >> numero;
                std::cin.ignore(); // Limpiar el buffer
                std::cout << "Ingrese el nombre del socio: ";
                std::getline(std::cin, nombre);
                std::cout << "Ingrese el domicilio del socio: ";
                std::getline(std::cin, domicilio);
                std::cout << "Ingrese el año de ingreso: ";
                std::cin >> anioIngreso;

                SocioClub nuevoSocio(numero, nombre, domicilio, anioIngreso);

                // Insertar en la lista ordenada por número de socio
                Node<SocioClub>* actual = listaSocios.primero();
                Node<SocioClub>* anterior = nullptr;

                // Buscar la posición adecuada para insertar
                while (actual != nullptr && actual->data.getNumeroSocio() < nuevoSocio.getNumeroSocio()) {
                    anterior = actual;
                    actual = actual->sig;
                }

                // Evitar duplicados
                if (actual != nullptr && actual->data == nuevoSocio) {
                    std::cout << "Error: Ya existe un socio con ese numero.\n";
                } else {
                    listaSocios.insertar(anterior, nuevoSocio);
                    std::cout << "Socio registrado exitosamente.\n";
                }
                break;
            }
            case 2: {
                // Dar de baja un socio
                int numero;
                std::cout << "Ingrese el numero de socio a eliminar: ";
                std::cin >> numero;

                Node<SocioClub>* actual = listaSocios.primero();
                while (actual != nullptr && actual->data.getNumeroSocio() != numero) {
                    actual = actual->sig;
                }

                if (actual == nullptr) {
                    std::cout << "Error: No se encontro ningun socio con ese numero.\n";
                } else {
                    listaSocios.eliminar(actual);
                    std::cout << "Socio eliminado exitosamente.\n";
                }
                break;
            }
            case 3: {
                // Generar reporte de todos los socios
                std::cout << "Lista de socios:\n";
                listaSocios.imprimir();
                break;
            }
            case 4: {
                // Buscar socio por nombre y domicilio
                std::string nombre, domicilio;
                std::cin.ignore(); // Limpiar el buffer
                std::cout << "Ingrese el nombre del socio: ";
                std::getline(std::cin, nombre);
                std::cout << "Ingrese el domicilio del socio: ";
                std::getline(std::cin, domicilio);

                Node<SocioClub>* actual = listaSocios.primero();
                bool encontrado = false;

                while (actual != nullptr) {
                    if (actual->data.getNombre() == nombre && actual->data.getDomicilio() == domicilio) {
                        std::cout << "Socio encontrado: " << actual->data << "\n";
                        encontrado = true;
                        break;
                    }
                    actual = actual->sig;
                }

                if (!encontrado) {
                    std::cout << "No se encontro ningun socio con esos datos.\n";
                }
                break;
            }
            case 5: {
                // Calcular total de socios registrados
                Node<SocioClub>* actual = listaSocios.primero();
                int totalSocios = 0;
                while (actual != nullptr) {
                    totalSocios++;
                    actual = actual->sig;
                }
                std::cout << "Total de socios registrados: " << totalSocios << "\n";
                break;
            }
            case 6:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion invalida, intente nuevamente.\n";
        }
    } while (opcion != 6);

    return 0;
}
