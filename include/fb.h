

#define 	MYFB0		"/dev/fb0"
#define WIDTH	1024
#define HEIGHT	600
#define WRITE	0xffffffff
#define BLACK	0x00000000
#define BLUE	0xff0000ff
#define RED		0xffff0000
#define GREEN	0xff00ff00

void fb_draw_pixel(unsigned x, unsigned y, unsigned color);
void fb_draw_picture(unsigned int x, unsigned int y, const unsigned char *str);
void fb_draw_picture1(unsigned int i, unsigned int j, const unsigned char *str);
void fb_draw_picture2(unsigned int x, unsigned int y, const unsigned char *str);
void fb_draw_picture3(unsigned int x, unsigned int y, const unsigned char *str);
void fb_draw_picture4(unsigned int x, unsigned int y, const unsigned char *str);



void fb_draw_back(unsigned int i, unsigned int j, unsigned long color);
int fb_open(void);
void fb_close(void);



