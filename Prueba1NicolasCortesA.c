#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pesoAcumulado = 0, beneficioAcumulado = 0;

/*---------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------ESTRUCTURA Y FUNCIONES PARA LA COLA CANDIDATOS-------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct colaCandidatos{
	char nombre [20];
	int peso;
	int beneficio;
	struct colaCandidatos *sgte;
}colaCandidatos;

typedef struct colaCandidatos *candidatos; //tipo dato puntero de colaCandidatos

void pushCandidatos(candidatos *inicio, candidatos *final, char nombre[], int peso, int beneficio){
	candidatos nuevo;
	nuevo = (candidatos)malloc(sizeof(colaCandidatos));
	strcpy(nuevo->nombre,nombre);
	nuevo->peso = peso;
	nuevo->beneficio = beneficio;
	nuevo->sgte = NULL;
	if(*final) (*final)->sgte = nuevo;		// Caso cola NO VACIA
	else *inicio = nuevo;					// Caso cola VACIA
	*final = nuevo;							// En ambos casos, el nuevo nodo siempre sera el final de la cola, ya que se ingresa por el final
}

void popCandidatos(candidatos *inicio, candidatos *final){
	candidatos aux;
	char dato[20];
	if(*inicio){											// Caso la cola EXISTE. Si no existe la cola simplemente se sale de la funcion
		aux = *inicio;
		if(*inicio == *final) *inicio = *final = NULL;		// Caso la cola tiene SOLO UN NODO
		else *inicio = (*inicio)->sgte;						// Caso la cola tiene 2 O MAS NODOS
		strcpy(dato,aux->nombre);
		free(aux);
		printf("\nNombre de producto: %s", dato);			//se imprime el producto que se elimina de la cola
	}
}

void show(candidatos *inicio){					// Funcion para mostrar los datos de los productos de la cola
	int i=1;
	candidatos aux = *inicio;
	while(aux){
		printf("\nProducto %d ----- Nombre: %s ----- Peso: %d Kg ----- Beneficio: %d", i, aux->nombre, aux->peso, aux->beneficio);
		aux = aux->sgte;
		i++;
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------ESTRUCTURA Y FUNCIONES PARA LA PILA PRIMER SOLUCION--------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct pilaPrimerSolucion{
	char nombre [20];
	int peso;
	int beneficio;
	struct pilaPrimerSolucion *sgte;
}pilaPrimerSolucion;

typedef struct pilaPrimerSolucion *primerSolucion; //tipo dato puntero de pilaPrimerSolucion
												
void pushPilaPrimerSolucion(primerSolucion *top, char nombre[], int peso, char beneficio){
	primerSolucion nuevo = (primerSolucion)malloc(sizeof(pilaPrimerSolucion)); 
	strcpy(nuevo->nombre,nombre);
	nuevo->peso = peso;
	nuevo->beneficio = beneficio;
	nuevo->sgte=*top;			//nuevo->sgte apuntará a lo mismo que apunta tope			
	*top=nuevo;					//tope dejará de apuntar al elemento anterior y ahora apunta al ultimo elemento que llego (nuevo)
}

int popPilaPrimerSolucion(primerSolucion *top){				
	primerSolucion eliminar = *top;
	char dato[20];
	
	if(!eliminar) return 0;		
	strcpy(dato,eliminar->nombre);
	*top=eliminar->sgte;
	free(eliminar);
	printf("\nSacando producto de la pila primer solucion: %s", dato);
}

/*---------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------ESTRUCTURA Y FUNCIONES PARA LA PILA SEGUNDA SOLUCION--------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct pilaSegundaSolucion{
	char nombre [20];
	int peso;
	int beneficio;
	struct pilaSegundaSolucion *sgte;
}pilaSegundaSolucion;

typedef struct pilaSegundaSolucion *segundaSolucion; //tipo dato puntero de pilaSegundaSolucion
												
void pushPilaSegundaSolucion(segundaSolucion *top, char nombre[], int peso, char beneficio){
	segundaSolucion nuevo = (segundaSolucion)malloc(sizeof(pilaSegundaSolucion)); 
	strcpy(nuevo->nombre,nombre);
	nuevo->peso = peso;
	nuevo->beneficio = beneficio;
	nuevo->sgte=*top;			//nuevo->sgte apuntará a lo mismo que apunta tope			
	*top=nuevo;					//tope dejará de apuntar al elemento anterior y ahora apunta al ultimo elemento que llego (nuevo)
}

int popPilaSegundaSolucion(segundaSolucion *top){				
	segundaSolucion eliminar = *top;
	char dato[20];
	
	if(!eliminar) return 0;		
	strcpy(dato,eliminar->nombre);
	*top=eliminar->sgte;
	free(eliminar);
	printf("\nSacando producto de la pila segunda solucion: %s", dato);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------*/

candidatos inicio = NULL, final = NULL;			// Los punteros Inicio y Final de la cola cadidatos apuntan a NULL
primerSolucion topPrimerSolucion = NULL;		// El puntero tope de la primer pila apunta a NULL
segundaSolucion topSegundaSolucion = NULL;		// El puntero tope de la segunda pila apunta a NULL


/*---------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------OPCIONES DEL MENU--------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------*/


void opcion_1(){
	system("cls");
	int s=1, peso, beneficio;
	char nombre[20];
	while(s==1)
    {
    	printf("\n----------------------------------------------");
		printf("\n---------------INGRESO DE DATOS---------------");
		printf("\n----------------------------------------------\n");
		
		printf("\nIngrese nombre del producto: ");
    	scanf("%s", nombre);
    	printf("\nIngrese peso del producto %s: ", nombre);
    	scanf("%d", &peso);
    	printf("\nIngrese beneficio del producto %s: ", nombre);
    	scanf("%d", &beneficio);
    	
    	pushCandidatos(&inicio,&final, nombre, peso, beneficio);
    	printf("\n 1 para ingresar otro producto, 0 para terminar: ");
    	scanf("%d",&s);
    }
	getch();
}

void opcion_2(){
	system("cls");
	show(&inicio);		// Aqui mostramos los datos de la cola
	//while(inicio) popCandidatos(&inicio,&final);		// Aqui podemos mostrar el nombre de los prductos de la cola a medida que lo vamos eliminando de la cola
	getch();
}

void opcion_3(){
	system("cls");
	printf("Opcion 3\n");
	while(topPrimerSolucion) popPilaPrimerSolucion(&topPrimerSolucion);		// Aqui mostramos los productos de la pila primer solucion, a medida que se eliminan de la pila
	getch();
}

void opcion_4(){
	system("cls");
	printf("Opcion 4\n");
	while(topSegundaSolucion) popPilaSegundaSolucion(&topSegundaSolucion);		// Aqui mostramos los productos de la pila segunda solucion, a medida que se eliminan de la pila
	getch();
}

void opcion_5(){
	system("cls");
	printf("\nEsta es la opcion 5");
	getch();
}

void opcion_6(){
}



/*---------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------FUNCION PRINCIPAL | MAIN------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------*/

int main(){
	
	int opc;
	
	do{
		system("cls");
		printf("Menu de navegacion\n\n");
		printf("1.- Ingresar productos en la cola Candidatos \n");
		printf("2.- Mostrar la cola de los productos que son candidatos para entrar en la mochila\n");
		printf("3.- Mostrar la primera solucion y como queda la cola de candidatos\n");
		printf("4.- Mostrar la segunda solucion y como queda la cola de candidatos\n");
		printf("5.- Entregar la mejor solucion\n");
		printf("6.- Salir\n");
		printf("Opcion a escoger: ");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				opcion_1();
				break;
			case 2:
				opcion_2();
				break;
			case 3 :
				opcion_3();
				break;
			case 4:
				opcion_4();
				break;
			case 5:
				opcion_5();
				break;
			case 6:
				opcion_6();
				break;
			default:
				system("cls");
				printf("La opcion que ingreso es incorrecta.\n");
				printf("Ingrese un valor de 1 a 6.");
				getch();
				break;
					
		}
	}while(opc !=6);
	
	return 0;
}

/*Mi idea era... desde la funcion pop hacer un return, que me retornara el nombre de los productos almacenados, para hacer cosas como estas...

	i=1;
	while(inicio){
		printf("\nNombre del producto %d: %s", i, popCandidatos(&inicio,&final));
		i++;
	}

No me funcionó, no supe arreglarlo, me enredé y no supe que más hacer u.u
*/
