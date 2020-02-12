#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler_tudo();
int verificar_adm();
void criar_adm();
int login(char login_digitado[], char senha_digitado[]);
int menu_adm();
void criar_usu();
void visu_usu();
void excluir_usu();
int busca_nome(char login_digitado[]);
int menu_usu();
void cadastrar_clube();
void continua();
void modificar(int controladora);
void escrever_tudo();

struct tipo_adm{
	char nome_adm[100];
	char login_adm[25];
	char senha_adm[20];

};

struct tipo_cadastro{
	char nome[100];
	char login[25];
	char senha[20];
	struct tipo_adm adm; 

};
struct tipo_clube{
	char nome_clube[30];
	char cidade[30];
	char estado[2];
	char estadio[50];
	int pontos;
	int gols;
	int gols_tomados;
	int cartao_a;
	int cartao_v;
	int saldo;
	int media_gols;
	int media_tomados;
	int movimentacao;
	
};
struct tipo_rodada{
	struct tipo_clube clube[20];	
};

struct tipo_rodada rodada[38];

int total_rodadas = 0;
int total_times = 0;

struct tipo_cadastro cadastro[6];
int total = 0;

int main(){
	int adm, c_adm, x = 0, o, controladora;
	char login_digitado[25], senha_digitado[20];
	
	ler_tudo();

	adm = verificar_adm();
	
	
	if(adm == 0){
		criar_adm();
		
	}
	
	do{	
		system("cls");
		printf("\tLOGIN\n");
		printf("Login: ");
		fflush(stdin);
		gets(login_digitado);
		printf("Senha: ");
		gets(senha_digitado);

		strcat(login_digitado, "\n");
		strcat(senha_digitado, "\n");


		x = login(login_digitado, senha_digitado);

		if(x == 1){
			do{
				system("cls");
				o = menu_adm();
				
				if(o == 1){
					system("cls");
					criar_usu();
				}

				else if(o == 2){
					system("cls");
					visu_usu();
				}

				else if(o == 3){
					system("cls");
					excluir_usu();
				}

				else if(o == 4){
					escrever_tudo();
					break;
				}

				else if(o == 5){
					escrever_tudo();
					exit(0);
				}
				
			}while(o != 4);
		}
		else if(x == 2){
			controladora = busca_nome(login_digitado);

			do{
				system("cls");
				printf("\tBem vindo %s\n", cadastro[controladora].nome);
				getchar();
				o = menu_usu();

				if(o == 1){
					cadastrar_clube();
					escrever_tudo();
				}

				else if(o == 2){
					continua();
					escrever_tudo();
				}

				else if(o == 3){
					modificar(controladora);
				}
				else if(o == 4){
					configuracoes();
				}

				else if (o == 5){
					printf("Ranking\n");
					getchar();
				}

				else if(o == 6){
					escrever_tudo();
					break;
				}
				else if(o == 7){
					escrever_tudo();
					exit(0);
				}



			}while(o != 6);	
		}

	}while(1);	
	
	escrever_tudo();
	
}

void ler_tudo(){
	int i, cm;
	FILE *c;
	FILE*j;
	FILE *f;
	f = fopen("total.txt","a+");
	fscanf(f, "%d", &total);
	fscanf(f, "%d", &total_times);
	fclose(f);

	j = fopen("usuarios.txt","a+");
	fgets(cadastro[0].adm.nome_adm, 100, j);
	fgets(cadastro[0].adm.login_adm, 25, j);
	fgets(cadastro[0].adm.senha_adm, 20, j);


	for(i = 1; i < total; i++){
		fgets(cadastro[i].nome, 100, j);
		fgets(cadastro[i].login, 25, j);
		fgets(cadastro[i].senha, 20, j);

	}
	fclose(j);

	c = fopen("times.txt", "a+");

	for(i = 0; i < total_times; i++){
		fgets(rodada[total_rodada].clube[i].nome_clube, 30, c);
		fgets(rodada[total_rodada].clube[i].cidade, 30, c);
		fgets(rodada[total_rodada].clube[i].estado, 2, c);
		fgets(rodada[total_rodada].clube[i].estadio, 50, c); 
	}
	fclose(c);
}

int verificar_adm(){
	int cm;

	cm = strlen(cadastro[0].adm.nome_adm);
	return cm; 	
}
void criar_adm(){
	printf("Cadastro\n");
	printf("Qual seu nome: ");
	fflush(stdin);
	gets(cadastro[0].adm.nome_adm);
	printf("login: ");
	fflush(stdin);
	gets(cadastro[0].adm.login_adm);
	printf("Senha: ");
	fflush(stdin);
	gets(cadastro[0].adm.senha_adm);
	strcat(cadastro[0].adm.nome_adm, "\n");
	strcat(cadastro[0].adm.login_adm, "\n");
	strcat(cadastro[0].adm.senha_adm, "\n");


	total++;	
}
int login(char login_digitado[], char senha_digitado[]){

	int cmp, cmp2, y = 0, cm, cm2, i;
	
	cmp = strcmp(cadastro[0].adm.login_adm, login_digitado);		
	cmp2 = strcmp(cadastro[0].adm.senha_adm, senha_digitado);
	
	if(cmp == 0 && cmp2 == 0){
		return 1;
	}
	else{

		for(i = 1; i < total; i++){
				
			cmp = strcmp(cadastro[i].login, login_digitado);		
			cmp2 = strcmp(cadastro[i].senha, senha_digitado);

			if(cmp == 0 && cmp2 == 0){
				return 2;
			}
		}
		return 0;	
	}	
}
int menu_adm(){
	int op;
	system("cls");
	printf("\t BEM VINDO ADM %s\n",cadastro[0].adm.nome_adm );	
	printf("1.Cadastrar usuario\n");
	printf("2.visualizar usuario\n");
	printf("3.Remover usuario\n");
	printf("4.Efetuar Logoff\n");
	printf("5.Sair\n");
	scanf("%d", &op);		
	return op;
}
void criar_usu(){
	int i;

	if(total < 6){
		printf("Digite o nome para usuario: ");
		fflush(stdin);
		gets(cadastro[total].nome);
		printf("Digite o login para o usuario: ");
		fflush(stdin);
		gets(cadastro[total].login);
		printf("Digite a senha para o usuario:");
		fflush(stdin);
		gets(cadastro[total].senha);
		strcat(cadastro[total].nome, "\n");
		strcat(cadastro[total].login, "\n");
		strcat(cadastro[total].senha, "\n");
		
		total++;
		escrever_tudo();
	}
	else{
		printf("Nao e possivel cadastrar mais usuarios!!!\n");
		sleep(5);
	}	
}

void visu_usu(){
	int i;
	printf("\tUsuarios\n");
	for(i = 1; i < total; i++){
		printf("Usuario %d\n", i);
		printf("Nome: %s",cadastro[i].nome);
		printf("Login: %s",cadastro[i].login);
		printf("Senha: %s\n",cadastro[i].senha);
	}
	fflush(stdin);
	getchar();
}

void excluir_usu(){

	if(total > 0){
		total--;
		printf("Usuario excluido\n");
		sleep(3);
		escrever_tudo();
	}
	else{
		printf("Nao e possivel excluir o admin\n");
		sleep(4);
	}	
}


int busca_nome(char login_digitado[]){
	int i, indice;

	for(i = 1; i < total; i++){
		if(strcmp(cadastro[i].login, login_digitado) == 0){
			indice = i;
			break;
		}
	}
	return indice;
}
int menu_usu(){
	int op;
	printf("\n1.Cadastrar time\n");
	printf("2.Continuar\n");
	printf("3.Modificar dados\n");
	printf("4.Configuracoes\n");
	printf("5.Ranking\n");
	printf("6.Efetuar Logoff\n");
	printf("7.Sair\n");
	scanf("%d", &op);		
	return op;
}

void cadastrar_clube(){
	int cm;

	printf("Digite o nome do clube: ");
	fflush(stdin);
	gets(clube[total_times].nome_clube);
	printf("Digite a cidade: ");
	fflush(stdin);
	gets(clube[total_times].cidade);
	printf("Digite o estado: ");
	fflush(stdin);
	gets(clube[total_times].estado);
	printf("Digite o estadio: ");
	fflush(stdin);
	gets(clube[total_times].estadio);


		if(strlen(clube[total_times].nome_clube) > 0){
			strcat(clube[total_times].nome_clube, "\n");
		}
		else if(strlen(clube[total_times].cidade) > 0){
			strcat(clube[total_times].cidade, "\n");
		}
		else if(strlen(clube[total_times].estado) > 0){
			strcat(clube[total_times].estado, "\n");
		}
		else if(strlen(clube[total_times].estadio) > 0){
			strcat(clube[total_times].estadio, "\n");
		}


	total_times++;
	escrever_tudo();
}

void continua(){
	int i, cm;
	for(i = 0; i < total_times-1; i++){

		if(strlen(clube[total_times].nome_clube) == 0){
			printf("Digite novamente o nome do clube: ");
			fflush(stdin);
			gets(clube[total_times].nome_clube);
			strcat(clube[total_times].nome_clubes, "\n");
		}
		else if(strlen(clube[total_times].cidade) == 0){
			printf("Digite novamente a cidade: ");
			fflush(stdin);
			gets(clube[total_times].cidade);
			strcat(clube.[total_times].cidade, "\n");
		}
		else if(strlen(clube[total_times].estado) == 0){
			printf("Digite novamente o estado: ");
			fflush(stdin);
			gets(clube[total_times].estado);
			strcat(clube[total_times].estado, "\n");
		}
		else if(strlen(clube[total_times].estadio) == 0){
			printf("Digite novamente o estadio: ");
			fflush(stdin);
			gets(clube[total_times].estadio);
			strcat(clube[total_times].estadio, "\n");
		}
	}

}

void modificar(int controladora){
	int opçao;

	printf("Qual dado gostaria de mudar:\n");
	printf("1.Nome\n");
	printf("2.Login\n");
	printf("3.Senha\n");
	scanf("%d", &opçao);

	if(opçao == 1){
		printf("Digite o nome que gostaria: ");
		fflush(stdin);
		gets(cadastro[controladora].nome);
	}
	if(opçao == 2){
		printf("Digite o login que gostaria: ");
		fflush(stdin);
		gets(cadastro[controladora].login);
	}
	if(opçao == 3){
		printf("Digite a senha que gostaria: ");
		fflush(stdin);
		gets(cadastro[controladora].senha);
	}
	escrever_tudo();
}

void escrever_tudo(){
	int i;
	FILE *c;
	FILE*f;
	FILE*j;

	f = fopen("total.txt", "w+");
	fprintf(f, "%d\n", total);
	fprintf(f, "%d\n", total_times);

	j = fopen("usuarios.txt","w+");
	fprintf(j, "%s", cadastro[0].adm.nome_adm);
	fprintf(j, "%s", cadastro[0].adm.login_adm);
	fprintf(j, "%s", cadastro[0].adm.senha_adm);
	
	for(i = 1; i < total; i++){
		fprintf(j, "%s", cadastro[i].nome);
		fprintf(j, "%s", cadastro[i].login);
		fprintf(j, "%s", cadastro[i].senha);
	}
	fclose(j);	
	c = fopen("times.txt", "w+");

	for(i = 0; i < total_times; i++){
		fprintf(c, "%s", clube[i].nome_clube);
		fprintf(c, "%s", clube[i].cidade);
		fprintf(c, "%s", clube[i].estado);
		fprintf(c, "%s", clube[i].estadio); 
	}
	fclose(c);
}


