#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<conio.h>
#include<windows.h>
#define chang 100
using namespace std;
class obj//����
{
public:
	int x,y,l,h;//�����Ͻ�x,y������l,h;�������Ͻ�x�������Ͻ�y���ڿ�h
	void move(int);//��
	obj()
	{
		y=3;x=5;l=3,h=2;
	}
	void setTube();
}bird,tube[30];
int guo=0,cnt=0,gg=0,p=1,level=15;//cnt���˼�������,guo���˼������ӣ�gg�ж��Ƿ�dead,p�ж��Ƿ��ؿ�
void prin(obj&);//��ӡ��ͼƬ
void chu();//����
void move();//�ܶ�
bool gameover();//��Ϸ�����ж�
void startBackground();//��ʼ����Now can you hear me can you hear me
bool stopg();//��Ϸ��������
void gotoxy(int, int);
void HideCuesor();
void xianshi()
{
	gotoxy(65,7);cout<<"FLAPPY BLOCK";
	int n=cnt;
	gotoxy(62,10);cout<<"YOUR SCORE:";
	for(int i=0;i<4;++i)
	{
		gotoxy(77-i,10);
		cout<<n%10;n/=10;
	}
}
int main()
{
	
	srand(time(NULL));
	system("mode con cols=80 lines=27");
	gotoxy(34,8);
	cout<<"Flappy Block";
	gotoxy(23,10);
	cout<<"ʹ�����������ƶ�����ܹܵ������ܴ����߽�";
	gotoxy(14,11);
	cout<<"������ܵ����(3��30��������(��ʼ����15��10������Ե))";
	gotoxy(39,12);
	cin>>level;
	while(level<3||level>30)
	{
		gotoxy(36,13);
		cout<<"��������";
		gotoxy(39,12);
		cout<<"  ";
		gotoxy(39,12);
		cin>>level;
	}
	gotoxy(36,13);
	cout<<"���ڼ���";
	Sleep(1000);
    while(p)
    {
        system("cls");
        startBackground();
        prin(bird);
        int shu=0;//shu���Ƴ���һ���ܵļ��
        while(1)
        {
            shu=(shu+1)%level;
            if(shu==0)
            chu();
			xianshi();
            int t=5;
            while(--t)
            {
                if(kbhit()!=0)
                {
                    bird.move(1);//�������½�
                    if(gameover()) 
                    {
                        gg=1;break;
                    }
                }
                Sleep(10);
            }
            if(gg) 
			{
				stopg();
				break;
			}
            bird.move(0);
			if(stopg()) break;
            move();
            if(stopg()) break;
        }
    }
	return 0; 
}
bool stopg()
{
	if(gameover())
    {
        gg=1;
        gotoxy(65,13);
        cout<<"Game over!!!";
		gotoxy(63,16);
		cout<<"����������ȼ�";
		gotoxy(67,17);
		cout<<"(0�˳�)";
		gotoxy(64,18);cout<<"level:";
		gotoxy(71,18);
		cin>>level;
		if(level>=3&&level<=30)
			p=1;
		else
		p=0;
		return 1;
    }
	return 0;
}
void obj::move(int p)
{
    for(int i=0;i<l;++i)
    {
        for(int j=0;j<h;++j)
        {
            gotoxy(x+i,y+j);cout<<' ';
        }
    }
	if(p)
	{
		char key_W = GetKeyState(38),     //��� W ���Ƿ���
        key_S = GetKeyState(40),      //��� S ���Ƿ���
        key_A = GetKeyState(37),      //��� A ���Ƿ���
        key_D = GetKeyState(39);     //��� D ���Ƿ���
        if(key_W<0) --y;
        if(key_S<0) ++y;
        if(key_A<0) --x;
        if(key_D<0) ++x;
	}
	else y+=1;
	prin(bird);
	return ;
}
void move()
{
	HideCuesor();
	for(int i=1+guo;i<=cnt;++i)//bagetuidiao,jiashangxinde,bianx,daotouquguanzi,++guo;
	{
		int m=i%30;
		--tube[m].x;	
		for(int j=0;j<tube[m].y;++j)
		{
			if(tube[m].x>=0&&tube[m].x<58)
			gotoxy(tube[m].x+2,j);cout<<' ';
			if(tube[m].x>=0&&tube[m].x<58)
			gotoxy(tube[m].x,j);cout<<'!';
		}
		for(int j=tube[m].y+tube[m].h;j<23;++j)
		{
			if(tube[m].x>=0&&tube[m].x<58)
			gotoxy(tube[m].x+2,j);cout<<' ';
			if(tube[m].x>=0&&tube[m].x<58)
			gotoxy(tube[m].x,j);cout<<'!';
		}
		if(tube[m].x==0) 
		{
			for(int j=0;j<23;++j) gotoxy(0,j),cout<<' ';
			for(int j=0;j<23;++j) gotoxy(1,j),cout<<' ';
			++guo;
		}
	}
}
void prin(obj& m)//
{
    for(int i=0;i<m.l;++i)
    {
        for(int j=0;j<m.h;++j)
        {
            gotoxy(m.x+i,m.y+j);cout<<'=';
        }
    }
	
}
void obj:: setTube()
{
	x=58;y=rand()%15;h=10;
}
void chu()
{
	HideCuesor();
	int m=(++cnt)%30;
	tube[m].setTube();
	for(int i=0;i<tube[m].y;++i)
	{
			gotoxy(tube[m].x,i);
			cout<<"!";
			gotoxy(tube[m].x+1,i);
			cout<<"!";
	}
	for(int i=tube[m].y+tube[m].h;i<23;++i)
	{
		gotoxy(tube[m].x,i);cout<<'!';
		gotoxy(tube[m].x+1,i);cout<<'!';
	}
}
void startBackground()
{
    for(int i=0;i<=25;++i) 
    {
        gotoxy(60,i);cout<<'|';
    }
	for(int i=0;i<59;++i)
	{
		gotoxy(i,23);cout<<'*';
	}
	bird.x=3;bird.y=5;guo=0,cnt=0,gg=0,p=1;
}
bool gameover()
{
	if(bird.x<0||bird.y<0||bird.y>21||bird.x>57) return 1;
	for(int i=guo+1;i<=cnt;++i)
	{
		int m=i%30;
		if(bird.x>tube[m].x-3&&bird.x<tube[m].x+2&&(bird.y<tube[m].y||bird.y>tube[m].y+tube[m].h-2))
		return 1;
	}
	return 0;
}
void HideCuesor()  //���ع��
{
	CONSOLE_CURSOR_INFO c = { 1,0 };  //�ڶ���ֵΪ0Ϊ���ع��
 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
 
}
void gotoxy(int x, int y)  //����ƶ���x,y
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
 
	pos.X = x;
	pos.Y = y;
 
	SetConsoleCursorPosition(handle, pos);
}