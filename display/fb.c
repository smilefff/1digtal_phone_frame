#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>		//open
#include <errno.h>		//errno
#include <sys/ioctl.h>	//ioctl
#include <unistd.h>		//close
#include <stdlib.h>		//exit
#include <sys/mman.h>	//mmap
#include <linux/fb.h> 	//fb_fix_screeninfo��FBIOGET_FSCREENINFO��

#include <fb.h>


static int fb_fd = -1;
static unsigned long *fbp = NULL;
static struct fb_fix_screeninfo 	fix_screen = {0};
static struct fb_var_screeninfo		var_screen = {0};


int fb_open(void)
{
	int ret = -1;
	
	//�ڶ�������framebuffer�ļ�
	fb_fd = open(MYFB0 ,O_RDWR);
	if(fb_fd < 0)
	{
		perror("open");
		exit(-1);
	}
	printf("fb_fd = %d\n", fb_fd);
	
	//����������ȡframebuffer�ļ���Һ����Ϣ��
	ret = ioctl(fb_fd, FBIOGET_FSCREENINFO, &fix_screen);
	if(ret < 0)
	{}
	ret = ioctl(fb_fd, FBIOGET_VSCREENINFO, &var_screen);
	if(ret < 0)
	{}
	//���ԣ���ӡ��ȡ��Ϣ��
	printf("smem_start = 0x%lx.\n", fix_screen.smem_start);
	printf("smem_len = %d.\n", fix_screen.smem_len);
	printf("xres = %d.\n", var_screen.xres);
	printf("yres = %d.\n", var_screen.yres);	
	printf("xres_virtual = %d.\n", var_screen.xres_virtual);
	printf("yres_virtual = %d.\n", var_screen.yres_virtual);
	printf("xoffset = %d.\n", var_screen.xoffset);
	printf("yoffset = %d.\n", var_screen.yoffset);

	//���Ĳ�����mmap��framebufferӳ��һ���ڴ�ռ䡣
	fbp = (unsigned long *)mmap(NULL , fix_screen.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
	if(!fbp)
	{
		perror("mmap");
		exit(-1);
	}
	printf("fbp success.\n");
	
	//���岽���������bmpͼƬ��
	
	
	//����������ʾͼƬ
	
	
	//���߲����ر��ļ�

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

//�ֱ�����1024*600��ͼƬ��ʾ
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

//��ͼƬ�趨��ʾ����ʼ�㣬
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

//�ó���ͼƬ��Χ�Ĳ��ֲ���ʾ
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

//�ó���ͼƬ��Χ�Ĳ��ֲ���ʾ,ͼƬ��ת180�ȡ�
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













