#include <iostream>
#include <clocale>
#include <cstring>

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
 * 		Operação	Reg			Destino
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
	0x01030003,
	0x01040004,
	0x03030405, // Mult reg[3] com reg[4] e salve em reg[5]
	0x01000000, // Load reg_addr[0] em reg[0]
	0x01010001, // Load reg_addr[1] em reg[1]
	0x00000102, // Add reg[0] com reg[1] e salve em reg[2]
	0x02020002, // Store reg[2] em reg_addr[2]
};

uint32_t addr_mem[] = {
	9, 4, 0, 2, 4, 0, 0, 0,
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
	
	// Zerar os registradores e o PC
	memset(reg, 8, sizeof(uint32_t));
	pc = 0;
	
	while (pc < 7)
	{
		instr = prog_mem[pc];
		decode();
		execute();
		pc++;
	}
	
	return 0;
}
