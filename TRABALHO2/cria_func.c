/* Paulo_Rodrigues 1713170 3WB */
/* Luan_Ferreira 1912993 3WB */
#include <stdio.h>
#include <stdlib.h>
#include "cria_func.h"

void libera_func (void* func){free(func);}

void* cria_func(void* f, DescParam params[], int n)
{
	int ind = 0;
	unsigned long ponteiro = (unsigned long) f; 
	unsigned long variavelPonteiro, parametroPonteiro;
	//array com os parametros edi, esi e edx 
	unsigned char parametros[3] = {0xbf, 0xbe, 0xba};
	//array com os registradores
	unsigned char registradores[3] = {0xb9, 0xba, 0xbb};
	//array da movimentacao do conteúdo do pregistrador para o parametro
	unsigned char instrucao[3] = {0x39, 0x32, 0x13};
	//codigo que corresponde a nova função 
	unsigned char* codigo = (unsigned char*)malloc(sizeof(unsigned char)*512);
	if (codigo == NULL) exit(1);

	//tratando a pilha
	codigo[ind++] = 0x55;codigo[ind++] = 0x48;codigo[ind++] = 0x89;codigo[ind++] = 0xe5;

	//Para dois parâmetros trata as variáveis não amarradas.
	if (n == 2)
	{
		// mov %rdi, %rsi/mov %edi, %esi
		if (params[0].orig_val != PARAM && params[1].orig_val == PARAM)
		{
			if (params[1].tipo_val == PTR_PAR)
				codigo[ind++] = 0x48;
			codigo[ind++] = 0x89;
			codigo[ind++] = 0xfe;	
		}
	}
	//Para três parâmetros continua tratando as variáveis não amarradas.
	else if (n == 3)
	{ 
		if ((params[0].orig_val == PARAM) && (params[1].orig_val != PARAM) && (params[2].orig_val == PARAM))
		{
			//mov %esi, %edx/mov %rdi, %rdx (8 bytes)
			if (params[2].tipo_val == PTR_PAR)
				codigo[ind++] = 0x48;
			codigo[ind++] = 0x89;
			codigo[ind++] = 0xf2;
		}
		else if ((params[0].orig_val != PARAM) && (params[1].orig_val == PARAM) && (params[2].orig_val != PARAM))
		{
			//mov %edi, %esi
			if(params[2].tipo_val == PTR_PAR) 
				codigo[ind++] = 0x48;
			codigo[ind++] = 0x89;
			codigo[ind++] = 0xfe;
		}
		else if ((params[0].orig_val != PARAM) && (params[1].orig_val == PARAM) && (params[2].orig_val == PARAM))
		{
			//mov %esi, %edx
			if (params[2].tipo_val == PTR_PAR)
				codigo[ind++] = 0x48;
			codigo[ind++] = 0x89;
			codigo[ind++] = 0xf2;

			if (params[1].tipo_val == PTR_PAR)
				codigo[ind++] = 0x48;
			codigo[ind++] = 0x89;
			codigo[ind++] = 0xfe;
		}
		else if((params[0].orig_val != PARAM) && (params[1].orig_val != PARAM) && (params[2].orig_val == PARAM))
		{
			//mov %edi, %edx
			if(params[2].tipo_val == PTR_PAR) 
				codigo[ind++] = 0x48;
			codigo[ind++] = 0x89;
			codigo[ind++] = 0xfa; 
		}
	}
	for(int j = 0; j < n; j++)
	{
		//Parametro inteiro
		if(params[j].tipo_val == INT_PAR)
		{
			//Variavel fixa e inteira
			if(params[j].orig_val == FIX)
			{
				//guarda o valor no respectivo resgistrador
				codigo[ind++] = parametros[j];
				codigo[ind++] = (params[j].valor.v_int) & 0xff;
				for (int i = 1; i < 4; i++)
					codigo[ind++] = (params[j].valor.v_int >> 8*i) & 0xff;
			}
			//Variavel é o indice e inteira
			else if (params[j].orig_val == IND)
			{
				// movq $indice, (%registrador) - move o indice para o valor do ponteiro registrador
				codigo[ind++] = 0x49;
				codigo[ind++] = registradores[j];
				variavelPonteiro = (unsigned long) params[j].valor.v_ptr;
				codigo[ind++] = (variavelPonteiro) & 0xff;
				for (int i = 1; i < 8; i++)
					codigo[ind++] = (variavelPonteiro >> 8*i) & 0xff;

				//move o conteudo do ponteiro para o parametro
				codigo[ind++] = 0x41;codigo[ind++] = 0x8b;codigo[ind++] = instrucao[j];
			}
		}
		//Parametro ponteiro
		else if(params[j].tipo_val == PTR_PAR)
		{
			//Valor fixo
			if(params[j].orig_val == FIX)
			{
				//movq $fixo, (%registrador) - move valor fixo para o conteudo do registrador
				codigo[ind++] = 0x48;
				codigo[ind++] = parametros[j];
				parametroPonteiro = (unsigned long) params[j].valor.v_ptr;
				codigo[ind++] = parametroPonteiro & 0xff;
				for (int i = 1; i < 8; i++)
					codigo[ind++] = (parametroPonteiro >> 8*i) & 0xff;
			}
			//Valor indice
			//ponteiro para ponteiro variavel amarrada
			else if(params[j].orig_val == IND)
			{
				//movq $indice, (%registrador)
				codigo[ind++] = 0x49;
				codigo[ind++] = registradores[j];
				parametroPonteiro = (unsigned long) params[j].valor.v_ptr;
				codigo[ind++] = parametroPonteiro & 0xff;
				for (int i = 1; i < 8; i++)
					codigo[ind++] = (parametroPonteiro >> 8*i) & 0xff;

				//move o conteudo do ponteiro para o respectivo registrador
				codigo[ind++] = 0x49;codigo[ind++] = 0x8b;codigo[ind++] = instrucao[j];
			}
		}
	}
	//chamada da funcao
	//movq $constante, %rax
	codigo[ind++] = 0x48;codigo[ind++] = 0xb8;
	codigo[ind++] = (ponteiro) & 0xff;
	for (int i = 1; i < 8; i++)
		codigo[ind++] = (ponteiro >> 8*i) & 0xff;
	// call *%rax
	codigo[ind++] = 0xff;codigo[ind++] = 0xd0;
	//leave e ret 
	codigo[ind++] = 0xc9;codigo[ind++] = 0xc3;
	return codigo;
}









