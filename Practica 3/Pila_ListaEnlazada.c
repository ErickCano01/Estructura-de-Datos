#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "P3_Lib.h"

#define SIN_LIMITE 0
#define VERDADERO 1
#define FALSO 0

void mostrar_menu(void);

void imprimir_pila(Pila_LE p);
void capture_int(int *n);


//IMPLEMENTAR
void apilar_generos(Grupo_Pila *grupo,Book *libro);
void apilar_fecha(Grupo_Pila *grupo,Book *libro);

//funcion para regresar los libros a la caja
void regresar_a_caja(Pila_LE *pila, Pila_LE *caja);



int main(void)
{
    int i;
    int option;
    int corre_programa=VERDADERO;
    Book *libro;
    Pila_LE caja_libros;
    get_pila_of_books(&caja_libros);


    Grupo_Pila opciones[3];
    for(i=0;i<3;i++)
    {
        opciones[i].pilas = (Pila_LE *) malloc(sizeof(Pila_LE));
        opciones[i].num_elementos = 0;
        iniciarlizar_pila(opciones[i].pilas,SIN_LIMITE);
    }

    while(corre_programa)
    {
        if(caja_libros.cima==NULL){
            for(i=0;i<3;i++){
                regresar_a_caja(&opciones[i].pilas[0],&caja_libros);
            }

            for (i = 0; i < 3; i++) {
                opciones[i].num_elementos = 0;
                iniciarlizar_pila(opciones[i].pilas, SIN_LIMITE);
            }
        }
        
        system("cls");
        mostrar_menu();
        printf("\n\n\r Escoge opcion: ");
        capture_int(&option);


        fflush(stdin);
        system("cls");
        switch(option)
        {
            case 1:
                    printf("\n\r [1] APILAR TODO");
                    //DE LA PILA DE LA CAJA A UNA PILA EN MESA
                    if(caja_libros.cima!=NULL)
                    {
                        opciones[0].num_elementos=1;
                        while(!vacia(caja_libros))
                        {
                            insertar(opciones[0].pilas,mover(&caja_libros));
                        }
                    }
                    imprimir_pila(*opciones[0].pilas);
                    printf("\n\n\r");
                    system("pause");
                    break;
            case 2:
                    printf("\n\r [2] APILAR POR GENERO");
                    //DE LA PILA DE LA CAJA A UNA PILA EN MESA
                    if(caja_libros.cima!=NULL)
                    {
                        while(!vacia(caja_libros))
                        {
                            libro = mover(&caja_libros);
                            apilar_generos(&opciones[1],libro);
                        }
                    }

                    if (opciones[1].num_elementos>0)
                    {
                        printf("\n\n\r");
                        for(i=0;i<opciones[1].num_elementos;i++)
                        {
                            printf("\n\r [%d] %s",i,opciones[1].pilas[i].cima->libro->genero);
                        }
                        printf("\n\n\r Escoge opcion: ");
                        capture_int(&option);
                        if(option>=0 && option<opciones[1].num_elementos)
                        {
                            imprimir_pila(*((opciones[1].pilas)+option));
                        }
                        printf("\n\n\r");
                        system("pause");
                    }
                    break;
            case 3:
                    printf("\n\r [3] APILAR POR FECHA");
                    //DE LA PILA DE LA CAJA A UNA PILA EN MESA
                    if(caja_libros.cima!=NULL)
                    {
                        while(!vacia(caja_libros))
                        {
                            libro = mover(&caja_libros);
                            apilar_fecha(&opciones[2],libro);
                        }
                    }

                    if (opciones[2].num_elementos>0)
                    {
                        printf("\n\n\r");
                        for(i=0;i<opciones[2].num_elementos;i++)
                        {
                            printf("\n\r [%d] %d",i,opciones[2].pilas[i].cima->libro->release_date);
                        }
                        printf("\n\n\r Escoge opcion: ");
                        capture_int(&option);
                        if(option>=0 && option<opciones[2].num_elementos)
                        {
                            imprimir_pila(*((opciones[2].pilas)+option));
                        }
                        printf("\n\n\r");
                        system("pause");
                    }
                    break;
            case 4:
                    printf("\n\r [4] SALIR");
                    corre_programa=FALSO;
                    printf("\n\n\r");
                    system("pause");
                    break;
            default:
                    break;
        }
    }
    printf("\n\n\r");
    return 0;
}

void capture_int(int *n)
{
    char *end;
    char buf[64];
    do
    {
        if (!fgets(buf, sizeof buf, stdin))
            break;
        // remove \n
        buf[strlen(buf) - 1] = 0;
        *n = strtol(buf, &end, 10);
    }while (end != buf + strlen(buf));
}

void apilar_generos(Grupo_Pila *grupo,Book *libro){
    int i;
    int existe_genero=0;
    if(grupo->num_elementos==0){
        grupo->num_elementos=1;
        insertar(grupo->pilas,libro);
        return;
    }
    for(i=0;i<grupo->num_elementos;i++){
        if(strcmp(grupo->pilas[i].cima->libro->genero,libro->genero)==0){
            existe_genero=1;
            insertar(&grupo->pilas[i],libro);
            break;
        }
    }
    if(!existe_genero){
        grupo->num_elementos++;
        grupo->pilas = (Pila_LE *) realloc(grupo->pilas,grupo->num_elementos*sizeof(Pila_LE));
        iniciarlizar_pila(&grupo->pilas[grupo->num_elementos-1],SIN_LIMITE);
        insertar(&grupo->pilas[grupo->num_elementos-1],libro);
    }
}


void apilar_fecha(Grupo_Pila *grupo,Book *libro){
    int i;
    int existe_fecha=0;
    if(grupo->num_elementos==0){
        grupo->num_elementos=1;
        insertar(grupo->pilas,libro);
        return;
    }
    for(i=0;i<grupo->num_elementos;i++){
        if(grupo->pilas[i].cima->libro->release_date==libro->release_date){
            existe_fecha=1;
            insertar(&grupo->pilas[i],libro);
            break;
        }
    }
    if(!existe_fecha){
        grupo->num_elementos++;
        grupo->pilas = (Pila_LE *) realloc(grupo->pilas,grupo->num_elementos*sizeof(Pila_LE));
        iniciarlizar_pila(&grupo->pilas[grupo->num_elementos-1],SIN_LIMITE);
        insertar(&grupo->pilas[grupo->num_elementos-1],libro);
    }
}

//funcion para regresar los libros a la caja
void regresar_a_caja(Pila_LE *pila, Pila_LE *caja){
    while(!vacia(*pila)){
        insertar(caja,mover(pila));
    }
}

void mostrar_menu(void){
    printf("\n\r [1] APILAR TODO");
    printf("\n\r [2] APILAR POR GENERO");
    printf("\n\r [3] APILAR POR FECHA");
    printf("\n\r [4] SALIR");
}

void imprimir_pila(Pila_LE p)
{
    printf("\n\r Lista:");
    if(!vacia(p))
    {
        Elemento *i;
        i=p.cima;
        while(i!=NULL)
        {
            printf("\n\r %d | %s ,%s",i->libro->release_date,i->libro->nombre,i->libro->genero);
            i=i->siguiente;
        }
        return;
    }
    printf(" Vacia");
}
