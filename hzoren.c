/*width��Ӣ�ĵĿ��*/
#include <stdio.h>
#include <graphics.h>
unsigned char  hzoren(int pixelx,int pixely,unsigned char *text1,int width,int height)
{
	int x=0,y=height,flag=0;
	unsigned char *text=text1;
	while(*text!=0)
	{
			flag=0;
			

			if(*text>>7==0)
			{
				if(*text==10)
				{
					x=0;
					y+=height;
					text++;
					continue;
				}
				if(pixelx<x+width/2&&pixelx>=x&&pixely<=y&&pixely>y-height)//Ӣ������
					return 0;
				if(pixelx<x+width&&pixelx>=x+width/2&&pixely<=y&&pixely>y-height)//Ӣ���Ұ��
					return 1;
				x+=width;
				linefeed(&x,&y,width,height);
				text++;
				continue;
			}
			if(*text>>7==1)
			{
				x+=2*width;
				if(x-2*width<getmaxx()&&x-2*width>getmaxx()-2*width+1)
				{
					if(x-2*width<=pixelx&&pixelx<=getmaxx()&&pixely<=y&&pixely>y-height)//�����õĿո�
						return 4;
				}
				if(x-2*width<=pixelx&&pixelx<x-width&&pixely<=y&&pixely>y-height)//��������
					return 2;
				if(x-width<=pixelx&&pixelx<x&&pixely<=y&&pixely>y-height)//�����Ұ��
					return 3;
				linefeed(&x,&y,width,height);
				text+=2;

			

				
			}
			if(pixely+height<y){
				//printf("s");
				return 5;}
	}
	return 0;
}