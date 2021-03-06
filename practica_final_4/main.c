#include "funciones.h"
#include "ArrayList.h"
int main()
{
    ArrayList* clientes = al_newArrayList();
    ArrayList* ventas = al_newArrayList();
    ArrayList* clientes_bin = al_newArrayList();
    char resp = 's';
    int opcion;
    char nombre[100], apellido[100];
    int dni, dni_viejo;
    FILE* copia;
    int validar;
    parsear_cliente(clientes);
    parsear_cliente_binario(clientes_bin);
    while (resp == 's')
    {
        system("cls");
        printf("1) Agregar nuevo cliente\n");
        printf("2) Modificar cliente\n");
        printf("3) Baja de cliente\n");
        printf("4) Listar clientes\n");
        printf("5) Procesar venta\n");
        printf("6) Anular venta\n");
        printf("7) Informar ventas\n");
        printf("8) Informar ventas por producto\n");
        printf("9) Generar informe de ventas\n");
        printf("10) Informar cantidad ventas por cliente\n");
        printf("11) Salir\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            devuelve_nombre(nombre);
            devuelve_apellido(apellido);
            dni = devuelve_dni();
            agregar_cliente_binario(clientes_bin, nombre, apellido, dni);
            break;
        case 2:
            system("cls");
            dni_viejo = devuelve_dni();
            devuelve_nombre(nombre);
            devuelve_apellido(apellido);
            dni = devuelve_dni();
            validar = modifica_clientes(clientes_bin, dni, dni_viejo, nombre, apellido);
            if (validar)
            {
                copia = abrir_archivo_binario("clientes2.bin");
                //crea_txt_cliente(clientes, copia);
                crea_copia_binario(clientes_bin, copia);
                remove("clientes.bin");
                rename("clientes2.bin", "clientes.bin");
                printf("\n Todo OK\n");
                system("pause");
            }
            break;
        case 3:
            system("cls");
            dni = devuelve_dni();
            validar = baja_cliente(clientes_bin, dni);
            if (validar)
            {
                copia = abrir_archivo_texto("clientes2.bin");
                crea_copia_binario(clientes_bin, copia);
                remove("clientes.bin");
                rename("clientes2.bin", "clientes.bin");
                printf("\n Todo OK\n");
                system("pause");
            }
            break;
        case 4:
            imprimir_clientes(clientes_bin);
            break;
        case 5:
            break;
        }
    }
    return 0;
}
