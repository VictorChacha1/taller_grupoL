# Sistema de Gestión - Taller Mecánico
## Grupo L - Algoritmos de Programación / C++
### Universidad Técnica de Ambato

## Integrantes
- [Tu nombre completo]
- [Nombre compañero 2]
- [Nombre compañero 3]

## Caso asignado
Sistema de control de órdenes de trabajo, repuestos, horas de mano de 
obra, estados y costos finales para un taller mecánico.

## Metodología seguida
1. **Análisis:** identificación de clases, atributos, reglas de negocio y casos límite
2. **Diseño:** definición de clases OrdenTaller y Repuesto con encapsulamiento
3. **Construcción incremental:** estructura base, registros, reportes, recursividad y Ahorcado
4. **Pruebas:** casos normales, casos límite y corrección del fragmento defectuoso
5. **Versionamiento:** commits parciales con GitHub Desktop

## Partes implementadas
- Clase Repuesto con encapsulamiento completo
- Clase OrdenTaller con encapsulamiento completo
- Registro y validación de repuestos y órdenes
- Búsqueda por placa y por cédula
- Ordenamiento manual por mayor costo (burbuja)
- Historial de órdenes y detección de baja rentabilidad
- Función recursiva para sumar total facturado
- Corrección del fragmento defectuoso totalOrden()
- Módulo Ahorcado con vocabulario de taller mecánico

## Fragmento defectuoso corregido
Función totalOrden() tenía 3 errores:
1. Falta punto y coma en la línea del impuesto
2. Retornaba manoObra en lugar de total
3. No validaba que el descuento no supere el subtotal

## Herramientas utilizadas
- C++ con compilador g++ (MSYS2)
- Visual Studio Code
- GitHub Desktop
- GitHub