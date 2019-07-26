#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

#define TAMANIO 10000

void prueba_crear_destruir_pila() {

	printf("\n");
	printf("%s\n","========== PILA RECIEN CREADA ========" );

	pila_t* pila = pila_crear();

	print_test("pila creada correctamente", pila != NULL);

	print_test("ver tope en pila recien creada es incorrecto", pila_ver_tope(pila) == NULL);

	print_test("desapilar en pila recien creada es NULL", pila_desapilar(pila) == NULL);

	printf("%s\n", "pila se destruye correctamente... valgrind" );

	pila_destruir(pila);
}

void llenar_datos( int cadena[]) {

	for (int i = 0; i < TAMANIO; ++i) {

		cadena[i] = i + 1;
	}
}

void prueba_de_volumen() {

	printf("\n");
	printf("%s\n","========== PRUEBA VOLUMEN ========" );

	pila_t* pila = pila_crear();

	int cadena[TAMANIO];
	int* tope;
	int* dato_desapilado;

	llenar_datos(cadena);

	printf("%s\n","..........prueba de volumen  apilar............" );

	bool ok = true;
	bool ok_tope = true;
	

	for (int i = 0; i < TAMANIO; ++i) {
		
		ok &= pila_apilar(pila,&cadena[i]);

		tope = pila_ver_tope(pila);
		if (*tope != cadena[i]){
			ok_tope = false;
		}
		ok &= ok_tope;
	}
	print_test("todos los datos en la pila se apilaron correctamente",ok);

	printf("%s\n","..............prueba de volumen desapilar..........." );

	bool ok_desapilado = true;
	ok = true;
	ok_tope = true;

	for (int i = TAMANIO; i > 0; --i) {
		dato_desapilado = pila_desapilar(pila);
		if (*dato_desapilado != i){
			ok_desapilado = false;
		}

		ok &= ok_desapilado;

		tope = pila_ver_tope(pila);

		if ( i > 1)	{
			if (*tope != i - 1){
				ok_tope = false;
			}
		}

		ok &= ok_tope;
	}

	print_test("los datos se desapilaron correctamente",ok);

	pila_destruir(pila);
}

void prueba_apilar_NULL() {
	printf("\n");
	printf("%s\n","=========== APILAR NULL ===============" );
	pila_t* pila=pila_crear();

	int* dato=NULL;

	print_test("apilar NULL es correcto", pila_apilar(pila,dato));

	print_test("tope es el correcto",pila_ver_tope(pila) == NULL);

	print_test("al desapilar es NULL", pila_desapilar(pila) == NULL);

	pila_destruir(pila);
}

void pruebas_funcionamiento_LIFO() {
	printf("\n");
	printf("%s\n","=============== PRUEBA LIFO=================" );

	pila_t* pila=pila_crear();

	print_test("la acción de esta_vacía en una pila recién creada es verdadero",pila_esta_vacia(pila));

	int datos[3];
	int* tope;
	int* dato_desapilado;

	printf("%s\n","...........pruebas apilar............" );

	datos[0] = 10;
	print_test("primer dato apilado correctamente",pila_apilar(pila,&datos[0]));
	tope = pila_ver_tope(pila);
	print_test("el tope es el ultimo dato ingresado",*tope == 10);

	datos[1] = 20;
	print_test("primer dato apilado correctamente",pila_apilar(pila,&datos[1]));
	tope = pila_ver_tope(pila);
	print_test("el tope es el ultimo dato ingresado",*tope == 20);

	datos[2] = 30;
	print_test("primer dato apilado correctamente",pila_apilar(pila,&datos[2]));
	tope = pila_ver_tope(pila);
	print_test("el tope es el ultimo dato ingresado",*tope == 30);

	printf("%s\n","................pruebas desapilar..............." );

	dato_desapilado = pila_desapilar(pila);
	print_test("el dato desapilado es el correcto", *dato_desapilado == 30);
	tope = pila_ver_tope(pila);
	print_test("despues de desapilar el nuevo tope es el adecuado",*tope == 20);

	dato_desapilado = pila_desapilar(pila);
	print_test("el dato desapilado es el correcto", *dato_desapilado == 20);
	tope = pila_ver_tope(pila);
	print_test("despues de desapilar el nuevo tope es el adecuado",*tope == 10);

	dato_desapilado = pila_desapilar(pila);
	print_test("el ultimo dato desapilado es el correcto", *dato_desapilado == 10);
	
	printf("\n");
	printf("%s\n"," despues de desapilar todos los datos , la pila se comporta como recien creada" );
	
	print_test("despues de desapilar todos los datos la pila esta vacia", pila_esta_vacia(pila));

	print_test("desapilar una pila vacia es NULL", pila_desapilar(pila) == NULL);

	print_test("pila_ver_tope en una pila vacia es NULL", pila_ver_tope(pila) == NULL);

	pila_destruir(pila);
}

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);

   prueba_crear_destruir_pila();
   prueba_de_volumen();
   prueba_apilar_NULL();
   pruebas_funcionamiento_LIFO();
}
