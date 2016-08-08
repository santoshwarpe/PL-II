#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#define pi 3.42
class Pcm
{
	public:
		int F,a;
		int maxx,maxy;
		int midx,midy;
		int arrn[100],count,arrq[100];
		int level;
	void drawgraph();
	void read();
	void analogsignal();
	void sampling();
	void quantization();
	void encoding();
};

void Pcm::read()
{
	cout<<"\n Enter the frequency :";
	cin>>F;
	cout<<"\n Enter the amplitute :";
	cin>>a;
	cleardevice();
}

void Pcm::drawgraph()
{
	maxx=getmaxx();
	maxy=getmaxy();
	midx=maxx/2;
	midy=maxy/2;
	setlinestyle(3,0,2);
	line(midx,0,midx,maxy);
	line(0,midy,maxx,midy);
	putpixel(midx,midy,3);
}

void Pcm::analogsignal()
{
	int xt,t;
	int i;
	drawgraph();
	for(t=0;t<200;t++)
	{
		xt=a*sin((2*pi*1/F*t));
		putpixel(t+midx,-xt+midy,3);
	}
}

void Pcm::sampling()
{
	cleardevice();
	outtextxy(30,30,"Sampling");
	int fs,f;
	int t,xt,i;
	count=0;
	drawgraph();
	fs=2*F;
	for(t=0;t<200;)
	{
		setcolor(5);
		xt=a*sin((2*pi*1/fs*t));
		line(t+midx,midy-xt,t+midx,midy);
		count++;
		t=t+10;
	}
getch();
return;
}

void Pcm::quantization()
{
	cleardevice();
	//int level;
	cout<<"\n Enter the no. of levels:";
	cin>>level;
	int i,b,xt,c;
	b=0;
	int yinc;
	cleardevice();
	analogsignal();
	sampling();
	outtextxy(50,50,"Quantization");
	yinc=midy+a;
	b=2*a/level; //for positive and negative quantization
	for(i=0;i<=level;i++)
	{
		line(midx,yinc,2*midx,yinc);
		arrq[i]=yinc-midy;
		yinc=yinc-b;
	}
}

void Pcm::encoding()
{
	cleardevice();
	int arr[5];
	int end;
	int i,q,val;
	end=level/2;

	for(i=0;i<end;i++)
	{
		arr[i]=0;
	}

	cout<<"\n Enter the value to be encoded:";
	cin>>val;

	if(end==3 && val>=8)
	{
		cout<<"\n Sorry value cannot be more or equal to 8 for 6 levels!";
		return;
	}

	if(end==4 && val>=16)
	{
		cout<<"\n Sorry value cannot be more or equal to 16 for 8 levels!";
		return;
	}

	if(end==5 && val>=32)
	{
		cout<<"\n Sorry value cannot be more than 32 for 5 levels!";
		return;
	}

	q=val;

	for(i=0;q!=0;i++)
	{
		arr[i]=q%2;
		q=q/2;
	}

	cout<<"\n Encoded value of "<<val<<": ";

	for(i=end-1;i>=0;i--)
	{
		cout<<arr[i];
	}
}

int main()
{
	clrscr();
	int gd,gm;
	Pcm p;
	gd=DETECT;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	setcolor(5);
	p.read();
	p.analogsignal();
	getch();
	p.sampling();
	p.quantization();
	getch();
	p.encoding();
	getch();
return 0;
}