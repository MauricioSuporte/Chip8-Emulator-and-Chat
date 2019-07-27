#include <stdbool.h>

#include "gb_opcodes.h"

#define F_ZERO      0x80
#define F_SUBTRACT  0x40
#define F_HALFCARRY 0x20
#define F_CARRY     0x10

int8_t const times[0x100] = {
//	x0  x1  x2  x3  x4  x5  x6  x7  x8  x9  xA  xB  xC  xD  xE  xF
	 4, 12,  8,  8,  4,  4,  8,  4, 20,  8,  8,  8,  4,  4,  8,  4, // 0x
	 4, 12,  8,  8,  4,  4,  8,  4, 12,  8,  8,  8,  4,  4,  8,  4, // 1x
	 8, 12,  8,  8,  4,  4,  8,  4,  8,  8,  8,  8,  4,  4,  8,  4, // 2x
	 8, 12,  8,  8, 12, 12, 12,  4,  8,  8,  8,  8,  4,  4,  8,  4, // 3x
	 4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4, // 4x
	 4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4, // 5x
	 4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4, // 6x
	 8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4,  4,  4,  8,  4, // 7x
	 4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4, // 8x
	 4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4, // 9x
	 4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4, // Ax
	 4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4, // Bx
	 8, 12, 12, 16, 12, 16,  8, 16,  8, 16, 12,  4, 12, 24,  8, 16, // Cx
	 8, 12, 12, -1, 12, 16,  8, 16,  8, 16, 12, -1, 12, -1,  8, 16, // Dx
	12, 12,  8, -1, -1, 16,  8, 16, 16,  4, 16, -1, -1, -1,  8, 16, // Ex
	12, 12,  8,  4, -1, 16,  8, 16, 12,  8, 16,  4, -1, -1,  8, 16  // Fx
};
int8_t const times_alt[0x100] = {
//	x0  x1  x2  x3  x4  x5  x6  x7  x8  x9  xA  xB  xC  xD  xE  xF
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 1x
	 4,  0,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0, // 2x
	 4,  0,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0, // 3x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 4x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 5x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 6x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 7x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 8x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 9x
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Ax
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Bx
	12,  0,  4,  0, 12,  0,  0,  0, 12,  0,  4,  0, 12,  0,  0,  0, // Cx
	12,  0,  4,  0, 12,  0,  0,  0, 12,  0,  4,  0, 12,  0,  0,  0, // Dx
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Ex
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Fx
};

union {
	struct {
		union {
			struct {uint8_t F, A;};
			uint16_t AF;
		};
		union {
			struct {uint8_t C, B;};
			uint16_t BC;
		};
		union {
			struct {uint8_t E, D;};
			uint16_t DE;
		};
		union {
			struct {uint8_t L, H;};
			uint16_t HL;
		};
		uint16_t SP, PC;
	};
	uint8_t r8[8];
	uint16_t r16[6];
} reg;

int halt = 0;
int stop = 0;
struct {int m, t;} clock = {0, 0};

void cpu_reset(void)
{
	for (int i = 0; i < 6; reg.r16[i++] = 0);
	clock.m = clock.t = 0;
}

/// register operands (last 3 bits)
//  000  001  010  011  100  101  110  111
//    B    C    D    E    H    L (HL)    A
uint8_t reg_i[8] = {3, 2, 5, 4, 7, 6, 0xff, 1};
static uint8_t r_op(uint8_t r)
{
	if (0xff == (r = reg_i[i]))
		return mmu_rb(reg.HL);
	return reg.r8[r];
}

#define getf(flag) (reg.F & (flag))
#define setf(flag) (reg.F |= (flag))
#define unsetf(flag) (reg.F &= ~(flag))
// Test half-carry
static inline void testHC_add(int8_t a, int8_t b, int8_t c)
{
	if (((a & 0xf) + (b & 0xf) + c) & 0x10)
		setf(F_HALFCARRY);
	else
		unsetf(F_HALFCARRY);
}
static inline void testHC_sub(int8_t a, int8_t b, int8_t c)
{
	if (((a & 0xf) - (b & 0xf) - c) < 0)
		setf(F_HALFCARRY);
	else
		unsetf(F_HALFCARRY);
}
// Test zero
static inline void testZ(uint8_t a)
{
	if (a) unsetf(F_ZERO); else setf(F_ZERO);
}
// 8-bit load/store
static void op_ld8(uint8_t dst, uint8_t src)
{
	dst = reg_i[dst];
	src = reg_i[src];
	if (dst == 0xff)
		mmu_wb(HL, reg.r8[src]);
	else if (src == 0xff)
		reg.r8[dst] = mmu_rb(HL);
	else
		reg.r8[dst] = reg.r8[src];
}
// 8-bit addition
static void op_add8(uint8_t x, bool carry)
{
	int8_t c = (carry && getf(F_CARRY)) ? 1 : 0;
	uint16_t tmp = reg.A + x + c;
	testHC_add(reg.A, x, c);
	if (tmp > 0xff) setf(F_CARRY);
	reg.A = tmp & 0xff;
	testZ(reg.A);
	unsetf(F_SUBTRACT);
}
// 8-bit subtraction
static void op_sub8(uint8_t x, bool carry)
{
	int8_t c = (carry && getf(F_CARRY)) ? 1 : 0;
	int16_t tmp = reg.A - x - c;
	testHC_sub(reg.A, x, c);
	if (tmp < 0) setf(F_CARRY);
	reg.A = tmp & 0xff;
	testZ(reg.A);
	setf(F_SUBTRACT);
}
// 8-bit increment
static void op_inc8(uint8_t r)
{
	uint8_t x = r_op(r);
	if (++x == 0x10)
		setf(F_HALFCARRY);
	else
		unsetf(F_HALFCARRY);
	testZ(x);
	if (r == 0xff)
		mmu_wb(reg.HL, x);
	else
		reg.r8[r] = x;
	unsetf(F_SUBTRACT);
}
// 8-bit decrement
static void op_dec8(uint8_t r)
{
	uint8_t x = r_op(r);
	if (--x == 0xff)
		setf(F_HALFCARRY);
	else
		unsetf(F_HALFCARRY);
	testZ(x);
	if (r == 0xff)
		mmu_wb(reg.HL, x);
	else
		reg.r8[r] = x;
	setf(F_SUBTRACT);
}

// 8-bit AND
static void op_and8(uint8_t x)
{
	reg.A &= r_op(x);
	reg.F = reg.A ? (F_ZERO|F_HALFCARRY) : F_HALFCARRY;
}
// 8-bit XOR
static void op_xor8(uint8_t x)
{
	reg.A ^= r_op(x);
	reg.F = reg.A ? F_ZERO : 0;
}
// 8-bit OR
static void op_or8(uint8_t x)
{
	reg.A |= r_op(x);
	reg.F = reg.A ? F_ZERO : 0;
}

static void cpu_exec(void)
{
	uint8_t op = mmu_rb(reg.PC++);
	
	switch (op & 0xf0) {
	case 0x70:
		if (op == 0x76) {
			op_halt(); // TODO
			break;
		}
		/* fall through */
	case 0x40: case 0x50: case 0x60:
		op_ld8((op >> 3) & 7, op & 7);
		break;
	case 0x80: op_add8(op & 7, op & 8); break;
	case 0x90: op_sub8(op & 7, op & 8); break;
	case 0xa0: if (op & 8) op_xor8(op & 7); else op_and8(op & 7); break;
	case 0xb0: if (op & 8) op_cp8(op & 7); else op_or8(op & 7); break;
	default:;
	}
	
	switch (op) {
	// Complement
	case CPL:
		reg.A = ~reg.A;
		setf(F_SUBTRACT | F_HALFCARRY);
		break;
	// 16-bit increment/decrement
	case INCbc: reg.BC++; break;	case DECbc: reg.BC--; break;
	case INCde: reg.DE++; break;	case DECde: reg.DE--; break;
	case INChl: reg.HL++; break;	case DEChl: reg.HL--; break;
	case INCsp: reg.SP++; break;	case DECsp: reg.SP--; break;
	default:;
	}
}
