// mouse
#include "util.h"
/* mouse moudle. */

//���
#define MOUSE_LEFTPRESS 1
//�Ҽ�
#define MOUSE_RIGHTPRESS 2
//û�а������
#define MOUSE_NOPRESS 0

bool initmouse(void);
//��ʾ���
int showmouseptr(void);
//�������
int hidemouseptr(void);
//�õ����λ�úͰ���״̬��ȡֵΪ����3���꣩
bool getmousepos(int *button,int *x,int *y);