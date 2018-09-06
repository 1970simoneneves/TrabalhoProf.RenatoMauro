#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* cria estrutura de registro que ir� receber dos dados do arquivo*/
typedef struct _Registro Registro;

struct _Registro{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[2];
	char sobra[2];
	
	
}; 
/* cria m�todo de busca, que utiliza a busca bin�ria onde dividir� o 
arquivo em duas partes, tendo o meio como referencia. caso o registro procurado
for menor que o meio, procurar� no primeiro bloco, caso o valor seja maior que o meio,
buscar� na parte onde os valores s�o superiores ao meio, para isso o arquivo
tem que estar ordenado.*/
void procuraCep(long fim,FILE *f, char* cep){
	
	/* varivel i como contador,para saber quantas compara��es foram feitas,
	inicio inicializado com o valor 0, primeiro �ndice do arquivo, a variavel meio
	ir� receber o valor do calculo do ultimo registro - o inicio dividido por dois
	menos 1 para saber o endere�o de mem�ria do registro que ser� utilizado como pivo 
	para comparar com o registro buscado. Foi criado a variavel r que � do tipo Registro
	que receber� o conteudo o registro.
	*/
	int i = 0;
	long inicio = 0;
	long meio;
	Registro r;
	
	/* se inicio for maior que o final, o registro n�o existe ou foi achado, 
	haver� compara��o.*/
	while(inicio <=fim){
		i++; // conta as compara��es executadas.
		meio = (inicio + fim)/2; //busca o endere�o do meio do arquivo
		fseek(f,meio*sizeof(Registro),SEEK_SET); // ?posi��o absoluta.. l� o meio?
		fread(&r, sizeof(Registro),1,f);// le o endere�o do ponteiro da variavel
		// que aponta para o meio, at� o tamanho do registro.
		if(strncmp(cep, r.cep,8)== 0){
			/*strncmp.. comando para comparar string
			 se a diferen�a entre o o campo cep do registro encontrado e do
			 atributo cep do registro passado for igual a zero, significa que
			encontrou */
			
			/* achou... imprimir o registro!
			%72s formata cada atributo do registro que tem tamanho 72
			logradouro,bairro,cidade,uf.. sigla e cep ter�o os valores de
			acordo com o tamanho do campo no registro.
			*/
			printf("%.72s\n%.72s\n%.72s\n%72.s\n%2.s\n%8.s\n"
			,r.logradouro,r.bairro,r.cidade,r.uf,r.sigla,r.cep);
			
			// interrompe a execu��o do programa
			break;
			
		}else{
			/* o registro passado n�o � igual ao registro que foi comparado,
			verificar se o registro do meio e maior que o registro passado,
			recalcular  meio de maneira que a busca seja feita do meio para o inicio*/
			if(strncmp(cep,r.cep,8)>0){
				
				inicio = meio + 1;
				
				// a busca ser� realizada nos valores maiores que o meio
			}else{
				/* a busca ser� realizada nos registros que tem valores menores que
				o meio */
				fim = meio -1;
			}
			}
			} // fim do enquanto
			
			// imprimir a quantidade de compara��es
			printf("Quantidade de Compara��es:%d",i);
		} // fim do m�todo procuraCep
	
int main(int argc, char *argv[]) {
	FILE *f;  // declara ponteiro de arquivo
	Registro r; // instancia uma vari�vel com o nome r do Tipo Registro
	return 0;
	long posicao, final;
	
	/* Se a quantidade de par�metro informada for diferente de dois, enviar�
	mensagem de erro e finalizar� o programa*/
	if(argc != 2){
		 printf(stderr,"Problemas: %s[cep]",argv[0] );
		 return 1; // finaliza o programa
		 
	}
	
	// abre o arquivo cep_ordenado para leitura.. "r"
	f = fopen("cep_ordenado.dat","r");
	fseek(f,0,SEEK_END); // posiciona o cabe�ote de leitura no final do arquivo
	// afim de saber qual o tamanho do arquivo
	posicao = ftell(f); // a variavel posi��o recebe o endere�o? do tamanho do
	// arquivo.
	rewind(f); // recoloca o cabe�ote de leitura no inicio do arquivo para inicia a
	// busca.
	
	// calculo para saber qual a posi��o do meio do arquivo
	final = (posicao/sizeof(Registro))-1;
	/* pega o tamho do aquivo divide pelo tamanho do registro, tendo o valor de
	quantos resgistros existe neste arquivo, como trabalhamos com base 0 � descontado -1*/
	
	// chama a fun��o de procura passando a quantidade de registros, o arquivo
	// e o cep procurado.
	
	procuraCep(final,f,argv[1]);
	
	fclose(f); // fecha o arquivo
	return 0; // finaliza o programa
	
		}
