#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo{
    int dato;
    struct nodo *siguiente;
}Lista;

//prototipos
void menu(void);
void insertar(Lista **, int);
void mostrar(Lista *);
void eliminar(Lista **, int);
void inicializar(Lista **);
void buscar(Lista *, int);

int main(void){
    Lista *p;
    inicializar(&p);

    bool inicio = true;
    int opc, dato;
    do{
        system("cls");
        mostrar(p);
        menu();
        printf("Opcion: ");
        scanf("%d", &opc);
        switch(opc){
            case 1:
                printf("Dato: ");
                scanf("%d", &dato);
                insertar(&p, dato);
                break;
            case 2:
                printf("Dato a eliminar: ");
                scanf("%d", &dato);
                eliminar(&p, dato);
                break;
            case 3:
                inicio = false;
                break;
            default:
                printf("Opcion no valida\n");
        }
    }while(inicio != false);

    return 0;
}

void menu(void){
    printf("\n");
    printf("1.- Insertar\n");
    printf("2.- Eliminar\n");
    printf("3.- Salir\n");
}

void inicializar(Lista **p){
    *p = NULL;
}

void insertar(Lista **p, int dato){
    Lista *nuevo;
    nuevo = (Lista *)malloc(sizeof(Lista));
    nuevo->dato = dato;
    nuevo->siguiente = *p;
    *p = nuevo;
}

void mostrar(Lista *p){
    while(p != NULL){
        printf("%d -> ", p->dato);
        p = p->siguiente;
    }
    printf("NULL\n");
}

void eliminar(Lista **p, int dato){
    Lista *aux, *ant;
    aux = *p;
    ant = NULL;
    while(aux != NULL){
        if(aux->dato == dato){
            if(ant == NULL){
                *p = aux->siguiente;
            }else{
                ant->siguiente = aux->siguiente;
            }
            free(aux);
            return;
        }
        ant = aux;
        aux = aux->siguiente;
    }
}



