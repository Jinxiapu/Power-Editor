#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
struct fonts
{
	unsigned char hzk;
	FILE *fp;
	unsigned char height;
	unsigned char width;
	unsigned int bytes;
};


void displayen(int bs,unsigned int innercode,unsigned char fontchoose,int x0,int y0,int textcolor,int bkcolor);
/*�������ڲ���ɾ���������λ�õı仯*/
void adjusttext(int x0,int y0,int length,int height,struct fonts *font,void *charu)//x0,y0ΪҪ����λ�õĵײ�����
{
	int xmax=getmaxx(),i=0;
	int ymax=getmaxy();
	int mallocsize=imagesize(0,0,xmax,font->height);
	void *a=malloc(mallocsize);
	void *c=malloc(mallocsize);
	void *d=malloc(mallocsize);
	int length1=xmax-x0-length;
	int length3=xmax-length;
	int currenty=y0-font->height;
	int currentx=x0;
	getimage(x0,currenty,x0+length1,currenty+font->height,c);
	getimage(x0+length1,currenty,xmax,currenty+font->height,d);//����length��һ��
	if(charu!=NULL)
		putimage(x0,currenty,charu,COPY_PUT);
	putimage(x0+length,currenty,c,COPY_PUT);//��һ�д�����
	memmove(a,d,mallocsize);
	currenty+=font->height;
	while(1)
	{
		if(currenty+font->height>ymax)
		{
			break;
		}
		getimage(0,currenty,length3,currenty+font->height,c);
		getimage(length3,currenty,xmax,currenty+font->height,d);
		putimage(0,currenty,a,COPY_PUT);
		memmove(a,d,mallocsize);//memmove(void *dest,void *b,int bytes);��bָ��Ĵ�СΪbytes����������dest
		putimage(length,currenty,c,COPY_PUT);//�ڶ��д�����
		currenty+=font->height;
	}
	free(a);
	free(c);
	free(d);
}
/*void main()
{
	int gdriver=DETECT,gmode,j,i;
	struct fonts font;
	void *charu;
	font.height=16;
	initgraph(&gdriver,&gmode,"c:\\borlandc\\bgi");
	setbkcolor(WHITE);
	charu=malloc(imagesize(1,1,129,17));
	for(j=0;j<4;j++)
	for(i=0;i<80;i++)
	displayen(1,'1'+i,0,8*i,16*j,1,15);
	getimage(0,240,128,240+16,charu);
	getch();
	adjusttext(23,16,128,16,&font,charu);
	getch();
	free(charu);
	closegraph();
}*/