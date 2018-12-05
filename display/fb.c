#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>		//open
#include <errno.h>		//errno
#include <sys/ioctl.h>	//ioctl
#include <unistd.h>		//close
#include <stdlib.h>		//exit
#include <sys/mman.h>	//mmap
#include <linux/fb.h> 	//fb_fix_screeninfo、FBIOGET_FSCREENINFO等

#include <fb.h>


static int fb_fd = -1;
static unsigned long *fbp = NULL;
static struct fb_fix_screeninfo 	fix_screen = {0};
static struct fb_var_screeninfo		var_screen = {0};


int fb_open(void)
{
	int ret = -1;
	
	//第二步，打开framebuffer文件
	fb_fd = open(MYFB0 ,O_RDWR);
	if(fb_fd < 0)
	{
		perror("open");
		exit(-1);
	}
	printf("fb_fd = %d\n", fb_fd);
	
	//第三步，读取framebuffer文件的液晶信息。
	ret = ioctl(fb_fd, FBIOGET_FSCREENINFO, &fix_screen);
	if(ret < 0)
	{}
	ret = ioctl(fb_fd, FBIOGET_VSCREENINFO, &var_screen);
	if(ret < 0)
	{}
	//调试：打印读取信息。
	printf("smem_start = 0x%lx.\n", fix_screen.smem_start);
	printf("smem_len = %d.\n", fix_screen.smem_len);
	printf("xres = %d.\n", var_screen.xres);
	printf("yres = %d.\n", var_screen.yres);	
	printf("xres_virtual = %d.\n", var_screen.xres_virtual);
	printf("yres_virtual = %d.\n", var_screen.yres_virtual);
	printf("xoffset = %d.\n", var_screen.xoffset);
	printf("yoffset = %d.\n", var_screen.yoffset);

	//第四步，用mmap给framebuffer映射一段内存空间。
	fbp = (unsigned long *)mmap(NULL , fix_screen.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
	if(!fbp)
	{
		perror("mmap");
		exit(-1);
	}
	printf("fbp success.\n");
	
	//第五步，处理传入的bmp图片。
	
	
	//第六步，显示图片
	
	
	//第七步，关闭文件

	return 0;
}

void fb_close(void)
{
	munmap(fbp, fix_screen.smem_len);
	close(fb_fd);
}

void fb_draw_pixel(unsigned x, unsigned y, unsigned color)
{	
	*(fbp + WIDTH * y + x) = color;
}

void fb_draw_back(unsigned int i, unsigned int j, unsigned long color)
{
	for(i = 0; i< HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			fb_draw_pixel(j, i, color);		
		}
	}
}

void fb_draw_picture(unsigned int i, unsigned int j, const unsigned char *str)
{
	unsigned int color;
	int cnt = 0;
	for(i = 0; i< HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			color = (str[cnt+2]<<16 | str[cnt+1]<<8 | str[cnt]<<0);
			fb_draw_pixel(j, i, color);
			cnt += 3;
		}
	}
}

//分辨率是1024*600的图片显示
void fb_draw_picture1(unsigned int i, unsigned int j, const unsigned char *str)
{
	unsigned int color;
	int cnt = 0;
	for(i = 0; i< 347; i++)
	{
		for(j = 0; j < 500; j++)
		{
			color = (str[cnt+2]<<16 | str[cnt+1]<<8 | str[cnt]<<0);
			fb_draw_pixel(j, i, color);
			cnt += 3;
		}
	}
}

//给图片设定显示的起始点，
void fb_draw_picture2(unsigned int x, unsigned int y, const unsigned char *str)
{
	int i,j;
	unsigned int color;
	int cnt = 0;
	for(i = y; i< y + 347; i++)
	{
		for(j = x; j < x + 500; j++)
		{
			color = (str[cnt+2]<<16 | str[cnt+1]<<8 | str[cnt]<<0);
			fb_draw_pixel(j, i, color);
			cnt += 3;
		}
	}
}

//让超出图片范围的部分不显示
void fb_draw_picture3(unsigned int x, unsigned int y, const unsigned char *str)
{
	int i,j;
	unsigned int color;
	int cnt = 0;
	for(i = y; i< y + 347; i++)
	{
		for(j = x; j < x + 500; j++)
		{
			color = (str[cnt+2]<<16 | str[cnt+1]<<8 | str[cnt]<<0);
			if((j < 1024) && (i < 600))
				{
					fb_draw_pixel(j, i, color);
				}
			cnt += 3;
		}
	}
}

//让超出图片范围的部分不显示,图片调转180度。
void fb_draw_picture4(unsigned int x, unsigned int y, const unsigned char *str)
{
	int i,j;
	unsigned int color;
	int cnt = 0;
	for(i = y + 347; i > y ; i--)
	{
		for(j = x + 500 ; j > x ; j--)
		{
			color = (str[cnt+2]<<16 | str[cnt+1]<<8 | str[cnt]<<0);
			if((j < 1024) && (i < 600))
				{
					fb_draw_pixel(j, i, color);
				}
			cnt += 3;
		}
	}
}













