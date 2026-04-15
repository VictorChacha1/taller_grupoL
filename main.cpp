#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

// ==================== CLASE REPUESTO ====================
class Repuesto {
private:
    string codigo;
    string nombre;
    double precioUnitario;
    int cantidad;

public:
    Repuesto() {
        codigo = "";
        nombre = "";
        precioUnitario = 0.0;
        cantidad = 0;
    }

    void setCodigo(string c)    { codigo = c; }
    void setNombre(string n)    { nombre = n; }
    void setPrecio(double p)    { precioUnitario = p; }
    void setCantidad(int c)     { cantidad = c; }

    string getCodigo()          { return codigo; }
    string getNombre()          { return nombre; }
    double getPrecio()          { return precioUnitario; }
    int getCantidad()           { return cantidad; }
};

// ==================== CLASE ORDENTALLER ====================
class OrdenTaller {
private:
    string placa;
    string cliente;
    string cedula;
    string tipoServicio;
    double horasManoObra;
    double costoPorHora;
    string estado;

    string repuestosUsados[5];
    int cantidadRepuestos[5];
    int numRepuestos;

public:
    OrdenTaller() {
        placa = "";
        cliente = "";
        cedula = "";
        tipoServicio = "";
        horasManoObra = 0.0;
        costoPorHora = 0.0;
        estado = "pendiente";
        numRepuestos = 0;
    }

    void setPlaca(string p)         { placa = p; }
    void setCliente(string c)       { cliente = c; }
    void setCedula(string c)        { cedula = c; }
    void setTipoServicio(string t)  { tipoServicio = t; }
    void setHoras(double h)         { horasManoObra = h; }
    void setCostoPorHora(double c)  { costoPorHora = c; }
    void setEstado(string e)        { estado = e; }

    string getPlaca()               { return placa; }
    string getCliente()             { return cliente; }
    string getCedula()              { return cedula; }
    string getTipoServicio()        { return tipoServicio; }
    double getHoras()               { return horasManoObra; }
    double getCostoPorHora()        { return costoPorHora; }
    string getEstado()              { return estado; }
    int getNumRepuestos()           { return numRepuestos; }
    string getRepuestoNombre(int i) { return repuestosUsados[i]; }
    int getRepuestoCantidad(int i)  { return cantidadRepuestos[i]; }

    void agregarRepuesto(string nombre, int cant) {
        if (numRepuestos < 5) {
            repuestosUsados[numRepuestos] = nombre;
            cantidadRepuestos[numRepuestos] = cant;
            numRepuestos++;
        }
    }

    // Calcula el costo de mano de obra
    double getCostoManoObra() {
        return horasManoObra * costoPorHora;
    }

    // Calcula costo de repuestos buscando precio en el arreglo global
    double getCostoRepuestos(Repuesto repuestos[], int numRep) {
        double total = 0;
        for (int i = 0; i < numRepuestos; i++) {
            for (int j = 0; j < numRep; j++) {
                if (repuestosUsados[i] == repuestos[j].getNombre()) {
                    total += repuestos[j].getPrecio() * cantidadRepuestos[i];
                }
            }
        }
        return total;
    }

    // Calcula el valor final con descuento e impuesto
    double getValorFinal(Repuesto repuestos[], int numRep) {
        double subtotal = getCostoManoObra() + getCostoRepuestos(repuestos, numRep);
        double descuento = 0;
        if (tipoServicio == "preventivo") descuento = subtotal * 0.10;
        else if (tipoServicio == "express") descuento = subtotal * 0.05;
        double impuesto = (subtotal - descuento) * 0.15;
        return subtotal - descuento + impuesto;
    }

    // Clasifica la reparacion segun valor final
    string getClasificacion(Repuesto repuestos[], int numRep) {
        double valor = getValorFinal(repuestos, numRep);
        if (valor < 100) return "Menor";
        else if (valor <= 500) return "Moderada";
        else return "Mayor";
    }
};

// ==================== ARREGLOS GLOBALES ====================
const int MAX = 50;
Repuesto repuestos[MAX];
OrdenTaller ordenes[MAX];
int numRepuestos = 0;
int numOrdenes = 0;

// ==================== REGISTRAR REPUESTO ====================
void registrarRepuesto() {
    if (numRepuestos >= MAX) {
        cout << "\nNo hay espacio para mas repuestos." << endl;
        return;
    }

    string codigo, nombre;
    double precio;
    int cantidad;

    cout << "\n===== REGISTRAR REPUESTO =====" << endl;

    cout << "Codigo: ";
    cin >> codigo;

    // Validar que no exista ya ese codigo
    for (int i = 0; i < numRepuestos; i++) {
        if (repuestos[i].getCodigo() == codigo) {
            cout << "Ya existe un repuesto con ese codigo." << endl;
            return;
        }
    }

    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nombre);

    do {
        cout << "Precio unitario: ";
        cin >> precio;
        if (precio <= 0) cout << "El precio debe ser mayor a 0." << endl;
    } while (precio <= 0);

    do {
        cout << "Cantidad en stock: ";
        cin >> cantidad;
        if (cantidad < 0) cout << "La cantidad no puede ser negativa." << endl;
    } while (cantidad < 0);

    repuestos[numRepuestos].setCodigo(codigo);
    repuestos[numRepuestos].setNombre(nombre);
    repuestos[numRepuestos].setPrecio(precio);
    repuestos[numRepuestos].setCantidad(cantidad);
    numRepuestos++;

    cout << "Repuesto registrado correctamente." << endl;
}

// ==================== REGISTRAR ORDEN ====================
void registrarOrden() {
    if (numOrdenes >= MAX) {
        cout << "\nNo hay espacio para mas ordenes." << endl;
        return;
    }

    string placa, cliente, cedula, tipoServicio;
    double horas, costoPorHora;

    cout << "\n===== REGISTRAR ORDEN DE TRABAJO =====" << endl;

    cout << "Placa del vehiculo: ";
    cin >> placa;

    cout << "Nombre del cliente: ";
    cin.ignore();
    getline(cin, cliente);

    cout << "Cedula del cliente: ";
    cin >> cedula;

    cout << "Tipo de servicio (preventivo/correctivo/express): ";
    cin >> tipoServicio;
    while (tipoServicio != "preventivo" && tipoServicio != "correctivo" && tipoServicio != "express") {
        cout << "Tipo invalido. Ingrese preventivo, correctivo o express: ";
        cin >> tipoServicio;
    }

    do {
        cout << "Horas de mano de obra: ";
        cin >> horas;
        if (horas <= 0) cout << "Las horas deben ser mayor a 0." << endl;
    } while (horas <= 0);

    do {
        cout << "Costo por hora: ";
        cin >> costoPorHora;
        if (costoPorHora <= 0) cout << "El costo debe ser mayor a 0." << endl;
    } while (costoPorHora <= 0);

    ordenes[numOrdenes].setPlaca(placa);
    ordenes[numOrdenes].setCliente(cliente);
    ordenes[numOrdenes].setCedula(cedula);
    ordenes[numOrdenes].setTipoServicio(tipoServicio);
    ordenes[numOrdenes].setHoras(horas);
    ordenes[numOrdenes].setCostoPorHora(costoPorHora);

    // Agregar repuestos a la orden
    char agregar;
    cout << "Desea agregar repuestos a la orden? (s/n): ";
    cin >> agregar;

    while (agregar == 's' && ordenes[numOrdenes].getNumRepuestos() < 5) {
        if (numRepuestos == 0) {
            cout << "No hay repuestos registrados aun." << endl;
            break;
        }
        cout << "\nRepuestos disponibles:" << endl;
        for (int i = 0; i < numRepuestos; i++) {
            cout << "  " << i+1 << ". " << repuestos[i].getNombre()
                 << " - $" << repuestos[i].getPrecio() << endl;
        }
        string nombreRep;
        int cantRep;
        cout << "Nombre del repuesto: ";
        cin.ignore();
        getline(cin, nombreRep);
        do {
            cout << "Cantidad: ";
            cin >> cantRep;
            if (cantRep <= 0) cout << "La cantidad debe ser mayor a 0." << endl;
        } while (cantRep <= 0);

        ordenes[numOrdenes].agregarRepuesto(nombreRep, cantRep);
        cout << "Agregar otro repuesto? (s/n): ";
        cin >> agregar;
    }

    numOrdenes++;
    cout << "\nOrden registrada correctamente." << endl;
}

// ==================== MOSTRAR ORDEN ====================
void mostrarOrden(int i) {
    cout << "\n--- Orden #" << i+1 << " ---" << endl;
    cout << "Placa:          " << ordenes[i].getPlaca() << endl;
    cout << "Cliente:        " << ordenes[i].getCliente() << endl;
    cout << "Cedula:         " << ordenes[i].getCedula() << endl;
    cout << "Tipo servicio:  " << ordenes[i].getTipoServicio() << endl;
    cout << "Horas:          " << ordenes[i].getHoras() << endl;
    cout << "Costo/hora:     $" << ordenes[i].getCostoPorHora() << endl;
    cout << "Estado:         " << ordenes[i].getEstado() << endl;
    cout << "Repuestos usados:" << endl;
    for (int j = 0; j < ordenes[i].getNumRepuestos(); j++) {
        cout << "  - " << ordenes[i].getRepuestoNombre(j)
             << " x" << ordenes[i].getRepuestoCantidad(j) << endl;
    }
    cout << "Costo mano obra: $" << ordenes[i].getCostoManoObra() << endl;
    cout << "Costo repuestos: $" << ordenes[i].getCostoRepuestos(repuestos, numRepuestos) << endl;
    cout << "Valor final:     $" << ordenes[i].getValorFinal(repuestos, numRepuestos) << endl;
    cout << "Clasificacion:   " << ordenes[i].getClasificacion(repuestos, numRepuestos) << endl;
}
// ==================== BUSCAR ORDEN ====================
void buscarOrden() {
    int opcion;
    cout << "\n===== BUSCAR ORDEN =====" << endl;
    cout << "1. Buscar por placa" << endl;
    cout << "2. Buscar por cedula" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    string busqueda;
    bool encontrado = false;

    if (opcion == 1) {
        cout << "Ingrese la placa: ";
        cin >> busqueda;
        for (int i = 0; i < numOrdenes; i++) {
            if (ordenes[i].getPlaca() == busqueda) {
                mostrarOrden(i);
                encontrado = true;
            }
        }
    } else if (opcion == 2) {
        cout << "Ingrese la cedula: ";
        cin >> busqueda;
        for (int i = 0; i < numOrdenes; i++) {
            if (ordenes[i].getCedula() == busqueda) {
                mostrarOrden(i);
                encontrado = true;
            }
        }
    } else {
        cout << "Opcion invalida." << endl;
        return;
    }

    if (!encontrado) {
        cout << "No se encontraron ordenes." << endl;
    }
}

// ==================== ORDENAR ORDENES ====================
void ordenarOrdenes() {
    if (numOrdenes < 2) {
        cout << "\nNo hay suficientes ordenes para ordenar." << endl;
        return;
    }

    // Ordenamiento burbuja por mayor valor final
    for (int i = 0; i < numOrdenes - 1; i++) {
        for (int j = 0; j < numOrdenes - 1 - i; j++) {
            double valorA = ordenes[j].getValorFinal(repuestos, numRepuestos);
            double valorB = ordenes[j+1].getValorFinal(repuestos, numRepuestos);
            if (valorA < valorB) {
                OrdenTaller temp = ordenes[j];
                ordenes[j] = ordenes[j+1];
                ordenes[j+1] = temp;
            }
        }
    }

    cout << "\nOrdenes ordenadas por mayor costo:" << endl;
    for (int i = 0; i < numOrdenes; i++) {
        cout << i+1 << ". " << ordenes[i].getPlaca()
             << " - " << ordenes[i].getCliente()
             << " - $" << ordenes[i].getValorFinal(repuestos, numRepuestos)
             << " - " << ordenes[i].getClasificacion(repuestos, numRepuestos)
             << endl;
    }
}

// ==================== VER HISTORIAL ====================
void verHistorial() {
    if (numOrdenes == 0) {
        cout << "\nNo hay ordenes registradas." << endl;
        return;
    }

    cout << "\n===== HISTORIAL DE ORDENES =====" << endl;
    for (int i = 0; i < numOrdenes; i++) {
        mostrarOrden(i);
    }

    // Ordenes con baja rentabilidad (valor final menor a 100)
    cout << "\n--- Ordenes con baja rentabilidad ---" << endl;
    bool hayBaja = false;
    for (int i = 0; i < numOrdenes; i++) {
        if (ordenes[i].getValorFinal(repuestos, numRepuestos) < 100) {
            cout << "  Placa: " << ordenes[i].getPlaca()
                 << " - Cliente: " << ordenes[i].getCliente()
                 << " - Valor: $" << ordenes[i].getValorFinal(repuestos, numRepuestos)
                 << endl;
            hayBaja = true;
        }
    }
    if (!hayBaja) cout << "  Ninguna orden con baja rentabilidad." << endl;
}

// ==================== FRAGMENTO CORREGIDO ====================
// Errores corregidos:
// 1. Falta punto y coma en linea del impuesto
// 2. Retornaba manoObra en lugar de total
// 3. No validaba que descuento no supere el subtotal
double totalOrden(double manoObra, double repuestos, double descuento) {
    double subtotal = manoObra + repuestos;
    if (descuento > subtotal) descuento = subtotal;
    double total = subtotal - descuento;
    total = total + total * 0.15;
    if (total < 0) total = 0;
    return total;
}

// ==================== FUNCION RECURSIVA ====================
// Suma el valor total de todas las ordenes de forma recursiva
double sumarTotalOrdenes(int indice) {
    if (indice >= numOrdenes) return 0;
    return ordenes[indice].getValorFinal(repuestos, numRepuestos) 
           + sumarTotalOrdenes(indice + 1);
}

// ==================== MENU AHORCADO ====================
// ==================== MODULO AHORCADO ====================
string palabrasFacil[] = {"ORDEN", "PLACA", "MOTOR", "FRENO", "LLANTA"};
string palabrasDificil[] = {"CARBURADOR", "TRANSMISION", "AMORTIGUADOR", "DIFERENCIAL", "ALTERNADOR"};

// Historial de partidas
string historialGanador[20];
string historialPalabra[20];
int historialPartidas = 0;

void mostrarAhorcado(int errores) {
    cout << "\n";
    switch(errores) {
        case 0: cout << "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n"; break;
        case 1: cout << "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n"; break;
        case 2: cout << "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n"; break;
        case 3: cout << "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n"; break;
        case 4: cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n"; break;
        case 5: cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n"; break;
        case 6: cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"; break;
    }
}

void jugarAhorcado() {
    int nivel;
    cout << "\nSeleccione nivel:" << endl;
    cout << "1. Facil" << endl;
    cout << "2. Dificil" << endl;
    cout << "Opcion: ";
    cin >> nivel;
    while (nivel != 1 && nivel != 2) {
        cout << "Opcion invalida. Ingrese 1 o 2: ";
        cin >> nivel;
    }

    // Seleccionar palabra aleatoria
    srand(time(0));
    string palabra;
    if (nivel == 1)
        palabra = palabrasFacil[rand() % 5];
    else
        palabra = palabrasDificil[rand() % 5];

    string letrasUsadas = "";
    int errores = 0;
    int maxErrores = 6;
    bool gano = false;

    cout << "\nPalabra del vocabulario de taller mecanico." << endl;
    cout << "Tienes " << maxErrores << " intentos." << endl;

    while (errores < maxErrores) {
        mostrarAhorcado(errores);

        // Mostrar palabra oculta
        cout << "Palabra: ";
        bool completa = true;
        for (int i = 0; i < palabra.length(); i++) {
            bool revelada = false;
            for (int j = 0; j < letrasUsadas.length(); j++) {
                if (letrasUsadas[j] == palabra[i]) {
                    revelada = true;
                    break;
                }
            }
            if (revelada) cout << palabra[i] << " ";
            else { cout << "_ "; completa = false; }
        }
        cout << endl;

        if (completa) { gano = true; break; }

        cout << "Letras usadas: " << letrasUsadas << endl;
        cout << "Intentos restantes: " << (maxErrores - errores) << endl;

        // Pedir letra
        char letra;
        cout << "Ingrese una letra: ";
        cin >> letra;
        letra = toupper(letra);

        // Validar que sea letra
        if (!isalpha(letra)) {
            cout << "Solo se permiten letras." << endl;
            continue;
        }

        // Validar que no se repita
        bool repetida = false;
        for (int i = 0; i < letrasUsadas.length(); i++) {
            if (letrasUsadas[i] == letra) { repetida = true; break; }
        }
        if (repetida) {
            cout << "Esa letra ya fue usada." << endl;
            continue;
        }

        letrasUsadas += letra;

        // Verificar si esta en la palabra
        bool acierto = false;
        for (int i = 0; i < palabra.length(); i++) {
            if (palabra[i] == letra) { acierto = true; break; }
        }
        if (!acierto) {
            errores++;
            cout << "Letra incorrecta." << endl;
        } else {
            cout << "Letra correcta." << endl;
        }
    }

    mostrarAhorcado(errores);

    string ganador;
    if (gano) {
        cout << "\nFelicidades! Adivinaste la palabra: " << palabra << endl;
        ganador = "Jugador";
    } else {
        cout << "\nPerdiste. La palabra era: " << palabra << endl;
        ganador = "CPU";
    }

    // Guardar en historial
    if (historialPartidas < 20) {
        historialGanador[historialPartidas] = ganador;
        historialPalabra[historialPartidas] = palabra;
        historialPartidas++;
    }
}

void verHistorialAhorcado() {
    if (historialPartidas == 0) {
        cout << "\nNo hay partidas jugadas aun." << endl;
        return;
    }
    cout << "\n===== HISTORIAL DE PARTIDAS =====" << endl;
    int jugadorGana = 0, cpuGana = 0;
    for (int i = 0; i < historialPartidas; i++) {
        cout << i+1 << ". Palabra: " << historialPalabra[i]
             << " - Resultado: " << historialGanador[i] << endl;
        if (historialGanador[i] == "Jugador") jugadorGana++;
        else cpuGana++;
    }
    cout << "\nJugador: " << jugadorGana << " victorias" << endl;
    cout << "CPU: " << cpuGana << " victorias" << endl;
}

void menuAhorcado() {
    int opcion;
    do {
        cout << "\n===== AHORCADO - TALLER MECANICO =====" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ver historial de partidas" << endl;
        cout << "3. Ver instrucciones" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: jugarAhorcado(); break;
            case 2: verHistorialAhorcado(); break;
            case 3:
                cout << "\n--- INSTRUCCIONES ---" << endl;
                cout << "Adivina la palabra del vocabulario de taller mecanico." << endl;
                cout << "Tienes 6 intentos antes de que el ahorcado este completo." << endl;
                cout << "Ingresa una letra por turno." << endl;
                cout << "Nivel facil: palabras cortas del taller." << endl;
                cout << "Nivel dificil: palabras tecnicas del taller." << endl;
                break;
            case 0: break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}

// ==================== MENU PRINCIPAL ====================
void menuPrincipal() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "   SISTEMA DE GESTION - TALLER MECANICO" << endl;
        cout << "========================================" << endl;
        cout << "  1. Registrar repuesto" << endl;
        cout << "  2. Registrar orden de trabajo" << endl;
        cout << "  3. Buscar orden" << endl;
        cout << "  4. Ordenar ordenes" << endl;
        cout << "  5. Ver historial" << endl;
        cout << "  6. Total facturado (recursivo)" << endl;
        cout << "  7. Modulo Ahorcado" << endl;
        cout << "  0. Salir" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarRepuesto(); break;
            case 2: registrarOrden(); break;
            case 3: buscarOrden(); break;
            case 4: ordenarOrdenes(); break;
            case 5: verHistorial(); break;
            case 6: 
                cout << "\nTotal facturado en todas las ordenes: $" 
                     << sumarTotalOrdenes(0) << endl; 
                    break;
            case 7: menuAhorcado(); break;
            case 0: cout << "\nCerrando sistema..." << endl; break;
            default: cout << "\nOpcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}

// ==================== MAIN ====================
int main() {
    menuPrincipal();
    return 0;
}