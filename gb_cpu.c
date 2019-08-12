#include <stdbool.h>

#include "gb_opcodes.h"

#define F_ZERO      0x80
#define F_SUBTRACT  0x40
#define F_HALFCARRY 0x20
#define F_CARRY     0x10

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
int ie = 1;
struct {int m, t;} clock = {0, 0};

void cpu_reset(void)
{
	for (int i = 0; i < 6; reg.r16[i++] = 0);
	clock.m = clock.t = 0;
}

enum target_r8 {
	reg_B = 0,
	reg_C = 1,
	reg_D = 2,
	reg_E = 3,
	reg_H = 4,
	reg_L = 5,
	ptr_HL = 6,
	reg_A = 7
};
int const r8_i[8] = {3, 2, 5, 4, 7, 6, -1, 1};

enum target_r16 {
	reg_BC = 0,
	reg_DE = 1,
	reg_HL = 2,
	reg_SP = 3
};
int const r16_i[4] = {1, 2, 3, 4};

enum target_r16_pushpop {
	reg_BC = 0,
	reg_DE = 1,
	reg_HL = 2,
	reg_AF = 3
};
int const r16_pushpop_i[4] = {1, 2, 3, 0};

enum logic_op {
	add = 0,
	adc = 1,
	sub = 2,
	sbc = 3,
	and = 4,
	xor = 5,
	or = 6,
	cp = 7
};

static uint8_t r8_op(uint8_t r)
{
	if (0xff == (r = r8_i[i]))
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

// LD r8, r8
static void op_ld_r8(uint8_t dst, uint8_t src)
{
	dst = r8_i[dst];
	src = r8_i[src];
	if (dst == 0xff)
		mmu_wb(HL, reg.r8[src]);
	else if (src == 0xff)
		reg.r8[dst] = mmu_rb(HL);
	else
		reg.r8[dst] = reg.r8[src];
}
// LD r8, d8
static void op_ld_r8_d8(uint8_t dst)
{
	dst = r8_i[dst];
	uint8_t d = mmu_rb(reg.PC++);
	if (dst == 0xff)
		mmu_wb(HL, d);
	else
		reg.r8[dst] = d;
}
// 8-bit addition
static void op_add8(uint8_t x, int8_t carry)
{
	int8_t c = getf(F_CARRY) ? carry : 0;
	uint16_t tmp = reg.A + x + c;
	testHC_add(reg.A, x, c);
	if (tmp > 0xff) setf(F_CARRY);
	reg.A = tmp & 0xff;
	testZ(reg.A);
	unsetf(F_SUBTRACT);
}
static void op_add16_hl(uint16_t x)
{
	uint32_t tmp = reg.HL + x;
	if (tmp > 0xffff) setf(F_CARRY);
	testHC_add(reg.HL & 0xff, x & 0xff, 0); // ??
	reg.HL = tmp & 0xffff;
	unsetf(F_SUBTRACT);
}
// 8-bit subtraction
static void op_sub_r8(uint8_t x, int8_t carry)
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
static void op_inc_r8(uint8_t r)
{
	uint8_t x = r8_op(r);
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
static void op_dec_r8(uint8_t r)
{
	uint8_t x = r8_op(r);
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
static void op_and_r8(uint8_t x)
{
	reg.A &= x;
	reg.F = reg.A ? (F_ZERO|F_HALFCARRY) : F_HALFCARRY;
}
// 8-bit XOR
static void op_xor_r8(uint8_t x)
{
	reg.A ^= x;
	reg.F = reg.A ? F_ZERO : 0;
}
// 8-bit OR
static void op_or_r8(uint8_t x)
{
	reg.A |= x;
	reg.F = reg.A ? F_ZERO : 0;
}

void cpu_step(void)
{
	uint8_t op = mmu_rb(reg.PC++);
	if (op != NOP)
		cpu_dispatch(op);
}

static void arith_logic_dispatch(uint8_t op, uint8_t x)
{
	switch ((op & 0b00111000) >> 3) {
	case 0: op_add8(x, 0); break; // add
	case 1: op_add8(x, 1); break; // adc
	case 2: op_sub8(x, 0); break; // sub
	case 3: op_sub8(x, 1); break; // sbc
	case 4: op_and8(x); break;    // and
	case 5: op_xor8(x); break;    // xor
	case 6: op_or8(x); break;     // or
	case 7: op_cp8(x); break;     // cp
	}
}

static int get_cc(uint8_t op)
{
	switch ((op & 0b00011000) >> 3) {
	case 0: return !getf(F_ZERO);
	case 1: return getf(F_ZERO);
	case 2: return !getf(F_CARRY);
	case 3: return getf(F_CARRY);
	}
}

static void cpu_dispatch(uint8_t op)
{
	switch (op & 0b11000000) {
	case 0b01000000:
		// ld r8, r8
		op_ld_r8((op >> 3) & 7, op & 7);
		return;
	case 0b10000000:
		// <add/adc/sub/sbc/and/xor/or/cp> r8
		arith_logic_dispatch(op, r8_op(op & 7));
		return;
	default: break;
	}

	switch (op & 0b11000111) {
	case 0b11000110:
		// <add/adc/sub/sbc/and/xor/or/cp> d8
		arith_logic_dispatch(op, mmu_rb(reg.PC++));
		return;
#define arg ((op & 0b00111000) >> 3)
	case 0b00000100:
		// inc r8
		op_inc_r8(arg);
		return;
	case 0b00000101:
		// dec r8
		op_dec_r8(arg);
		return;
	case 0b00000110:
		// ld r8, d8
		op_ld_r8_d8(arg);
		return;
	case 0b11000111:
		// rst f
		mmu_ww(reg.SP -= 2, reg.PC);
		reg.PC = (uint16_t)(op & 0b00111000);
		return;
#undef arg
	default: break;
	}
	
	switch (op & 0b11001111) {
#define ri r16_i[((op & 0x30) >> 4)]
	case 0b00000010:
		// ld (r16), A
		mmu_wb(reg.r16[ri], reg.A);
		return;
	case 0b00001010:
		// ld A, (r16)
		reg.A = mmu_rb(reg.r16[ri]);
		return;
	case 0b00000001:
		// ld r16, d16
		reg.r16[ri] = mmu_rw(reg.PC);
		reg.PC += 2;
		return;
	case 0b00000011:
		// inc r16
		reg.r16[ri]++;
		return;
	case 0b00001011:
		// dec r16
		reg.r16[ri]--;
		return;
	case 0b00001001:
		// add HL, r16
		op_add16_hl(reg.r16[ri]);
		return;
	case 0b11000001:
		// pop r16
		reg.r16[r16_pushpop_i[((op & 0x30) >> 4)]] = mmu_rw(reg.SP);
		reg.SP += 2;
		return;
	case 0b11000101:
		// push r16
		mmu_ww(reg.SP -= 2, reg.r16[r16_pushpop_i[((op & 0x30) >> 4)]]);
		return;
#undef ri
	default: break;
	}
	
	switch (op & 0b11100111) {
	case 0b00100000:
		// jr cc, e8
		if (get_cc(op)) {
			union {int8_t i; uint8_t u;} e;
			e.u = mmu_rb(reg.PC);
			reg.PC += e.i;
			clock += 4;
		} else {
			reg.PC++;
		}
		return;
	case 0b11000000:
		// ret cc
		if (get_cc(op)) {
			reg.PC = mmu_rw(reg.SP);
			reg.SP += 2;
			clock += 12;
		}
		return;
	case 0b11000010:
		// jp cc, a16
		if (get_cc(op)) {
			reg.PC = mmu_rw(reg.PC);
			clock += 4;
		} else {
			reg.PC += 2;
		}
		return;
	case 0b11000100:
		// call cc, a16
		if (get_cc(op)) {
			mmu_ww(reg.SP -= 2, reg.PC);
			reg.PC = mmu_rw(reg.PC);
			clock += 12;
		} else {
			reg.PC += 2;
		}
		return;
	default: break;
	}
	
	switch (op) {
	case 0x10: // stop 0
		reg.PC++;
		stop = 1;
		return;
	case 0x27: // daa
		if (getf(F_SUBTRACT)) {
			if (getf(F_CARRY))
				reg.A -= 0x60;
			if (getf(F_HALFCARRY))
				reg.A -= 0x06;
		} else {
			if (getf(F_CARRY) || reg.A > 0x99) {
				reg.A += 0x60;
				setf(F_CARRY);
			}
			if (getf(F_HALFCARRY) || (reg.A & 0x0f) > 0x09)
				reg.A += 0x06;
		}
		testZ(reg.A);
		unsetf(F_HALFCARRY);
		return;
	case 0x2f: // cpl
		reg.A = ~reg.A;
		setf(F_SUBTRACT | F_HALFCARRY);
		return;
	case 0x37: // scf
		setf(F_CARRY);
		unsetf(F_SUBTRACT | F_HALFCARRY);
		return;
	case 0x3f: // ccf
		if (getf(F_CARRY))
			unsetf(F_CARRY);
		else
			setf(F_CARRY);
		unsetf(F_SUBTRACT | F_HALFCARRY);
		return;
	case 0x76: halt = 1; return; // halt
	case 0xd9: ie = 1; // reti
		/* fall through */
	case 0xc9: // ret
		reg.PC = mmu_rw(reg.SP);
		reg.SP += 2;
		return;
	case 0xf3: mmu_wb(0xffff, 0); return; // di
	case 0xfb: mmu_rb(0xffff, 1); return; // ei
	default:
		fprintf(stderr, "Unknown opcode $%02x!\n", (int) op);
		// (crash)
	}
}
