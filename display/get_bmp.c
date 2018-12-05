#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>		//open
#include <errno.h>		//errno
#include <unistd.h>		//close
#include <stdlib.h>		//exit malloc
#include <sys/types.h>	//lseek
#include <unistd.h>

#include <fb.h>
#include <config.h>
#include <get_bmp.h>


#define IDENTIFIER_LONG 	2

#define PIXEL	((1920) * (1080))
#define MAXBYTE	(PIXEL * (3))

unsigned char bmp_data[MAXBYTE];

int is_bmp(unsigned char *pathname)
{
	int ret = -1;
	int fd = -1;
	unsigned char bmp_sign[IDENTIFIER_LONG];
	fd = open(BMP, O_RDONLY);
	if(fd < 0)
		{
			perror("open BMP");
			exit(-1);
		}
	ret = read(fd, bmp_sign, sizeof(bmp_sign));
	printf("bmp_sign[0] = %x\n", bmp_sign[0]);
	printf("bmp_sign[1] = %x\n", bmp_sign[1]);	
	if((bmp_sign[0] = 'B') && (bmp_sign[1] = 'M'))
		{
			return 0;
		}

	close(fd);
	return -1;	
}

int bmp_get(struct bmp_info *pPic)
{
	int ret = -1;
	int fd = -1;
	struct bmp_header  bmp_h;
	
	fd = open(BMP, O_RDONLY);	//打开.bmp格式的文件。
	if(fd < 0)
		{
			perror("open BMP");
			exit(-1);
		}

	lseek(fd, IDENTIFIER_LONG, SEEK_SET);
	//2、读取bmp格式文件的信息，第一，文件的分辨率，第二，文件的尺寸，第三，文件颜色数据
	ret = read(fd, &bmp_h, sizeof(struct bmp_header));
	if(ret < 0)
		{
			perror("read BMP");
			close(fd);
		}
	printf("fd = %d\n", fd);
	//3、打印分辨率等信息
//	unsigned int  filesize ;
//	filesize = bmp_h->ImageWidth;		//开始以为bmp格式的图片是大端格式，所以就用大小端转换，实际BMP是小端格式， 不用转换
//	bmp_h->ImageWidth = (filesize & 0x000000FFU) << 24 | ((filesize & 0x0000FF00U) ) << 8 | ((filesize & 0x00FF0000U) ) >> 8 | ((filesize & 0xFF000000U)) >> 24;

	printf("sizeof(bmp_h) = %d\n", sizeof(struct bmp_header));
	printf("DIBHeaderSize = %d\n", bmp_h.DIBHeaderSize);
	printf("FileSize = %d\n", bmp_h.FileSize);
	printf("FileOffset = %d\n", bmp_h.FileOffset);
	printf("ImageWidth = %d\n", bmp_h.ImageWidth);
	printf("ImageHight = %d\n", bmp_h.ImageHight);
	printf("BPP = %hd\n", bmp_h.BPP);
	printf("ImageSize = %d\n", bmp_h.ImageSize);

	pPic->ImageWidth = bmp_h.ImageWidth;
	pPic->ImageHight = bmp_h.ImageHight;
	pPic->BPP		 = bmp_h.BPP;
	pPic->FileOffset = bmp_h.FileOffset;

	lseek(fd, bmp_h.FileOffset , SEEK_SET);
	ret = read(fd, bmp_data, bmp_h.ImageSize);
	{
		perror("read BMP");
		close(fd);
	}

	pPic->pdata = bmp_data;

	fb_draw_picture4(200, 200, pPic->pdata);

	return 0;
}







