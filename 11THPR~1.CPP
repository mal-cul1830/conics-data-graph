#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<dos.h>
#include<math.h>

//the functions outside main

void ellipses(float a,float b,float g,float f)
{
	int x,y;
	x=-g/2*a;
	y=-f/2*b;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	line(getmaxx()/2,0,getmaxx()/2,getmaxx());
	line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
	ellipse(getmaxx()/2+x,getmaxy()/2+y,0,360,a*50,b*50);
	cout<<"click any key to continue"<<endl;
	getch();
}

void parabola(float a,float b,float g,float f)
{
	float x1,y1,x2,y2;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	line(getmaxx()/2,0,getmaxx()/2,getmaxy());
	line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
	if(a==0.0)
	{
		for(int i=0;i<getmaxy()/2;i++)
		{
			y1=i;
			x1=y1*y1/-g;
			y2=i+1;
			x2=y2*y2/-g;
			line(x1*10+getmaxx()/2,getmaxy()/2-y1*10,x2*10+getmaxx()/2,getmaxy()/2-y2*10);
			line(x1*10+getmaxx()/2,getmaxy()/2+y1*10,x2*10+getmaxx()/2,getmaxy()/2+y2*10);
		}
	}
	if(b==0.0)
	{
		for(int i=0;i<getmaxx()/2;i++)
		{
			x1=i;
			y1=x1*x1/-f;
			x2=i+1;
			y2=x2*x2/-f;
			line(-x1*10+getmaxx()/2,getmaxy()/2-y1*10,-x2*10+getmaxx()/2,getmaxy()/2-y2*10);
			line(x1*10+getmaxx()/2,getmaxy()/2-y1*10,x2*10+getmaxx()/2,getmaxy()/2-y2*10);
		}
	}
	getch();
	closegraph();
}

void lines(float g,float f,float c)
{
	float m,x1,y1,x2,y2,x,y,i;
	m=-g/f;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	for(i=0;(x1!=getmaxx()/2&&y!=getmaxy()/2)&&i<2000;i++)
	{
		x=i;
		y=m*x+c;
		putpixel(x,getmaxy()-(getmaxy()/2-y), WHITE);
	}
	setcolor(WHITE);
	line(getmaxx()/2,0,getmaxx()/2,getmaxy());
	line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
	getch();
	closegraph();
}

void circles(float a,float b,float g,float f,float c)
{
	float x,y,r;
	a/=a;
	b/=b;
	c/=a;
	f/=a;
	g/=a;
	c/=b;
	f/=b;
	g/=b;
	c+=(-f/2)*(-f/2);
	c+=(-g/2)*(-g/2);
	x=(-g/2);
	y=(-f/2);
	r=sqrt(-c);
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	circle(x*50+getmaxx()/2,y*50+getmaxy()/2,r*50);
	line(getmaxx()/2,0,getmaxx()/2,getmaxy());
	line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
	getch();
	closegraph();
}

void welcome()
{
	int gd=DETECT,gm;
	char d=' ';
	d+=146;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	gotoxy(getmaxx()/2,getmaxy()/2);
	outtextxy(getmaxx()/2-30,getmaxy()/2-60,"LOADING");
	cout<<"                      ";
	gotoxy(getmaxx()/2,getmaxy()/2);
	for(int i=0;i<360;i++)
	{
		setfillstyle(SOLID_FILL,WHITE);
		pieslice(getmaxx()/2,getmaxy()/2,0,i,30);
		delay(10);
	}
	cleardevice();
	cout<<endl;
	settextstyle(7,0,5);
	outtextxy(70,getmaxy()/2-200,"THE GRAPH PLOTTER");
	outtextxy(50,getmaxy()/2+30,"Click ENTER to continue");
	getch();
	cleardevice();
}

int feed(char x)
{
	switch(x)
	{
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
	}
	return x;
}

int getconst(char eqn[])
{
	int i,c=0,j;
	for(i=0;eqn[i]!='\0';i++);
	for(;eqn[i]!='+'&&eqn[i]!='-';i--);
	i++;
	j=i;
	for(;eqn[i]!='\0';i++)
	{
		if(eqn[i]!='x'&&eqn[i]!='y')
		{
			c+=feed(eqn[i]);
			c*=10;
		}
	}
	c/=10;
	if(eqn[j-1]=='-')
	c=-c;
	cout<<"c = "<<c<<endl;
	return c;
}

int getthat(int i,char eqn[])
{       // +123x^2+246y
	int coeff=0,count=0,m,j;
	for(j=i-1;eqn[j]!='+'&&eqn[j]!='-'&&j>=0;j--)
	count++;
	count--;

	//m=pow(10,count);               //malu to check

	for(;eqn[i]!='+'&&eqn[i]!='-'&&i>=0;i--);
	i++;
	for(;eqn[i]!='x'&&eqn[i]!='y';i++)
	{
		coeff+=feed(eqn[i]);
		coeff*=10;
	}
	coeff/=10;
	return coeff;
}

void axes0400(char namex[20], char namey[20])
{
	line(50,50,50,450);        //y axis
	line(50,450,600,450);      //x axis
	outtextxy(40,40, "Y");
	outtextxy(605,450, "X");
	outtextxy(40,455, "0");
	outtextxy(300,465, namex);
	outtextxy(20,355, "100");
	outtextxy(20,255, "200");
	outtextxy(20,155, "300");
	outtextxy(20,55, "400");
	settextstyle(DEFAULT_FONT, VERT_DIR,0);
	outtextxy(20,200, namey);
}

void axes050(char namex[20], char namey[20])
{
	line(50,50,50,450);        //y axis
	line(50,450,600,450);      //x axis
	outtextxy(40,40, "Y");
	outtextxy(605,450, "X");
	outtextxy(40,455, "0");
	outtextxy(300,465, namex);
	outtextxy(30,370, "10");
	outtextxy(30,290, "20");
	outtextxy(30,210, "30");
	outtextxy(30,130, "40");
	outtextxy(30,50, "50");
	settextstyle(DEFAULT_FONT, VERT_DIR,0);
	outtextxy(20,200, namey);
}

void axes0100(char namex[20], char namey[20])
{
	line(50,50,50,450);        //y axis
	line(50,450,600,450);      //x axis
	outtextxy(40,40, "Y");
	outtextxy(605,450, "X");
	outtextxy(40,455, "0");
	outtextxy(300,465, namex);
	outtextxy(30,410, "10");
	outtextxy(30,370, "20");
	outtextxy(30,330, "30");
	outtextxy(30,290, "40");
	outtextxy(30,250, "50");
	outtextxy(30,210, "60");
	outtextxy(30,170, "70");
	outtextxy(30,130, "80");
	outtextxy(30,90, "90");
	outtextxy(30,50, "100");
	settextstyle(DEFAULT_FONT, VERT_DIR,0);
	outtextxy(20,200, namey);
}

void scale0400(char xname[30], char yname[30])
{
	line(50,50,50,450);        //y axis
	line(50,450,600,450);      //x axis
	outtextxy(40,40, "Y");
	outtextxy(605,450, "X");
	outtextxy(40,455, "0");
	outtextxy(585,460, xname);
	outtextxy(20,355, "100");
	outtextxy(20,255, "200");
	outtextxy(20,155, "300");
	outtextxy(20,55, "400");
	settextstyle(DEFAULT_FONT, VERT_DIR,0);
	outtextxy(20,200, yname);
}

void scale050(char xname[30], char yname[30])
{
	line(50,50,50,450);        //y axis
	line(50,450,600,450);      //x axis
	outtextxy(40,40, "Y");
	outtextxy(605,450, "X");
	outtextxy(40,455, "0");
	outtextxy(585,460, xname);
	outtextxy(30,370, "10");
	outtextxy(30,290, "20");
	outtextxy(30,210, "30");
	outtextxy(30,130, "40");
	outtextxy(30,50, "50");
	settextstyle(DEFAULT_FONT, VERT_DIR,0);
	outtextxy(20,200, yname);
}

void scale0100(char xname[30], char yname[30])
{
	line(50,50,50,450);        //y axis
	line(50,450,600,450);      //x axis
	outtextxy(40,40, "Y");
	outtextxy(605,450, "X");
	outtextxy(40,455, "0");
	outtextxy(585,460, xname);
	outtextxy(30,410, "10");
	outtextxy(30,370, "20");
	outtextxy(30,330, "30");
	outtextxy(30,290, "40");
	outtextxy(30,250, "50");
	outtextxy(30,210, "60");
	outtextxy(30,170, "70");
	outtextxy(30,130, "80");
	outtextxy(30,90, "90");
	outtextxy(30,50, "100");
	settextstyle(DEFAULT_FONT, VERT_DIR,0);
	outtextxy(20,200, yname);
}

void main()
{

	welcome();
	int er;
	char in[20];
	cout<<'\n'<<"Welcome to The Graph Plotter."<<'\n'<<"This program enables you to plot a graph based on data provided or based"<<'\n'<<"on an equation"<<'\n'<<"To continue, choose 1 or 2 -"<<endl;
	re:
	cout<<"1.DATA-BASED GRAPH"<<'\n'<<"2.EQUATION-BASED GRAPH"<<endl;
	cin>>in;
	if(in[0]!='1'&&in[0]!='2')
		{
			cout<<"enter valid input"<<endl;
			goto re;
		}
	if(in[0]=='1')
	{
		//data-based
		START:
		clrscr();
		char xname[30], yname[30],n1[30][30],namex[20],namey[20],x[30][30],datn[30][30],choice[20];
		int y[30],i=0,total,topy=0,lowx,lowy,topyaxis,topxaxis,j,diff,f[10],no,topval=0,col,n;
		float data[50],sum=0,perc[50],deg[50],k;
		cout<<"ENTER :"<<endl;
		res:
		cout<<"1.LINE GRAPH"<<endl;
		cout<<"2.BAR GRAPH"<<endl;
		cout<<"3.PIE CHART"<<endl;
		cout<<"ENTER CHOICE - ";
		gets(choice);
		cout<<endl;
		if(choice[0]!='1'&&choice[0]!='2'&&choice[0]!='3')
			{
				cout<<"enter valid choice"<<endl;
				goto res;
			}
		if(choice[0]=='1')
		{
			clrscr();
			cout<<"Welcome to LINE GRAPH."<<endl;
			cout<<"LINE GRAPH enables you to draw a graph on entering a certain data and"<<endl;
			cout<<"its respective frequency. You can enter a maximum of 30 data values, "<<endl;
			cout<<"with frequencies ranging from 0 to 400."<<endl;
			cout<<"NOTE : NO NEGATIVE VALUES. Press any key to continue."<<endl<<endl;
			getch();
			cout<<"To draw the line graph - "<<endl;
			cout<<"Enter your X axis plot name - ";
			gets(xname);
			cout<<"Enter your Y axis plot name - ";
			gets(yname);
			cout<<"Provide the total number of plots you would like to use - ";
			cin>>total;
			cout<<endl;
			cout<<"Enter name of X coordinate and corresponding Y coordinate.(Ensure that you only enter integer value!):-"<<endl<<endl;
			cout<<"NAME"<<'\t'<<'\t'<<'\t'<<"FREQUENCY( ENTER ONLY DIGITS - NO SPECIAL CHARS,ALPHABETS ) "<<endl;
			for(i=1;i<=total;i++)
			{
				cout<<i<<". ";
				gets(x[i]);
				cout<<'\t'<<'\t'<<'\t';
				cin>>y[i];
				cout<<endl;
			}

			for(i=1;i<=total;i++)             //to find highest value of x and y
			{
				if (y[i]>topy)
				topy=y[i];
			}
			lowy=topy;
			for(i=1;i<=total;i++)         //to find lowest value of x and y
			{
				if (y[i]<lowy)
				lowy=y[i];
			}

			diff=500/(total+1);
			int gd=DETECT;                //prints axes and line...
			int gm;
			initgraph(&gd,&gm,"C:\\TC\\BGI");

			if (topy<=50 && lowy>=0)
			{
				scale050(xname,yname);
				for(i=1;i<total;i++)
				{
					setcolor(YELLOW);
					line ( 50+(diff*i), 450-(y[i]*8), 50+(diff*(i+1)), 450-(y[i+1]*8) );
				}
				for(i=1;i<=total;i++)
				{
					setcolor(WHITE);
					settextstyle(DEFAULT_FONT, HORIZ_DIR,0);
					outtextxy(50+(diff*i), 460, x[i]);
				}
			}
			else if (topy<=100 && lowy>=0)
			{
				scale0100(xname,yname);
				for(i=1;i<total;i++)
				{
					setcolor(YELLOW);
					line ( 50+(diff*i), 450-(y[i]*4), 50+(diff*(i+1)), 450-(y[i+1]*4) );
				}
				for(i=1;i<=total;i++)
				{
					setcolor(WHITE);
					settextstyle(DEFAULT_FONT, HORIZ_DIR,0);
					outtextxy(50+(diff*i), 460, x[i]);
				}
			}

			else if (topy<=400 && lowy>=0)
			{
				scale0400(xname,yname);
				for (i=1;i<total;i++)
				{
					setcolor(YELLOW);
					line ( 50+(diff*i), 450-y[i], 50+(diff*(i+1)), 450-y[i+1] );
				}
				for (i=1;i<=total;i++)
				{
					setcolor(WHITE);
					settextstyle(DEFAULT_FONT, HORIZ_DIR,0);
					outtextxy(50+(diff*i), 460, x[i]);
				}
			}
			getch();
			closegraph();
		}

		else if(choice[0]=='2')
		{
			clrscr();
			cout<<"Welcome to BAR GRAPH."<<endl;
			cout<<"BAR GRAPH enables you to draw a bar graph on entering a certain data and"<<endl;
			cout<<"its respective frequency. You can enter a maximum of 30 bar values, "<<endl;
			cout<<"with frequencies ranging from 0 to 400."<<endl;
			cout<<"NOTE : NO NEGATIVE VALUES. Press any key to continue."<<endl<<endl;
			getch();
			cout<<"To draw the bar graph - "<<endl;
			cout<<"Enter your X axis plot name - ";
			gets(namex);
			cout<<"Enter your Y axis plot name - ";
			gets(namey);
			cout<<"Provide the total number of bars you would like to use (ENTER ONLY DIGITS - NO SPECIAL CHARACTERS,ALPHABETS) - ";
			cin>>no;
			cout<<endl;
			cout<<"Enter name of X coordinate and corresponding Y coordinate:-"<<endl<<endl;
			cout<<"NAME"<<'\t'<<'\t'<<'\t'<<"FREQUENCY (ENTER ONLY DIGITS - NO SPECIAL CHARACTERS, ALPHABETS) "<<endl;

			for(i=1;i<=no;i++)            //accepts x and y values
			{
				cout<<i<<". ";
				gets(n1[i]);
				cout<<'\t'<<'\t'<<'\t';
				cin>>f[i];
				cout<<endl;
			}

			for(i=1;i<=no;i++)           //find topf
			{
				if (f[i]>=topval)
				topval=f[i];
			}

			int lowval=topval;
			for(i=1;i<=no;i++)                      //finds lowf
			{
				if (f[i]<=lowval)
				lowval=f[i];
			}

			diff=500/no+1;
			int gd=DETECT;
			int gm;
			initgraph(&gd,&gm,"C:\\TC\\BGI");

			if (topval<=50 && lowval>=0)
			{
				axes050(namex,namey);
				for(i=1;i<=no;i++)
				{
					setfillstyle(1,i+3);
					bar(50+(diff*i),450-(f[i]*8),60+(diff*i),450);
				}
				for (i=1;i<=no;i++)
				{
					setcolor(WHITE);
					settextstyle(DEFAULT_FONT, HORIZ_DIR,0);
					outtextxy(50+(diff*i), 440-(f[i]*8), n1[i]);
				}
				getch();
				closegraph();
			}

			else if(topval<=100 && lowval>=0)
			{
				axes0100(namex,namey);
				for(i=1;i<=no;i++)
				{
					setfillstyle(1,i+3);
					bar(50+(diff*i),450-(f[i]*4),60+(diff*i),450);
				}
				for (i=1;i<=no;i++)
				{
					setcolor(WHITE);
					settextstyle(DEFAULT_FONT, HORIZ_DIR,0);
					outtextxy(50+(diff*i), 440-(f[i]*4), n1[i]);
				}
				getch();
				closegraph();
			}

			else
			{
				axes0400(namex,namey);
				for(i=1;i<=no;i++)
				{
					setfillstyle(1,i+3);
					bar(50+(diff*i),450-f[i],60+(diff*i),450);
				}
				for (i=1;i<=no;i++)
				{
					setcolor(WHITE);
					settextstyle(DEFAULT_FONT, HORIZ_DIR,0);
					outtextxy(50+(diff*i), 440-f[i], n1[i]);
				}
				getch();
				closegraph();
			}
		}

		else if(choice[0]=='3')
		{
			clrscr();
			cout<<"Welcome to PIE CHART."<<endl;
			cout<<"PIE CHART enables you to draw a pie chart on entering a certain data and"<<endl;
			cout<<"its respective frequency. You can enter a maximum of 30 pie slices."<<endl;
			cout<<"NOTE : NO NEGATIVE VALUES. Press any key to continue."<<endl<<endl;
			getch();
			cout<<"Enter number of sectors, ie, pie slices required (ENTER ONLY DIGITS - NO SPECIAL CHARACTERS, ALPHABETS) - ";
			cin>>n;
			cout<<"Below, enter the name of each pie slice and its corresponding frequency :-"<<endl;
			cout<<"NAME"<<'\t'<<'\t'<<'\t'<<"FREQUENCY (ENTER ONLY DIGITS - NO SPECIAL CHARACTERS, ALPHABETS)"<<endl;
			for(i=0;i<n;i++)
			{
				cout<<i+1<<".";
				gets(datn[i]);
				cout<<'\t'<<'\t'<<'\t';
				cin>>data[i];
				cout<<endl;
				sum+=data[i];
			}
			data[i]=10101010.0;
			for(i=0;data[i]!=10101010.0;i++)
			{
				perc[i]=data[i]/sum;
			}
			perc[i]=10101010.0;
			for(i=0;perc[i]!=10101010.0;i++)
			{
				deg[i]=perc[i]*360;
				cout<<"fract "<<i+1<<" is measured "<<deg[i]<<endl;
			}
			deg[i]=10101010.0;
			int gd=DETECT,gm;
			initgraph(&gd,&gm,"C:\\TC\\BGI");
			cout<<'\n'<<"KEY - "<<'\n'<<"(In anti-clockwise order from red)"<<endl;
			for(i=0,k=0,col=0;deg[i]!=10101010.0;i++,col++)
			{
				switch(col)
				{
				case 0:
					setfillstyle(SOLID_FILL,RED);
					pieslice(getmaxx()/2,getmaxy()/2,k,k+deg[i],150);
					cout<<"RED - "<<datn[i]<<endl;
					//outtextxy(cos(2*k+deg[i])*150+getmaxx()/2,sin(2*k+deg[i])*150+getmaxy()/2,datn[i]);
					break;
				case 1:
					setfillstyle(SOLID_FILL,BLUE);
					pieslice(getmaxx()/2,getmaxy()/2,k,k+deg[i],150);
					cout<<"BLUE - "<<datn[i]<<endl;
					//outtextxy(cos(2*k+deg[i])*150+getmaxx()/2,sin(2*k+deg[i])*150+getmaxy()/2,datn[i]);
					break;
				case 2:
					setfillstyle(SOLID_FILL,WHITE);
					pieslice(getmaxx()/2,getmaxy()/2,k,k+deg[i],150);
					cout<<"WHITE - "<<datn[i]<<endl;
					//outtextxy(cos(2*k+deg[i])*150+getmaxx()/2,sin(2*k+deg[i])*150+getmaxy()/2,datn[i]);
					break;
				case 3:
					setfillstyle(SOLID_FILL,YELLOW);
					pieslice(getmaxx()/2,getmaxy()/2,k,k+deg[i],150);
					cout<<"YELLOW - "<<datn[i]<<endl;
					//outtextxy(cos(2*k+deg[i])*150+getmaxx()/2+50,sin(2*k+deg[i])*150+50+getmaxy()/2,datn[i]);
					break;
				case 4:
					setfillstyle(SOLID_FILL,GREEN);
					pieslice(getmaxx()/2,getmaxy()/2,k,k+deg[i],150);
					cout<<"GREEN - "<<datn[i]<<endl;
					//outtextxy(cos(2*k+deg[i])*150+getmaxx()/2,sin(2*k+deg[i])*150+getmaxy()/2,datn[i]);
					break;
				case 5:
					setfillstyle(SOLID_FILL,LIGHTBLUE);
					pieslice(getmaxx()/2,getmaxy()/2,k,k+deg[i],150);
					cout<<"LIGHT BLUE - "<<datn[i]<<endl;
					//outtextxy(cos(2*k+deg[i])*150,sin(2*k+deg[i])*150,datn[i]);
					break;
				}
				if(i%5==0)
				col=0;
				k+=deg[i];
			}
			getch();
			closegraph();
		}

		else
		{
			cout<<"ERROR : You have entered an invalid option. Try again.";
			getch();
			goto START;
		}
		getch();
	}
	else if (in[0]=='2')
	{
		char x='x',p='2',ad='+',as='-',y='y',eqn[50];
		int i;
		float xs=0,ys=0,a=0,b=0,d,type;
		float g=0,f=0,h=0,c=0;
		reenter:
		cout << "Enter equation."<<'\n'<<"RULES - "<<'\n'<<"1. MAX - 2 DEGREE EQUATION."<<'\n'<<"2.ALL COEFFICIENTS MUST BE SINGLE DIGIT ONLY!"<<'\n'<<"3. NO HYPERBOLA"<<'\n'<<"4. ENTER CONSTANT TERM AS LAST TERM"<<'\n'<<"5. ONLY PARABOLAS WITH VERTICE AT ORIGIN ACCEPTED "<<endl;
		gets(eqn);
		for(i=0;eqn[i]!='\0';i++)//getting the constants
		{
			if(eqn[i]==x)
			{
				if(eqn[i+2]==p && (eqn[i+1]!=ad || eqn[i+1]!=as))
				{
					cout<<"x^2 loop"<<endl;
					xs=1;
					if(eqn[i-1] == ad || eqn[i-1]==as || i==0)
					{
						a=1;
						if(eqn[i-1]==as)
						a=-a;
						cout<<"a ="<<a<<endl;
					}
					else
					{
						a=getthat(i,eqn);
						if(eqn[i-2]==as)
						a=-a;
						cout<<"a = "<<a<<endl;//check
					}

				}
				else
				{
					cout<<"g loop"<<endl;
					if(eqn[i-1]==ad || eqn[i-1]==as || i==0)
					{
						g=1;
						if(eqn[i-1]==as)
						g=-g;
						cout<<"g = "<<g<<endl;
					}
					else
					{
						g=getthat(i,eqn);
						if(eqn[i-2]==as)
						g=-g;
						cout<<"g = "<<g<<endl;//check
					}

				}
			}
			else if(eqn[i]==y)
			{
				if(eqn[i+2]==p)
				{
					cout<<"y^2 loop"<<endl;
					ys=1;
					if(eqn[i-1]==ad || eqn[i-1]==as || i==0)
					{
						b=1;
						if(eqn[i-1]==as)
						b=-b;
						cout<<"b = "<<b<<endl;
					}
					else
					{
						b=getthat(i,eqn);
						if(eqn[i-2]==as)
						b=-b;
						cout<<"b = "<<b<<endl;//check
					}

				}
				else
				{
					cout<<"f loop"<<endl;
					if(eqn[i-1]==ad || eqn[i-1]==as || i==0)
					{
						f=1;
						if(eqn[i-1]==as)
						f=-f;
					}
					else
					{
						f=getthat(i,eqn);
						if(eqn[i-2]==as)
						f=-f;
						cout<<"f = "<<f<<endl;//check
					}

				}
			}

			if (eqn[i]==x&&eqn[i+1]==y)
			{
				cout<<"xy loop"<<endl;//check
				if(eqn[i-1]==ad || eqn[i-1]==as || i==0)
				{
					h=1;
					if(eqn[i-1]==as)
					h=-h;
				}
				else
				{
					h=getthat(i,eqn);
					if(eqn[i-2]==as)
					h=-h;
					cout<<"h  "<<h<<endl;//check
				}
			}
		}
		c=getconst(eqn);
		d=(a*b*c)+(2*g*f*h)-(a*f*f)-(b*g*g)-(c*f*f);
		//detetection of type
		/*type case 1 = line, 2 = PARABOLLA , 3 = CIRCLE , 4 = HYPERBOLLA , 5 = ELLIPSE 0 = pair of straight lines*/
		if(xs==0&&ys==0)
		{
			type=1;
			goto thatsit;
		}
		if(xs==1||ys==1)
		{
			if(xs==0||ys==0)
			{
				if(d!=0)
				type=2;//parabola
				else
				type=0;
			}
			else
			{
				if(a==b)
				type = 3;
		else if (a>=0 && b>=0 && a!=b)
		   type = 5;
		if (d==0.0)
		   type = 0;
	       else if (((a>=0 && b<0)||(b>=0 && a<0)) && a!=b)
		   type = 4;

	       }

		}//abc+2fgh−af2−bg2−cf2=0
		else
			type=1;//line
		thatsit:
		cout<<"Type = "<<type<<endl;
		cout<<"case 1 = line, 2 = PARABOLLA , 3 = CIRCLE , 4 = HYPERBOLLA , 5 = ELLIPSE 0 = pair of straight lines"<<endl;


		if(type==0)
		    {
			cout<<"pair of straight lines not accepted"<<endl;
			goto reenter;
		       }         //malu - add c or no?
		else if(type==1)
			lines(g,f,c);
		else if(type==2)
			parabola(a,b,g,f);
		else if(type==3)
			circles(a,b,g,f,c);
		else if(type==4)
		{
			cout<<"equation of hyperbola not accepted"<<endl;
			cout<<"reenter equation"<<endl;
			goto reenter;
		}
		else if(type==5)
			ellipses(a,b,g,f);
		else
		{
			cout<<"equation is invalid"<<endl;
			cout<<"reenter equation"<<endl;
			goto reenter;
		}
		getch();
	}
	if(in[0]!='1'&&in[0]!='2')
    {
	cout<<"enter valid input"<<endl;
        goto re;
    }
    char ans;
    cout<<"DO YOU WISH TO EXIT?(Y/N)"<<endl;
    cin>>ans;
    r:
    if(ans=='y'||ans=='Y')
        goto exit;
    else if(ans=='n'||ans=='N')
	goto re;
    else
    {
	cout<<"enter valid answer"<<endl;
	goto r;
    }
    exit:
	getch();
}
