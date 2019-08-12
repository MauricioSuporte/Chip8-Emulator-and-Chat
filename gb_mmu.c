
union {
	struct {
		uint8_t rom0[0x4000]; // ROM bank 0 (0x0000 - 0x3fff)
		uint8_t romN[0x4000]; // ROM bank N (0x4000 - 0x7fff)
		uint8_t tile[0x1800]; // Tile RAM (0x8000 - 0x97ff)
		uint8_t bgmap[0x800]; // Background map (0x9800 - 0x9fff)
		uint8_t cram[0x2000]; // Cartridge RAM (0xa000 - 0xbfff)
		uint8_t wram[0x2000]; // Working RAM (0xc000 - 0xdfff)
		                      // Echo of WRAM (0xe000 - 0xfdff)
		uint8_t oam[0xa0];    // Object Attribute Memory (0xfe00 - 0xfe9f)
		                      // Here there be dragons (0xfea0 - 0xfeff)
		union {
			uint8_t ioreg[0x80];  // I/O registers (0xff00 - 0xff7f)
			struct {
			uint8_t __filler[3];
			// http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-Timers
			uint8_t div; // counts up at 16384 Hz
			uint8_t ctr; // counts up at specified rate, triggers interrupt 0x50 on overflow
			uint8_t mod; // when ctr overflows, it's set to this
			uint8_t ctl; // timer control
			};
		};
		uint8_t hram[0x7f];   // High RAM area (0xff80 - 0xfffe)
		uint8_t ie;           // Interrupt enable register (0xffff)
	};
	uint8_t mem[0xe1a0];
} mem;

uint8_t *mmu_ptr(uint16_t addr)
{
	if (0xff00 <= addr)
		return mem.mem + addr - 0x1e60;
	if (0xe000 > addr)
		return mem.mem + addr;
	if (0x1ea0 > (addr -= 0xe000))
		return mem.wram + addr;
	return NULL;
}

uint8_t mmu_rb(uint16_t addr)
{
	uint8_t *p = mmu_ptr(addr);
	return p ? *p : 0;
}

void mmu_wb(uint16_t addr, uint8_t b)
{
	uint8_t *p = mmu_ptr(addr);
	if (p) *p = b;
}

uint16_t mmu_rw(uint16_t addr)
{
	return mmu_rb(addr) | (mmu_rb(addr+1) << 8);
}

void mmu_ww(uint16_t addr, uint16_t w)
{
	mmu_wb(addr, w & 0xff);
	mmu_wb(addr+1, (w & 0xff00) >> 8);
}
