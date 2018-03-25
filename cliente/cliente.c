#include "cliente.h"

#ifdef _WIN32
void habilita_sockets(WSADATA *wsaData)
{
	/* Habilita o uso de sockets pelo sistema */
	if (WSAStartup(MAKEWORD(1,1), wsaData)) {
		puts("Erro na inicialização do WSAData");
		WSACleanup();
		exit(1);
	}
}
#endif

int cria_socket(void)
{
	int id_socket;
	
	/* Cria o socket para a conexão */
	if ((id_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		#ifdef _WIN32
		printf("Erro: %d\n", WSAGetLastError());
		#else
		perror("cria_socket()");
		#endif
		
		exit(id_socket);
	}
	
	return id_socket;
}

int conecta_ip(int socket, char *ip)
{
	int conexao;
	struct sockaddr_in servidor;
	
	servidor.sin_family = AF_INET; /* Família */
	servidor.sin_addr.s_addr = inet_addr(ip); /* Endereço IP */
	servidor.sin_port = htons(PORTA_CONEXAO); /* Porta */
	memset(&(servidor.sin_zero), 0, 8); /* Zera o restante da estrutura */
	
	/* Faz a conexão com o servidor */
	if ((conexao = connect(socket, (struct sockaddr *)&servidor, sizeof(struct sockaddr_in))) < 0) {
		#ifdef _WIN32
		switch (WSAGetLastError())
		{
			case WSAECONNREFUSED:
				puts("Connection refused.");
			break;
			
			case WSAEHOSTUNREACH:
				puts("Host unreachable");
			break;
		}
		#else
		perror("conecta_ip()");
		#endif
		
		exit(conexao);
	}
	
	return conexao;
}

int envia_mensagem(int socket, char *mensagem)
{
	int resultado;
	
	if ((resultado = send(socket, mensagem, strlen(mensagem), 0)) < 0)
		#ifdef _WIN32
		printf("Erro ao enviar mensagem! Codigo: %d\n", WSAGetLastError());
		#else
		perror("envia_mensagem()");
		#endif
		
	return resultado;
}

int le_mensagem(int socket, char *mensagem)
{
	int recebido;
	
	if ((recebido = recv(socket, mensagem, TAM_MSG, 0)) < 0) {
		#ifdef _WIN32
		printf("Erro ao ler mensagem! Codigo: %d\n", WSAGetLastError());
		#else
		perror("le_mensagem()");
		#endif
	} else if (recebido == 0) {
		#ifdef _WIN32
		printf("Conexao encerrada! Codigo: %d\n", WSAGetLastError());
		#else
		perror("le_mensagem()");
		#endif
		mensagem[0] = 0;
	} else {
		mensagem[recebido] = 0;
	}
	
	return recebido;
}
