#ifndef _GB_OPCODES_H
#define _GB_OPCODES_H

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

#endif /* _GB_OPCODES_H */
