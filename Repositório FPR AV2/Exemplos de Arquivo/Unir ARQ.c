
	Quest�o 06:
	Desenvolver uma fun��o que, dados dois arquivos textos arqA e arqB, crie um novo
	arquivo arqC, considerando que:
		- arqA e arqB cont�m n�meros reais, um por linha, ordenados crescentemente e
		  sem repeti��o no arquivo;
		- arqC deve conter todos os n�meros dos dois arquivos originais;
		- Assim como arqA e arqB, arqC tamb�m n�o possuir� repeti��es de elementos e
		  estes dever�o estar ordenados de forma crescente.
*/

//importa��o de bibliotecas
#include <stdio.h>

//defini��o de constantes
#define TRUE 1
#define FALSE 0

//prot�tipos das fun��es
int uniaoArquivos (char nomeArqA[], char nomeArqB[], char nomeArqC[]);

//main
void main ()
{
	//declara��o de arquivos
	char nomeArquivoA[30], nomeArquivoB[30], nomeArquivoC[30];
	int retorno;

	//lendo o nome do arquivo A
	printf ("Entre com o nome do primeiro arquivo: ");
	fflush (stdin);
	gets (nomeArquivoA);

	//lendo o nome do arquivo B
	printf ("Entre com o nome do segundo arquivo: ");
	fflush (stdin);
	gets (nomeArquivoB);

	//lendo o nome do arquivo uni�o
	printf ("Entre com o nome do arquivo uniao a ser gerado: ");
	fflush (stdin);
	gets (nomeArquivoC);

	//chamando a fun��o
	retorno = uniaoArquivos (nomeArquivoA, nomeArquivoB, nomeArquivoC);

	//exibindo o resultado
	if (retorno == TRUE)
	{
		printf ("\nArquivo uniao gerado com sucesso.");
	}
	else
	{
		printf ("\nErro na abertura dos arquivos.");
	}
}

//implementa��o das fun��es
int uniaoArquivos (char nomeArqA[], char nomeArqB[], char nomeArqC[])
{
	//declara��o de vari�veis
	FILE *arqA, *arqB, *arqC;
	int num1, num2;
	int continuarA = TRUE, continuarB = TRUE;

	//abrindo os arquivos
	arqA = fopen (nomeArqA, "r");
	arqB = fopen (nomeArqB, "r");
	arqC = fopen (nomeArqC, "w");

	//verificar se houve erro na abertura do arquivo
	if ((arqA == NULL) || (arqB == NULL) || (arqC == NULL))
	{
		//garantindo que os arquivos ser�o fechados, visto que o erro pode ter ocorrido em apenas um, por exemplo
		fclose (arqA);
		fclose (arqB);
		fclose (arqC);

		//retornando FALSE para informar que houve erro na abertura dos arquivos
		return FALSE;
	}
	else
	{
		//lendo o primeiro elemento de cada arquivo
		if (fscanf (arqA,"%d",&num1) == EOF)
		{
			continuarA = FALSE;
		}

		if (fscanf (arqB,"%d",&num2) == EOF)
		{
			continuarB = FALSE;
		}

		//enquanto n�o se chegar ao final do primeiro ou do segundo arquivo ...
		while ((continuarA == TRUE) && (continuarB == TRUE))
		{
			//comparando os valores de num1 e num2
			if (num1 < num2)
			{
				//escrevendo o menor elemento no arquivo uni�o
				fprintf (arqC, "%d\n", num1);

				//lendo o pr�ximo elemento do primeiro arquivo
				if (fscanf (arqA,"%d",&num1) == EOF)
				{
					continuarA = FALSE;
				}
			}
			else
			{
				if (num2 < num1)
				{
					//escrevendo o menor elemento no arquivo uni�o
					fprintf (arqC, "%d\n", num2);

					//lendo o pr�ximo elemento do segundo arquivo
					if (fscanf (arqB,"%d",&num2) == EOF)
					{
						continuarB = FALSE;
					}
				}
				else
				{
					//num1 == num2

					//escrevendo o elemento no arquivo uni�o
					fprintf (arqC, "%d\n", num1);  //ou num2

					//lendo o pr�ximo elemento de cada arquivo
					if (fscanf (arqA,"%d",&num1) == EOF)
					{
						continuarA = FALSE;
					}

					if (fscanf (arqB,"%d",&num2) == EOF)
					{
						continuarB = FALSE;
					}
				}
			}
		}

		//verificando se algum dos arquivos ainda cont�m valores
		if ((continuarA == TRUE) || (continuarB == TRUE))
		{
			//verificar se ainda existem elementos no arquivo A
			//caso existam, copiar para o arquivo Uni�o os n�meros remanescentes em A
			if (continuarA == TRUE)
			{
				do
				{
					fprintf (arqC, "%d\n", num1);
				}
				while (fscanf (arqA, "%d", &num1) != EOF);
			}
			else
			{
				do
				{
					fprintf (arqC, "%d\n", num2);
				}
				while (fscanf (arqB, "%d", &num2) != EOF);

			}
		}

		//fechando os arquivos
		fclose (arqA);
		fclose (arqB);
		fclose (arqC);

		return TRUE;
	}
}
