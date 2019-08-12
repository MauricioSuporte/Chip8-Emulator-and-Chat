#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gb_opcodes.c"

static void dump(FILE *rom)
{
	size_t pc = 0;
	int op, i, s;
	union {
		uint8_t u8[2];
		uint16_t u16;
	} p;
	while (!feof(rom)) {
		op = fgetc(rom);
		if (op == EOF)
			break;
		printf("%04lx\t", pc);
		if (op == 0xcb) {
			printf("cb %02hhx     ", p.u8[0] = fgetc(rom));
			puts(opcodes[0x100 + p.u8[0]].fmt);
			pc += 2;
			continue;
		}
		s = opcodes[op].size;
		for (i = 1; i < s; i++)
			p.u8[i-1] = fgetc(rom);
		switch (s) {
		case 1:
			printf("%02hhx        ", (uint8_t) op);
			fputs(opcodes[op].fmt, stdout);
			break;
		case 2:
			printf("%02hhx %02hhx     ", (uint8_t) op, p.u8[0]);
			printf(opcodes[op].fmt, p.u8[0]);
			break;
		case 3:
			printf("%02hhx %02hhx %02hhx  ", (uint8_t) op, p.u8[0], p.u8[1]);
			printf(opcodes[op].fmt, p.u16);
			break;
		}
		fputc('\n', stdout);
		pc += s;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		puts("Usage: gb_dasm <rom_file>");
		return 0;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "Cannot open file: %s\n", argv[1]);
		return 1;
	}
	dump(f);
	fclose(f);
	return 0;
}
