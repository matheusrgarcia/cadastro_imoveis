/*Sistema de Cadastro de Imóveis residencias à venda.

1)Menu:	
	a)Cadastro de um novo imóvel.(String) OK
	b)Retirada de um imóvel do cadastro. OK
	c)Pesquisa de Imóveis. OK
	d)Sair do Programa. 
	
2)Dados dos imóveis(Minímo 5 dados):d
	a)Preço do imóvel.(Float) OK
	b)Quantidade de quartos do imóvel.(Int)OK
	c)Bairro do Imóvel.(String). OK
	d)Endereço do Imóvel.(String)OK
	e)Área do imóvel em metros quadrados.(Float)OK
	f)Vagas na garagem.(Int)OK
	g)Código referente ao Imóvel(Int).OK
	

3)Opções de pesquisa(Minímo de 3 opções de pesquisa): OK
	1) Leva em consideração um critério de pesquisa:
		ex: Pesquisar pelo Código do imóvel. OK
	2)Leva em consideração dois critérios de pesquisa:
		ex: Pesquisar pelo preço do imóvel e Bairro do imóvel. OK
		ex2: Pesquisar pela Quantidade de quartos do imóvel e Área minima do imóvel. OK
		
4)Ao solicitar a saída do programa deverá aparecer um relatório em tela contendo:
	-A quantidade de novos imóveis adicionados.( ContImoveis ) OK
	-A quantidade de imóveis retirados do cadastro. OK
	-O valor total recebido em comissão durante o periódo em que o programa esteve em execução, ou seja, 1% do valor
	de cada imóvel retirado do programa.
*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>

void opcao(int *cont, int *contRet, float *comissao); // OK (Declaração dos contadores utlizados + comissão).
void cadastro(int *cont); //OK (Cadastro entra o primeiro contador de entrada).
void pesquisa(); // OK
void pesquisaCodigo(); // OK
void pesquisaPrecoBairro(); // OK
void pesquisaQuartosArea(); // OK
float retirada(int *contRet, float *comissao); // OK (Retirada precisa do contador de saida + valor da comissao).
void relatorio(int cont, int contRet, float comissao);  // OK (Relatório precisa receber os três valores salvos nos contadores e na comissão).

struct tImovel{
		float custo; //preço.
		int quartos; // Quantidade de quartos.
		char bairro[60]; // Bairro.
		char endereco[60]; // Endereço.
		float area; // Área em metros quadrados.
		int vagas; // Quantidade de vagas na garagem.
	 	int codigo; //Código referente ao Imóvel.
		int validar;	
	};

FILE *arq; // Apontador para o arquivo Global

struct tImovel imovel; // declaração da estrutura

int main(){	 
	
	int cont=0;  // INICIALIZAÇÃO DO PRIMEIRO CONTADOR(ENTRADA)
	int contRet=0;  // INICIALIZAÇÃO DO SEGUNDO CONTADOR(RETIRADA)
	float comissao=0; // INICIALIZAÇÃO PARA O VALOR DA COMISSAO = 0.

	setlocale(LC_ALL,"Portuguese"); // ACEITAR ACENTOS / CARACTERES ESPECIAIS EM PT-BR.

	opcao(&cont, &contRet, &comissao); // MENU
	relatorio(cont, contRet, comissao); // EXECUTA AO SAIR DE OPÇÃO, NO CASO SE O USUÁRIO DIGITAR 4.(Recebe os valores dos contadores/comissao).
	
	system("PAUSE");
	
}


void opcao(int *cont, int *contRet, float *comissao){ 
	
	int op=1, x=0;
	
	arq = fopen("database.txt","a+"); // SENÃO N IRIA FUNCIONAR A PARTE DE NÃO HÁ IMOVEL CADASTRADO, JÁ QUE NÃO EXISTIRIA ARQUIVO.
		fclose(arq);
				
	do{
		printf("\n\t\tSistema para cadastro de Imóveis\n");
		printf("\n");
		printf("1) Cadastro de um novo imóvel\n");
		printf("2) Pesquisa de Imóveis\n");
		printf("3) Retirada de um imóvel do cadastro\n");
		printf("4) Sair do Programa\n");
		printf("\n");
		printf("Digite a opção desejada:");
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
			printf("\t\tFim de execução do programa\n");
			printf("Relatório:\n\n");
			break;
		default:
			system("cls");
			printf("Opção inválida!\n");
			printf("Digite uma opção válida\n");
			break;
	}
}
	while(op!=4);
}

void cadastro(int *cont){
	int codigo;
	FILE *arq;
	
	printf("\t\t\tCadastro de Imóvel");
	arq = fopen("database.txt","a+");
		fclose(arq);
//PARTE DO FREAD (PARA VER SE JÁ TEM O CÓDIGO)		
	arq = fopen("database.txt","r"); // abre o arquivo para editar e salvar no sempre no fim do arquivo
	
	printf("\nCódigo referente ao Imóvel:\n");
		fflush(stdin);
			scanf("%d", &codigo);

	fread(&imovel, sizeof(struct tImovel), 1, arq);	
	
		while(!feof(arq)){
				if(imovel.codigo == codigo){
					printf("Já existe um imóvel cadastrado com este código!\n");
					printf("\nCódigo referente ao Imóvel:\n");
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
		
	printf("\nPreço do Imóvel:\n");
		fflush(stdin);
			scanf("%f", &imovel.custo);
			
	printf("\nQuantidade de quartos:\n");
		fflush(stdin);
			scanf("%d", &imovel.quartos);
			
			
	printf("\nBairro do Imóvel:\n");
		fflush(stdin);
			gets(imovel.bairro);
			
		
	printf("\nEndereço do Imóvel:\n");
		fflush(stdin);	
			gets(imovel.endereco);
			
			
	printf("\nÁrea em metros quadrados do Imóvel:\n");
		fflush(stdin);
			scanf("%f", &imovel.area);
			
			
	printf("\nQuantidade de vagas na garagem:\n");
		fflush(stdin);
			scanf("%d", &imovel.vagas);
		
		fwrite(&imovel, sizeof(struct tImovel), 1, arq); // escreve as informações salvas nos scanfs/gets
		fclose(arq); // fecha o arquivo
		system("cls");	
}

void pesquisa(){
	
	int op=1;
	
	do{
		printf("\n\t\t\tMenu de Pesquisa\n\n");
	printf("1) Pesquisar pelo Código do imóvel\n");
	printf("2) Pesquisar pelo Bairro do imóvel e preço mínimo do imóvel\n");
	printf("3) Pesquisar pela Quantidade de quartos do imóvel e Área minima do imóvel\n");
	printf("4) Voltar ao Menu inicial\n");
	printf("\n");
	printf("Digite a opção desejada: ");
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
				printf("Opção inválida!\n");
				printf("Digite uma opção válida\n");
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
	
	printf("Digite o código do imóvel a ser excluído\n");
		printf("Código:");
			scanf("%d", &selec);
		
	fread(&imovel, sizeof(struct tImovel), 1, arq);
	
	if(feof(arq)){
		system("cls");
		printf("Não há nenhum imóvel cadastrado no momento!\n");
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
	
	fread(&imovel, sizeof(struct tImovel), 1, arq); // lê o arquivo
	
	
	if(feof(arq)){ // Retorna VERDADE se chegou ao fim do arquivo = Não ter nada salvo (BUGADO)
		printf("Ainda não há nenhum imóvel cadastrado no momento!!\n");
	}
		
	else{ // Se houver algo salvo ele ira executar o else
		printf("Digite o Código do imóvel:");
			scanf("%d", &selec);
				fflush(stdin);	
				
			while(!feof(arq)){ // Se for 0 ira entrar no if
				if(selec==imovel.codigo){
					if(imovel.validar==1){
						printf("\n");
						printf("\t\tImoveis com este padrão\n");
						printf("\nPreço do Imóvel:");
							printf("%.2f R$\n", imovel.custo);
			
						printf("\nQuantidade de quartos:");		
							printf("%d Quartos\n", imovel.quartos); 
				
						printf("\nBairro do Imóvel:");	
							printf("%s\n", imovel.bairro);
			
						printf("\nEndereço do Imóvel:");		
							printf("%s\n", imovel.endereco);
			
						printf("\nÁrea do Imóvel:");		
							printf("%.2f m²\n", imovel.area);
			
						printf("\nQuantidade de vagas na garagem:");	
							printf("%d\n", imovel.vagas);
		
						printf("\nCódigo referente ao Imóvel:");	
							printf("%d\n", imovel.codigo);	
					}
					else{
						system("cls");
						printf("Código de registro inválido!");
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
		printf("Ainda não há nenhum imóvel cadastrado no momento!!\n");
	}
	
	else{ 
		printf("\nDigite o bairro desejado:");
			fflush(stdin);
				gets(bairro);
				
		printf("\nDigite o preço mínimo do imóvel:");
			scanf("%d", &preco);
				fflush(stdin);
				
		while(!feof(arq)){
			if(strcmp(bairro, imovel.bairro)==0){
				if(imovel.custo >= preco){
					if(imovel.validar==1){
						printf("\n");
						printf("\t\tImoveis com este padrão\n");
						printf("\nPreço do Imóvel:");
							printf("%.2f R$\n", imovel.custo);
			
						printf("\nQuantidade de quartos:");		
							printf("%d Quartos\n", imovel.quartos); 
				
						printf("\nBairro do Imóvel:");	
							printf("%s\n", imovel.bairro);
							
						printf("\nEndereço do Imóvel:");		
							printf("%s\n", imovel.endereco);
			
						printf("\nÁrea do Imóvel:");		
							printf("%.2f m²\n", imovel.area);
				
						printf("\nQuantidade de vagas na garagem:");	
							printf("%d\n", imovel.vagas);
		
						printf("\nCódigo referente ao Imóvel:");	
							printf("%d\n", imovel.codigo);	
					}
				}	
				else{
					printf("Não há imóvel com este preço mínimo!\n");
				}	
			fread(&imovel, sizeof(struct tImovel), 1, arq);	
			}
			else{
				printf("Não há imóvel cadastrado neste bairro!\n");
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
		printf("Ainda não há nenhum imóvel cadastrado no momento!!\n");
	}
	
	else{
		printf("Digite a quantidade de quartos desejada:");
			scanf("%d", &quantQuartos);
			
		printf("Digite a área mínima desejada para o imóvel:");
			scanf("%f", &areaMin);
			
		if(imovel.validar==1){
			while(!feof(arq)){
				if(quantQuartos == imovel.quartos){
					if(areaMin <= imovel.area){
						printf("\n");
						printf("\t\tImoveis com este padrão\n");
						printf("\nPreço do Imóvel:");
							printf("%.2f R$\n", imovel.custo);
			
						printf("\nQuantidade de quartos:");		
							printf("%d Quartos\n", imovel.quartos); 
					
						printf("\nBairro do Imóvel:");	
							printf("%s\n", imovel.bairro);
			
						printf("\nEndereço do Imóvel:");		
							printf("%s\n", imovel.endereco);
			
						printf("\nÁrea do Imóvel:");		
							printf("%.2f m²\n", imovel.area);
			
						printf("\nQuantidade de vagas na garagem:");	
							printf("%d\n", imovel.vagas);
		
						printf("\nCódigo referente ao Imóvel:");	
							printf("%d\n", imovel.codigo);	
					}
					else{
						printf("Não há imóvel com esta área mínima!\n");
					}	
				}
				else{
					printf("Não há imóvel com esta quantidade de quartos!\n");
				}
			fread(&imovel, sizeof(struct tImovel), 1, arq);	
			}
		}
	}
	fclose(arq);
}

void relatorio(int cont, int contRet, float comissao){	

	printf("\t%d novos imóveis foram adicionados desde a execução do programa!\n", cont);
	printf("\t%d imóveis foram retirados desde a execução do programa!\n", contRet);
	printf("\tA comissão recebida desde a execução do programa foi de R$ %.2f!\n\n", comissao);
}

