#include <stdio.h>
#include <stdlib.h>
void swap (int*, int*);
void mostrarVector (int*, int);

int main()
{
    int x = 5;
    int y = 18;
    int vec[5];
    for (int i = 0; i < 5; i++)
    {
        printf("\nIngrese un numero: ");
        scanf("%d", (vec+i)); //sin & (ampersar) xq vec ya tiene guardada la direccion de memoria de donde empieza el vector.
    }
    /*printf("\n\nValores antes del swap\n\n");
    printf("X = %d\n", x);
    printf("Y = %d\n", y);

    swap(&x, &y);

    printf("\nValores despues del swap y en el main\n\n");
    printf("X = %d\n", x);
    printf("Y = %d\n", y);*/
    mostrarVector(vec, 5);
    return 0;
}


void swap (int* x, int* y)
{
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
    printf("\nValores en el swap\n\n");
    printf("X = %d\n", *x);
    printf("Y = %d\n", *y);
}


void mostrarVector (int* x, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d  ", *(x + i)); // suma a la direccion de memoria guardada en *x el valor de i. Donde i valdria el sizeof() de int.
    }                             // O sea, muestra el valor de la direccion de memoria 0, despues la 1, despues la 2, etc
}                                 //Los vectores arrancan en la posicion 0 y se van moviendo la cantidad de bytes que tenga el tipo de dato del que son
