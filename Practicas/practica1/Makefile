#*****************************************************************
# Fichero: 	Makefile
# Autores: 	Diego García Aranda 820506ç
#			Simón Alonso Gutiérrez 821038
# Fecha entrega:	18/10/2023
# Coms:   Makefile para la práctica 1 de Algoritmia para Problemas Difíciles
#		  "make pruebas" construye el ejecutable para las pruebas automáticas
#		  "make datosSinteticos" construye el ejecutable para la generación
# 		   de datos sintéticos
#		  "make clean" destruye archivos .o y ejecutables
#*****************************************************************

#---------------------------------------------------------
CODIGO_DIR=src
BUILD_DIR=build
BIN_DIR=bin

QUICKSORT=quicksort
RADIXSORT=radixsort
MERGESORT=mergesort
PRUEBAS=pruebas
PRUEBASINTENSIVAS=pruebasIntensivas
GENERARDATOSSINTETICOS=generarDatosSinteticos

CC=g++
CPPFLAGS=-std=c++11 # Flags compilacion


pruebas : ${BIN_DIR}/${PRUEBAS}
datosSinteticos: ${BIN_DIR}/${GENERARDATOSSINTETICOS}
#----------------------------------------------------------------------------
# QUICKSORT
# Compilacion
${BUILD_DIR}/${QUICKSORT}.o: ${CODIGO_DIR}/${QUICKSORT}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${QUICKSORT}.cpp -o ${BUILD_DIR}/${QUICKSORT}.o
#----------------------------------------------------------------------------
# RADIXSORT
# Compilacion
${BUILD_DIR}/${RADIXSORT}.o: ${CODIGO_DIR}/${RADIXSORT}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${RADIXSORT}.cpp -o ${BUILD_DIR}/${RADIXSORT}.o
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# MERGESORT
# Compilacion
${BUILD_DIR}/${MERGESORT}.o: ${CODIGO_DIR}/${MERGESORT}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${MERGESORT}.cpp -o ${BUILD_DIR}/${MERGESORT}.o
#----------------------------------------------------------------------------
#-----------------------------------------------------------
# PRUEBAS
# Compilacion
${BUILD_DIR}/${PRUEBAS}.o: ${CODIGO_DIR}/${PRUEBAS}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${PRUEBAS}.cpp -o ${BUILD_DIR}/${PRUEBAS}.o
# Linkado
${BIN_DIR}/${PRUEBAS}: ${BUILD_DIR}/${PRUEBAS}.o ${BUILD_DIR}/${QUICKSORT}.o ${BUILD_DIR}/${MERGESORT}.o ${BUILD_DIR}/${RADIXSORT}.o 
	${CC} ${BUILD_DIR}/${QUICKSORT}.o ${BUILD_DIR}/${MERGESORT}.o ${BUILD_DIR}/${RADIXSORT}.o ${BUILD_DIR}/${PRUEBAS}.o -o ${BIN_DIR}/${PRUEBAS}
#-----------------------------------------------------------
# GENERAR DATOS SINTETICOS
# Compilacion
${BUILD_DIR}/${GENERARDATOSSINTETICOS}.o: ${CODIGO_DIR}/${GENERARDATOSSINTETICOS}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${GENERARDATOSSINTETICOS}.cpp -o ${BUILD_DIR}/${GENERARDATOSSINTETICOS}.o
# Linkado
${BIN_DIR}/${GENERARDATOSSINTETICOS}: ${BUILD_DIR}/${GENERARDATOSSINTETICOS}.o
	${CC} ${BUILD_DIR}/${GENERARDATOSSINTETICOS}.o -o ${BIN_DIR}/${GENERARDATOSSINTETICOS}
#-----------------------------------------------------------
