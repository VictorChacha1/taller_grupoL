#include <iostream>
#include <string>
using namespace std;

// ==================== CLASE REPUESTO ====================
class Repuesto {
private:
    string codigo;
    string nombre;
    double precioUnitario;
    int cantidad;

public:
    // Constructor
    Repuesto() {
        codigo = "";
        nombre = "";
        precioUnitario = 0.0;
        cantidad = 0;
    }

    // Setters
    void setCodigo(string c)        { codigo = c; }
    void setNombre(string n)        { nombre = n; }
    void setPrecio(double p)        { precioUnitario = p; }
    void setCantidad(int c)         { cantidad = c; }

    // Getters
    string getCodigo()              { return codigo; }
    string getNombre()              { return nombre; }
    double getPrecio()              { return precioUnitario; }
    int getCantidad()               { return cantidad; }
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
    double descuento;
    double impuesto;

    // Repuestos usados en esta orden
    string repuestosUsados[5];
    int cantidadRepuestos[5];
    int numRepuestos;

public:
    // Constructor
    OrdenTaller() {
        placa = "";
        cliente = "";
        cedula = "";
        tipoServicio = "";
        horasManoObra = 0.0;
        costoPorHora = 0.0;
        estado = "pendiente";
        descuento = 0.0;
        impuesto = 0.0;
        numRepuestos = 0;
    }

    // Setters
    void setPlaca(string p)         { placa = p; }
    void setCliente(string c)       { cliente = c; }
    void setCedula(string c)        { cedula = c; }
    void setTipoServicio(string t)  { tipoServicio = t; }
    void setHoras(double h)         { horasManoObra = h; }
    void setCostoPorHora(double c)  { costoPorHora = c; }
    void setEstado(string e)        { estado = e; }

    // Getters
    string getPlaca()               { return placa; }
    string getCliente()             { return cliente; }
    string getCedula()              { return cedula; }
    string getTipoServicio()        { return tipoServicio; }
    double getHoras()               { return horasManoObra; }
    double getCostoPorHora()        { return costoPorHora; }
    string getEstado()              { return estado; }
    int getNumRepuestos()           { return numRepuestos; }
    double getDescuento()           { return descuento; }
    double getImpuesto()            { return impuesto; }

    // Agregar repuesto a la orden
    void agregarRepuesto(string nombre, int cant) {
        if (numRepuestos < 5) {
            repuestosUsados[numRepuestos] = nombre;
            cantidadRepuestos[numRepuestos] = cant;
            numRepuestos++;
        }
    }

    string getRepuestoNombre(int i) { return repuestosUsados[i]; }
    int getRepuestoCantidad(int i)  { return cantidadRepuestos[i]; }
};

// ==================== MENU AHORCADO ====================
void menuAhorcado() {
    cout << "\n===== MODULO AHORCADO - TALLER =====" << endl;
    cout << "  (modulo en construccion)" << endl;
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
        cout << "  6. Modulo Ahorcado" << endl;
        cout << "  0. Salir" << endl;
        cout << "----------------------------------------" << endl;
        cout << "  Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: cout << "\n[Registrar repuesto - en construccion]" << endl; break;
            case 2: cout << "\n[Registrar orden - en construccion]" << endl; break;
            case 3: cout << "\n[Buscar orden - en construccion]" << endl; break;
            case 4: cout << "\n[Ordenar ordenes - en construccion]" << endl; break;
            case 5: cout << "\n[Historial - en construccion]" << endl; break;
            case 6: menuAhorcado(); break;
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