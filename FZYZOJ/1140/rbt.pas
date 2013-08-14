program P1140;
const
	maxn=500500;
type
	stack=array[0..20]of longint;
var
	ans:int64;
	n,head,tail:longint;
	min,min5,hrs:stack;
	ball:array[0..maxn*2]of longint;
	perm:array[0..maxn]of longint;

procedure init;
var
	i:longint;
begin
	readln(n);
	for i:=1 to n do ball[i]:=i;
	head:=1;
	tail:=n;
end;

procedure push(var opt:stack;const key:longint);
begin
	inc(opt[0]);
	opt[opt[0]]:=key;
end;

function pop(var opt:stack):longint;
begin
	pop:=opt[opt[0]];
	dec(opt[0]);
end;

procedure empty(var opt:stack);
var
	t:longint;
begin
	while opt[0]>0 do
	begin
		t:=pop(opt);
		inc(tail);
		ball[tail]:=t;
	end;
end;

procedure simulate;
var
	i,t:longint;
begin
	for i:=1 to 60*24 do
	begin
		push(min,ball[head]);
		if min[0]=5 then
		begin
			t:=pop(min);
			empty(min);
			push(min5,t);
			if min5[0]=12 then
			begin
				t:=pop(min5);
				empty(min5);
				push(hrs,t);
				if hrs[0]=12 then
				begin
					t:=pop(hrs);
					empty(hrs);
					inc(tail);
					ball[tail]:=t;
				end;
			end;
		end;
		inc(head);
	end;
end;

function gcd(const a,b:int64):int64;
begin
	if b=0 then exit(a);
	exit(gcd(b,a mod b));
end;

procedure main;
var
	i,p,t:longint;
	s:int64;
begin
	simulate;
	for i:=head to tail do
	begin
		perm[i-head+1]:=ball[i];
//		write(ball[i],' ');
	end;
//	writeln;
	ans:=1;
	for i:=1 to n do
	begin
		if perm[i]=0 then continue;
		p:=i;
		s:=0;
		repeat
			t:=p;
			p:=perm[p];
			perm[t]:=0;
			s:=s+1;
		until p=i;
		ans:=ans*(s div gcd(ans,s));
	end;
end;

procedure print;
begin
	writeln(ans);
end;

begin
	init;
	main;
	print;
end.

