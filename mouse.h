#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <bios.h>
extern union REGS inregs,outregs;
//�õ�ʱ��Ҫ���ȶ���ȫ�ֱ���inregs��outregs
void initmouse();//����ʼ����������һ����İ�������������ĺ�����ֻ��Ҫ��ʼ��һ��
char mouseclick();//�������������1���Ҽ�����2���޵����������0����֧�ֹ���
void mousemove();//����ƶ��������е������������������ʱ�˳�����
void initmouse()
{
	inregs.x.ax=0;
	int86(0x33,&inregs,&outregs);
	inregs.x.ax=1;
	int86(0x33,&inregs,&outregs);
}
char mouseclick()
{
	int b;
	inregs.x.ax=3;
	int86(0x33,&inregs,&outregs);
	b=outregs.x.bx;
	if(b%2==1)
		return 1;
	else if((b>>1)/2==1)
		return 2;
	else
		return 0;
}
void mousemove()
{
	int i=0,prex,prey;
	void*buf;
	buf=malloc(imagesize(1,1,5,5));
	setcolor(RED);
	circle(50,50,30);
	while(!outregs.x.bx&&!bioskey(1))
	{
		inregs.x.ax=3;
		int86(0x33,&inregs,&outregs);
		if(prex!=outregs.x.cx||prey!=outregs.x.dx)
		{
			putimage(prex,prey,buf,0);
			prex=outregs.x.cx;
			prey=outregs.x.dx;
			getimage(outregs.x.cx,outregs.x.dx,outregs.x.cx+4,outregs.x.dx+4,buf);
			bar(outregs.x.cx,outregs.x.dx,outregs.x.cx+4,outregs.x.dx+4);
			
		
		}
		;
		prex=outregs.x.cx;
		prey=outregs.x.dx;
	}
	putimage(prex,prey,buf,0);
	free(buf);
}