#include "parse.h"
#include "ArrayList.h"


int parse_Log(ArrayList* lista)
{
    if (lista == NULL)
        return 1;
    FILE* archivo;
    char auxDate[110];
    char auxTime[60];
    char AuxServiceId[100];
    char AuxGravedad[100];
    char AuxMsg[650];
    archivo = fopen("log.txt", "r");// falta validar que no sea NULL
    S_LogEntry* nuevoLog;
    while(!feof(archivo))
    {
        //Funciona bien, la ultima mascara lee todo hasta el salto de pagina
        fscanf(archivo, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n", auxDate, auxTime, AuxServiceId, AuxGravedad, AuxMsg);
        nuevoLog = log_constructor();
        if (nuevoLog != NULL)
        {
            strcpy(nuevoLog->date, auxDate);
            strcpy(nuevoLog->time, auxTime);
            nuevoLog->gravedad = atoi(AuxGravedad);
            nuevoLog->serviceId = atoi(AuxServiceId);
            strcpy(nuevoLog->msg, AuxMsg);
        }
        lista->add(lista, nuevoLog);
    }
    fclose(archivo);
    return 0;
}


S_LogEntry* log_constructor()
{
    S_LogEntry* aux;
    aux = (S_LogEntry*) malloc(sizeof(S_LogEntry));
    if (aux != NULL)
    {
        strcpy(aux->date, "");
        strcpy(aux->msg, "");
        strcpy(aux->time, "");
        aux->gravedad = 0;
        aux->serviceId = 0;
    }
    return aux;
}


S_Service* constructor_service()
{
    S_Service* aux;
    aux = (S_Service*) malloc(sizeof(S_Service)); //el sizeof es del tama�o de la estructura, no del puntero a estructura
    if (aux != NULL)                              //Lo que se castea es lo que devuelve malloc()
    {
        aux->id = 0;
        strcpy(aux->email, "");
        strcpy(aux->name, "");
    }
    return aux;
}


int parse_sistema(ArrayList* lista)
{
    if (lista == NULL)
        return 1;
    FILE* archivo;
    char auxId[100];
    char auxEmail[100];
    char auxName[100];
    S_Service* auxiliar;
    archivo = fopen("service.txt", "r"); // falta validar que no sea NULL archivo
    while (!feof(archivo))
    {
        fscanf(archivo,"%[^;];%[^;];%[^\n]\n", auxId, auxEmail, auxName);
        auxiliar =constructor_service();
        if (auxiliar != NULL)
        {
            auxiliar->id = atoi(auxId);
            set_Name(auxiliar, auxName);
            set_Mail(auxiliar, auxEmail);
        }
        lista->add(lista, auxiliar);
    }
    fclose(archivo);
    return 0;
}


void imprimir(ArrayList* lista)
{
    S_LogEntry* log;
    int i;
    for (i = 0; i < lista->len(lista); i++)
    {
        log = lista->get(lista, i);
        printf("%s   %s   %d   %d   %s \n", log->date, log->time, log->serviceId, log->gravedad, log->msg);
    }
}


void imprimir_service(ArrayList* lista)
{
    S_Service* service;
    int i;
    for (i = 0; i < lista->len(lista); i++)
    {
        service = lista->get(lista, i);
        printf("%d     %s     %s\n", service->id, service->email, service->name);
    }
}

void set_Name(S_Service* persona, char* nombre)
{
    strcpy(persona->name, nombre);
}


void set_Mail(S_Service* persona, char* mail)
{
    strcpy(persona->email, mail);
}




void generar_reporte(ArrayList* logs, ArrayList* servicios)
{
    FILE* warnings;
    FILE* errors;
    int i, j, t;
    S_LogEntry* auxLog;
    S_Service* auxService;
    warnings = abrir_archivo("warnings.txt");
    errors = abrir_archivo("errors.txt");
    for (i = 0; i < logs->len(logs); i++)
    {
        auxLog = logs->get(logs, i);
        if (auxLog->gravedad == 3 && auxLog->serviceId != 44)
        {
            for (j = 0; j < servicios->len(servicios); j++)
            {
                auxService = servicios->get(servicios, j);
                if (auxLog->serviceId == auxService->id)
                {
                    fprintf(warnings, "%s ;%s ;%s ;%s ;  %s\n", auxLog->date, auxLog->time, auxService->name, auxLog->msg, auxService->email);
                    break;
                }
            }
        }
        else
        {
            if (auxLog->gravedad > 3 && auxLog->gravedad <= 7)
            {
                for (t = 0; t < servicios->len(servicios); t++)
                {
                    auxService = servicios->get(servicios, t);
                    if (auxLog->serviceId == auxService->id)
                    {
                        printf("%s     %s           %s         %s         %d\n", auxLog->date, auxLog->time, auxService->name, auxLog->msg, auxLog->gravedad);
                        break;
                    }
                }
            }
            else
            {
                if(auxLog->gravedad > 7)
                {
                    for (j = 0; j < servicios->len(servicios); j++)
                    {
                        auxService = servicios->get(servicios, j);
                        if (auxLog->serviceId == auxService->id)
                        {
                            fprintf(errors, "%s ;%s ;%s ;%s ;  %s\n", auxLog->date, auxLog->time, auxService->name, auxLog->msg, auxService->email);
                            break;
                        }
                    }
                }
            }
        }
    }
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



void mostrar_estadistica(ArrayList* logs, ArrayList* servicios)
{
    int i;
    int cont[] = {0,0,0,0,0,0,0,0,0,0};
    S_LogEntry* aux;
    for (i = 0; i < logs->len(logs); i++)
    {
        aux = logs->get(logs, i);
        switch (aux->gravedad)
        {
        case 0:
            cont[0]++;
            break;
        case 1:
            cont[1]++;
            break;
        case 2:
            cont[2]++;
            break;
        case 3:
            cont[3]++;
            break;
        case 4:
            cont[4]++;
            break;
        case 5:
            cont[5]++;
            break;
        case 6:
            cont[6]++;
            break;
        case 7:
            cont[7]++;
            break;
        case 8:
            cont[8]++;
            break;
        case 9:
            cont[9]++;
            break;
        }
    }
    printf("\nCantidad de errores de gravedad menor a 3: %d", cont[0]+cont[1]+cont[2]);
    printf("\nCantidad de errores de gravedad 3: %d", cont[3]);
    printf("\nCantidad de errores de gravedad entre 4 y 7: %d", cont[4]+cont[5]+cont[6]+cont[7]);
    printf("\nCantidad de errores de gravedad mayor a 7: %d", cont[8]+cont[9]);
}

int mayorError(ArrayList* logs)
{
    int mayor = 0, cont;
    int idFinal;
    S_LogEntry* aux;
    S_LogEntry* aux2;
    int i,j;
    for (i = 0; i < logs->len(logs);i++)
    {
        aux = logs->get(logs, i);
        cont = 0;
        for (j = 0; j < logs->len(logs);j++)
        {
            aux2 = logs->get(logs,j);
            if (aux->serviceId == aux2->serviceId)
            {
                cont++;
            }
        }
        if (cont > mayor)
        {
            mayor = cont;
            idFinal = aux->serviceId;
        }
    }
    return idFinal;
}
