# Trabalho - Sistemas Operacionais

* Simulador de um Sistema Detector de Incêndios Florestais

* Professor: João Victor Oliveira

* Alunos(as): Jacksson Yuri, Matheus Santiago, Shirlene Oliveira

* Data de entrega: 16/12/2022

## 

* Sistema Operacional: Linux.
* Linguagem de programação: C.
* Bibliotecas padrões da linguagem C utilizadas: 

  <string.h>, <stdio.h>, <stdlib.h>, <pthread.h>, <unistd.h>
* Como compilar: seguir os passos do arquivo Makefile.
  
 
## Objetivo

* Criar uma matriz 30x30 para representar uma floresta, detectar e apagar os incêndios ocorridos utilizando a programação de múltiplas threads.

## Implementação

O programa foi realizado com modularização. Abaixo está cada modulo e suas funções.

* Map: geração de uma matriz 30x30, onde será verificado os incêndios e é preenchida com "-" e "T".  

* Threads: criação de todas as threads através da função - void  create_threads(). Cada "T" vira uma thread sensor, que se comunica com os vizinhos e enviam um alerta para a thread central (reponsável por despertar a thread bombeiro) quando há ocorrência de incêncio. O fogo é gerado de forma aleatória pela thread incêndio.  A thread bombeiro apaga o fogo e espera a próxima chamada.

* Sensor: cria os sensores. Na ocorrência de incêndio, comunica os vizinhos numa distância de 3 elementos e envia uma messagem. Especifica quais threads nó sensor podem se comunicar com a thread central. Detrói a thread nó sensor caso o fogo caia exatamente na mesma posição de "T" no mapa. 

* Message: criação das mensagens. Armazena os dados das mensagens no arquivo. Verifica se a mensagem é nova.

* Queue: guarda numa fila as mensagens recebidas da thread central e de cada nó sensor. 

* Utils: funções pra criar o arquivo e struct que armazena o id do nó sensor, hora e localização onde ocorreu o incêndio. 
* Main: programa principal executável.
