#*****************************************************************
# Fichero: 	Makefile
# Autores: 	Diego García Aranda 820506
#			Simón Alonso Gutiérrez 821038
# Fecha entrega:	22/11/2023
# Coms:   Makefile para la práctica 3 de Algoritmia para Problemas Difíciles
#		  "make pruebas" construye el ejecutable para las pruebas
#*****************************************************************

#---------------------------------------------------------
CODIGO_DIR=src
BUILD_DIR=build
BIN_DIR=bin

BOOTSTRAP=bootstraps
ENTREGARPAQUETE=entregarPaquete
LEERMAPA=leerMapa
PRUEBAS=pruebas
CC=g++
CPPFLAGS=-std=c++11 # Flags compilacion


pruebas : ${BIN_DIR}/${PRUEBAS}
#----------------------------------------------------------------------------
# BOOTSTRAP
# Compilacion
${BUILD_DIR}/${BOOTSTRAP}.o: ${CODIGO_DIR}/${BOOTSTRAP}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${BOOTSTRAP}.cpp -o ${BUILD_DIR}/${BOOTSTRAP}.o
#----------------------------------------------------------------------------
# ENTREGAR PAQUETE
# Compilacion
${BUILD_DIR}/${ENTREGARPAQUETE}.o: ${CODIGO_DIR}/${ENTREGARPAQUETE}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${ENTREGARPAQUETE}.cpp -o ${BUILD_DIR}/${ENTREGARPAQUETE}.o
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# LEER MAPA
# Compilacion
${BUILD_DIR}/${LEERMAPA}.o: ${CODIGO_DIR}/${LEERMAPA}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${LEERMAPA}.cpp -o ${BUILD_DIR}/${LEERMAPA}.o
#----------------------------------------------------------------------------
#-----------------------------------------------------------
# PRUEBAS
# Compilacion
${BUILD_DIR}/${PRUEBAS}.o: ${CODIGO_DIR}/${PRUEBAS}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${PRUEBAS}.cpp -o ${BUILD_DIR}/${PRUEBAS}.o
# Linkado
${BIN_DIR}/${PRUEBAS}: ${BUILD_DIR}/${PRUEBAS}.o ${BUILD_DIR}/${BOOTSTRAP}.o ${BUILD_DIR}/${LEERMAPA}.o ${BUILD_DIR}/${ENTREGARPAQUETE}.o 
	${CC} ${BUILD_DIR}/${BOOTSTRAP}.o ${BUILD_DIR}/${LEERMAPA}.o ${BUILD_DIR}/${ENTREGARPAQUETE}.o ${BUILD_DIR}/${PRUEBAS}.o -o ${BIN_DIR}/${PRUEBAS}
#-----------------------------------------------------------
