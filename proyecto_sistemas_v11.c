#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include <windows.h>
#include<stdlib.h>


void llenar_arreglo(int cantidad);
void suma_actualizada(int cantidad);
void gotoxy(short x, short y);
void actualizar(int tiempo,int cantidad);
void procesar(int numero, int numero_proceso);
void dibuja();
void llenar_porprocesar();
void limpiar_porprocesar();
void imprimir_tiempo();

int ta, tb, tc, td, cuantum;
char porprocesar[25] = { 'A','B','C','D' };
char procesados[25] = { ' ',' ',' ',' ' };
int ultimo = 0;
int tiempo_transcurrido = 0;
int sobran;

int tiempo[25];
int quantum[25];
char nombre_proceso[25];
int suma=0;





int main()
{
	int cant,i;
	
	system("cls");//limpiar pantalla
	printf("Ingrese la cantidad de procesos: ");
	scanf("%d", &cant);
	sobran = cant - 1;//cantidad de procesos a procesar
	llenar_arreglo(cant);//quitar si implemento otro

	for (i=0; i < cant; i++) {
		system("cls");
		printf("Tiempo de ejecucion del proceso %c?",nombre_proceso[i]);
		scanf("%d",&tiempo[i]);
		printf("Tiempo de CPU del proceso %c?", nombre_proceso[i]);
		scanf("%d", &quantum[i]);

	}

	system("cls");
	suma_actualizada(cant);
	dibuja();
	llenar_porprocesar();
	while (suma>0){
		imprimir_tiempo();
		for (i = 0; i < cant; i++) {
			if (tiempo[i] > 0) {
				procesar(i, cant);
				suma_actualizada(cant);
				
			}
			else {
				
				tiempo_transcurrido++;
			}
	
		}
		
	} 
	gotoxy(47, 11);
	printf("EMPTY");
	gotoxy(0, 7);
	printf("                         " );
	gotoxy(0, 10);
	printf("                         " );
	gotoxy(0, 40);//mover puntero al final
	printf("\n");
	//getch();
	return 0;
}
//********************************************************************************************************************************


void imprimir_tiempo() {
	gotoxy(0, 0);
	printf("Tiempo Transcurrido: %d segundos", tiempo_transcurrido);


}
//********************************************************************************************************************************
void llenar_porprocesar() {
	int i;
	int x = 33;
	for (i = 0; i<=sobran + 1; i++) {
		porprocesar[i] = nombre_proceso[i];
		gotoxy(x, 17); printf("%c", porprocesar[i]);//sin procesar
		x += 4;
	}
}
//********************************************************************************************************************************
void limpiar_porprocesar() {
	int i;
	int x = 33;
	for (i = 0; i < sobran + 1; i++) {
		gotoxy(x, 17); printf(" ");//sin procesar
		x += 4;
	}	
}
//********************************************************************************************************************************
void procesar(int numero, int numero_proceso) { // Procesar 
	gotoxy(49, 11);
	printf("%c", nombre_proceso[numero]);//ubicar a en cpu
	
	cuantum = quantum[numero];
	
	while (cuantum >= 0 && tiempo[numero]>0)
	{
		gotoxy(0, 7);
		printf("|Tiempo restante de %c: %d |", nombre_proceso[numero], tiempo[numero]);
		gotoxy(0, 10);
		printf("|Tiempo restante de cuantum: %d|",cuantum);

		if (tiempo[numero] > 0 && cuantum > 0) {//si todavia tiene tiempo de ejecucion
			tiempo[numero]--;
			tiempo_transcurrido++;
			Sleep(1000);
		}
		else if (tiempo[numero] == 0){//si se le acabo el tiempo de ejecucion
			break;
			tiempo_transcurrido++;
			Sleep(1000);
		}
		cuantum--;
		//Sleep(1000);
		imprimir_tiempo();
	}

	actualizar(tiempo[numero],numero_proceso);
}

//********************************************************************************************************************************
void actualizar(int tiempo, int cantidad){ // actualizar dibujo de CPU
	int x,i;

	if (tiempo == 0)//si ya proceso todo
	{
		x = 33;
		limpiar_porprocesar();//limpia lista
		
		procesados[ultimo++] = porprocesar[0];//se a๑ade al final en lista de procesados

		x = 33;
		for (int i = 0; i <= sobran; i++) {
			porprocesar[i] = porprocesar[i + 1];//se mueven todos los procesos 1 puesto
			
		}
	
		porprocesar[sobran] = ' '; // se borra el ultimo por procesar
	
		sobran--; // se decrementa la cantidad de procesos activos
	}
	else//si le queda tiempo de ejecucion
	{
		char tmp = porprocesar[0];//se guarda el proceso que salio de cpu
		for (i = 0; i <=sobran; i++) {
			porprocesar[i] = porprocesar[i+1]; // se corren todos los procesos 1 puesto
		}
		porprocesar[cantidad-1] = ' '; // se a๑ade al final el vacio
		porprocesar[sobran] = tmp; // se asigna en la ultima posicion el caracter guardado
	}

	x = 33;
	for (i = 0; i <= ultimo; i++) {
		gotoxy(x, 5); printf("%c", procesados[i]);//procesados
		x += 4;
	}
	x = 33;
	for (i = 0; i<sobran+1; i++) {
		gotoxy(x, 17); printf("%c", porprocesar[i]);//sin procesar
		x += 4;
	}
	
}

//********************************************************************************************************************************
void llenar_arreglo(int cantidad) {
	int i = 0;
	int valor = 65;
	for (i; i < cantidad; i++, valor++)
		nombre_proceso[i] = valor;

	for (i = 0; i < cantidad+1; i++)
		printf("%c \n", nombre_proceso[i]);
}
//********************************************************************************************************************************
void suma_actualizada(int cantidad) { // modulo para sumatoria de tiempos de procesos
	int i = 0;
	suma = 0;
	for (i; i < cantidad; i++)
		suma = suma+ tiempo[i];

}
//********************************************************************************************************************************
void gotoxy(short x, short y) { // funcion para pintar en pantalla en (x,y)
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//********************************************************************************************************************************
void dibuja() // Grafico CPU
{
	gotoxy(31, 3); printf("PROCESADOS    ");
	gotoxy(31, 4); printf("ษอออหอออหอออหอออหอออหอออหอออหอออษอออหอออหอออป");
	gotoxy(31, 5); printf("บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ");
	gotoxy(31, 6); printf("ศอออสอออสอออสอออสอออสอออสอออสอออสอออสอออสอออผ");

	gotoxy(45, 8); printf("ษอออออออป");
	gotoxy(45, 9); printf("บ C P U บ");
	gotoxy(45, 10); printf("บ       บ");
	gotoxy(45, 11); printf("บ       บ");
	gotoxy(45, 12); printf("บ       บ");
	gotoxy(45, 13); printf("ศอออออออผ");

	gotoxy(31, 15); printf("POR PROCESAR  ");
	gotoxy(31, 16); printf("ษอออหอออหอออหอออหอออหอออหอออหอออษอออหอออหอออป");
	gotoxy(31, 17); printf("บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ"); // nombre procesos
	gotoxy(31, 18); printf("ศอออสอออสอออสอออสอออสอออสอออสอออสอออสอออสอออผ");

	gotoxy(31, 21); printf("POR PROCESAR  ");
	gotoxy(31, 22); printf("ษอออหอออหอออหอออหอออหอออหอออหอออษอออหอออหอออป");
	gotoxy(31, 23); printf("บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ"); // nombre procesos
	gotoxy(31, 24); printf("ศอออสอออสอออสอออสอออสอออสอออสอออสอออสอออสอออผ");

	gotoxy(31, 27); printf("POR PROCESAR  ");
	gotoxy(31, 28); printf("ษอออหอออหอออหอออหอออหอออหอออหอออษอออหอออหอออป");
	gotoxy(31, 29); printf("บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ"); // nombre procesos
	gotoxy(31, 30); printf("ศอออสอออสอออสอออสอออสอออสอออสอออสอออสอออสอออผ");

	gotoxy(31, 33); printf("POR PROCESAR  ");
	gotoxy(31, 34); printf("ษอออหอออหอออหอออหอออหอออหอออหอออษอออหอออหอออป");
	gotoxy(31, 35); printf("บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ   บ"); // nombre procesos
	gotoxy(31, 36); printf("ศอออสอออสอออสอออสอออสอออสอออสอออสอออสอออสอออผ");
	

}
//********************************************************************************************************************************