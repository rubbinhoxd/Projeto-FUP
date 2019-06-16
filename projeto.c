#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct{

char nome[200];
float preco;
char genero[200];
bool alugado;

}livro;

typedef struct{
	
char login[200];
char senha[200];
int livros[10];
int index;
}usuario;


void travar();
livro* add_livro(livro *v, int *n, livro novo);  //escopo para a le_livro();
usuario * add_user(usuario *p, int *qte_user, usuario novo); //escopo para a add_user


void salva_livro(livro *v, int *n){

int i;


FILE *fp = fopen ("C:\\Users\\Rubens\\Progamas C geany\\livros.txt", "w");
for(i=0;i<*n;+i++){
	fprintf(fp, "%s %s %f", v[i].nome, v[i].genero, v[i].preco);
	if(i != *n -1){
	  fprintf(fp, "\n");
	}
	}
fclose(fp);
}

int buscar_livro(int *n,livro *v, char nome[]){
	int i;
	for(i=0;i<*n;i++){
		if((strcmp(nome, v[i].nome)==0)){
			if(v[i].alugado==false){
			v[i].alugado=true;
						
				
			travar();
				return i;
			}
			else{
				printf("Livro está alugado\n");				
			}
		}
	}
	printf("Livro nao encontrado\n");	
	travar();
	return buscar_livro(n, v, nome);
}
/*
int buscar_usuario(usuario *p, int *qtd_user){
	int k;
	char user[50], senha_user[50];
	printf("Digite o login: ");
	fgets(user, sizeof(user), stdin);
	printf("Agora digite a senha: ");
	fgets(senha_user, sizeof(senha_user), stdin);
	for(k=0;k<*qtd_user;k++){
		if((strcmp(user, p[k].login)==0) && (strcmp(senha_user,p[k].senha)==0)){
			return i;
		}
	}
	printf("Usuario nao enconotrado\n");
	travar();
	return buscar_usuario(n, v, nome, p, qtd_user);
}
void emprestimo_livro(usuario *p, int *qte_user,livro *v, int *n, char nome[]){
	int emprestimo=buscar_livro(n,v, nome,p, qte_user);
	int user=buscar_usuario(p,qte_user);
	if(p[user].index==10){
		p[user].livros[p[user].index]=emprestimo;
		p[user].index++;
	}
	else{
		printf("Usuário já tem 10 livros cadastrados");
	}
	
}*/
void salva_user(usuario *p, int *qte_user){

int i;
FILE *fp = fopen ("C:\\Users\\Rubens\\Progamas C geany\\usuario.txt", "w");
for(i=0;i<*qte_user;i++){
	fprintf(fp, "%s %s", p[i].login, p[i].senha);
	if(i != *qte_user -1){
	  fprintf(fp, "\n");
	}
	}
fclose(fp);
}

usuario * le_user(usuario *p, int *qte_user){

  FILE *fp = fopen ("C:\\Users\\Rubens\\Progamas C geany\\usuario.txt", "r");
	if (fp == 0) {
      printf("Erro: nao foi possivel abrir arquivo!");
      return 0;
   }
   
	  usuario novo;
	  
	  while(fscanf(fp, "%s %s", novo.login, novo.senha) == 2){
		printf("%s, %s\n", novo.login, novo.senha); 
		p = add_user(p, qte_user, novo);
	  }
      
   
   fclose(fp);

return p;
}


livro* le_livro(livro *v, int *n){
  FILE *fp = fopen ("C:\\Users\\Rubens\\Progamas C geany\\livros.txt", "r");
	if (fp == 0) {
      printf("Erro: nao foi possivel abrir arquivo!");
      return 0;
   }
   


   livro novo;
   while (fscanf(fp, "%s %s %f", novo.nome, novo.genero, &novo.preco) == 4) {
	  printf("%s %s %f\n", novo.nome,novo.genero,novo.preco);
      v = add_livro(v, n, novo);
   }
   fclose(fp);

return v;
}

void limpar(){
	system("cls");
	printf("===================================\n");
	printf("--------------TheBooks-------------\n");
	printf("===================================\n");
	printf("===================================\n");
}
void travar(){
	char input[10];
	printf("Continuar ?\n");
	scanf("%s", input);	
}

usuario* add_user(usuario *v, int *n, usuario novo){
      v = (usuario*) realloc(v, (*n+1)*sizeof(usuario));
      if(v==0){
          return 0;
      }
      (*n)++;
      v[*n-1] = novo;
      
      return v;
}

usuario* excluir_user(usuario *v, int *n, char nome[]){
	int i;
       for(i=0;i<*n;i++){
           if(strcmp(v[i].login, nome) == 0){
               v[i] = v[*n-1];
               v = (usuario*)realloc(v, (*n-1) * sizeof(usuario));
               (*n)--;
               break;
           }
       }
       return v;
    }

void lista_user(int *n, usuario *v){
	int i;
	
	for(i=0;i<*n;i++){
		printf("Login do Usuario(s): %s\n\n", v[i].login);
		printf("Senha do Usuario(s) %s\n\n", v[i].senha);
		printf("\n");
	}
}


livro* add_livro(livro *v, int *n, livro novo){
      v = (livro*) realloc(v, (*n+1)*sizeof(livro));
      if(v==0){
          return 0;
      }
      (*n)++;
      v[*n-1] = novo;
      
      return v;
}

void lista_livro(int *n, livro *v){
	int i;
	
	for(i=0;i<*n;i++){
		printf("Nome do Livro: %s\n\n", v[i].nome);
		printf("Genero do Livro: %s\n\n", v[i].genero);
		printf("Preco do livro: %.1f\n\n", v[i].preco);
		printf("\n");
	}
}

	
	





livro* excluir_livro(livro *v, int *n, char nome[]){
	int i;
       for(i=0;i<*n;i++){
           if(strcmp(v[i].nome, nome) == 0){
               v[i] = v[*n-1];
               v = (livro*)realloc(v, (*n-1) * sizeof(livro));
               (*n)--;
               break;
           }
       }
       return v;
    }



void menu(livro *v, int *n, usuario *p, int *qte_user){


int op;


do{


limpar();
printf("Bem Vindo a loja de e-books do Rubens, Mateus e Alexandre!!\n");
printf("\n");
printf("Escolha uma dos modulos: \n");
printf("1.Adicionar Livro\n");
printf("2.Listar livro\n");
printf("3.Emprestimo de livro\n");
printf("4.Relatorio de Livros emprestados\n");
printf("5.Excluir livro\n");
printf("6.Adicionar usuario\n");
printf("7.Excluir usuario\n");
printf("8.Listar usuario(s)\n");
printf("9.Sair\n");
scanf("%d", &op); getchar();

switch(op){
	
	case 1: {
	
		livro novo;
		limpar();
		printf("Digite o nome do seu livro: ");
		fgets(novo.nome, sizeof(novo.nome), stdin);
		novo.nome[strlen(novo.nome)-1] = '\0';
		printf("Agora, digite o genero do livro: ");
		fgets(novo.genero, sizeof(novo.genero), stdin);
		novo.genero[strlen(novo.genero)-1] = '\0';
		printf("Digite o valor do exemplar: ");
		scanf("%f", &novo.preco);
		novo.alugado=false;
		v = add_livro(v, n, novo);    //Adiciona livro
		limpar();
		printf("Adicionado com sucesso!\n\n");
		travar();
		break;
    }
	case 2:{
		limpar();
		printf("Livros Disponiveis: \n");
		printf("\n");
	
		lista_livro(n, v);  //Busca Livro
		if(v==0) printf("Nao ha livros\n\n");
		travar();
		break;
	}
	case 3:{
		char livro_empresta[200];
		printf("Qual livro deseja alugar?\n");
		fgets(livro_empresta, sizeof(livro_empresta), stdin);
		//buscar_livro(n, v,livro_empresta, p, qte_user);
		break;
		
		
	}
	case 4:
		//relatorio_livro();  //Empréstimo de Livro
		break;
	case 5:{
		limpar();
		char nome[200];
		printf("Digite o nome do exemplar a ser excluido: ");
		fgets(nome,sizeof(nome), stdin);
		nome[strlen(nome)-1] = '\0';
		v = excluir_livro(v, n, nome);              //Excluir livro			
		printf("Livro excluido com sucesso!\n\n");
		travar();
		break;
	}		
	case 6:{
		usuario novo;
		limpar();
		printf("Digite o seu login: ");
		fgets(novo.login, sizeof(novo.login), stdin);
		novo.login[strlen(novo.login)-1] = '\0';
		printf("Agora, digite uma senha segura: ");
		fgets(novo.senha, sizeof(novo.senha), stdin);
		novo.senha[strlen(novo.senha)-1] = '\0';
		novo.index=0;
		p = add_user(p, qte_user, novo);    //Adiciona usuario
		limpar();
		printf("Adicionado com sucesso!\n\n");
		travar();
		break;
    }
	case 7:
	    limpar();
		char nome[200];
		printf("Digite o login do usuario a ser excluido: ");
		fgets(nome,sizeof(nome), stdin);
		nome[strlen(nome)-1] = '\0';
		p = excluir_user(p, qte_user, nome);                             //Excluir Usuario			
		printf("Usuario excluido com sucesso!\n\n");
		travar();
		break;
	case 8:{
		limpar();
		printf("Usuario(s) Disponiveis: \n");
		printf("\n");
		lista_user(qte_user, p);  //Busca Livro
		if(p==0) printf("Nao ha Usuarios!\n\n");
		travar();
		break;
	}	
	case 9:{
		salva_livro(v, n);
		salva_user(p,qte_user);
		printf("Ate mais!\n");
		printf("Contamos com a sua volta, companheiro");   
		break;
	}	
	default: 
		printf("Escolha Inválida!");
		break;   			
		}
	} while(op!=9);
}


int main() {
	
	
	usuario *p = 0;
	int qte_user = 0;
	
	p = le_user(p, &qte_user); 
	
    livro *v = 0; 
	int n = 0;
	v = le_livro(v, &n);
	
	menu(v,&n, p, &qte_user);
	
	return 0;
}
