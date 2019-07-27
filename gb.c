
uint8_t const boot_rom[] = {
	0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32,
	0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
	0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3,
	0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
	0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A,
	0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
	0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06,
	0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
	0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99,
	0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
	0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64,
	0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
	0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90,
	0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
	0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62,
	0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
	0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42,
	0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
	0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04,
	0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
	0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9,
	0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
	0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
	0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
	0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
	0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
	0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
	0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
	0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13,
	0xBE, 0x00, 0x00, 0x23, 0x7D, 0xFE, 0x34, 0x20,
	0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20,
	0xFB, 0x86, 0x00, 0x00, 0x3E, 0x01, 0xE0, 0x50
};

/* Joypad input */
#define P1	(mem[0xff00])	// (rw) joypad
#define BTN_A		((uint8_t) 0b100001)
#define BTN_B		((uint8_t) 0b100010)
#define BTN_SELECT	((uint8_t) 0b100100)
#define BTN_START	((uint8_t) 0b101000)
#define BTN_RT		((uint8_t) 0b010001)
#define BTN_LT		((uint8_t) 0b010010)
#define BTN_UP		((uint8_t) 0b010100)
#define BTN_DN		((uint8_t) 0b011000)

/* Serial data transfer */
#define SB	(mem[0xff01])	// (rw) serial transfer data
#define SC	(mem[0xff02])	// (rw) serial transfer control

/* Timer */
#define DIV	(mem[0xff04])	// (rw) divider register
#define TIMA	(mem[0xff05])	// (rw) timer counter
#define TMA	(mem[0xff06])	// (rw) timer modulo
#define TAC	(mem[0xff07])	// (rw) timer control

/* Sound controller */
#define NR10	(mem[0xff10])	// (rw) ch1 sweep register
#define NR11	(mem[0xff11])	// (rw) ch1 sound length/wave pattern duty
#define NR12	(mem[0xff12])	// (rw) ch1 volume envelope
#define NR13	(mem[0xff13])	// (-w) ch1 frequency low data
#define NR14	(mem[0xff14])	// (rw) ch1 frequency high data
#define NR21	(mem[0xff16])	// (rw) ch2 sound length/wave pattern duty
#define NR22	(mem[0xff17])	// (rw) ch2 volume envelope
#define NR23	(mem[0xff18])	// (-w) ch2 frequency low data
#define NR24	(mem[0xff19])	// (rw) ch2 frequency high data
#define NR30	(mem[0xff1a])	// (rw) ch3 sound on/off
#define NR31	(mem[0xff1b])	// (rw) ch3 sound length
#define NR32	(mem[0xff1c])	// (rw) ch3 select output level
#define NR33	(mem[0xff1d])	// (-w) ch3 frequency low data
#define NR34	(mem[0xff1e])	// (rw) ch3 frequency high data
#define NR41	(mem[0xff20])	// (rw) ch4 sound length
#define NR42	(mem[0xff21])	// (rw) ch4 volume envelope
#define NR43	(mem[0xff22])	// (rw) ch4 polynomial counter
#define NR44	(mem[0xff23])	// (rw) ch4 counter/consecutive initial
#define NR50	(mem[0xff24])	// (rw) channel control / on-off / volume
#define NR51	(mem[0xff25])	// (rw) selection of sound output terminal
#define NR52	(mem[0xff26])	// (rw) sound on/off

/* Pixel processing unit */
#define LCDC	(mem[0xff40])	// (rw) LCD control
#define STAT	(mem[0xff41])	// (rw) LCDC status
#define SCY	(mem[0xff42])	// (rw) scroll Y
#define SCX	(mem[0xff43])	// (rw) scroll X
#define LY	(mem[0xff44])	// (r-) LCDC Y-coordinate
#define LYC	(mem[0xff45])	// (rw) LY compare
#define DMA	(mem[0xff46])	// (-w) DMA transfer and start address
#define BGP	(mem[0xff47])	// (rw) BG palette data
#define OBP0	(mem[0xff48])	// (rw) object palette 0 data
#define OBP1	(mem[0xff49])	// (rw) object palette 1 data
#define WY	(mem[0xff4a])	// (rw) window Y position
#define WX	(mem[0xff4b])	// (rw) window X position - 7

/* Interrupt controller */
#define IF	(mem[0xff0f])	// (rw) interrupt flag
#define IE	(mem[0xffff])	// (rw) interrupt enable

#define U16(lsb, msb) (uint16_t)((lsb) | ((msb) << 8))
#define MSB(x) (uint8_t)((x) >> 8)
#define LSB(x) (uint8_t)((x) & 0xff)

int test(uint8_t op)
{
	switch ((opcode & 0b00011000) >> 3) {
	case 0b00: return flags.Z == 0;
	case 0b10: return flags.Z == 1;
	case 0b01: return flags.C == 0;
	case 0b11: return flags.C == 1;
	}
	return 0;
}

void do_op(void)
{
	uint8_t opcode = mem[PC++];
	uint16_t nn;
	uint8_t r;
	switch (opcode) {
		
	}
}
