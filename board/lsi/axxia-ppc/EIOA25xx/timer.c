static ncr_command_t timer[] = {
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001000c, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010010, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010014, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010018, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001001c, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001002c, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010030, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010034, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010038, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001003c, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000004, 0x000808a1, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000100, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000104, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000108, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000010c, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000110, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000114, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000118, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000011c, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000120, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000124, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000128, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000012c, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000130, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000134, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000138, 0x000000ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000013c, 0x40015001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000300, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000304, 0x00008001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004008, 0x0000007f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000400c, 0x9001b001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000300, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000304, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004010, 0x0000007f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004014, 0x9001b001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000300, 0x00008001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000304, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004018, 0x0000007f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000401c, 0x9001b001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000300, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000304, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004020, 0x0000007f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004024, 0x9001b001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000308, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000030c, 0x00008001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004028, 0x0000007f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000402c, 0x9001b001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000308, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000030c, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004030, 0x0000007f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004034, 0x9001b001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000308, 0x00008001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000030c, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00004038, 0x0000007f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000403c, 0x9001b001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000308, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000030c, 0x80018001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 1), 0x00000004, 0x6800183e, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000020, 0x11110000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00001000, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001000c, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010010, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010014, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010018, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001001c, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001002c, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010030, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010034, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00010038, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0001003c, 0x00000001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 1), 0x00000400, 0x00000001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 1), 0x00000404, 0x00000001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 4), 0x0000000c, 0x04081818, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 4), 0x00000008, 0x38301806, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 4), 0x00000024, 0x02040c0c, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 6), 0x00000100, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 3), 0x00000800, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x000001f0, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x000001f4, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000200, 0x51eb851e, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000204, 0xb851ec00, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000208, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000210, 0x51eb851e, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000214, 0xb851ec00, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000218, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000220, 0x6d3a06d3, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000224, 0xa06d3800, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000228, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000230, 0x6d3a06d3, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000234, 0xa06d3800, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000238, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000300, 0x20000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000304, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000308, 0x00000001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x0000030c, 0xbfa15848, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000310, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000320, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000330, 0x0000000a, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000100, 0x00000002, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000100, 0x00000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000100, 0x00000001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000108, 0x00000005, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000014, 0x000363ae, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 1), 0x0000000c, 0x555516ff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 2), 0x0000000c, 0x0000000f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 3), 0x00000008, 0x0000002b, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 5), 0x00000014, 0x00027fdf, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 6), 0x00000014, 0x0000131f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000030, 0xffffffff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000034, 0xffffffff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000038, 0xaaabffff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x0000003c, 0xaaaaaaaa, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000040, 0xfe17fffe, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000044, 0xffffffff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x00000048, 0x03c0ffff, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 16), 0x0000004c, 0xfffffdc0, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 4), 0x00000004, 0xe8000000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 2), 0x00000004, 0x00000001, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 6), 0x00000004, 0x00000641, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000004, 0x000808a1, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x0000005c, 0x000d0000, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000004, 0x000808a5, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 1), 0x00000004, 0x6800183f, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 1), 0x00000018, 0x00072720, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 6), 0x00000004, 0x00000638, 0},
	{NCR_COMMAND_WRITE, NCP_REGION_ID(25, 0), 0x00000004, 0x00080880, 0},
	{NCR_COMMAND_NULL, 0, 0, 0, 0}
};