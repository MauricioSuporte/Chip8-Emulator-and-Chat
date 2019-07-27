
#define F_ZERO      0x80
#define F_OPERATION 0x40
#define F_HALFCARRY 0x20
#define F_CARRY     0x10

/* Opcodes */
enum {
	NOP=0x00,
	/* prefixed */
	PREFIX_CB=0xcb,
	/* stop/halt */
	STOP=0x10,
	HALT=0x76,
	/* interrupts */
	DI=0xf3,
	EI=0xfb,
	
	/* 8-bit load/store */
	// immediate
	LDa_d8=0x3e, LDb_d8=0x06, LDc_d8=0x0e, LDd_d8=0x16,
	LDe_d8=0x1e, LDh_d8=0x26, LDl_d8=0x2e, LDmhl_d8=0x36,
	// immediate address
	LDa16_a=0xea, LDa_a16=0xfa,
	LDHa8_a=0xe0, LDHa_a8=0xf0,
	// register/register
	LDa_b=0x78, LDa_c, LDa_d, LDa_e, LDa_h, LDa_l, LDa_a=0x7f,
	LDb_b=0x40, LDb_c, LDb_d, LDb_e, LDb_h, LDb_l, LDb_a=0x47,
	LDc_b=0x48, LDc_c, LDc_d, LDc_e, LDc_h, LDc_l, LDc_a=0x4f,
	LDd_b=0x50, LDd_c, LDd_d, LDd_e, LDd_h, LDd_l, LDd_a=0x57,
	LDe_b=0x58, LDe_c, LDe_d, LDe_e, LDe_h, LDe_l, LDe_a=0x5f,
	LDh_b=0x60, LDh_c, LDh_d, LDh_e, LDh_h, LDh_l, LDh_a=0x67,
	LDl_b=0x68, LDl_c, LDl_d, LDl_e, LDl_h, LDl_l, LDl_a=0x6f,
	// register/memory
	LDa_mhl=0x7e,
	LDb_mhl=0x46, LDc_mhl=0x4e,
	LDd_mhl=0x56, LDe_mhl=0x5e,
	LDh_mhl=0x66, LDl_mhl=0x6e,
	LDmhl_a=0x77, LDmhl_b=0x70, LDmhl_c, LDmhl_d, LDmhl_e, LDmhl_h, LDmhl_l,
	LDmbc_a=0x02, LDmde_a=0x12, LDmhl_inc_a=0x22, LDmhl_dec_a=0x32,
	LDa_mbc=0x0a, LDa_mde=0x1a, LDa_mhl_inc=0x2a, LDa_mhl_dec=0x3a,
	LDmc_a=0xe2, LDa_mc=0xf2,
	
	/* 16-bit load/store */
	// immediate
	LDbc_d16=0x01, LDde_d16=0x11, LDhl_d16=0x21, LDsp_d16=0x31,
	// immediate address
	LDa16_sp=0x08,
	// push/pop
	PUSHbc=0xc5, PUSHde=0xd5, PUSHhl=0xe5, PUSHaf=0xf5,
	POPbc=0xc1, POPde=0xd1, POPhl=0xe1, POPaf=0xf1,
	// register/register
	LDsp_hl=0xf9, LDhl_sp_plus_r8=0xf8,
	
	/* 8-bit arithmetic/logic */
	// increment/decrement
	INCb=0x04, INCd=0x14, INCh=0x24, INCmhl=0x34,
	INCc=0x0c, INCe=0x1c, INCl=0x2c, INCa  =0x3c,
	DECb=0x05, DECd=0x15, DECh=0x25, DECmhl=0x35,
	DECc=0x0d, DECe=0x1d, DECl=0x2d, DECa  =0x3d,
	// addition
	ADDb=0x80, ADDc, ADDd, ADDe, ADDh, ADDl, ADDmhl, ADDa, ADDd8=0xc6,
	// addition with carry
	ADCb=0x88, ADCc, ADCd, ADCe, ADCh, ADCl, ADCmhl, ADCa, ADCd8=0xce,
	// subtraction
	SUBb=0x90, SUBc, SUBd, SUBe, SUBh, SUBl, SUBmhl, SUBa, SUBd8=0xd6,
	// subtraction with carry
	SBCb=0x98, SBCc, SBCd, SBCe, SBCh, SBCl, SBCmhl, SBCa, SBCd8=0xde,
	// bitwise operations
	ANDb=0xa0, ANDc, ANDd, ANDe, ANDh, ANDl, ANDmhl, ANDa, ANDd8=0xe6,
	XORb=0xa8, XORc, XORd, XORe, XORh, XORl, XORmhl, XORa, XORd8=0xee,
	ORb=0xb0, ORc, ORd, ORe, ORh, ORl, ORmhl, ORa, ORd8=0xf6,
	// comparison
	CPb=0xb8, CPc, CPd, CPe, CPh, CPl, CPmhl, CPa, CPd8=0xfe,
	// misc.
	DAA=0x27, SCF=0x37, CPL=0x2f, CCF=0x3f,
	
	/* 16-bit arithmetic */
	// increment/decrement
	INCbc=0x03, INCde=0x13, INChl=0x23, INCsp=0x33,
	DECbc=0x0b, DECde=0x1b, DEChl=0x2b, DECsp=0x3b,
	// addition
	ADDhl_bc=0x09, ADDhl_de=0x19, ADDhl_hl=0x29, ADDhl_sp=0x39,
	ADDsp_r8=0xe8,
	
	/* control flow */
	// relative jumps
	JRr8=0x18,
	JRNZ_r8=0x20, JRNC_r8=0x30,
	JRZ_r8=0x28, JRC_r8=0x38,
	// absolute jumps
	JPa16=0xc3, JPmhl=0xe9,
	JPNZ_a16=0xc2, JPNC_a16=0xd2,
	JPZ_a16=0xca, JPC_a16=0xda,
	// call/return
	CALLa16=0xcd,
	CALLNZ_a16=0xc4, CALLNC_a16=0xd4,
	CALLZ_a16=0xcc, CALLC_a16=0xdc,
	RET=0xc9, RETI=0xd9,
	RETNZ=0xc0, RETNC=0xd0,
	RETZ=0xc8, RETC=0xd8,
	// rst
	RST00h=0xc7, RST08h=0xcf,
	RST10h=0xd7, RST18h=0xdf,
	RST20h=0xe7, RST28h=0xef,
	RST30h=0xf7, RST38h=0xff
};

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

void cpu_dispatch(void)
{
	uint8_t opcode = mmu_rb(reg.PC++);
	op(opcode);
	clock.m += times[opcode] + times_alt[opcode]; // ?
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
static inline void testZ(uint8_t a)
{
	if (a)
		reg.F &= ~F_ZERO;
	else
		reg.F |= F_ZERO;
}
// 8-bit loads (0x40 - 0x7f)
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
// 8-bit addition (0x80 - 0x87)
static void op_add8(uint8_t x)
{
	reg.A += r_op(x);
	testZ(reg.A);
	reg.F &= ~F_OPERATION;
	// TODO F_HALFCARRY F_CARRY
}
// 8-bit subtraction (0x90 - 0x97)
static void op_sub8(uint8_t x)
{
	reg.A -= r_op(x);
	testZ(reg.A);
	reg.F |= F_OPERATION;
	// TODO F_HALFCARRY F_CARRY
}
// 8-bit AND (0xa0 - 0xa7)
static void op_and8(uint8_t x)
{
	reg.A &= r_op(x);
	reg.F = reg.A ? (F_ZERO|F_HALFCARRY) : F_HALFCARRY;
}
// 8-bit XOR (0xa8 - 0xaf)
static void op_xor8(uint8_t x)
{
	reg.A ^= r_op(x);
	reg.F = reg.A ? F_ZERO : 0;
}
// 8-bit OR (0xb0 - 0xb7)
static void op_or8(uint8_t x)
{
	reg.A |= r_op(x);
	reg.F = reg.A ? F_ZERO : 0;
}

static void cpu_dispatch(uint8_t op)
{
	switch (op & 0xf0) {
	case 0x00: break;
	case 0x10: break;
	case 0x20: break;
	case 0x30: break;
	case 0x70:
		if (op == 0x76) {
			op_halt();
			break;
		}
		/* fall through */
	case 0x40: case 0x50: case 0x60:
		op_ld8((op >> 3) & 7, op & 7);
		break;
	case 0x80: if (op & 8) op_adc8(op & 7); else op_add8(op & 7); break;
	case 0x90: if (op & 8) op_sbc8(op & 7); else op_sub8(op & 7); break;
	case 0xa0: if (op & 8) op_xor8(op & 7); else op_and8(op & 7); break;
	case 0xb0: if (op & 8) op_cp8(op & 7); else op_or8(op & 7); break;
	case 0xc0: break;
	case 0xd0: break;
	case 0xe0: break;
	case 0xf0: break;
	}
}
