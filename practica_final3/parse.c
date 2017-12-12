#include "ArrayList.h"
#include "parse.h"

void parse_clientes(ArrayList* lista)
{
    FILE* archivo = abrir_archivo("clientes.txt");
    eCliente* aux;
    char auxId[100];
    char auxNombre[100];
    char auxApellido[100];
    char auxDni[100];
    while (!feof(archivo))
    {
        fscanf(archivo, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxApellido, auxDni);
        aux = constructor_clientes();
        if (aux != NULL)
        {
            strcpy(aux->nombre, auxNombre);
            strcpy(aux->apellido, auxApellido);
            aux->id = atoi(auxId);
            aux->dni = atoi(auxDni);
        }
        lista->add(lista, aux);
    }
    fclose(archivo);
}


void parsear_ventas(ArrayList* lista)
{
    FILE* archivo = abrir_archivo("ventas.txt");
    eVentas* aux;
    char auxIdVenta[100];
    char auxIdCliente[100];
    char auxCodProducto[100];
    char auxCantidad[100];
    char auxPrecio[100];
    while(!feof(archivo))
    {
        fscanf(archivo, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",auxIdVenta, auxIdCliente, auxCodProducto, auxCantidad, auxPrecio);
        aux = constructor_ventas();
        if (aux != NULL)
        {
            aux->id_venta = atoi(auxIdVenta);
            aux->id_cliente = atoi(auxIdCliente);
            aux->cantidad = atoi(auxCantidad);
            aux->precioUnitario = atoi(auxPrecio);
            aux->codProducto = atoi(auxCodProducto);
        }
        lista->add(lista, aux);
    }
    fclose(archivo);
}



eCliente* constructor_clientes()
{
    eCliente* aux;
    aux = (eCliente*) malloc(sizeof(eCliente));
    if (aux !=NULL)
    {
        strcpy(aux->apellido,"");
        strcpy(aux->nombre, "");
        aux->id = 0;
        aux->dni = 0;
    }
    return aux;
}



eVentas* constructor_ventas()
{
    eVentas* aux;
    aux = (eVentas*) malloc(sizeof(eVentas));
    if (aux != NULL)
    {
        aux->cantidad = 0;
        aux->codProducto = 0;
        aux->id_cliente = 0;
        aux->id_venta = 0;
        aux->precioUnitario = 0;
    }
    return aux;
}


FILE* abrir_archivo(char* path)
{
    FILE* archivo;
    if ((archivo = fopen(path, "r+")) == NULL)
        if((archivo = fopen(path, "w+")) == NULL)
        {
            printf("\nNo se pudo abrir el archivo\n");
        }
    return archivo;
}


void imprimir_clientes(ArrayList* lista)
{
    eCliente* aux;
    int i;
    for (i = 0; i < lista->len(lista); i++)
    {
        aux = lista->get(lista, i);
        printf("%d     %s     %s       %li\n", aux->id, aux->nombre, aux->apellido, aux->dni);
    }
}


void imprimir_ventas(ArrayList* lista)
{
    eVentas* aux;
    int i;
    for (i = 0; i < lista->len(lista); i++)
    {
        aux = lista->get(lista, i);
        printf("%d    %d    %d     %d     %d\n", aux->id_venta, aux->id_cliente, aux->codProducto,aux->cantidad, aux->precioUnitario);
    }
}



void sacarEnter(char vec[]) // borra el enter que queda en la ultima posicion del string cuando se usa fgets().
{
    int cant;
    cant = strlen(vec);
    vec[cant-1] = '\0';
}

void devuelve_nombre(char nom[])
{
    printf("Ingrese el nombre del cliente: ");
    setbuf(stdin, NULL);
    fgets(nom, 101, stdin);
    sacarEnter(nom);
}

void devuelve_apellido(char ape[])
{
    printf("\nIngrese apellido del cliente: ");
    setbuf(stdin, NULL);
    fgets(ape, 101, stdin);
    sacarEnter(ape);
}

long int devuelve_dni()
{
    long int dni;
    printf("\nIngrese el DNI del cliente: ");
    scanf("%li", &dni);
    return dni;
}

void crea_txt_cliente(ArrayList* lista, FILE* archivo)
{
    int i;
    eCliente* aux;
    for (i = 0; i < lista->len(lista); i++)
    {
        aux = (eCliente*)lista->get(lista, i);
        fprintf(archivo, "%d,%s,%s,%li\n", aux->id, aux->nombre, aux->apellido, aux->dni);
    }
    fclose(archivo);
}

void modifica_clientes(ArrayList* lista, int id, long int dni, char nombre[], char apellido[])
{
    int i;
    eCliente* aux;
    for (i = 0; i < lista->len(lista); i++)
    {
        aux = (eCliente*) lista->get(lista, i);
        if (aux->id == id)
        {
            strcpy(aux->apellido, apellido);
            strcpy(aux->nombre, nombre);
            aux->dni = dni;
            lista->set(lista, i, aux);
            break;
        }
    }
}


int buscar_id_ventas(ArrayList* lista, int id)
{
    int i;
    int flag = 1;
    eVentas* auxV;
    for (i = 0; i < lista->len(lista); i++)
    {
        auxV = (eVentas*)lista->get(lista, i);
        if (auxV->id_cliente == id)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

int buscar_id_cliente(ArrayList* lista, int id)
{
    int i, flag = 0;
    eCliente* aux;
    for (i = 0; i < lista->len(lista); i++)
    {
        aux = (eCliente*) lista->get(lista, i);
        if (aux->id == id)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

int buscar_indice_clientes(ArrayList* lista, int id)
{
    eCliente* aux;
    int i;
    for (i = 0; i < lista->len(lista); i++)
    {
        aux = lista->get(lista, i);
        if (aux->id == id)
            return i;
    }
}
