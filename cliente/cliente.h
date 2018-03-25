/*
  Arquivo: cliente.h
  Detalhes: Declara funções, constantes e variáveis necessárias para o funcionamento do cliente
*/

#ifndef _CLIENTE_H_
#define _CLIENTE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Diretivas de portabilidade... */
#ifdef _WIN32
  #include <winsock.h>
  #include <winsock2.h>
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netdb.h>
#endif

#define PORTA_CONEXAO 16122
#define STR_PORTA_CONEXAO "16122"

/* ... */
#ifdef _WIN32
extern void habilita_sockets(WSADATA *); /* Coisas do Windows... */
#endif

extern int cria_socket(void); /* Cria um socket para efetuar ou receber uma conexão */

extern int conecta_ip(int, char *); /* Efetua a conexão com o servidor */

extern void associa_porta(int, int); /* Habilita uma porta para receber conexões */

extern int envia_mensagem(int, char *); /* Envia os dados via socket */

extern int le_mensagem(int, char *); /* Recebe os dados via socket */

extern int nooo(); /* Luke, eu sou seu pai! */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* _CLIENTE_H_ */
