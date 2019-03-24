/*Sistema de Cadastro de Im�veis residencias � venda.

1)Menu:	
	a)Cadastro de um novo im�vel.(String) OK
	b)Retirada de um im�vel do cadastro. OK
	c)Pesquisa de Im�veis. OK
	d)Sair do Programa. 
	
2)Dados dos im�veis(Min�mo 5 dados):d
	a)Pre�o do im�vel.(Float) OK
	b)Quantidade de quartos do im�vel.(Int)OK
	c)Bairro do Im�vel.(String). OK
	d)Endere�o do Im�vel.(String)OK
	e)�rea do im�vel em metros quadrados.(Float)OK
	f)Vagas na garagem.(Int)OK
	g)C�digo referente ao Im�vel(Int).OK
	

3)Op��es de pesquisa(Min�mo de 3 op��es de pesquisa): OK
	1) Leva em considera��o um crit�rio de pesquisa:
		ex: Pesquisar pelo C�digo do im�vel. OK
	2)Leva em considera��o dois crit�rios de pesquisa:
		ex: Pesquisar pelo pre�o do im�vel e Bairro do im�vel. OK
		ex2: Pesquisar pela Quantidade de quartos do im�vel e �rea minima do im�vel. OK
		
4)Ao solicitar a sa�da do programa dever� aparecer um relat�rio em tela contendo:
	-A quantidade de novos im�veis adicionados.( ContImoveis ) OK
	-A quantidade de im�veis retirados do cadastro. OK
	-O valor total recebido em comiss�o durante o peri�do em que o programa esteve em execu��o, ou seja, 1% do valor
	de cada im�vel retirado do programa.
*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>

void opcao(int *cont, int *contRet, float *comissao); // OK (Declara��o dos contadores utlizados + comiss�o).
void cadastro(int *cont); //OK (Cadastro entra o primeiro contador de entrada).
void pesquisa(); // OK
void pesquisaCodigo(); // OK
void pesquisaPrecoBairro(); // OK
void pesquisaQuartosArea(); // OK
float retirada(int *contRet, float *comissao); // OK (Retirada precisa do contador de saida + valor da comissao).
void relatorio(int cont, int contRet, float comissao);  // OK (Relat�rio precisa receber os tr�s valores salvos nos contadores e na comiss�o).

struct tImovel{
		float custo; //pre�o.
		int quartos; // Quantidade de quartos.
		char bairro[60]; // Bairro.
		char endereco[60]; // Endere�o.
		float area; // �rea em metros quadrados.
		int vagas; // Quantidade de vagas na garagem.
	 	int codigo; //C�digo referente ao Im�vel.
		int validar;	
	};

FILE *arq; // Apontador para o arquivo Global

struct tImovel imovel; // declara��o da estrutura

int main(){	 
	
	int cont=0;  // INICIALIZA��O DO PRIMEIRO CONTADOR(ENTRADA)
	int contRet=0;  // INICIALIZA��O DO SEGUNDO CONTADOR(RETIRADA)
	float comissao=0; // INICIALIZA��O PARA O VALOR DA COMISSAO = 0.

	setlocale(LC_ALL,"Portuguese"); // ACEITAR ACENTOS / CARACTERES ESPECIAIS EM PT-BR.

	opcao(&cont, &contRet, &comissao); // MENU
	relatorio(cont, contRet, comissao); // EXECUTA AO SAIR DE OP��O, NO CASO SE O USU�RIO DIGITAR 4.(Recebe os valores dos contadores/comissao).
	
	system("PAUSE");
	
}


void opcao(int *cont, int *contRet, float *comissao){ 
	
	int op=1, x=0;
	
	arq = fopen("database.txt","a+"); // SEN�O N IRIA FUNCIONAR A PARTE DE N�O H� IMOVEL CADASTRADO, J� QUE N�O EXISTIRIA ARQUIVO.
		fclose(arq);
				
	do{
		printf("\n\t\tSistema para cadastro de Im�veis\n");
		printf("\n");
		printf("1) Cadastro de um novo im�vel\n");
		printf("2) Pesquisa de Im�veis\n");
		printf("3) Retirada de um im�vel do cadastro\n");
		printf("4) Sair do Programa\n");
		printf("\n");
		printf("Digite a op��o desejada:");
			scanf("%d",&op);
			
		system("cls");
		
	switch(op){
		
		case 1: cadastro(&*cont);  //COLOCADO &*
			break;
		case 2: pesquisa();
			break;
		case 3: (*comissao) = retirada(&*contRet, &*comissao); //COLOCADO &*
			break;
		case 4: 
			printf("\t\tFim de execu��o do programa\n");
			printf("Relat�rio:\n\n");
			break;
		default:
			system("cls");
			printf("Op��o inv�lida!\n");
			printf("Digite uma op��o v�lida\n");
			break;
	}
}
	while(op!=4);
}

void cadastro(int *cont){
	int codigo;
	FILE *arq;
	
	printf("\t\t\tCadastro de Im�vel");
	arq = fopen("database.txt","a+");
		fclose(arq);
//PARTE DO FREAD (PARA VER SE J� TEM O C�DIGO)		
	arq = fopen("database.txt","r"); // abre o arquivo para editar e salvar no sempre no fim do arquivo
	
	printf("\nC�digo referente ao Im�vel:\n");
		fflush(stdin);
			scanf("%d", &codigo);

	fread(&imovel, sizeof(struct tImovel), 1, arq);	
	
		while(!feof(arq)){
				if(imovel.codigo == codigo){
					printf("J� existe um im�vel cadastrado com este c�digo!\n");
					printf("\nC�digo referente ao Im�vel:\n");
					scanf("%d", &codigo);
					rewind(arq);
				}
					
				fread(&imovel, sizeof(struct tImovel), 1, arq);	
		}
	
		fclose(arq);
		
//PARTE DO FWRITE

	arq = fopen("database.txt","a+");

	(*cont)++;
	imovel.validar = 1;
	imovel.codigo = codigo;
		
	printf("\nPre�o do Im�vel:\n");
		fflush(stdin);
			scanf("%f", &imovel.custo);
			
	printf("\nQuantidade de quartos:\n");
		fflush(stdin);
			scanf("%d", &imovel.quartos);
			
			
	printf("\nBairro do Im�vel:\n");
		fflush(stdin);
			gets(imovel.bairro);
			
		
	printf("\nEndere�o do Im�vel:\n");
		fflush(stdin);	
			gets(imovel.endereco);
			
			
	printf("\n�rea em metros quadrados do Im�vel:\n");
		fflush(stdin);
			scanf("%f", &imovel.area);
			
			
	printf("\nQuantidade de vagas na garagem:\n");
		fflush(stdin);
			scanf("%d", &imovel.vagas);
		
		fwrite(&imovel, sizeof(struct tImovel), 1, arq); // escreve as informa��es salvas nos scanfs/gets
		fclose(arq); // fecha o arquivo
		system("cls");	
}

void pesquisa(){
	
	int op=1;
	
	do{
		printf("\n\t\t\tMenu de Pesquisa\n\n");
	printf("1) Pesquisar pelo C�digo do im�vel\n");
	printf("2) Pesquisar pelo Bairro do im�vel e pre�o m�nimo do im�vel\n");
	printf("3) Pesquisar pela Quantidade de quartos do im�vel e �rea minima do im�vel\n");
	printf("4) Voltar ao Menu inicial\n");
	printf("\n");
	printf("Digite a op��o desejada: ");
			scanf("%d",&op);
			
		switch(op){
			case 1: pesquisaCodigo();
					break;
			case 2: pesquisaPrecoBairro();
				break;
			case 3: pesquisaQuartosArea();
					break;
			case 4: system("cls");
					break;
			default:
				system("cls");
				printf("Op��o inv�lida!\n");
				printf("Digite uma op��o v�lida\n");
				break;
		}
	}
	while(op !=4);
}

float retirada(int *contRet, float *comissao){ 

	int selec;
	float comissao1=0;
	
	system("cls");
	
	arq = fopen("database.txt","r+");
	
	printf("Digite o c�digo do im�vel a ser exclu�do\n");
		printf("C�digo:");
			scanf("%d", &selec);
		
	fread(&imovel, sizeof(struct tImovel), 1, arq);
	
	if(feof(arq)){
		system("cls");
		printf("N�o h� nenhum im�vel cadastrado no momento!\n");
	}
	while(!feof(arq)){
		 if(imovel.codigo == selec){
		 	(*contRet)++; //EDITADO: TEM QUE COLOCAR DENTRO DO WHILE O CONTADOR
			imovel.validar=0;
			fseek(arq, -1*sizeof(imovel), SEEK_CUR);
			fwrite(&imovel, sizeof(struct tImovel), 1, arq);
			fseek(arq, 0*sizeof(imovel), SEEK_CUR);
			
			comissao1 = (*comissao) + imovel.custo/100;
		}
		fread(&imovel, sizeof(struct tImovel), 1, arq);
	}
	
	fclose(arq);
	
	return comissao1;
}

void pesquisaCodigo(){ 
	
	system("cls");
	
	int selec;
	
	FILE *arq;

	arq = fopen("database.txt","r"); // Abre o arquivo para leitura 
	
	fread(&imovel, sizeof(struct tImovel), 1, arq); // l� o arquivo
	
	
	if(feof(arq)){ // Retorna VERDADE se chegou ao fim do arquivo = N�o ter nada salvo (BUGADO)
		printf("Ainda n�o h� nenhum im�vel cadastrado no momento!!\n");
	}
		
	else{ // Se houver algo salvo ele ira executar o else
		printf("Digite o C�digo do im�vel:");
			scanf("%d", &selec);
				fflush(stdin);	
				
			while(!feof(arq)){ // Se for 0 ira entrar no if
				if(selec==imovel.codigo){
					if(imovel.validar==1){
						printf("\n");
						printf("\t\tImoveis com este padr�o\n");
						printf("\nPre�o do Im�vel:");
							printf("%.2f R$\n", imovel.custo);
			
						printf("\nQuantidade de quartos:");		
							printf("%d Quartos\n", imovel.quartos); 
				
						printf("\nBairro do Im�vel:");	
							printf("%s\n", imovel.bairro);
			
						printf("\nEndere�o do Im�vel:");		
							printf("%s\n", imovel.endereco);
			
						printf("\n�rea do Im�vel:");		
							printf("%.2f m�\n", imovel.area);
			
						printf("\nQuantidade de vagas na garagem:");	
							printf("%d\n", imovel.vagas);
		
						printf("\nC�digo referente ao Im�vel:");	
							printf("%d\n", imovel.codigo);	
					}
					else{
						system("cls");
						printf("C�digo de registro inv�lido!");
					}
				}
				fread(&imovel, sizeof(struct tImovel), 1, arq);	
			}
	}
	fclose(arq);
}

void pesquisaPrecoBairro(){
		
	system("cls");	
		
	int preco;
	
	char bairro[60];
		
	FILE *arq;
	
	arq = fopen("database.txt","r");
	
    fread(&imovel, sizeof(struct tImovel), 1, arq);
    
    if(feof(arq)){ 
		printf("Ainda n�o h� nenhum im�vel cadastrado no momento!!\n");
	}
	
	else{ 
		printf("\nDigite o bairro desejado:");
			fflush(stdin);
				gets(bairro);
				
		printf("\nDigite o pre�o m�nimo do im�vel:");
			scanf("%d", &preco);
				fflush(stdin);
				
		while(!feof(arq)){
			if(strcmp(bairro, imovel.bairro)==0){
				if(imovel.custo >= preco){
					if(imovel.validar==1){
						printf("\n");
						printf("\t\tImoveis com este padr�o\n");
						printf("\nPre�o do Im�vel:");
							printf("%.2f R$\n", imovel.custo);
			
						printf("\nQuantidade de quartos:");		
							printf("%d Quartos\n", imovel.quartos); 
				
						printf("\nBairro do Im�vel:");	
							printf("%s\n", imovel.bairro);
							
						printf("\nEndere�o do Im�vel:");		
							printf("%s\n", imovel.endereco);
			
						printf("\n�rea do Im�vel:");		
							printf("%.2f m�\n", imovel.area);
				
						printf("\nQuantidade de vagas na garagem:");	
							printf("%d\n", imovel.vagas);
		
						printf("\nC�digo referente ao Im�vel:");	
							printf("%d\n", imovel.codigo);	
					}
				}	
				else{
					printf("N�o h� im�vel com este pre�o m�nimo!\n");
				}	
			fread(&imovel, sizeof(struct tImovel), 1, arq);	
			}
			else{
				printf("N�o h� im�vel cadastrado neste bairro!\n");
				pesquisa();
			}
		}
		fclose(arq);
	}
}

void pesquisaQuartosArea(){
	
	system("cls");	
		
	int quantQuartos;
	float areaMin;
	
	FILE *arq;
	
	arq = fopen("database.txt","r");
	
    fread(&imovel, sizeof(struct tImovel), 1, arq);
    
    if(feof(arq)){ 
    	system("cls");
		printf("Ainda n�o h� nenhum im�vel cadastrado no momento!!\n");
	}
	
	else{
		printf("Digite a quantidade de quartos desejada:");
			scanf("%d", &quantQuartos);
			
		printf("Digite a �rea m�nima desejada para o im�vel:");
			scanf("%f", &areaMin);
			
		if(imovel.validar==1){
			while(!feof(arq)){
				if(quantQuartos == imovel.quartos){
					if(areaMin <= imovel.area){
						printf("\n");
						printf("\t\tImoveis com este padr�o\n");
						printf("\nPre�o do Im�vel:");
							printf("%.2f R$\n", imovel.custo);
			
						printf("\nQuantidade de quartos:");		
							printf("%d Quartos\n", imovel.quartos); 
					
						printf("\nBairro do Im�vel:");	
							printf("%s\n", imovel.bairro);
			
						printf("\nEndere�o do Im�vel:");		
							printf("%s\n", imovel.endereco);
			
						printf("\n�rea do Im�vel:");		
							printf("%.2f m�\n", imovel.area);
			
						printf("\nQuantidade de vagas na garagem:");	
							printf("%d\n", imovel.vagas);
		
						printf("\nC�digo referente ao Im�vel:");	
							printf("%d\n", imovel.codigo);	
					}
					else{
						printf("N�o h� im�vel com esta �rea m�nima!\n");
					}	
				}
				else{
					printf("N�o h� im�vel com esta quantidade de quartos!\n");
				}
			fread(&imovel, sizeof(struct tImovel), 1, arq);	
			}
		}
	}
	fclose(arq);
}

void relatorio(int cont, int contRet, float comissao){	

	printf("\t%d novos im�veis foram adicionados desde a execu��o do programa!\n", cont);
	printf("\t%d im�veis foram retirados desde a execu��o do programa!\n", contRet);
	printf("\tA comiss�o recebida desde a execu��o do programa foi de R$ %.2f!\n\n", comissao);
}

