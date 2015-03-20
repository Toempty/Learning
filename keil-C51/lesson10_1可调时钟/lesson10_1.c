#include<reg52.h>
#include<shizhong.h>

void delay(uint);
void write_com(uchar);//дָ��
void write_data(uchar);//д����
void init();//��ʼ��
void setclock();//����ʱ��
void write_sfm(uchar,uchar,uchar);//дʱ����
uchar keyscan();//������̼��

uint num,shi,shi1,shi2,fen,fen1,fen2,miao,miao1,miao2,m,n;
uchar i,temp;
uchar key11,key22,key33;//��¼key1��key2��key3���´���

void main()
{
	init();

	TR0=1;//��ʱ��1

	while(1)
		{
			setclock();
		}	
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void init()
{
	TMOD=0x01;//����ģʽ1
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;//�����ж�
	ET0=1;//�򿪶�ʱ���ж�0

	wr=0;
		
	write_com(0x38);//��ʾģʽ����
	write_com(0x0c);//��ʾ���ؼ��������
	write_com(0x01);//������������ָ��
	
	write_com(0x80);//��ʼ����ָ��
	for(i=0;i<13;i++)
		{
			write_data(table[i]);
		}
	write_com(0x80+0x40);
	for(i=0;i<11;i++)
		{
			write_data(table1[i]);
		}
}

void write_com(uchar com)//д����
{
	rs=0;
	lcde=0;
	P0=com;
	delay(5);
	lcde=1;
	delay(5);
	lcde=0;	
}

void write_data(uchar dat)//д����
{
	rs=1;
	P0=dat;
	delay(5);
	lcde=1;
	delay(5);
	lcde=0;
}

void timer0 () interrupt 1//��ʱ���ж�0
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
	
	if(num%20==0)
		{
			num=0;
			miao++;
			
			if(miao%60==0)
				{
					miao=0;
					fen++;

				if(fen%60==0)
					{
						fen=0;
						shi++;
						if(shi%24==0)
							{
								shi=0;
							}
					}
				}
			miao1=miao/10;
			miao2=miao%10;
			fen1=fen/10;
			fen2=fen%10;
			shi1=shi/10;
			shi2=shi%10;
		}

}

void setclock()//����ʱ��
{
	m=10;
	n=0;
	if(key1==0)//����ʱ
		{
			delay(5);
			if(key1==0)
				{
					key11++;
					while(!key1);//���ּ��
					
						
							TR0=0;//ֹͣʱ��
							write_com(0x80+0x40+3);
							write_com(0x0f);//����������˸
							m=10;
							m=keyscan();
							while(m>2)//����ʱ�ĵ�һλ
								{
									m=keyscan();
									if(key1==0)
										{
											delay(5);
											if(key1==0)
												{
													while(!key1);
													n=1;//����ż��������ʱ
													key11++;
												}
										}
									if(n==1)
										{
											write_com(0x0c);
											break;//��������ʱ
										}
								}
							if(n!=1)
								{
									shi1=m;
									write_com(0x80+0x40+3);
									write_data(table2[shi1]);
									m=10;
									m=keyscan();
									if(shi1==2)//����ʱ�ĵڶ�λ
										{
											while(m>3)//���ʱ�ĵ�һλ��2��ʱ�ĵڶ�λӦС��4
												{
													m=keyscan();
													if(key1==0)
														{
															delay(5);
															if(key1==0)
																{
																	while(!key1);
																	n=1;
																	key11++;
																}
														}
													if(n==1)
														{
														if(shi1*10+shi2>3)
															{
																shi2=(10*shi1+shi2)%24;
																shi1=0;
																write_com(0x80+0x40+3);
																write_data(table2[shi1]);
																write_data(table2[shi2]);
															}
															write_com(0x0c);
															break;//��������ʱ
														}
												}
												if(n!=1)
													{
														shi2=m;
														write_data(table2[shi2]);
														write_com(0x80+0x40+3);
													}
										}
									else
										{
											while(m>9)//���ʱ�ĵ�һλΪ0 ��1��ڶ�λΪ��λ������
												{
													m=keyscan();
													if(key1==0)
														{
															delay(5);
															if(key1==0)
																{
																	while(!key1);
																	n=1;
																	key11++;
																}
														}
													if(n==1)
														{
															write_com(0x0c);
															break;
														}
												}
												if(n!=1)//���û��ֹͣ����ʱ
													{
														shi2=m;	
														key11++;
														write_data(table2[shi2]);
														write_com(0x80+0x40+3);
													}
										}
								shi=10*shi1+shi2;
								}
							write_com(0x80+0x40+6);//����ָ���ַָ�����÷ִ�
						    write_com(0x0c);//ֹͣ��˸						
				}
		}
	if(key2==0)//���÷�
		{
			delay(5);
			if(key2==0)
				{
					key22++;
					while(!key2);
					

						TR0=0;//ֹͣʱ��
						write_com(0x80+0x40+6);
						write_com(0x0f);
						m=keyscan();
						while(m>5)
							{
								m=keyscan();
								if(key2==0)
									{
										delay(5);
										if(key2==0)
											{
												while(!key2);
												n=1;
												key22++;
											}
									}
								if(n==1)
									{
										write_com(0x0c);
										break;
									}
							}
						if(n!=1)
							{
								fen1=m;
		
								write_com(0x80+0x40+6);
		
								write_data(table2[fen1]);
								m=10;
								m=keyscan();
								while(m>9)
									{
										m=keyscan();
										if(key2==0)
											{
												delay(5);

												if(key2==0)
													{
														while(!key2);
														n=1;
														key22++;
													}
											}
										if(n==1)
											{
												write_com(0x0c);
												break;
											}
									}
								if(n!=1)
									{
										fen2=m;
										key22++;
										write_data(table2[fen2]);
										write_com(0x80+0x40+6);	
									}
								fen=10*fen1+fen2;
							}
						write_com(0x80+0x40+6);
						write_com(0x0c);
				}				
		}
	if(key3==0)
		{
			delay(5);
			if(key3==0)//������
				{	
					key33++;
					while(!key3);
					

						TR0=0;//ֹͣʱ��
						write_com(0x80+0x40+9);
						write_com(0x0f);
						m=keyscan();
						while(m>5)
							{
								m=keyscan();
								if(key3==0)
									{
										delay(5);
										if(key3==0)
											{
												while(!key3);
												n=1;
												key33++;
											}
									}
								if(n==1)
									{
										write_com(0x0c);
										break;
									}
							}
						if(n!=1)
							{
								miao1=m;
		
								write_com(0x80+0x40+9);
		
								write_data(table2[miao1]);
								m=10;
								m=keyscan();
								while(m>9)
									{
										m=keyscan();
										if(key3==0)
											{
												delay(5);

												if(key3==0)
													{
														while(!key3);
														n=1;
														key33++;
													}
											}
										if(n==1)
											{
												write_com(0x0c);
												break;
											}
									}
								if(n!=1)
									{
										miao2=m;
										key33++;
										write_data(table2[miao2]);
										write_com(0x80+0x40+9);	
									}
								miao=10*miao1+miao2;
							}
						write_com(0x80+0x40+9);
						write_com(0x0c);							
				
				}
		}
	if((key11%2==0)&&(key22%2==0)&&(key33%2==0))
	{
		TR0=1;
		write_sfm(9,miao1,miao2);
		write_sfm(3,shi1,shi2);
		write_sfm(6,fen1,fen2);
	}	
}


void write_sfm(uchar add,uchar shiwei,uchar gewei)
{
	write_com(0x80+0x40+add);
	write_data(table2[shiwei]);
	delay(5);
	write_data(table2[gewei]);
}
uchar keyscan()
{
		uint num1=10;
		P1=0xfd;
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
			{
				delay(10);
				P1=0xfd;
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
					{
						temp=P1;
						switch(temp)
							{
								case 0xed:num1=1;
										break;
								case 0xdd:num1=2;
										break;
								case 0xbd:num1=3;
										break;
								case 0x7d:num1=4;
										break;
							}
						while(temp!=0xf0)//���ּ��
							{
								temp=P1;
								temp=temp&0xf0;
							}
					}
			}
		P1=0xfb;
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
			{
				delay(10);
				P1=0xfb;
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
					{
						temp=P1;
						switch(temp)
							{
								case 0xeb:num1=5;
										break;
								case 0xdb:num1=6;
										break;
								case 0xbb:num1=7;
										break;
								case 0x7b:num1=8;
										break;
							}
						while(temp!=0xf0)
							{
								temp=P1;
								temp=temp&0xf0;
							}
					}
			}
		P1=0xf7;
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
			{
				delay(10);
				P1=0xf7;
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
					{
						temp=P1;
						switch(temp)
							{
								case 0xe7:num1=9;
										break;
								case 0xd7:num1=0;
										break;
								case 0xb7:num1=11;
										break;
								case 0x77:num1=12;
										break;
							}
						while(temp!=0xf0)
							{
								temp=P1;
								temp=temp&0xf0;
							}
					}
			}
return num1;
}

//ע���ڹ����˸��ʱ����ˢ������


