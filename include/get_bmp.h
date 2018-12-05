
#define	BMP		"./orange.bmp"

typedef unsigned char	U8;
typedef unsigned int	U32;
typedef unsigned short	U16;


//4、定义一个bmp格式的头文件，这里用一个结构体来表示bmp 格式文件的头，但是由于结构体需要对齐，所以导致字节
//计算出现错误，本来头应该是54个字节，但我们构造的结构体是56个字节。为了解决这个问题，我们把U8	Signatue[2] 
//移到外面，这样就可以使结构体与bmp格式的头对应，但是在读取bmp文件的时候，需要读两次。
struct bmp_header
{
    //bmp header

    U32 FileSize ;     //文件大小
    U16 Reserv1 ; 
    U16 Reserv2 ; 
    U32 FileOffset ;   //文件头偏移量

    //DIB header
    U32 DIBHeaderSize ; //DIB头大小
    U32 ImageWidth   ;  //文件宽度
    U32 ImageHight   ;  //文件高度
    U16 Planes       ; 
    U16 BPP          ;  //每个相素点的位数
    U32 Compression  ; 
    U32 ImageSize    ;  //图文件大小
    U32 XPPM ; 
    U32 YPPM ; 
    U32 CCT ; 
    U32 ICC ;          
};


int is_bmp(unsigned char *pathname);

int bmp_get(struct bmp_info *pPic);







