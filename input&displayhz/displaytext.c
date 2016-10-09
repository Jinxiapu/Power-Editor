#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <bios.h>
#include <string.h>

struct fonts				//adjust the function according to different hzk
{
	unsigned char hzk;
	FILE *fp;
	unsigned char height;
	unsigned char width;
	unsigned int bytes;// bytes every hanzi occupys in hzk file
};
void enchoose(struct fonts *font);	
void displayhz(int bs,unsigned int innercode,unsigned char fontchoose,int x0,int y0,int textcolor,int bkcolor);
unsigned int receivehz(int bs,char*pinyin,int mode);
void displayen(int bs,unsigned int innercode,unsigned char fontchoose,int x0,int y0,int textcolor,int bkcolor);
void hzkchoose(struct fonts *font);
void linefeed(int *x,int *y,int width,int height)
{
	if(*x>getmaxx())
	{
		*x=0;
		*y+=height;
	}
	else if(*x<0)
	{
		*x=getmaxx()+1-width;
		*y-=height;
	}
	if(*y<height)
	{
		*x=0;
		*y=height;
	}
}
void displaytext(unsigned char hzk,unsigned char enzk,int x0,int y0,int textcolor,int bkcolor)//����1˵������esc���˳�
{
	int spckey,c,currentx=x0,currenty=y0;
	char curlshift,prelshift,language,temp,pinyin[7]={0};
	struct fonts font,enfont,*allfont,*curfont;
	FILE*fq=fopen("hzoren.bin","w+");
	font.hzk=hzk;
	enfont.hzk=enzk;
	hzkchoose(&font);
	enchoose(&enfont);
	language=0;//Ĭ��languageΪ�������뷨
	while(1)
	{
		spckey=bioskey(2);
		curlshift=spckey/2%2;/////////////��shift������Ӣ��
		if(curlshift&&prelshift==0)
		language=!language;
		prelshift=curlshift;
		if(!bioskey(1))
		{
			continue;
		}//û���������ѭ��
		c=bioskey(1);
		if(c==283)
			break;

		if(language==0)//�������뷨
		{
			curfont=&font;
			c=receivehz(1,pinyin,0);
			while(c==8&&strlen(pinyin)!=0)
			{
				c=receivehz(0,pinyin,1);
				if(strlen(pinyin)==0)///////���ƴ���˵�ͷ
				{
					c=0;
					break;		
				}	
			}
			if(c==0)///////cֵ����Ҫ��
				continue;
		}
		else if(language==1)
		{
			curfont=&enfont;
			c=bioskey(0);
		}
		if(language==0&&c==8||language==1&&c==3592)//backspace�Ĵ���
		{
			fseek(fq,-1,SEEK_END);///�ж�backspace����Ӣ�Ļ��Ǻ��֣�Ҫ��
			fread(&temp,1,1,fq);///�ж�backspace����Ӣ�Ļ��Ǻ��֣�Ҫ��
			if(temp==0)
				allfont=&font;
			else
				allfont=&enfont;
			currentx-=allfont->width;
			linefeed(&currentx,&currenty,allfont->width,allfont->height);
			moveto(currentx,currenty);
			if(temp==1)
				displayen(1,' ',enfont.hzk,currentx,currenty,textcolor,bkcolor);
			if(temp==0)
				displayhz(1,0xa1a1,font.hzk,currentx,currenty,textcolor,bkcolor);
			continue;
			
		}
		if(language==0)
			displayhz(1,c,font.hzk,currentx,currenty,textcolor,bkcolor);

		else if(language==1)
			displayen(1,c%256,enfont.hzk,currentx,currenty,textcolor,bkcolor);	

		currentx+=curfont->width;
		linefeed(&currentx,&currenty,curfont->width,curfont->height);
		moveto(currentx,currenty);

		fwrite(&language,1,1,fq);

	}	
			fclose(fq);
}
void main()
{
	int gdriver=DETECT,gmode,esc;
	initgraph(&gdriver,&gmode,"c:\\borlandc\\bgi");
	displaytext(2,0,0,16,1,15);
	closegraph();
}
