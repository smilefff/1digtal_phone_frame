

typedef struct bmp_info
{
    unsigned int 	ImageWidth		;  //文件宽度
    unsigned int 	ImageHight		;  //文件高度
    short		 	BPP				;  //每个相素点的位数
	unsigned int 	FileOffset		;  //文件头偏移量
	unsigned char 	*pdata			;
}bmp_info_t;










