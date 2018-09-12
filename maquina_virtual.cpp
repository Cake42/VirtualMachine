#include <iostream>
#include <clocale>

using namespace std;

/**
 * 		Alunos:
 * 			Flávio Brusamolin Brito - 1249
 * 			Heitor Toledo Lassarote de Paula - 1241
 * 			Leonardo Eufrazio Nogueira - 1221
 * 
 * 		Tamanho das instruções: 32-bits
 * 
 *		ADD			0000 0000
 * 		LOAD		0000 0001
 * 		STORE		0000 0010
 * 		MUL			0000 0011
 * 
 * 		Instruções tipo 1:
 * 
 * 		Operação	Reg. 1		Reg. 2		Destino
 * 		8 bits		8 bits		8 bits		8 bits
 * 
 * 		Instruções tipo 2:
 * 
 * 		Operação	Reg			Memória
 * 		8 bits		8 bits		16 bits
 */

/* Program counter */
uint32_t pc;
/* Instrução atual */
uint32_t instr;
/* Tipo de instrução */
uint32_t instr_type;
/* Registrador A */
uint32_t reg_a;
/* Registrador B */
uint32_t reg_b;
/* Registrador destino */
uint32_t reg_dest;
/* Registrador endereço de memória */
uint32_t reg_addr;
/* Registrador de propósito geral */
uint32_t reg[8];
/* Memória de programa */
uint32_t prog_mem[] = {
	0x01000000, // Carrega mem[0] em reg[0]
	0x01010001, // Carrega mem[1] em reg[1]
	0x00000102, // Soma reg[0] com reg[1] em reg[2]
	0x01030002, // Carrega mem[2] em reg[3]
	0x03020302, // Multiplica reg[2] com reg[3] em reg[2]
	0x02020003, // Salva reg[2] em mem[3]
};

uint32_t addr_mem[] = {
	2, 3, 10, 0, 0, 0, 0, 0,
};

void decode()
{
	// Pegando o tipo de instrução
	instr_type = instr >> 24;
	switch (instr_type)
	{
		// ADD
		case 0x00:
		// MUL
		case 0x03:
			reg_a 	 = (instr & 0x00FF0000) >> 16;
			reg_b 	 = (instr & 0x0000FF00) >>  8;
			reg_dest = (instr & 0x000000FF) >>  0;
			break;
		// LOAD
		case 0x01:
			reg_dest = (instr & 0x00FF0000) >> 16;
			reg_addr = (instr & 0x0000FFFF) >>  0;
			break;
		// STORE
		case 0x02:
			reg_a 	 = (instr & 0x00FF0000) >> 16;
			reg_addr = (instr & 0x0000FFFF) >>  0;
			break;
		default:
			cout << instr_type << ": instrução ilegal" << endl;
			break;
	}
}

void execute()
{
	switch (instr_type)
	{
		// ADD
		case 0x00:
			reg[reg_dest] = reg[reg_a] + reg[reg_b];
			cout << "Add: " << reg[reg_dest] << endl;
			break;
		// LOAD
		case 0x01:
			reg[reg_dest] = addr_mem[reg_addr];
			cout << "Load: " << reg[reg_dest] << endl;
			break;
		// STORE
		case 0x02:
			addr_mem[reg_addr] = reg[reg_a];
			cout << "Store: " << addr_mem[reg_addr] << endl;
			break;
		// MUL
		case 0x03:
			reg[reg_dest] = reg[reg_a] * reg[reg_b];
			cout << "Mul: " << reg[reg_dest] << endl;
			break;
	}
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	pc = 0;
	
	while (pc < 6)
	{
		instr = prog_mem[pc];
		decode();
		execute();
		pc++;
	}
	
	return 0;
}
