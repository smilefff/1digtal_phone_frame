
#define	BMP		"./orange.bmp"

typedef unsigned char	U8;
typedef unsigned int	U32;
typedef unsigned short	U16;


//4������һ��bmp��ʽ��ͷ�ļ���������һ���ṹ������ʾbmp ��ʽ�ļ���ͷ���������ڽṹ����Ҫ���룬���Ե����ֽ�
//������ִ��󣬱���ͷӦ����54���ֽڣ������ǹ���Ľṹ����56���ֽڡ�Ϊ�˽��������⣬���ǰ�U8	Signatue[2] 
//�Ƶ����棬�����Ϳ���ʹ�ṹ����bmp��ʽ��ͷ��Ӧ�������ڶ�ȡbmp�ļ���ʱ����Ҫ�����Ρ�
struct bmp_header
{
    //bmp header

    U32 FileSize ;     //�ļ���С
    U16 Reserv1 ; 
    U16 Reserv2 ; 
    U32 FileOffset ;   //�ļ�ͷƫ����

    //DIB header
    U32 DIBHeaderSize ; //DIBͷ��С
    U32 ImageWidth   ;  //�ļ����
    U32 ImageHight   ;  //�ļ��߶�
    U16 Planes       ; 
    U16 BPP          ;  //ÿ�����ص��λ��
    U32 Compression  ; 
    U32 ImageSize    ;  //ͼ�ļ���С
    U32 XPPM ; 
    U32 YPPM ; 
    U32 CCT ; 
    U32 ICC ;          
};


int is_bmp(unsigned char *pathname);

int bmp_get(struct bmp_info *pPic);







