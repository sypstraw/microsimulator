#include <stdio.h>
#include <graphics.h>
#define A1 1
#define A2 2
#define ALU 3
#define BITS 4
#define C 5
#define CLOCK 6
#define CONTROL 7
#define DATA 8
#define ENTRY 9
#define INVALID 10
#define IR 11
#define IR2 12
#define MAR 13
#define MENU 14
#define MEM 15
#define MBR 16
#define MICRO 17
#define NZ 18
#define OFF 19
#define REG 20
#define SP 21
#define PC 22
#define VERSION "Version 1.1 (C) 20/08/1996"

unsigned char in[50][5],set[13][5],temp[50],mi[50],mench=0,f=0,ad=0;
unsigned int pc=65535,sp=128,ir=65535,ir2=65535,a1=65535,a2=65535,ac=0,mbr=65535,c=0,n=0,z=0,s=0,op=0;
unsigned int r[8],m[128],ra=7,rb=7,a=0,mar=15,omar=15,cl=65535,off=0,p=0,end=0,noin=0,wait=0;
unsigned char ad_agb[4], op_agb[3];

void clearer(unsigned int what, unsigned int i)
{
	if (what == A1) setviewport(36*8,(13*16)+1,40*8,(14*16)-1,0);
	if (what == A2) setviewport(30*8,(13*16)+1,34*8,(14*16)-1,0);
	if (what == ALU) setviewport(27*8,(18*16)+1,43*8,(19*16)-1,0);
	if (what == BITS) setviewport(27*8,(18*16)+1,43*8,(19*16)-1,0);
	if (what == C) setviewport(35*8,(19.7*16)+1,36*8,(20.5*16)-1,0);
	if (what == CLOCK) setviewport(9*8,(2*16)+1,13*8,(3*16)-1,0);
	if (what == CONTROL) setviewport(28*8,(4*16)+1,41*8,(5*16)-1,0);
	if (what == DATA) setviewport(49*8,(36*16)+1,53*8,(37*16)-1,0);
	if (what == ENTRY) setviewport((43+i-1)*8,(34*16)+1,(43+i)*8,(35*16)-1,0);
	if (what == INVALID) setviewport(24*8,(35*16)+1,57*8,(36*16)-1,0);
	if (what == IR) setviewport(30*8,(7*16)+1,34*8,(8*16)-1,0);
	if (what == IR2) setviewport(36*8,(7*16)+1,40*8,(8*16)-1,0);
	if (what == MAR) setviewport(55*8,(7*16)+1,59*8,(8*16)-1,0);
	if (what == MBR) setviewport(55*8,(18*16)+1,59*8,(19*16)-1,0);
	if (what == MEM) setviewport(71*8,((i+1)*16)+1,75*8,((i+2)*16)-1,0);
	if (what == MENU) setviewport(0,450,799,599,0);
	if (what == MICRO) setviewport(43*8,(34*16)+1,51*8,(35*16)-1,0);
	if (what == NZ) setviewport(48*8,(22*16)+1,50*8,(23*16)-1,0);
	if (what == OFF) setviewport(65*8,16,69*8,375,1);
	if (what == PC) setviewport(6*8,(7*16)+1,10*8,(8*16)-1,0);
	if (what == REG) setviewport(7*8,((15+i)*16)+1,11*8,((16+i)*16)-1,0);
	if (what == SP) setviewport(18*8,(7*16)+1,22*8,(8*16)-1,0);

	clearviewport();
	setviewport(0,0,getmaxx(),getmaxy(),0);
}

void vline(float x, float b, float t)
{
	moveto(8*x,16*b);
	lineto(8*x,16*(t+1));
}

void hline(float y, float l, float r)
{
	y = 16*y;
	moveto(8*l,y);
	lineto(8*(r+1),y);
}

void box(float l, float r, float b, float t)
{
	l=8*l;
	r=8*(r+1);
	b=(b+1)*16;
	t=t*16;
	line(l,b,r,b);
	line(r,b,r,t);
	line(r,t,l,t);
	line(l,t,l,b);
}

void arrow(unsigned char d, float x, float y)
{
	int x1,x2;
	int y1,y2;

	if (d == 'd') {
		x=8*x;
		y=(y+1)*16-16;
		x1=x-4;
		x2=x+4;
		y1=y-4;
		y2=y1;
	}
	if (d == 'u') {
		x=8*x;
		y=y*16+16;
		x1=x-4;
		x2=x+4;
		y1=y+4;
		y2=y1;
	}
	if (d == 'l') {
		x=8*x+2;
		y=y*16;
		x1=x+4;
		x2=x1;
		y1=y+4;
		y2=y-4;
	}
	if (d == 'r') {
		x=8*x;
		y=y*16;
		x1=x-4;
		x2=x1;
		y1=y+4;
		y2=y-4;
	}
	line(x,y,x1,y1);
	line(x,y,x2,y2);
}

void printat(float x, float y, unsigned char *string)
{
	x=x*8+1;
	y=y*16+4;
	outtextxy(x,y,string);        
}

void values(void)
{
	int i;

	for (i=0;i<=21;i++) {
		clearer(MEM, i);
		sprintf(temp,"%.4x",m[off+i]);
		printat(71,i+1,temp);
	}
}

void add(void)
{
	strcpy(op_agb,"ADD");
	if (ad==4) {
		s=0;
		strcpy(set[s],"REA1");
	} 
	else {
		s++; 
		strcpy(set[s],"REEM");
		s++; 
		strcpy(set[s],"MBA1");
	}
	s++; 
	strcpy(set[s],"REA2"); 
	s++; 
	strcpy(set[s],"ADEG");
	switch (op) {
	case 5:  
		strcpy(op_agb,"ADC");
		strcpy(set[s],"ACEG");
		break;
	case 6:  
		strcpy(op_agb,"SUB");
		strcpy(set[s],"SUEG");
		break;
	case 7:  
		strcpy(op_agb,"SBC");
		strcpy(set[s],"SBEG");
		break;
	case 8:  
		strcpy(op_agb,"CMP");
		strcpy(set[s],"CMCC");
		break;
	case 9:  
		strcpy(op_agb,"AND");
		strcpy(set[s],"ANEG");
		break;
	case 10: 
		strcpy(op_agb,"EOR");
		strcpy(set[s],"EOEG");
		break;
	case 11: 
		strcpy(op_agb,"OR");
		strcpy(set[s],"OREG");
		break;
	}
}

void decode3(void)
{
	s++;
	if (ad==4) {
		s=0;
		strcpy(set[s],"REBR");
	} 
	else strcpy(set[s],"REEM");
	s++;
	if (op==3 || op==2) s=3;
	switch (op) {
	case 1:  
		strcpy(op_agb,"LDR");
		strcpy(set[s],"MBEG");
		break;
	case 2:  
		strcpy(op_agb,"JMP");
		strcpy(set[s],"MBPC");
		break;
	case 3:  
		strcpy(op_agb,"JSR");
		strcpy(set[s],"MBR2"); 
		s++;
		strcpy(set[s],"DESP"); 
		s++;
		strcpy(set[s],"SPAR"); 
		s++;
		strcpy(set[s],"PCBR"); 
		s++;
		strcpy(set[s],"WREM"); 
		s++;
		strcpy(set[s],"IRPC");
		break;
	}
}

void decode2(void)
{
	switch (ad) {
	case 0:  
		strcpy(ad_agb,"ABS"); 
		strcpy(set[0],"PCAR");
		strcpy(set[1],"INPC");
		strcpy(set[2],"REEM");
		strcpy(set[3],"MBAR");
		s=3;
		break;
	case 2:  
		strcpy(ad_agb,"IMM");
		strcpy(set[0],"PCAR");
		strcpy(set[1],"INPC");
		s=1;
		break;
	case 3:  
		strcpy(ad_agb,"IDX");
		strcpy(set[0],"PCAR");
		strcpy(set[1],"INPC");
		strcpy(set[2],"REEM");
		strcpy(set[3],"MBA2");
		strcpy(set[4],"REA1");
		strcpy(set[5],"ADAR");
		s=5;
		break;
	case 4:  
		strcpy(ad_agb,"REG");
		break;
	case 5:  
		strcpy(ad_agb,"IND");
		strcpy(set[0],"REAR");
		break;
	case 6:  
		strcpy(ad_agb,"RPI");
		strcpy(set[0],"REAR");
		strcpy(set[1],"REA1");
		strcpy(set[2],"INEG");
		s=2;
		break;
	case 7:  
		strcpy(ad_agb,"RPD");
		strcpy(set[0],"REA1");
		strcpy(set[1],"DEEG");
		strcpy(set[2],"REAR");
		s=2;
		break;
	}
	if (op==0) {
		strcpy(op_agb,"STO");
		s++; 
		strcpy(set[s],"REBR");
		s++; 
		strcpy(set[s],"WREM");
	}
	if (op>0 && op<4) decode3();
	if (op>3) add();
}

void imp(void)
{
	strcpy(ad_agb,"IMP");
	switch (op) {
	case 27: 
		strcpy(op_agb,"NOP"); 
		break;
	case 28: 
		strcpy(op_agb,"CLC");
		strcpy(set[0],"CLLU");
		break;
	case 29: 
		strcpy(op_agb,"SEC");
		strcpy(set[0],"SELU");
		break;
	case 30: 
		strcpy(op_agb,"RTS");
		strcpy(set[0],"SPAR");
		strcpy(set[1],"INSP");
		strcpy(set[2],"REEM");
		strcpy(set[3],"MBPC");
		s=3;
		break;
	case 31: 
		strcpy(op_agb,"STP");
		end=1;
		break;
	}
}

void rel(void)
{
	strcpy(set[0],"PCAR");
	strcpy(set[1],"INPC");
	strcpy(set[2],"REEM");
	strcpy(set[3],"MBA1");
	strcpy(set[4],"PCA2");
	strcpy(set[5],"ADPC");
	s=5;
	if (op==20) strcpy(op_agb,"BCC");
	if (op==21) strcpy(op_agb,"BCS");
	if (op==22) strcpy(op_agb,"BEQ");
	if (op==23) strcpy(op_agb,"BMI");
	if (op==24) strcpy(op_agb,"BNE");
	if (op==25) strcpy(op_agb,"BPL");
	if (op==26) strcpy(op_agb,"BRA");
	if ((op==20 && c==1) || (op==21 && c==0) || (op==22 && z==0) || (op==23 && n==0) || (op==24 && z==1) || (op==25 && n==1)) {
		strcpy(set[0],"INPC");
		s=0;
	}
}

void reg(void)
{
	strcpy(set[0],"REA1");
	s=1;
	switch (op) {
	case 12: 
		strcpy(op_agb, "ASL");
		strcpy(set[1],"ASEG");
		break;
	case 13: 
		strcpy(op_agb, "DEC");
		strcpy(set[1],"DEEG");
		break;
	case 14: 
		strcpy(op_agb, "INC");
		strcpy(set[1],"INEG");
		break;
	case 15: 
		strcpy(op_agb, "LSR");
		strcpy(set[1],"LSEG");
		break;
	case 16: 
		strcpy(op_agb, "MOV");
		strcpy(set[0],"REBR");
		strcpy(set[1],"MBEG");
		break;
	case 17: 
		strcpy(op_agb, "ROL");
		strcpy(set[1], "ROEG");
		break;
	case 18: 
		strcpy(op_agb, "POP");
		strcpy(set[0],"SPAR");
		strcpy(set[1],"REEM");
		strcpy(set[2],"INSP");
		strcpy(set[3],"MBEG");
		s=3;
		break;
	case 19: 
		strcpy(op_agb, "PSH");
		strcpy(set[0],"DESP");
		strcpy(set[1],"SPAR");
		strcpy(set[2],"REBR");
		strcpy(set[3],"WREM");
		s=3;
		break;
	}
}

void decode(void)
{
	unsigned int d;

	s=0;
	strcpy(set[0],"NOOP");
	d=ir;
	rb=d%8; 
	d/=16;
	ra=d%8; 
	d/=16;
	ad=d%8; 
	op=d/8;
	if (op>26) {
		ad=8;
		imp();
	}
	if (op<27 && op>19) {
		strcpy(ad_agb, "REL");
		rel();
	}
	if (op<20 && op>11) {
		strcpy(ad_agb, "REG");
		reg();
	}
	if (op<12) decode2();

	clearer(CONTROL,0);
	sprintf(temp, "%s %s R%d R%d", op_agb, ad_agb, ra, rb);
	printat(28,4,temp);

	if (p==1) f=0;
}

void off_agb(unsigned int t)
{
	int i;

	off=t;
	if (t>106) off=106;

	clearer(OFF,0);
	for (i=0;i<=21;i++) {
		sprintf(temp,"%.4x",off+i);
		printat(65,i+1,temp);
	}
	values();
}

void lines(unsigned int t)
{
	t=t%128;
	if (t<off || t>off+21) off_agb(t);
	t=t-off+1;
	line(504,96,504,8+16*t);
	line(632,400,632,8+16*t);
	hline(t+0.5,63,63.8);
	hline(t+0.5,76.2,78);
	arrow('r',64.8,t+0.5);
	arrow('l',76.2,t+0.5);
}

void point(void)
{
	if (mar>127) mar=0;
	setcolor(0);
	lines(omar);
	setcolor(2);
	lines(mar);
	omar=mar;
}

int huge DetectVGA16()
{
	return(4);
}

void capsoff(void)
{
	unsigned char status;

	status = peekb(0x0040, 0x0017);
	if (status & 64) {
		status -= 64;
		pokeb(0x0040,0x0017,status);
	}
}

void welcome(void)
{
	int Gd = DETECT, Gm;
	char GrErr;

	installuserdriver("Svga16",DetectVGA16);        
	initgraph(&Gd,&Gm,"");

	GrErr = graphresult();
	if (GrErr != grOk) {
		printf("Graphics error: %s\n",grapherrormsg(GrErr));
		exit(-1);
	}

	clearviewport();
	setcolor(3);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
	outtextxy(10,200,"The Microprocessor Simulator");
	setcolor(4);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(54,240,"Based on a program by Clive S. Fraser");
	outtextxy(38,280,"Written for the IBM-PC by Adam G. Byrne");
	setcolor(3);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	outtextxy(246,340,VERSION);
	sleep(2);
	clearviewport();
}

void clock(void)
{
	cl++;
	clearer(CLOCK,0);
	sprintf(temp, "%.4x", cl);
	printat(9,2,temp);
}

void flash(int x, int y, int i)
{
	clock();
	sprintf(temp, "%.4x", i);
	printat(x,y,temp);
	delay(wait);
}

void clockreset(void)
{
	cl=0;
	clearer(CLOCK,0);
	printat(9,2,"0000");
}

void bits(void)
{
	unsigned int t;
	int i=0;

	a=a%65536;
	t=a;
	for (i=0;i<16;i++) {
		if (t%2) temp[i]='1';
		else temp[i]='0';
		t/=2;
	}
	temp[16]='\0';
	clearer(BITS,0);
	printat(27,18,temp);
}

void c_agb(void)
{
	clearer(C,0);
	sprintf(temp, "%c", c+48);
	outtextxy(8*35,16*19.8,temp);
}

void cllu(void)
{
	if (p==1) printat(43,34,"CLC  ALU");
	c=0;
	c_agb();
}

void selu(void)
{
	if (p==1) printat(43,34,"SEC  ALU");
	c=1;
	c_agb();
}

void inpc(void)
{
	if (p==1) printat(43,34,"INC  PC");
	pc++;
	clearer(PC,0);
	sprintf(temp, "%.4x", pc);
	printat(6,7,temp);
}

void desp(void)
{
	if (p==1) printat(43,34,"DEC  SP");
	sp--;
	clock();
	clearer(SP,0);
	sprintf(temp, "%.4x", sp);
	printat(18,7,temp);
}

void insp(void)
{
	if (p==1) printat(43,34,"INC  SP");
	sp++;
	clock();
	clearer(SP,0);
	sprintf(temp, "%.4x", sp);
	printat(18,7,temp);
}

void irpc(void)
{
	if (p==1) printat(43,34,"IR2  PC");
	pc=ir2;
	clearer(PC,0);
	flash(6,7,pc);
}

void mba1(void)
{
	if (p==1) printat(43,34,"MBR  A1");
	a1=mbr;
	a=a1;
	bits();
	clearer(A1,0);
	flash(36,13,a1);
}

void mba2(void)
{
	if (p==1) printat(43,34,"MBR  A2");
	a2=mbr;
	clearer(A2,0);
	flash(30,13,a1);
}

void pcbr(void)
{
	if (p==1) printat(43,34,"PC   MBR");
	mbr=pc;
	clearer(MBR,0);
	flash(55,18,mbr);
}

void mbr2(void)
{
	if (p==1) printat(43,34,"MBR  IR2");
	ir2=mbr;
	clearer(IR2,0);
	flash(36,7,ir2);
}

void mbar(void)
{
	if (p==1) printat(43,34,"MBR  MAR");
	mar=mbr;
	point();
	clearer(MAR,0);
	flash(55,7,mar);
}

void mbpc(void)
{
	if (p==1) printat(43,34,"MBR  PC");
	pc=mbr;
	clearer(PC,0);
	flash(6,7,pc);
}

void mbsp(void)
{
	if (p==1) printat(43,34,"MBR  SP");
	sp=mbr;
	clearer(SP,0);
	flash(18,7,sp);
}

void pca2(void)
{
	if (p==1) printat(43,34,"PC   A2");
	a2=pc;
	clearer(A2,0);
	flash(30,13,a2);
}

void pcar(void)
{
	if (p==1) printat(43,34,"PC   MAR");
	mar=pc;
	point();        
	clearer(MAR,0);
	flash(55,7,mar);
}

void reem(void)
{
	if (p==1) printat(43,34,"READ MEM");
	mbr=m[mar%128];
	clearer(MBR,0);
	flash(55,18,mbr);
}

void spar(void)
{
	if (p==1) printat(43,34,"SP   MAR");
	mar=sp;
	point();
	clearer(MAR,0);
	flash(55,7,mar);
}

void spbr(void)
{
	if (p==1) printat(43,34,"SP   MBR");
	mbr=sp;
	clearer(MBR,0);
	flash(55,18,mbr);
}

void wrem(void)
{
	if (p==1) printat(43,34,"WRI  MEM");
	m[mar%128]=mbr;
	clearer(MEM,mar-off);
	flash(71,mar+1-off,mbr);
}

void a_agb(void)
{
	bits();
	if (a==0) z=1;
	else z=0;
	if (a/32768==1) n=1;
	else n=0;
	clearer(NZ,0);
	sprintf(temp, "%c%c", n+48, z+48);
	printat(48,22,temp);
}

void aceg(void)
{
	if (p==1) printat(43,34,"ADC  REG");
	a=a1+a2+c;
	c=a/65536;
	c_agb();
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void adar(void)
{
	if (p==1) printat(43,34,"ADD  MAR");
	a=a1+a2;
	c=a/65536;
	c_agb();
	a_agb();
	mar=a;
	point();
	clearer(MAR,0);
	flash(55,7,mar);
}

void adpc(void)
{
	if (p==1) printat(43,34,"ADD  PC");
	a=a1+a2;
	c=a/65536;
	c_agb();
	a_agb();
	pc=a;
	clearer(PC,0);
	flash(6,7,pc);
}

void adeg(void)
{
	if (p==1) printat(43,34,"ADD  REG");
	a=a1+a2;
	c=a/65536;
	c_agb();
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void aneg(void)
{
	if (p==1) printat(43,34,"AND  REG");
	a=a1 & a2;
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void aseg(void)
{
	if (p==1) printat(43,34,"ASL  REG");
	a*=2;
	c=a/65536;
	c_agb();
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void cmcc(void)
{
	if (p==1) printat(43,34,"CMP  ACC");
	a=a1-a2;
	if (a<0) a+=65536;
	c=a/65536;
	c_agb();
	a_agb();
}

void deeg(void)
{
	if (p==1) printat(43,34,"DEC  REG");
	a--;
	if (a<0) a+=65536;
	c=a/65536;
	c_agb();
	a_agb();
	if (ad==7) {
		r[ra]=a;
		clearer(REG,ra);
		flash(7,15+ra,a);
	} 
	else {
		r[rb]=a;
		clearer(REG,rb);
		flash(7,15+rb,a);
	}
}

void eoeg(void)
{
	if (p==1) printat(43,34,"EOR  REG");
	a=a1^a2;
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void ineg(void)
{
	if (p==1) printat(43,34,"INC  REG");
	a++;
	c=a/65536;
	c_agb();
	a_agb();
	if (ad==6) {
		r[ra]=a;
		clearer(REG,ra);
		flash(7,15+ra,a);
	} 
	else {
		r[rb]=a;
		clearer(REG,rb);
		flash(7,15+rb,a);
	}
}

void lseg(void)
{
	if (p==1) printat(43,34,"LSR  REG");
	c=a%2;
	a/=2;
	c_agb();
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void mbeg(void)
{
	if (p==1) printat(43,34,"MBR  REG");
	r[rb]=mbr;
	clearer(REG,rb);
	flash(7,15+rb,mbr);
}

void oreg(void)
{
	if (p==1) printat(43,34,"OR   REG");
	a=a1|a2;
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void rea1(void)
{
	if (p==1) printat(43,34,"REG  A1");
	a1=r[ra];
	a=a1;
	bits();
	clearer(A1,0);
	flash(36,13,a1);
}

void rea2(void)
{
	if (p==1) printat(43,34,"REG  A2");
	a2=r[rb];
	clearer(A2,0);
	flash(30,13,a2);
}

void rear(void)
{
	if (p==1) printat(43,34,"REG  MAR");
	mar=r[ra];
	point();
	clearer(MAR,0);
	flash(55,7,mar);
}

void rebr(void)
{
	if (p==1) printat(43,34,"REG  MBR");
	if (ad==4) mbr=r[ra];
	else mbr=r[rb];
	clearer(MBR,0);
	flash(55,18,mbr);
}

void resp(void)
{
	if (p==1) printat(43,34,"REG  SP");
	sp=r[ra];
	clearer(SP,0);
	flash(18,7,sp);
}

void roeg(void)
{
	if (p==1) printat(43,34,"ROL  REG");
	a=a*2+c;
	c=a/65536;
	c_agb();
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void sbeg(void)
{
	if (p==1) printat(43,34,"SBC  REG");
	a=a2+c+(a1^65535);
	c=a/65536;
	c_agb();
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,sp);
}

void speg(void)
{
	if (p==1) printat(43,34,"SP   REG");
	r[rb]=sp;
	clearer(REG,rb);
	flash(7,15+rb,sp);
}

void sueg(void)
{
	if (p==1) printat(43,34,"SUB  REG");
	a=a2+1+(a1^65535);
	c=a/65536;
	c_agb();
	a_agb();
	r[rb]=a;
	clearer(REG,rb);
	flash(7,15+rb,a);
}

void mbir(void)
{
	if (p==1) printat(43,34,"MBR  IR");
	ir=mbr;
	clearer(IR,0);
	flash(30,7,ir);
	decode();
}

void select(void)
{
	clearer(MICRO,0);
	if (strcmp(mi, "ACEG") == 0) aceg();
	if (strcmp(mi, "ADAR") == 0) adar();
	if (strcmp(mi, "ADPC") == 0) adpc();
	if (strcmp(mi, "ADEG") == 0) adeg();
	if (strcmp(mi, "ANEG") == 0) aneg();
	if (strcmp(mi, "ASEG") == 0) aseg();
	if (strcmp(mi, "CLLU") == 0) cllu();
	if (strcmp(mi, "CMCC") == 0) cmcc();
	if (strcmp(mi, "DEEG") == 0) deeg();
	if (strcmp(mi, "DESP") == 0) desp();
	if (strcmp(mi, "EOEG") == 0) eoeg();
	if (strcmp(mi, "INPC") == 0) inpc();
	if (strcmp(mi, "INEG") == 0) ineg();
	if (strcmp(mi, "INSP") == 0) insp();
        if (strcmp(mi, "IRPC") == 0) irpc();
	if (strcmp(mi, "LSEG") == 0) lseg();
	if (strcmp(mi, "MBA1") == 0) mba1();
	if (strcmp(mi, "MBA2") == 0) mba2();
	if (strcmp(mi, "MBIR") == 0) mbir();
	if (strcmp(mi, "MBR2") == 0) mbr2();
	if (strcmp(mi, "MBAR") == 0) mbar();
	if (strcmp(mi, "MBPC") == 0) mbpc();
	if (strcmp(mi, "MBEG") == 0) mbeg();
	if (strcmp(mi, "MBSP") == 0) mbsp();
	if (strcmp(mi, "OREG") == 0) oreg();
	if (strcmp(mi, "PCA2") == 0) pca2();
	if (strcmp(mi, "PCAR") == 0) pcar();
	if (strcmp(mi, "PCBR") == 0) pcbr();
	if (strcmp(mi, "REEM") == 0) reem();
	if (strcmp(mi, "REA1") == 0) rea1();
	if (strcmp(mi, "REA2") == 0) rea2();
	if (strcmp(mi, "REAR") == 0) rear();
	if (strcmp(mi, "REBR") == 0) rebr();
	if (strcmp(mi, "RESP") == 0) resp();
	if (strcmp(mi, "ROEG") == 0) roeg();
	if (strcmp(mi, "SBEG") == 0) sbeg();
	if (strcmp(mi, "SELU") == 0) selu();
	if (strcmp(mi, "SPAR") == 0) spar();
	if (strcmp(mi, "SPBR") == 0) spbr();
	if (strcmp(mi, "SPEG") == 0) speg();
	if (strcmp(mi, "SUEG") == 0) sueg();
	if (strcmp(mi, "WREM") == 0) wrem();
	if (strcmp(mi, "NOOP") == 0) printat(43,34,"NOP");
}

void execute(unsigned int max)
{
	unsigned char x=32;
	unsigned int jj;

	for (jj=0;jj<=max;jj++) {
		if (mench==5) do x=getch(); 
		while (x!=32 && x!=113);
		if (x==113) {
			end=1;
			return;
		}

		clearer(MICRO,0);
		if (f==1) printat(43,34,"FETCH");
		else printat(43,34,"EXECUTE");

		strcpy(mi,set[jj]);
		select();
		if (x==113) end=1;
	}
}

void prog(void)
{
	unsigned char x=0;

	p=1; 
	end=0; 
	x=32; 
	sp=128;
	clearer(SP,0);
	printat(18,7,"0080");

	while (!end) {
		strcpy(set[0],"PCAR");
		strcpy(set[1],"INPC");
		strcpy(set[2],"REEM");
		strcpy(set[3],"MBIR");
		s=3;
		if (mench==4 || mench==5) do x=getch(); 
		while (x!=32 && x!=49 && x!=50 && x!=51 && x!=113);
		if (x==49) wait=1;
		if (x==50) wait=100;
		if (x==51 || x==113) return;
		clockreset();
		clearer(MICRO,0);
		printat(43,34,"FETCH");
		f=1;
		execute(s);
		if (!end) execute(s);
		if (kbhit()) {
			x=getch();
			if (x==49) wait=1;
			if (x==50) wait=100;
		}
	}
	if (op==31) {
		clearer(MICRO,0);
		printat(43,34,"HALT");
		getch();
	}
}

void entry(unsigned char h)
{
	unsigned char y=0;
	unsigned int s=0;
	int i=0;

	sprintf(temp, "%c", h);
	printat(49,36,temp);
	if (h<60) s=h-48;
	else s=h-87;       
	for (i=1;i<=3;i++) {
		do y=getch(); 
		while ((y<48 || y>57) && (y<97 || y>102));
		sprintf(temp, "%c", y);
		printat(49+i,36,temp);
		s*=16;
		if (y<60) s=s+y-48;
		else s=s+y-87;
	}
	m[mar%128]=s;

	clearer(MEM, mar-off);
	clearer(DATA, 0);

	sprintf(temp, "%.4x", s);
	printat(71,mar+1-off, temp);
	mar++;
	point();
}

void counter(void)
{
	unsigned char y=0;
	int s=0;
	int i=0;

	printat(0,29,"PROGRAM");
	printat(0,30,"COUNTER");
	printat(24,29,"Enter value as 4 hexadecimal digits");
	printat(24,31,"Counter:");
	box(33,38,31,31);

	for (i=1;i<=4;i++) {
		s*=16;
		do y=getch(); 
		while ((y<48 || y>57) && (y<97 || y>102));
		if (y<60) s=s+y-48;
		else s=s+y-87;
		sprintf(temp, "%c", y);
		printat(33+i,31,temp);
	}
	pc = s;
	clearer(PC,0);
	sprintf(temp, "%.4x", pc);
	printat(6,7,temp);
}

void data(void)
{
	unsigned char x=0;
	int i;

	printat(0,29,"DATA");
	printat(0,30,"ENTRY");
	printat(24,29,"Use the cursor keys to select a memory location");
	printat(24,30,"Type 4 hexadecimal digits to enter data");
	printat(24,31,"Press I to insert a blank line");
	printat(24,32,"Press Z to zero address register");
	printat(24,33,"Press R to remove the current line");
	printat(24,34,"Press Q to quit");
	printat(24,36,"Enter instruction word:");
	box(48,53,36,36);

	while (x != 113) {
		while (!kbhit());
		x = getch();
		if (x==122) {
			mar=0;
			point();
		}
		if (x==0) {
			x=getch();
			if (x=='H' && mar!=0) {
				mar--;
				point();
			}
			if (x=='P') {
				mar++;
				point();
			}
		}
		if (x==105) {
			for (i=127;i>=(mar % 128)+1;i--) m[i]=m[i-1];
			m[mar%128]=65535;
			values();
		}
		if (x==114) {
			for (i=mar%128;i<=126;i++) m[i]=m[i+1];
			m[127]=65535;
			values();
		}
		if ((x>47 && x<58) || (x>96 && x<103)) entry(x);

		clearer(MAR,0);
		sprintf(temp, "%.4x", mar);
		printat(55,7,temp);
	}
}

void run(void)
{
	printat(0,29,"RUN");
	printat(0,30,"PROGRAM");
	printat(24,29,"1.  Fast");
	printat(24,30,"2.  Slow");
	printat(24,31,"3.  Quit");
	printat(24,34,"Microinstruction:");
	box(42,51,34,34);
	wait=1;
	prog();
}

void step(void)
{
	printat(0,29,"SINGLE STEP");
	printat(0,30,"BY INSTRUCTIONS");
	printat(24,29,"1.  Fast");
	printat(24,30,"2.  Slow");
	printat(24,31,"3.  Quit");
	printat(24,32,"Press SPACE for next instruction");
	printat(24,34,"Microinstruction:");
	box(42,51,34,34);
	wait=1;
	prog();
}

void micro(void)
{
	printat(0,29,"SINGLE STEP");
	printat(0,30,"BY MICROINSTRUCTIONS");
	printat(24,29,"1.  Fast");
	printat(24,30,"2.  Slow");
	printat(24,31,"3.  Quit");
	printat(24,32,"Press SPACE for next instruction");
	printat(24,34,"Microinstruction:");
	box(42,51,34,34);
	wait=1;
	prog();
}

void manent(void)
{
	unsigned int i=0;
	unsigned char key=0;

	clearer(MICRO,0);
	while (key != 13) {
		key=getch();
		if (key == 8) {
			if (i>0) {
				clearer(ENTRY,i);
				i--;
			}
		}
		else if (key != 13 && i<8) {
			sprintf(temp, "%c", key);
			printat(43+i,34,temp);
			mi[i]=key;
			i++;
		}
	}
	mi[i]='\0'; 
	strupr(mi);
}

void manual(void)
{
	unsigned int i=0, vi=0;

	wait=50; 
	p=0;
	printat(0,29,"MANUAL");
	printat(0,30,"OPERATION");
	printat(24,29,"Use LOWER CASE letters only");
	printat(24,30,"Enter any valid microinstruction");
	printat(24,31,"Enter Q to quit");
	printat(24,34,"Microinstruction:");
	box(42,51,34,34);
	clockreset();

	while (vi != 2) {
		vi=0;
		manent();
		if (strnicmp(mi, "Q", 1) == 0) vi=2;
		if (strlen(mi) < 4) strcpy(mi,"FFFF");
		if (strnicmp(mi, "ADC", 3) == 0) strcpy(mi, "ACEG");
		mi[2] = mi[strlen(mi)-2]; 
		mi[3] = mi[strlen(mi)-1]; 
		mi[4] = NULL;
		for (i=0;i<noin;i++) if (strcmp(mi, in[i]) == 0) vi=1;
		if (vi==0) {
			printat(24,35,"INVALID INSTRUCTION - Press a key");
			getch();
			clearer(INVALID,0);
		}
		if (vi==1) select();
	}
}

void menu(void)
{
	unsigned char x=0;

	clearer(MENU,0);
	printat(0,29,"MAIN");
	printat(0,30,"MENU");
	printat(24,29,"1.  Enter data");
	printat(24,30,"2.  Set program counter");
	printat(24,31,"3.  Run program");
	printat(24,32,"4.  Single step by instructions");
	printat(24,33,"5.  Single step by microinstructions");
	printat(24,34,"6.  Manual operation");
	printat(24,35,"7.  Finish");

	while (x<=48 || x>=56) x=getch();
	mench=x-48;

	clearer(MENU,0);
	switch (mench) {
	case 1: 
		data(); 
		break;
	case 2: 
		counter(); 
		break;
	case 3: 
		run(); 
		break;
	case 4: 
		step(); 
		break;
	case 5: 
		micro(); 
		break;
	case 6: 
		manual(); 
		break;
	}
}

void screen(void)
{
	int i;

	setcolor(2);
	printat(18,0,"CENTRAL PROCESSING UNIT");
	printat(2,2,"CLOCK  ffff");
	printat(19,3,"CONTROL");
	printat(20,4,"UNIT");
	printat(56,3,"Address");
	printat(58,4,"Bus");
	printat(55,5,"(7 bits)");
	printat(60,24,"Data Bus (16 bits)");
	printat(70,0,"MEMORY");
	printat(50,7,"MAR  000f");
	printat(50,18,"MBR  ffff");
	printat(40,22,"STATUS  00");
	printat(21,18,"ALU");
	printat(42,13,"A1");
	printat(26,13,"A2  ffff  ffff");
	printat(3,13,"REGISTERS");
	printat(21,10,"INTERNAL DATA BUS");
	printat(2,7,"PC  ffff");
	printat(14,7,"SP  0080");
	printat(26,7,"IR  ffff  ffff");
	printat(42,7,"IR2");
	printat(28,4,"STP IMP R7 R7");
	outtextxy(8*29.5,16*16.5,"ACCUMULATOR");
	outtextxy(8*32,16*19.8,"C  0");
	outtextxy(8*48,16*23.5,"NZ");
	box(8,13,2,2);
	box(5,10,7,7);
	box(17,22,7,7);
	box(29,34,7,7);
	box(35,40,7,7);
	box(54,59,7,7);
	box(27,42,5,3);
	box(0,59,10,10);
	box(29,34,13,13);
	box(35,40,13,13);
	box(25,44,20,16);
	box(26,43,18,18);
	box(34,36,19.5,19.5);
	box(54,59,18,18);
	box(47,50,22,22);
	vline(8,10,7);
	vline(20,10,7);
	vline(32,10,7);
	vline(38,10,7);
	vline(57,10,7);
	vline(32,7,5);
	vline(16,22.5,10);
	vline(19,22,10);
	vline(35,22,20);
	vline(32,16,13);
	vline(38,16,13);
	vline(32,13,10);
	vline(38,13,10);
	vline(48,22,17.5);
	vline(49.5,22,10);
	vline(57,18,10);
	vline(57,25.1,18);
	vline(57,7,5);
	hline(22,19,34);
	hline(18.5,45,47);
	hline(6,57,62);
	hline(25.1,57,78);
	arrow('u', 8, 7);
	arrow('u', 20, 7);
	arrow('u', 32, 7);
	arrow('u', 38, 7);
	arrow('u', 57, 7);
	arrow('u', 32, 5);
	arrow('u', 16, 10);
	arrow('u', 19, 10);
	arrow('u', 49.5, 10);
	arrow('u', 57, 10);
	arrow('u', 57, 18);
	arrow('d', 8, 10);
	arrow('d', 20, 10);
	arrow('d', 38, 10);
	arrow('d', 32, 13);
	arrow('d', 38, 13);
	arrow('d', 32, 16);
	arrow('d', 38, 16);
	arrow('d', 57, 18);
	arrow('d', 48, 22);
	point();

	for (i=0;i<=7;i++) {
		box(6,11,15+i,15+i);
		hline(15.5+i,12,15);
		arrow('l',12,15.5+i);
		arrow('r',16,15.5+i);
		sprintf(temp, "R%d", i);
		printat(3,15+i,temp);
		printat(7,15+i,"ffff");
	}
	for (i=0;i<=21;i++) {
		box(70,75,i+1,i+1);
		sprintf(temp,"%.4x",i);
		printat(65,i+1,temp);
		sprintf(temp,"%.4x",65535);
		printat(71,i+1,temp);
	}
	printat(27,18,"0000000000000000");
}

void readins(void)
{
	FILE *fp = fopen("microins.dat","rb");

	if (fp == NULL) {
		printf("File error: Microinstructions file not found (MICROINS.DAT)\n");
		exit(-1);
	}
	while (!feof(fp)) {
		fgets(in[noin],5,fp);
		noin++;
	}
	fclose(fp);
}

void main(void)
{
	int i;

	readins();
	capsoff();
	welcome();
	screen();

	for (i=0;i<=127;i++) m[i] = 65535;
	for (i=0;i<=7;i++) r[i] = 65535;

	while (mench != 7) menu();
	closegraph();
}
