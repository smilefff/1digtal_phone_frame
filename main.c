#include <stdio.h>
#include <unistd.h>

#include <fb.h>


#include <config.h>
#include "1024600.h"
#include "500300.h"

#include "get_bmp.h"

static unsigned char pathname[100] = BMP;
struct bmp_info pPicure = {0};

int main(void)
{
	int x,y;
	x = 0;
	y = 0;
	printf("hello world\n");
	is_bmp("./orange.bmp");

	fb_open();

	fb_draw_picture(x, y, picture);

	sleep(1);
	bmp_get(&pPicure);


	fb_close();

	return 0;
}










