/* Polyomino Solver! */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

string itos(int n);
string itos2(int n);
string itoc(char c);
char getch(bool btmp[50]);

int main()
{
	int box;
	int boxtype;
	int tate;
	int yoko;
	int boxwidth;
	int boxheight;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	int p;
	int q;
	int tmp;
	int xmax;
	int xmin;
	int ymax;
	int initx;
	int inity;
	int max;
	int strtmp;
	int piecewidth;
	int pieceheight;
	int boxsize;
	int piecesize;
	int piecenum;
	int piecenum2;
	int print;
	int multiple;
	int maxpiecesizenum;
	
	int itmp1i;
	int itmp1f;
	int jtmp1i;
	int jtmp1f;
	int itmp2i;
	int itmp2f;
	int jtmp2i;
	int jtmp2f;
	int itmp3i;
	int itmp3f;
	int jtmp3i;
	int jtmp3f;
	int itmp4i;
	int itmp4f;
	int jtmp4i;
	int jtmp4f;
	int itmp5i;
	int itmp5f;
	int jtmp5i;
	int jtmp5f;
	
	int xtmp[8];
	int ytmp[8];
	int num[25];
	int numnum[70];
	int piecesizenum[50];
	int strcell[200][10];
	
	bool b1;
	bool b2;
	bool b3;
	bool b4;
	bool b5;
	//bool monomino;
	//bool domino;
	//bool tromino;
	bool bbb[50];
	
	char c;
	
	char boxcode[300];
	char piece[100];
	char piececode[100];
	
	char piecetmp1[10][10];
	char piecetmp2[10][10];
	char piecetmp3[10][10];
	char piecetmp4[10][10];
	char piecetmp5[10][10];
	char piecetmp6[10][10];
	char piecetmp7[10][10];
	char piecetmp8[10][10];
	
	char boxtmp1[50][50];
	char boxtmp2[50][50];
	char boxtmp3[50][50];
	char boxtmp4[50][50];
	char boxtmp5[50][50];
	char boxtmp6[50][50];
	char boxtmp7[50][50];
	char boxtmp8[50][50];
	
	cout << "★☆ ポリオミノ解答プログラム（平面版）by HARAKEN && KITAGAWA ☆★" << endl << endl;
	
	ofstream fout("poliomino.cpp");
	
	if(!fout)
	{
		cout << "！！！設定ファイルをオープンできませんでした。他プロセスからの書き込みが禁止されていないかどうか確かめてください。！！！" << endl;
		return 1;
	}
	
	fout << "#include <iostream>" << endl << "using namespace std;" << endl << "int main(){" << endl;
	fout << "char* p; char* p2; int x , y;";
	fout << "int num , i , j;";
	
	p1:
	cout << "★敷き詰める箱の種類を設定します。1か2を選んでください。" << endl;
	cout << "1．長方形" << endl;
	cout << "2．長方形以外" << endl;
	cin >> box;
	cout << endl;
	
	if(box == 1)
	{
		cout << "★縦の長さと横の長さを設定します（縦≧横にしてください）。" << endl;
		p3:
		cout << "縦の長さを入力してください。" << endl;
		cin >> tate;
		
		if(tate <= 0)
		{
			cout << "！！！縦の長さは自然数でなければなりません。入力し直してください。！！！" << endl;
			goto p3;
		}
		
		p4:
		cout << "横の長さを入力してください。" << endl;
		cin >> yoko;
		
		if(yoko <= 0)
		{
			cout << "！！！横の長さは自然数でなければなりません。入力し直してください。！！！" << endl;
			goto p4;
		}
		
		boxwidth = yoko;
		boxheight = tate;
		boxsize = tate*yoko;
		
		fout << "char cell[" << boxwidth * boxheight << "];" << endl;
		fout << "p = cell; for(i=0; i<" << boxwidth * boxheight << "; i++){*p = \'\\0\'; p++;}" << endl;
		
		if(tate == yoko)
		{
			boxtype = 8;
		}
		else
		{
			boxtype = 4;
		}
	}
	else if(box == 2)
	{
		p5:
		b1 = true;
		b3 = true;
		m = 0;
		n = 0;
		boxwidth = 0;
		boxheight = 1;
		boxsize = 0;
		for(int j=0; j<300; j++)
		{
			boxcode[j] = '\0';
		}
		
		cout << "★箱の形を設定します（全体的に縦≧横の傾向がある方が良い）。" << endl;
		cout << "敷き詰め可能な部分を1、不可能な部分を0として入力してください。" << endl;
		cin >> boxcode;
		
		for(int i=0; boxcode[i]!='\0'; i++)
		{
			if(b1 == true && boxcode[i] == '-')
			{
				boxwidth = i;
				b1 = false;
			}
			if(boxcode[i] == '-')
			{
				boxheight++;
			}
			if(boxcode[i] == '1')
			{
				boxsize++;
			}
			if(boxcode[i] != '0' && boxcode[i] != '1' && boxcode[i] != '-')
			{
				cout << "！！！箱の形の設定が不正です。入力し直してください。！！！" << endl;
				goto p5;
			}
		}
		
		if(b1 == true)
		{
			for(int i=0; i<300; i++)
			{
				if(boxcode[i] == '\0')
				{
					boxwidth = i;
					b1 = false;
					break;
				}
			}
		}
		
		for(int i=0; i<150; i++)
		{
			if(boxcode[(boxwidth+1)*i+boxwidth] != '\0' && boxcode[(boxwidth+1)*i+boxwidth] != '-')
			{
				cout << "！！！箱の形の設定が不正です。！！！" << endl;
				goto p5;
			}
			else if(boxcode[(boxwidth+1)*i+boxwidth] == '\0')
			{
				if(boxcode[(boxwidth+1)*i+boxwidth-1] != '\0')
				{
					break;
				}
				else
				{
					cout << "！！！箱の形の設定が不正です。！！！" << endl;
					goto p5;
				}
			}
		}
		
		for(int i=0; boxcode[i]!='\0'; i++)
		{
			if(boxcode[i] == '-')
			{
				if((i+1)%(boxwidth+1) != 0)
				{
					cout << "！！！箱の形の設定が不正です。入力し直してください。！！！" << endl;
					goto p5;
				}
			}
		}
		
		if(boxsize == 0)
		{
			cout << "！！！箱の形の設定が不正です。入力し直してください。！！！" << endl;
			goto p5;
		}
		
		fout << "char cell[" << boxwidth * boxheight << "];" << endl;
		fout << "p = cell; for(i=0; i<" << boxwidth * boxheight << "; i++){*p = \'*\'; p++;}" << endl;
		
		i = 0;
		
		for(int k=0; boxcode[k]!='\0'; k++)
		{
			if(boxcode[k] == '0')
			{
				fout << "cell[" << i << "]=\'*\';" << endl;
				i++;
			}
			else if(boxcode[k] == '1')
			{
				if(b3 == true)
				{
					b3 = false;
				}
				fout << "cell[" << i << "]=\'\\0\';" << endl;
				i++;
			}
		}
		
		if(boxwidth >= boxheight)
		{
			max = boxwidth;
		}
		else
		{
			max = boxheight;
		}
		
		for(int l=0; boxcode[l]!='\0'; l=l)
		{
			if(m < max)
			{
				if(boxcode[l] != '-')
				{
					boxtmp1[m][n] = boxcode[l];
					m++;
					l++;
				}
				else
				{
					if(m != 0)
					{
						for(int i=m; i<max; i++)
						{
							boxtmp1[i][n] = '0';
						}
						m = 0;
						n++;
						l++;
					}
					else
					{
						l++;
					}
				}
			}
			else
			{
				m = 0;
				n++;
			}
		}
		
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp1[i][j] == '\0')
				{
					boxtmp1[i][j] = '0';
				}
			}
		}
		
		m = max-1;
		n = 0;
		
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				boxtmp2[m][n] = boxtmp1[i][j];
				n++;
				if(n == max)
				{
					n = 0;
					m--;
				}
			}
		}
		
		m = max-1;
		n = 0;
		
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				boxtmp3[m][n] = boxtmp2[i][j];
				n++;
				if(n == max)
				{
					n = 0;
					m--;
				}
			}
		}
		
		m = max-1;
		n = 0;
		
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				boxtmp4[m][n] = boxtmp3[i][j];
				n++;
				if(n == max)
				{
					n = 0;
					m--;
				}
			}
		}
		
		m = max-1;
		n = 0;
		
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				boxtmp5[m][n] = boxtmp1[i][j];
				m--;
				if(m == -1)
				{
					m = max-1;
					n++;
				}
			}
		}
		
		m = max-1;
		n = 0;
		
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				boxtmp6[m][n] = boxtmp5[i][j];
				n++;
				if(n == max)
				{
					n = 0;
					m--;
				}
			}
		}
		
		for(int i=0; i<max; i++)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp1[i][j] != '0')
				{
					itmp1i = i;
					goto r1;
				}
			}
		}
		
		r1:
		for(int i=max-1; i>=0; i--)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp1[i][j] != '0')
				{
					itmp1f = i;
					goto r2;
				}
			}
		}
		
		r2:
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp1[i][j] != '0')
				{
					jtmp1i = j;
					goto r3;
				}
			}
		}
		
		r3:
		for(int j=max-1; j>=0; j--)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp1[i][j] != '0')
				{
					jtmp1f = j;
					goto r4;
				}
			}
		}
		
		r4:
		for(int i=0; i<max; i++)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp2[i][j] != '0')
				{
					itmp2i = i;
					goto r5;
				}
			}
		}
		
		r5:
		for(int i=max-1; i>=0; i--)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp2[i][j] != '0')
				{
					itmp2f = i;
					goto r6;
				}
			}
		}
		
		r6:
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp2[i][j] != '0')
				{
					jtmp2i = j;
					goto r7;
				}
			}
		}
		
		r7:
		for(int j=max-1; j>=0; j--)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp2[i][j] != '0')
				{
					jtmp2f = j;
					goto r8;
				}
			}
		}
		
		r8:
		for(int i=0; i<max; i++)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp3[i][j] != '0')
				{
					itmp3i = i;
					goto r9;
				}
			}
		}
		
		r9:
		for(int i=max-1; i>=0; i--)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp3[i][j] != '0')
				{
					itmp3f = i;
					goto r10;
				}
			}
		}
		
		r10:
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp3[i][j] != '0')
				{
					jtmp3i = j;
					goto r11;
				}
			}
		}
		
		r11:
		for(int j=max-1; j>=0; j--)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp3[i][j] != '0')
				{
					jtmp3f = j;
					goto r12;
				}
			}
		}
		
		r12:
		for(int i=0; i<max; i++)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp4[i][j] != '0')
				{
					itmp4i = i;
					goto r13;
				}
			}
		}
		
		r13:
		for(int i=max-1; i>=0; i--)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp4[i][j] != '0')
				{
					itmp4f = i;
					goto r14;
				}
			}
		}
		
		r14:
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp4[i][j] != '0')
				{
					jtmp4i = j;
					goto r15;
				}
			}
		}
		
		r15:
		for(int j=max-1; j>=0; j--)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp4[i][j] != '0')
				{
					jtmp4f = j;
					goto r16;
				}
			}
		}
		
		r16:
		for(int i=0; i<max; i++)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp5[i][j] != '0')
				{
					itmp5i = i;
					goto r17;
				}
			}
		}
		
		r17:
		for(int i=max-1; i>=0; i--)
		{
			for(int j=0; j<max; j++)
			{
				if(boxtmp5[i][j] != '0')
				{
					itmp5f = i;
					goto r18;
				}
			}
		}
		
		r18:
		for(int j=0; j<max; j++)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp5[i][j] != '0')
				{
					jtmp5i = j;
					goto r19;
				}
			}
		}
		
		r19:
		for(int j=max-1; j>=0; j--)
		{
			for(int i=0; i<max; i++)
			{
				if(boxtmp5[i][j] != '0')
				{
					jtmp5f = j;
					goto r20;
				}
			}
		}
		
		r20:
		if(itmp1f-itmp1i == itmp2f-itmp2i && jtmp1f-jtmp1i == jtmp2f-jtmp2i)
		{
			for(int i=0; i<itmp1f-itmp1i+1; i++)
			{
				for(int j=0; j<jtmp1f-jtmp1i+1; j++)
				{
					if(boxtmp1[itmp1i+i][jtmp1i+j] != boxtmp2[itmp2i+i][jtmp2i+j])
					{
						goto r22;
					}
					if(i == itmp1f-itmp1i && j == jtmp1f-jtmp1i)
					{
						if(itmp1f-itmp1i == itmp5f-itmp5i && jtmp1f-jtmp1i == jtmp5f-jtmp5i)
						{
							for(int k=0; k<itmp1f-itmp1i+1; k++)
							{
								for(int l=0; l<jtmp1f-jtmp1i+1; l++)
								{
									if(boxtmp1[itmp1i+k][jtmp1i+l] != boxtmp5[itmp5i+k][jtmp5i+l])
									{
										goto r21;
									}
									if(k == itmp1f-itmp1i && l == jtmp1f-jtmp1i)
									{
										boxtype = 8;
										goto r30;
									}
								}
							}
						}
						else
						{
							r21:
							boxtype = 4;
							goto r30;
						}
					}
				}
			}
		}
		
		r22:
		if(itmp1f-itmp1i == itmp3f-itmp3i && jtmp1f-jtmp1i == jtmp3f-jtmp3i)
		{
			for(int i=0; i<itmp1f-itmp1i+1; i++)
			{
				for(int j=0; j<jtmp1f-jtmp1i+1; j++)
				{
					if(boxtmp1[itmp1i+i][jtmp1i+j] != boxtmp3[itmp3i+i][jtmp3i+j])
					{
						goto r25;
					}
					if(i == itmp1f-itmp1i && j == jtmp1f-jtmp1i)
					{
						if(itmp1f-itmp1i == itmp5f-itmp5i && jtmp1f-jtmp1i == jtmp5f-jtmp5i)
						{
							for(int k=0; k<itmp1f-itmp1i+1; k++)
							{
								for(int l=0; l<jtmp1f-jtmp1i+1; l++)
								{
									if(boxtmp1[itmp1i+k][jtmp1i+l] != boxtmp5[itmp5i+k][jtmp5i+l])
									{
										goto r23;
									}
									if(k == itmp1f-itmp1i && l == jtmp1f-jtmp1i)
									{
										boxtype = 4;
										goto r30;
									}
								}
							}
						}
						else
						{
							r23:
							if(itmp2f-itmp2i == itmp5f-itmp5i && jtmp2f-jtmp2i == jtmp5f-jtmp5i)
							{
								for(int m=0; m<itmp2f-itmp2i+1; m++)
								{
									for(int n=0; n<jtmp2f-jtmp2i+1; n++)
									{
										if(boxtmp2[itmp2i+m][jtmp2i+n] != boxtmp5[itmp5i+m][jtmp5i+n])
										{
											goto r24;
										}
										if(m == itmp2f-itmp2i && n == jtmp2f-jtmp2i)
										{
											boxtype = 4;
											goto r30;
										}
									}
								}
							}
							else
							{
								r24:
								boxtype = 2;
								goto r30;
							}
						}
					}
				}
			}
		}
		
		r25:
		if(itmp5f-itmp5i == itmp1f-itmp1i && jtmp5f-jtmp5i == jtmp1f-jtmp1i)
		{
			for(int i=0; i<itmp5f-itmp5i+1; i++)
			{
				for(int j=0; j<jtmp5f-jtmp5i+1; j++)
				{
					if(boxtmp5[itmp5i+i][jtmp5i+j] != boxtmp1[itmp1i+i][jtmp1i+j])
					{
						goto r26;
					}
					if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
					{
						boxtype = 2;
						goto r30;
					}
				}
			}
		}
		
		r26:
		if(itmp5f-itmp5i == itmp2f-itmp2i && jtmp5f-jtmp5i == jtmp2f-jtmp2i)
		{
			for(int i=0; i<itmp5f-itmp5i+1; i++)
			{
				for(int j=0; j<jtmp5f-jtmp5i+1; j++)
				{
					if(boxtmp5[itmp5i+i][jtmp5i+j] != boxtmp2[itmp2i+i][jtmp2i+j])
					{
						goto r27;
					}
					if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
					{
						boxtype = 2;
						goto r30;
					}
				}
			}
		}
		
		r27:
		if(itmp5f-itmp5i == itmp3f-itmp3i && jtmp5f-jtmp5i == jtmp3f-jtmp3i)
		{
			for(int i=0; i<itmp5f-itmp5i+1; i++)
			{
				for(int j=0; j<jtmp5f-jtmp5i+1; j++)
				{
					if(boxtmp5[itmp5i+i][jtmp5i+j] != boxtmp3[itmp3i+i][jtmp3i+j])
					{
						goto r28;
					}
					if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
					{
						boxtype = 2;
						goto r30;
					}
				}
			}
		}
		
		r28:
		if(itmp5f-itmp5i == itmp4f-itmp4i && jtmp5f-jtmp5i == jtmp4f-jtmp4i)
		{
			for(int i=0; i<itmp5f-itmp5i+1; i++)
			{
				for(int j=0; j<jtmp5f-jtmp5i+1; j++)
				{
					if(boxtmp5[itmp5i+i][jtmp5i+j] != boxtmp4[itmp4i+i][jtmp4i+j])
					{
						goto r29;
					}
					if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
					{
						boxtype = 2;
						goto r30;
					}
				}
			}
		}
		
		r29:
		boxtype = 1;
		
		r30:
	}
	else
	{
		cout << "！！！1か2を選んでください。！！！" << endl;
		goto p1;
	}
	
	cout << endl;
	
	p6:
	
	piecesize = 0;
	strtmp = 0;
	l = -1;
	piecenum = -1;
	piecenum2 = 0;
	//monomino = false;
	//domino = false;
	//tromino = false;
	b4 = false;
	string* str = new string[200];
	
	for(int i=0; i<200; i++)
	{
		for(int j=0; j<10; j++)
		{
			strcell[i][j] = 0;
		}
	}
	
	for(int i=0; i<25; i++)
	{
		num[i] = 0;
	}
	
	for(int i=0; i<50; i++)
	{
		piecesizenum[i] = 0;
	}
	
	for(int i=0; i<50; i++)
	{
		bbb[i] = true;
	}
	
	cout << "★使うピースを設定します。" << endl;
	cout << "モノミノからペントミノまではアルファベットで、それ以外は「ピースの部分を1、それ以外の部分を0」として1つずつ入力してください。入力を終えるときはqを入力してください。" << endl;
	
	for(int k=0; k<100; k++)
	{
		
		for(int i=0; i<100; i++)
		{
			piece[i] = '\0';
			piececode[i] = '\0';
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp1[i][j] = '\0';
			}
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp2[i][j] = '\0';
			}
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp3[i][j] = '\0';
			}
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp4[i][j] = '\0';
			}
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp5[i][j] = '\0';
			}
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp6[i][j] = '\0';
			}
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp7[i][j] = '\0';
			}
		}
		
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				piecetmp8[i][j] = '\0';
			}
		}
		
		for(int i=strtmp; i<200; i++)
		{
			for(int j=0; j<10; j++)
			{
				strcell[i][j] = 0;
			}
		}
		
		cout << "->>";
		cin >> piece;
		piecenum++;
		l++;
		
		piecewidth = 0;
		pieceheight = 1;
		m = 0;
		n = 0;
		tmp = 0;
		initx = 0;
		inity =0;
		b2 = true;
		
		if(piece[0] == 'm')
		{
			num[0]++;
			//monomino = true;
			if(num[0] == 1)
			{
				c = 'm';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piecesize += 1;
			piecesizenum[l] = 1;
			goto p7;
		}
		else if(piece[0] == 'd')
		{
			num[1]++;
			//domino = true;
			if(num[1] == 1)
			{
				c = 'd';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piecesize += 2;
			piecesizenum[l] = 2;
			goto p7;
		}
		else if(piece[0] == 'a')
		{
			num[2]++;
			//tromino = true;
			if(num[2] == 1)
			{
				c = 'a';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = c;
			piecesize += 3;
			piecesizenum[l] = 3;
			goto p7;
		}
		else if(piece[0] == 'b')
		{
			num[3]++;
			//tromino = true;
			if(num[3] == 1)
			{
				c = 'b';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = '0';
			piececode[2] = '-';
			piececode[3] = c;
			piececode[4] = c;
			piecesize += 3;
			piecesizenum[l] = 3;
			goto p7;
		}
		else if(piece[0] == 'i')
		{
			num[4]++;
			if(num[4] == 1)
			{
				c = 'i';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = c;
			piececode[3] = c;
			piecesize += 4;
			piecesizenum[l] = 4;
			goto p7;
		}
		else if(piece[0] == 'l')
		{
			num[5]++;
			if(num[5] == 1)
			{
				c = 'l';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = '0';
			piececode[2] = '0';
			piececode[3] = '-';
			piececode[4] = c;
			piececode[5] = c;
			piececode[6] = c;
			piecesize += 4;
			piecesizenum[l] = 4;
			goto p7;
		}
		else if(piece[0] == 'n')
		{
			num[6]++;
			if(num[6] == 1)
			{
				c = 'n';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = '0';
			piececode[3] = '-';
			piececode[4] = '0';
			piececode[5] = c;
			piececode[6] = c;
			piecesize += 4;
			piecesizenum[l] = 4;
			goto p7;
		}
		else if(piece[0] == 'o')
		{
			num[7]++;
			if(num[7] == 1)
			{
				c = 'o';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = '-';
			piececode[3] = c;
			piececode[4] = c;
			piecesize += 4;
			piecesizenum[l] = 4;
			goto p7;
		}
		else if(piece[0] == 't')
		{
			num[8]++;
			if(num[8] == 1)
			{
				c = 't';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = c;
			piececode[3] = '-';
			piececode[4] = '0';
			piececode[5] = c;
			piececode[6] = '0';
			piecesize += 4;
			piecesizenum[l] = 4;
			goto p7;
		}
		else if(piece[0] == 'F')
		{
			num[9]++;
			if(num[9] == 1)
			{
				c = 'F';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = '0';
			piececode[1] = c;
			piececode[2] = c;
			piececode[3] = '-';
			piececode[4] = c;
			piececode[5] = c;
			piececode[6] = '0';
			piececode[7] = '-';
			piececode[8] = '0';
			piececode[9] = c;
			piececode[10] = '0';
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'I')
		{
			num[10]++;
			if(num[10] == 1)
			{
				c = 'I';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = c;
			piececode[3] = c;
			piececode[4] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'L')
		{
			num[11]++;
			if(num[11] == 1)
			{
				c = 'L';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = '0';
			piececode[2] = '0';
			piececode[3] = '0';
			piececode[4] = '-';
			piececode[5] = c;
			piececode[6] = c;
			piececode[7] = c;
			piececode[8] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'N')
		{
			num[12]++;
			if(num[12] == 1)
			{
				c = 'N';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = c;
			piececode[3] = '0';
			piececode[4] = '-';
			piececode[5] = '0';
			piececode[6] = '0';
			piececode[7] = c;
			piececode[8] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'P')
		{
			num[13]++;
			if(num[13] == 1)
			{
				c = 'P';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = '0';
			piececode[3] = '-';
			piececode[4] = c;
			piececode[5] = c;
			piececode[6] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'T')
		{
			num[14]++;
			if(num[14] == 1)
			{
				c = 'T';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = c;
			piececode[3] = '-';
			piececode[4] = '0';
			piececode[5] = c;
			piececode[6] = '0';
			piececode[7] = '-';
			piececode[8] = '0';
			piececode[9] = c;
			piececode[10] = '0';
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'U')
		{
			num[15]++;
			if(num[15] == 1)
			{
				c = 'U';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = '0';
			piececode[2] = c;
			piececode[3] = '-';
			piececode[4] = c;
			piececode[5] = c;
			piececode[6] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'V')
		{
			num[16]++;
			if(num[16] == 1)
			{
				c = 'V';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = '0';
			piececode[2] = '0';
			piececode[3] = '-';
			piececode[4] = c;
			piececode[5] = '0';
			piececode[6] = '0';
			piececode[7] = '-';
			piececode[8] = c;
			piececode[9] = c;
			piececode[10] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'W')
		{
			num[17]++;
			if(num[17] == 1)
			{
				c = 'W';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = '0';
			piececode[2] = '0';
			piececode[3] = '-';
			piececode[4] = c;
			piececode[5] = c;
			piececode[6] = '0';
			piececode[7] = '-';
			piececode[8] = '0';
			piececode[9] = c;
			piececode[10] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'X')
		{
			num[18]++;
			if(num[18] == 1)
			{
				c = 'X';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = '0';
			piececode[1] = c;
			piececode[2] = '0';
			piececode[3] = '-';
			piececode[4] = c;
			piececode[5] = c;
			piececode[6] = c;
			piececode[7] = '-';
			piececode[8] = '0';
			piececode[9] = c;
			piececode[10] = '0';
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'Y')
		{
			num[19]++;
			if(num[19] == 1)
			{
				c = 'Y';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = '0';
			piececode[1] = c;
			piececode[2] = '0';
			piececode[3] = '0';
			piececode[4] = '-';
			piececode[5] = c;
			piececode[6] = c;
			piececode[7] = c;
			piececode[8] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == 'Z')
		{
			num[20]++;
			if(num[20] == 1)
			{
				c = 'Z';
			}
			else
			{
				c = getch(bbb);
				if(c == '@')
				{
					cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			piececode[0] = c;
			piececode[1] = c;
			piececode[2] = '0';
			piececode[3] = '-';
			piececode[4] = '0';
			piececode[5] = c;
			piececode[6] = '0';
			piececode[7] = '-';
			piececode[8] = '0';
			piececode[9] = c;
			piececode[10] = c;
			piecesize += 5;
			piecesizenum[l] = 5;
			goto p7;
		}
		else if(piece[0] == '0' || piece[0] == '1')
		{
			b4 = true;
			c = getch(bbb);
			if(c == '@')
			{
				cout << "！！！ピースが多すぎます。ピースを最初から設定し直してください。！！！" << endl;
				delete[] str;
				goto p6;
			}
			
			for(int j=0; piece[j]!='\0'; j++)
			{
				if(piece[j] == '0' || piece[j] == '1' || piece[j] == '-')
				{
					if(piece[j] == '1')
					{
						piececode[j] = c;
						piecesize++;
						piecesizenum[l]++;
					}
					else
					{
						piececode[j] = piece[j];
					}
				}
				else
				{
					cout << "！！！ピースの設定が不正です。！！！" << endl;
					delete[] str;
					goto p6;
				}
			}
			
			p7:
			
			for(int i=0; piececode[i]!='\0'; i++)
			{
				if(b2 == true && piececode[i] == '-')
				{
					piecewidth = i;
					b2 = false;
				}
				if(piececode[i] == '-')
				{
					pieceheight++;
				}
			}
			
			if(b2 == true)
			{
				for(int i=0; i<10; i++)
				{
					if(piececode[i] == '\0')
					{
						piecewidth = i;
						b2 = false;
						break;
					}
				}
			}
			
			for(int i=0; i<50; i++)
			{
				if(piececode[(piecewidth+1)*i+piecewidth] != '\0' && piececode[(piecewidth+1)*i+piecewidth] != '-' || piecesizenum[l] == 0)
				{
					cout << "！！！ピースの設定が不正です。！！！" << endl;
					delete[] str;
					goto p6;
				}
				else if(piececode[(piecewidth+1)*i+piecewidth] == '\0')
				{
					if(piececode[(piecewidth+1)*i+piecewidth-1] != '\0')
					{
						break;
					}
					else
					{
						cout << "！！！ピースの設定が不正です。！！！" << endl;
						delete[] str;
						goto p6;
					}
				}
			}
			
			for(int i=0; piececode[i]!='\0'; i++)
			{
				if(piececode[i] == '-')
				{
					if((i+1)%(piecewidth+1) != 0)
					{
						cout << "！！！ピースの設定が不正です。！！！" << endl;
						delete[] str;
						goto p6;
					}
				}
			}
			
			if(piecewidth >= pieceheight)
			{
				max = piecewidth;
			}
			else
			{
				max = pieceheight;
			}
			
			for(int l=0; piececode[l]!='\0'; l=l)
			{
				if(m < max)
				{
					if(piececode[l] != '-')
					{
						piecetmp1[m][n] = piececode[l];
						m++;
						l++;
					}
					else
					{
						if(m != 0)
						{
							for(int i=m; i<max; i++)
							{
								piecetmp1[i][n] = '0';
							}
							m = 0;
							n++;
							l++;
						}
						else
						{
							l++;
						}
					}
				}
				else
				{
					m = 0;
					n++;
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp1[i][j] == '\0')
					{
						piecetmp1[i][j] = '0';
					}
				}
			}
			
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp1[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a1;
					}
				}
			}
			
			a1:
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp1[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			
			strtmp++;
			piecenum2++;
			
			m = max-1;
			n = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					piecetmp2[m][n] = piecetmp1[i][j];
					n++;
					if(n == max)
					{
						n = 0;
						m--;
					}
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp2[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a2;
					}
				}
			}
			
			a2:
			tmp = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp2[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			
			strtmp++;
			piecenum2++;
			
			m = max-1;
			n = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					piecetmp3[m][n] = piecetmp2[i][j];
					n++;
					if(n == max)
					{
						n = 0;
						m--;
					}
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp3[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a3;
					}
				}
			}
			
			a3:
			tmp = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp3[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			
			strtmp++;
			piecenum2++;
			
			m = max-1;
			n = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					piecetmp4[m][n] = piecetmp3[i][j];
					n++;
					if(n == max)
					{
						n = 0;
						m--;
					}
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp4[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a4;
					}
				}
			}
			
			a4:
			tmp = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp4[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			
			strtmp++;
			piecenum2++;
			
			m = max-1;
			n = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					piecetmp5[m][n] = piecetmp1[i][j];
					m--;
					if(m == -1)
					{
						m = max-1;
						n++;
					}
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp5[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a5;
					}
				}
			}
			
			a5:
			tmp = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp5[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			
			strtmp++;
			piecenum2++;
			
			m = max-1;
			n = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					piecetmp6[m][n] = piecetmp5[i][j];
					n++;
					if(n == max)
					{
						n = 0;
						m--;
					}
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp6[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a6;
					}
				}
			}
			
			a6:
			tmp = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp6[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			
			strtmp++;
			piecenum2++;
			
			for(int i=0; i<max; i++)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp1[i][j] != '0')
					{
						itmp1i = i;
						goto d1;
					}
				}
			}
			
			d1:
			for(int i=max-1; i>=0; i--)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp1[i][j] != '0')
					{
						itmp1f = i;
						goto d2;
					}
				}
			}
			
			d2:
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp1[i][j] != '0')
					{
						jtmp1i = j;
						goto d3;
					}
				}
			}
			
			d3:
			for(int j=max-1; j>=0; j--)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp1[i][j] != '0')
					{
						jtmp1f = j;
						goto d4;
					}
				}
			}
			
			d4:
			for(int i=0; i<max; i++)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp2[i][j] != '0')
					{
						itmp2i = i;
						goto d5;
					}
				}
			}
			
			d5:
			for(int i=max-1; i>=0; i--)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp2[i][j] != '0')
					{
						itmp2f = i;
						goto d6;
					}
				}
			}
			
			d6:
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp2[i][j] != '0')
					{
						jtmp2i = j;
						goto d7;
					}
				}
			}
			
			d7:
			for(int j=max-1; j>=0; j--)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp2[i][j] != '0')
					{
						jtmp2f = j;
						goto d8;
					}
				}
			}
			
			d8:
			for(int i=0; i<max; i++)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp3[i][j] != '0')
					{
						itmp3i = i;
						goto d9;
					}
				}
			}
			
			d9:
			for(int i=max-1; i>=0; i--)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp3[i][j] != '0')
					{
						itmp3f = i;
						goto d10;
					}
				}
			}
			
			d10:
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp3[i][j] != '0')
					{
						jtmp3i = j;
						goto d11;
					}
				}
			}
			
			d11:
			for(int j=max-1; j>=0; j--)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp3[i][j] != '0')
					{
						jtmp3f = j;
						goto d12;
					}
				}
			}
			
			d12:
			for(int i=0; i<max; i++)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp4[i][j] != '0')
					{
						itmp4i = i;
						goto d13;
					}
				}
			}
			
			d13:
			for(int i=max-1; i>=0; i--)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp4[i][j] != '0')
					{
						itmp4f = i;
						goto d14;
					}
				}
			}
			
			d14:
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp4[i][j] != '0')
					{
						jtmp4i = j;
						goto d15;
					}
				}
			}
			
			d15:
			for(int j=max-1; j>=0; j--)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp4[i][j] != '0')
					{
						jtmp4f = j;
						goto d16;
					}
				}
			}
			
			d16:
			for(int i=0; i<max; i++)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp5[i][j] != '0')
					{
						itmp5i = i;
						goto d17;
					}
				}
			}
			
			d17:
			for(int i=max-1; i>=0; i--)
			{
				for(int j=0; j<max; j++)
				{
					if(piecetmp5[i][j] != '0')
					{
						itmp5f = i;
						goto d18;
					}
				}
			}
			
			d18:
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp5[i][j] != '0')
					{
						jtmp5i = j;
						goto d19;
					}
				}
			}
			
			d19:
			for(int j=max-1; j>=0; j--)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp5[i][j] != '0')
					{
						jtmp5f = j;
						goto d20;
					}
				}
			}
			
			d20:
			if(itmp1f-itmp1i == itmp2f-itmp2i && jtmp1f-jtmp1i == jtmp2f-jtmp2i)
			{
				for(int i=0; i<itmp1f-itmp1i+1; i++)
				{
					for(int j=0; j<jtmp1f-jtmp1i+1; j++)
					{
						if(piecetmp1[itmp1i+i][jtmp1i+j] != piecetmp2[itmp2i+i][jtmp2i+j])
						{
							goto d22;
						}
						if(i == itmp1f-itmp1i && j == jtmp1f-jtmp1i)
						{
							if(itmp1f-itmp1i == itmp5f-itmp5i && jtmp1f-jtmp1i == jtmp5f-jtmp5i)
							{
								for(int k=0; k<itmp1f-itmp1i+1; k++)
								{
									for(int l=0; l<jtmp1f-jtmp1i+1; l++)
									{
										if(piecetmp1[itmp1i+k][jtmp1i+l] != piecetmp5[itmp5i+k][jtmp5i+l])
										{
											goto d21;
										}
										if(k == itmp1f-itmp1i && l == jtmp1f-jtmp1i)
										{
											strtmp -= 5;
											piecenum2 -= 5;
											numnum[piecenum] = 1;
											goto fin;
										}
									}
								}
							}
							else
							{
								d21:
								piecenum2 -= 5;
								str[strtmp-5] = "";
								
								m = max-1;
								n = 0;
								
								for(int j=0; j<max; j++)
								{
									for(int i=0; i<max; i++)
									{
										piecetmp5[m][n] = piecetmp1[i][j];
										m--;
										if(m == -1)
										{
											m = max-1;
											n++;
										}
									}
								}
								
								for(int j=0; j<max; j++)
								{
									for(int i=0; i<max; i++)
									{
										if(piecetmp5[i][j] != '0')
										{
											initx = i;
											inity = j;
											goto a9;
										}
									}
								}
								
								a9:
								tmp = 0;
								
								for(int j=0; j<max; j++)
								{
									for(int i=0; i<max; i++)
									{
										if(piecetmp5[i][j] != '0')
										{
											xtmp[tmp] = i-initx;
											ytmp[tmp] = j-inity;
											tmp++;
										}
									}
								}
								
								xmax = xtmp[0];
								for(int i=1; i<tmp; i++)
								{
									if(xtmp[i] > xmax)
									{
										xmax = xtmp[i];
									}
								}
								
								xmin = xtmp[0];
								for(int i=1; i<tmp; i++)
								{
									if(xtmp[i] < xmin)
									{
										xmin = xtmp[i];
									}
								}
								
								ymax = ytmp[0];
								for(int i=1; i<tmp; i++)
								{
									if(ytmp[i] > ymax)
									{
										ymax = ytmp[i];
									}
								}
								
								if(xmax != 0)
								{
									str[strtmp-5] +="x<" + itos2(boxwidth-xmax) + " && ";
								}
								if(ymax != 0)
								{
									str[strtmp-5] +="y<" + itos2(boxheight-ymax) + " && ";
								}
								if(xmin != 0)
								{
									str[strtmp-5] +="x>" + itos2(-xmin-1) + " && ";
								}
								
								for(int i=tmp-1; i>0; i--)
								{
									str[strtmp-5] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
									strcell[strtmp-5][i] = xtmp[i]+ytmp[i]*boxwidth;
								}
								str[strtmp-5] += "!b" + itos2(piecenum2);
								str[strtmp-5] += "){*p = \'" + itoc(c) + "\';";
								for(int i=1; i<tmp; i++)
								{
									str[strtmp-5] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
								}
								
								piecenum2++;
								strtmp -= 4;
								numnum[piecenum] = 2;
								goto fin;
							}
						}
					}
				}
			}
			
			d22:
			if(itmp1f-itmp1i == itmp3f-itmp3i && jtmp1f-jtmp1i == jtmp3f-jtmp3i)
			{
				for(int i=0; i<itmp1f-itmp1i+1; i++)
				{
					for(int j=0; j<jtmp1f-jtmp1i+1; j++)
					{
						if(piecetmp1[itmp1i+i][jtmp1i+j] != piecetmp3[itmp3i+i][jtmp3i+j])
						{
							goto d25;
						}
						if(i == itmp1f-itmp1i && j == jtmp1f-jtmp1i)
						{
							if(itmp1f-itmp1i == itmp5f-itmp5i && jtmp1f-jtmp1i == jtmp5f-jtmp5i)
							{
								for(int k=0; k<itmp1f-itmp1i+1; k++)
								{
									for(int l=0; l<jtmp1f-jtmp1i+1; l++)
									{
										if(piecetmp1[itmp1i+k][jtmp1i+l] != piecetmp5[itmp5i+k][jtmp5i+l])
										{
											goto d23;
										}
										if(k == itmp1f-itmp1i && l == jtmp1f-jtmp1i)
										{
											strtmp -= 4;
											piecenum2 -= 4;
											numnum[piecenum] = 2;
											goto fin;
										}
									}
								}
							}
							else
							{
								d23:
								if(itmp2f-itmp2i == itmp5f-itmp5i && jtmp2f-jtmp2i == jtmp5f-jtmp5i)
								{
									for(int m=0; m<itmp2f-itmp2i+1; m++)
									{
										for(int n=0; n<jtmp2f-jtmp2i+1; n++)
										{
											if(piecetmp2[itmp2i+m][jtmp2i+n] != piecetmp5[itmp5i+m][jtmp5i+n])
											{
												goto d24;
											}
											if(m == itmp2f-itmp2i && n == jtmp2f-jtmp2i)
											{
												strtmp -= 4;
												piecenum2 -= 4;
												numnum[piecenum] = 2;
												goto fin;
											}
										}
									}
								}
								else
								{
									d24:
									piecenum2 -= 4;
									str[strtmp-4] = "";
									
									m = max-1;
									n = 0;
									
									for(int j=0; j<max; j++)
									{
										for(int i=0; i<max; i++)
										{
											piecetmp5[m][n] = piecetmp1[i][j];
											m--;
											if(m == -1)
											{
												m = max-1;
												n++;
											}
										}
									}
									
									for(int j=0; j<max; j++)
									{
										for(int i=0; i<max; i++)
										{
											if(piecetmp5[i][j] != '0')
											{
												initx = i;
												inity = j;
												goto a10;
											}
										}
									}
									
									a10:
									tmp = 0;
									
									for(int j=0; j<max; j++)
									{
										for(int i=0; i<max; i++)
										{
											if(piecetmp5[i][j] != '0')
											{
												xtmp[tmp] = i-initx;
												ytmp[tmp] = j-inity;
												tmp++;
											}
										}
									}
									
									xmax = xtmp[0];
									for(int i=1; i<tmp; i++)
									{
										if(xtmp[i] > xmax)
										{
											xmax = xtmp[i];
										}
									}
									
									xmin = xtmp[0];
									for(int i=1; i<tmp; i++)
									{
										if(xtmp[i] < xmin)
										{
											xmin = xtmp[i];
										}
									}
									
									ymax = ytmp[0];
									for(int i=1; i<tmp; i++)
									{
										if(ytmp[i] > ymax)
										{
											ymax = ytmp[i];
										}
									}
									
									if(xmax != 0)
									{
										str[strtmp-4] +="x<" + itos2(boxwidth-xmax) + " && ";
									}
									if(ymax != 0)
									{
										str[strtmp-4] +="y<" + itos2(boxheight-ymax) + " && ";
									}
									if(xmin != 0)
									{
										str[strtmp-4] +="x>" + itos2(-xmin-1) + " && ";
									}
									
									for(int i=tmp-1; i>0; i--)
									{
										str[strtmp-4] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
										strcell[strtmp-4][i] = xtmp[i]+ytmp[i]*boxwidth;
									}
									str[strtmp-4] += "!b" + itos2(piecenum2);
									str[strtmp-4] += "){*p = \'" + itoc(c) + "\';";
									for(int i=1; i<tmp; i++)
									{
										str[strtmp-4] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
									}
									
									piecenum2++;
									
									str[strtmp-3] = "";
									
									m = max-1;
									n = 0;
									
									for(int j=0; j<max; j++)
									{
										for(int i=0; i<max; i++)
										{
											piecetmp6[m][n] = piecetmp5[i][j];
											n++;
											if(n == max)
											{
												n = 0;
												m--;
											}
										}
									}
									
									for(int j=0; j<max; j++)
									{
										for(int i=0; i<max; i++)
										{
											if(piecetmp6[i][j] != '0')
											{
												initx = i;
												inity = j;
												goto a11;
											}
										}
									}
									
									a11:
									tmp = 0;
									
									for(int j=0; j<max; j++)
									{
										for(int i=0; i<max; i++)
										{
											if(piecetmp6[i][j] != '0')
											{
												xtmp[tmp] = i-initx;
												ytmp[tmp] = j-inity;
												tmp++;
											}
										}
									}
									
									xmax = xtmp[0];
									for(int i=1; i<tmp; i++)
									{
										if(xtmp[i] > xmax)
										{
											xmax = xtmp[i];
										}
									}
									
									xmin = xtmp[0];
									for(int i=1; i<tmp; i++)
									{
										if(xtmp[i] < xmin)
										{
											xmin = xtmp[i];
										}
									}
									
									ymax = ytmp[0];
									for(int i=1; i<tmp; i++)
									{
										if(ytmp[i] > ymax)
										{
											ymax = ytmp[i];
										}
									}
									
									if(xmax != 0)
									{
										str[strtmp-3] +="x<" + itos2(boxwidth-xmax) + " && ";
									}
									if(ymax != 0)
									{
										str[strtmp-3] +="y<" + itos2(boxheight-ymax) + " && ";
									}
									if(xmin != 0)
									{
										str[strtmp-3] +="x>" + itos2(-xmin-1) + " && ";
									}
									
									for(int i=tmp-1; i>0; i--)
									{
										str[strtmp-3] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
										strcell[strtmp-3][i] = xtmp[i]+ytmp[i]*boxwidth;
									}
									str[strtmp-3] += "!b" + itos2(piecenum2);
									str[strtmp-3] += "){*p = \'" + itoc(c) + "\';";
									for(int i=1; i<tmp; i++)
									{
										str[strtmp-3] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
									}
									
									piecenum2++;
									strtmp -= 2;
									numnum[piecenum] = 4;
									goto fin;
								}
							}
						}
					}
				}
			}
			
			d25:
			if(itmp5f-itmp5i == itmp1f-itmp1i && jtmp5f-jtmp5i == jtmp1f-jtmp1i)
			{
				for(int i=0; i<itmp5f-itmp5i+1; i++)
				{
					for(int j=0; j<jtmp5f-jtmp5i+1; j++)
					{
						if(piecetmp5[itmp5i+i][jtmp5i+j] != piecetmp1[itmp1i+i][jtmp1i+j])
						{
							goto d26;
						}
						if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
						{
							strtmp -= 2;
							piecenum2 -= 2;
							numnum[piecenum] = 4;
							goto fin;
						}
					}
				}
			}
			
			d26:
			if(itmp5f-itmp5i == itmp2f-itmp2i && jtmp5f-jtmp5i == jtmp2f-jtmp2i)
			{
				for(int i=0; i<itmp5f-itmp5i+1; i++)
				{
					for(int j=0; j<jtmp5f-jtmp5i+1; j++)
					{
						if(piecetmp5[itmp5i+i][jtmp5i+j] != piecetmp2[itmp2i+i][jtmp2i+j])
						{
							goto d27;
						}
						if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
						{
							strtmp -= 2;
							piecenum2 -= 2;
							numnum[piecenum] = 4;
							goto fin;
						}
					}
				}
			}
			
			d27:
			if(itmp5f-itmp5i == itmp3f-itmp3i && jtmp5f-jtmp5i == jtmp3f-jtmp3i)
			{
				for(int i=0; i<itmp5f-itmp5i+1; i++)
				{
					for(int j=0; j<jtmp5f-jtmp5i+1; j++)
					{
						if(piecetmp5[itmp5i+i][jtmp5i+j] != piecetmp3[itmp3i+i][jtmp3i+j])
						{
							goto d28;
						}
						if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
						{
							strtmp -= 2;
							piecenum2 -= 2;
							numnum[piecenum] = 4;
							goto fin;
						}
					}
				}
			}
			
			d28:
			if(itmp5f-itmp5i == itmp4f-itmp4i && jtmp5f-jtmp5i == jtmp4f-jtmp4i)
			{
				for(int i=0; i<itmp5f-itmp5i+1; i++)
				{
					for(int j=0; j<jtmp5f-jtmp5i+1; j++)
					{
						if(piecetmp5[itmp5i+i][jtmp5i+j] != piecetmp4[itmp4i+i][jtmp4i+j])
						{
							goto d29;
						}
						if(i == itmp5f-itmp5i && j == jtmp5f-jtmp5i)
						{
							strtmp -= 2;
							piecenum2 -= 2;
							numnum[piecenum] = 4;
							goto fin;
						}
					}
				}
			}
			
			d29:
			
			m = max-1;
			n = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					piecetmp7[m][n] = piecetmp6[i][j];
					n++;
					if(n == max)
					{
						n = 0;
						m--;
					}
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp7[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a7;
					}
				}
			}
			
			a7:
			tmp = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp7[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			
			strtmp++;
			piecenum2++;
			
			m = max-1;
			n = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					piecetmp8[m][n] = piecetmp7[i][j];
					n++;
					if(n == max)
					{
						n = 0;
						m--;
					}
				}
			}
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp8[i][j] != '0')
					{
						initx = i;
						inity = j;
						goto a8;
					}
				}
			}
			
			a8:
			tmp = 0;
			
			for(int j=0; j<max; j++)
			{
				for(int i=0; i<max; i++)
				{
					if(piecetmp8[i][j] != '0')
					{
						xtmp[tmp] = i-initx;
						ytmp[tmp] = j-inity;
						tmp++;
					}
				}
			}
			
			xmax = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] > xmax)
				{
					xmax = xtmp[i];
				}
			}
			
			xmin = xtmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(xtmp[i] < xmin)
				{
					xmin = xtmp[i];
				}
			}
			
			ymax = ytmp[0];
			for(int i=1; i<tmp; i++)
			{
				if(ytmp[i] > ymax)
				{
					ymax = ytmp[i];
				}
			}
			
			str[strtmp] = "";
			if(xmax != 0)
			{
				str[strtmp] +="x<" + itos2(boxwidth-xmax) + " && ";
			}
			if(ymax != 0)
			{
				str[strtmp] +="y<" + itos2(boxheight-ymax) + " && ";
			}
			if(xmin != 0)
			{
				str[strtmp] +="x>" + itos2(-xmin-1) + " && ";
			}
			
			for(int i=tmp-1; i>0; i--)
			{
				str[strtmp] += "!*(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ")" + " && ";
				strcell[strtmp][i] = xtmp[i]+ytmp[i]*boxwidth;
			}
			str[strtmp] += "!b" + itos2(piecenum2);
			str[strtmp] += "){*p = \'" + itoc(c) + "\';";
			for(int i=1; i<tmp; i++)
			{
				str[strtmp] += " *(p" + itos(xtmp[i]+ytmp[i]*boxwidth) + ") = \'" + itoc(c) + "\';";
			}
			
			strtmp++;
			piecenum2++;
			numnum[piecenum] = 8;
		}
		else if(piece[0] == 'q')
		{
			if(boxsize != piecesize)
			{
				cout << "！！！箱の単位数とピースの単位数が一致していません。！！！" << endl;
				delete[] str;
				goto p6;
			}
			else if(piecenum == 1)
			{
				cout << "！！！ピースの数は2個以上にしてください。！！！" << endl;
				delete[] str;
				goto p6;
			}
			else
			{
				break;
			}
		}
		else
		{
			cout << "！！！ピースの設定が不正です。！！！" << endl;
			delete[] str;
			goto p6;
		}
		
		fin:;
	}
	
	b5 = false;
	
	if(b4 == true)
	{
		cout << endl << "★0と1で入力したピースのうち合同なピースが存在する場合、「ピースの重複度の階乗の積」を入力してください。合同なピースがない場合には1を入力してください。" << endl;
		cin >> num[21];
	}
	
	for(int i=0; i<25; i++)
	{
		if(num[i] >= 3)
		{
			b5 = true;
		}
	}
	
	multiple = 1;
	
	for(int i=0; i<25; i++)
	{
		if(num[i] > 1)
		{
			for(int j=0; num[i]>1; j++)
			{
				multiple *= num[i];
				num[i]--;
			}
		}
	}
	
	if(multiple >= 12)
	{
		b5 = true;
	}
	
	maxpiecesizenum = 0;
	for(int i=0; i<50; i++)
	{
		if(maxpiecesizenum < piecesizenum[i])
		{
			maxpiecesizenum = piecesizenum[i];
		}
	}
	
	q = (int)(strtmp/8)+1;
	if(strtmp%8 == 0)
	{
		q--;
	}
	
	cout << endl;
	
	fout << "__int64* bbbp;" << endl;
	
	for(int i=0; i<piecenum-1; i++)
	{
		fout << "char celltmp" << i << "[" << boxwidth*boxheight << "];";
		fout << "bool *bp" << i << ";";
		fout << "bool *bbp" << i << ";" << endl;
	}
	
	for(int i=0; i<piecenum; i++)
	{
		for(int m=0; m<maxpiecesizenum; m++)
		{
			fout << "char *cellp" << i << "00" << m <<";" << endl;
		}
	}
	
	for(int i=0; i<piecenum2; i++)
	{
		fout << "bool b" << i << " = false;" << endl;
	}
	
	for(int i=0; i<piecenum; i++)
	{
		fout << "bool bb" << i << " = false;" << endl;
	}
	
	fout << "char bbb[" << strtmp*(piecenum-1)+(piecenum-1)*8 << "];" << endl;
	
	fout << "p2 = cell; for(i=0; i<" << boxwidth*boxheight << "; i++){if(!*p2){x = i%" << boxwidth << "; y = (i-x)/" << boxwidth << "; p = p2; goto w;}p2++;}" << "w:" << endl;
	fout << "int solution = 0;" << endl;
	
	k = 0;
	
	for(int i=0; i<piecenum; i++)
	{
		k = k+8-k%8;
		
		if(i != piecenum-1)
		{
			fout << "bbbp = (__int64*)&bbb[" << k << "];" << endl;
			
			for(int j=0; j<q; j++)
			{
				fout << "bbbp[" << j << "] = 0;" << endl;
			}
		}
		
		fout << "opr" << i << ":" << endl;
		
		p = 0;
		
		for(int j=0; j<piecenum; j++)
		{
			fout << "if(!bb" << j << "){" << endl;
			for(int l=0; l<numnum[j]; l++)
			{
				if(l == 0)
				{
					if(i != piecenum-1)
					{
						fout << "if(!bbb[" << k << "] && " << str[p] << " b" << p << " = true;  bb" << j << " = true; bbb[" << k << "] = true; bp" << i << " = &b"<< p << "; bbp" << i << " = &bb" << j << ";";
						
						for(int m=0; m<maxpiecesizenum; m++)
						{
							if(strcell[p][m] != 0)
							{
								fout << " cellp" << i << "00" << m << " = p" << itos(strcell[p][m]) << ";";
							}
							else
							{
								fout << " cellp" << i << "00" << m << " = p;";
							}
						}
						
						fout << " goto h" << i << ";}" << endl;
					}
					else
					{
						fout << "if(" << str[p];
						
						for(int m=0; m<maxpiecesizenum; m++)
						{
							if(strcell[p][m] != 0)
							{
								fout << " cellp" << i << "00" << m << " = p" << itos(strcell[p][m]) << ";";
							}
							else
							{
								fout << " cellp" << i << "00" << m << " = p;";
							}
						}
						
						fout << " goto h" << i << ";}" << endl;
					}
				}
				else
				{
					if(i != piecenum-1)
					{
						fout << "else if(!bbb[" << k << "] && " << str[p] << " b" << p << " = true;  bb" << j << " = true; bbb[" << k << "] = true; bp" << i << " = &b"<< p << "; bbp" << i << " = &bb" << j << ";";
						
						for(int m=0; m<maxpiecesizenum; m++)
						{
							if(strcell[p][m] != 0)
							{
								fout << " cellp" << i << "00" << m << " = p" << itos(strcell[p][m]) << ";";
							}
							else
							{
								fout << " cellp" << i << "00" << m << " = p;";
							}
						}
						
						fout << " goto h" << i << ";}" << endl;
					}
					else
					{
						fout << "if(" << str[p];
						
						for(int m=0; m<maxpiecesizenum; m++)
						{
							if(strcell[p][m] != 0)
							{
								fout << " cellp" << i << "00" << m << " = p" << itos(strcell[p][m]) << ";";
							}
							else
							{
								fout << " cellp" << i << "00" << m << " = p;";
							}
						}
						
						fout << " goto h" << i << ";}" << endl;
					}
				}
				p++;
				k++;
			}
			fout << "}";
		}
		
		if(i == 0)
		{
			if(multiple == 1)
			{
				fout << "cout << endl; num = " << boxtype << "; cout << \"★真の解数は【 \" << solution / num << \" 】です。\" << endl; return 0;" << endl;
			}
			else if(b5 == false)
			{
				fout << "cout << endl; num = " << multiple << "; cout << \"★箱の向きを固定して考えた場合の解数は【 \" << solution / num << \" 】です。回転・裏返しで一致するものは除いてありません。\"; if(solution%(num*" << boxtype << ") == 0){cout << \"真の解数はたぶん【 \" << solution / (num*" << boxtype << ") << \" 】だと思います。\";} cout << endl; return 0;" << endl;
			}
			else
			{
				fout << "cout << endl; num = " << multiple << "; cout << \"★箱の向きを固定して考えた場合の解数は【 \" << solution / num << \" 】です。回転・裏返しで一致するものは除いてありません。\" << endl; return 0;" << endl;
			}
		}
		else
		{
			fout << "*bp" << i-1 << " = false; *bbp" << i-1 << " = false;" << endl;
			
			for(int m=0; m<maxpiecesizenum; m++)
			{
				fout << "*cellp" << i-1 << "00" << m << " = \'\\0\';";
			}
			
			fout << endl;
			fout << "p2 = cell; for(i=0; i<" << boxwidth*boxheight << "; i++){if(!*p2){x = i%" << boxwidth << "; y = (i-x)/" << boxwidth << "; p = p2; goto e" << i << ";}p2++;}" << "e" << i << ": goto opr" << i-1 << ";" << endl;
		}
		
		if(i != piecenum-1)
		{
			fout << "h" << i << ":";
			fout << "p2 = cell; for(i=0; i<" << boxwidth*boxheight << "; i++){if(!*p2){x = i%" << boxwidth << "; y = (i-x)/" << boxwidth << "; p = p2; goto f" << i << ";}p2++;}f" << i << ":" << endl;
			
			/*if(i >= piecenum/3)
			{
				if(!monomino && domino)
				{
					fout << "if(*(p+1) && *(p+" << boxwidth << ")){" << endl;
					fout << "*bp" << i << " = false; *bbp" << i << " = false;" << endl;
					
					for(int m=0; m<maxpiecesizenum; m++)
					{
						fout << "*cellp" << i << "00" << m << " = \'\\0\';";
					}
					
					if(i == 0)
					{
						fout << "x = xtmp; y = ytmp; p = ptmp; goto opr" << i << ";}" << endl;
					}
					else
					{
						fout << "p2 = cell; for(i=0; i<" << boxwidth*boxheight << "; i++){if(!*p2){x = i%" << boxwidth << "; y = (i-x)/" << boxwidth << "; p = p2; goto g" << i << ";}p2++;}g" << i << ": goto opr" << i << ";}" << endl;
					}
				}
				else if(!monomino && !domino && tromino)
				{
					fout << "if((*(*(cell+x+1)+y) && *(*(cell+x)+y+1)) || (*(*(cell+x+2)+y) && *(*(cell+x)+y+1) && *(*(cell+x+1)+y+1)) || (*(*(cell+x+1)+y) && *(*(cell+x+1)+y+1) && *(*(cell+x)+y+2)) && *(*(cell+x-1)+y+1)){" << endl;
					for(int j=0; j<piecenum2; j++)
					{
						fout << "b" << j << " = btmp" << i*piecenum2+j << ";" << endl;
						if(j < piecenum)
						{
							fout << "bb" << j << " = bbtmp" << i*piecenum+j << ";" << endl;
						}
					}
					fout << "for(i=0; i<" << boxwidth << "; i++){p2 = *(cell+i); p = *(celltmp" << i << "+i); for(j=0; j<" << boxheight << "; j++){*p2 = *p; p2++; p++;}}" << endl;
					fout << "for(j=0; j<" << boxheight << "; j++){for(i=0; i<" << boxwidth << "; i++){if(!cell[i][j]){x = i; y = j; goto g" << i << ";}}}" << "g" << i << ": goto opr" << i << ";}" << endl;
				}
				else if(!monomino && !domino && !tromino)
				{
					fout << "if((*(*(cell+x+1)+y) && *(*(cell+x)+y+1)) || (*(*(cell+x+2)+y) && *(*(cell+x)+y+1) && *(*(cell+x+1)+y+1)) || (*(*(cell+x+1)+y) && *(*(cell+x+1)+y+1) && *(*(cell+x)+y+2) && *(*(cell+x-1)+y+1)) || (*(*(cell+x+2)+y) && *(*(cell+x+1)+y+1) && *(*(cell+x)+y+2) && *(*(cell+x-1)+y+1)) || (*(*(cell+x+2)+y) && *(*(cell+x+2)+y+1) && *(*(cell+x+1)+y+2) && *(*(cell+x)+y+1)) || (*(*(cell+x+1)+y) && *(*(cell+x+2)+y+1) && *(*(cell+x+1)+y+2) && *(*(cell+x)+y+2) && *(*(cell+x-1)+y+1)) || (*(*(cell+x+3)+y) && *(*(cell+x+2)+y+1) && *(*(cell+x+1)+y+1) && *(*(cell+x)+y+1)) || (*(*(cell+x+1)+y) && *(*(cell+x+1)+y+1) && *(*(cell+x+1)+y+2) && *(*(cell+x)+y+3) && *(*(cell+x-1)+y+1) && *(*(cell+x-1)+y+2))){" << endl;
					for(int j=0; j<piecenum2; j++)
					{
						fout << "b" << j << " = btmp" << i*piecenum2+j << ";" << endl;
						if(j < piecenum)
						{
							fout << "bb" << j << " = bbtmp" << i*piecenum+j << ";" << endl;
						}
					}
					fout << "for(int i=0; i<" << boxwidth << "; i++){p2 = *(cell+i); p = *(celltmp" << i << "+i); for(int j=0; j<" << boxheight << "; j++){*p2 = *p; p2++; p++;}}" << endl;
					fout << "for(int j=0; j<" << boxheight << "; j++){for(int i=0; i<" << boxwidth << "; i++){if(!cell[i][j]){x = i; y = j; goto g" << i << ";}}}" << "g" << i << ": goto opr" << i << ";}" << endl;
				}
			}*/
		}
		
	}
	
	p8:
	cout << "★表示方法を設定します。1か2を選んでください。" << endl;
	cout << "1．全解を表示する（回転・裏返しによる重複を除かずに全解を表示します。）" << endl << "2．解の総数のみ表示する（速度が向上します）。" << endl;
	cin >> print;
	
	if(print == 1)
	{
		fout << "h" << piecenum-1 << ": cout << endl << \'[\' << solution+1 << \']\' << endl; for(i=0; i<" << boxwidth*boxheight << "; i++){cout << cell[i]; if((i+1)%" << boxwidth << "== 0){cout << endl;}}cout << endl;" << endl;
	}
	else if(print == 2)
	{
		fout << "h" << piecenum-1 << ":";
	}
	else
	{
		cout << "！！！1か2を選んでください。！！！" << endl;
		goto p8;
	}
	
	fout << "*bp" << piecenum-2 << " = false; *bbp" << piecenum-2 << " = false;" << endl;
	
	for(int m=0; m<maxpiecesizenum; m++)
	{
		fout << "*cellp" << piecenum-2 << "00" << m << " = \'\\0\';";
	}
	for(int m=0; m<maxpiecesizenum; m++)
	{
		fout << "*cellp" << piecenum-1 << "00" << m << " = \'\\0\';";
	}
	
	fout << endl;
	fout << "p2 = cell; for(i=0; i<" << boxwidth*boxheight << "; i++){if(!*p2){x = i%" << boxwidth << "; y = (i-x)/" << boxwidth << "; p = p2; goto h;}p2++;}" << "h:" << endl;
	fout << "solution++; goto opr" << piecenum-2 << ";}" << endl;
	fout.close();
	
	cout << endl << "★設定が完了しました。poliomino.cppをコンパイルして実行してください。" << endl;
	delete[] str;
	return 0;
}

string itos(int n)
{
	stringstream ss;
	if(n >= 0)
	{
		ss << '+';
		ss << n;
	}
	else
	{
		ss << n;
	}
	return ss.str();
}

string itos2(int n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

string itoc(char c)
{
	stringstream ss;
	ss << c;
	return ss.str();
}

char getch(bool btmp[50])
{
	char ch;
	if(btmp[0] == true)
	{
		ch = 'c';
		btmp[0] = false;
	}
	else if(btmp[1] == true)
	{
		ch = 'e';
		btmp[1] = false;
	}
	else if(btmp[2] == true)
	{
		ch = 'f';
		btmp[2] = false;
	}
	else if(btmp[3] == true)
	{
		ch = 'g';
		btmp[3] = false;
	}
	else if(btmp[4] == true)
	{
		ch = 'h';
		btmp[4] = false;
	}
	else if(btmp[5] == true)
	{
		ch = 'j';
		btmp[5] = false;
	}
	else if(btmp[6] == true)
	{
		ch = 'k';
		btmp[6] = false;
	}
	else if(btmp[7] == true)
	{
		ch = 'p';
		btmp[7] = false;
	}
	else if(btmp[8] == true)
	{
		ch = 'q';
		btmp[8] = false;
	}
	else if(btmp[9] == true)
	{
		ch = 'r';
		btmp[9] = false;
	}
	else if(btmp[10] == true)
	{
		ch = 's';
		btmp[10] = false;
	}
	else if(btmp[11] == true)
	{
		ch = 'u';
		btmp[11] = false;
	}
	else if(btmp[12] == true)
	{
		ch = 'v';
		btmp[12] = false;
	}
	else if(btmp[13] == true)
	{
		ch = 'w';
		btmp[13] = false;
	}
	else if(btmp[14] == true)
	{
		ch = 'x';
		btmp[14] = false;
	}
	else if(btmp[15] == true)
	{
		ch = 'y';
		btmp[15] = false;
	}
	else if(btmp[16] == true)
	{
		ch = 'z';
		btmp[16] = false;
	}
	else if(btmp[17] == true)
	{
		ch = 'A';
		btmp[17] = false;
	}
	else if(btmp[18] == true)
	{
		ch = 'B';
		btmp[18] = false;
	}
	else if(btmp[19] == true)
	{
		ch = 'C';
		btmp[19] = false;
	}
	else if(btmp[20] == true)
	{
		ch = 'D';
		btmp[20] = false;
	}
	else if(btmp[21] == true)
	{
		ch = 'E';
		btmp[21] = false;
	}
	else if(btmp[22] == true)
	{
		ch = 'G';
		btmp[22] = false;
	}
	else if(btmp[23] == true)
	{
		ch = 'H';
		btmp[23] = false;
	}
	else if(btmp[24] == true)
	{
		ch = 'J';
		btmp[24] = false;
	}
	else if(btmp[25] == true)
	{
		ch = 'K';
		btmp[25] = false;
	}
	else if(btmp[26] == true)
	{
		ch = 'M';
		btmp[26] = false;
	}
	else if(btmp[27] == true)
	{
		ch = 'O';
		btmp[27] = false;
	}
	else if(btmp[28] == true)
	{
		ch = 'Q';
		btmp[28] = false;
	}
	else if(btmp[29] == true)
	{
		ch = 'R';
		btmp[29] = false;
	}
	else if(btmp[30] == true)
	{
		ch = 'S';
		btmp[30] = false;
	}
	else if(btmp[31] == true)
	{
		ch = '#';
		btmp[31] = false;
	}
	else if(btmp[32] == true)
	{
		ch = '$';
		btmp[32] = false;
	}
	else if(btmp[33] == true)
	{
		ch = '%';
		btmp[33] = false;
	}
	else if(btmp[34] == true)
	{
		ch = '+';
		btmp[34] = false;
	}
	else if(btmp[35] == true)
	{
		ch = '\\';
		btmp[35] = false;
	}
	else if(btmp[36] == true)
	{
		ch = '!';
		btmp[36] = false;
	}
	else if(btmp[37] == true)
	{
		ch = '?';
		btmp[37] = false;
	}
	else if(btmp[38] == true)
	{
		ch = '<';
		btmp[38] = false;
	}
	else if(btmp[39] == true)
	{
		ch = '>';
		btmp[39] = false;
	}
	else if(btmp[40] == true)
	{
		ch = '/';
		btmp[40] = false;
	}
	else if(btmp[41] == true)
	{
		ch = '1';
		btmp[41] = false;
	}
	else if(btmp[42] == true)
	{
		ch = '2';
		btmp[42] = false;
	}
	else if(btmp[43] == true)
	{
		ch = '3';
		btmp[43] = false;
	}
	else if(btmp[44] == true)
	{
		ch = '4';
		btmp[44] = false;
	}
	else if(btmp[45] == true)
	{
		ch = '5';
		btmp[45] = false;
	}
	else if(btmp[46] == true)
	{
		ch = '6';
		btmp[46] = false;
	}
	else if(btmp[47] == true)
	{
		ch = '7';
		btmp[47] = false;
	}
	else if(btmp[48] == true)
	{
		ch = '8';
		btmp[48] = false;
	}
	else if(btmp[49] == true)
	{
		ch = '9';
		btmp[49] = false;
	}
	else
	{
		ch = '@';
	}
	
	return ch;
}

