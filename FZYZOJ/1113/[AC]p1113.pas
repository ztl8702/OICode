program p1113;
const
  MAXLL=2000000;
  MAXN=105;
var
  names:array[0..MAXN]of ansistring;
  next:array[0..MAXN]of longint;
  hash:array[0..MAXLL]of longint;
  team:array[0..MaxN,0..3]of longint;
  used:array[1..MAXN]of boolean;
  hcount,k:longint;
  maxans:longint;

  function BKDR(const str:ansistring):longint;
  var
    hash,base,i:longint;
  begin
    base:=131;
    hash:=0;
    for i:=1 to length(str) do
      hash:=(hash*base+longint(str[i])) mod MAXLL;
    while hash<0 do
      inc(hash,MAXLL);
    exit(hash);
  end;

  function find(const ss:ansistring):longint;
  var
    tmp,p:longint;
  begin
    tmp:=BKDR(ss);
    p:=hash[tmp];
    while p<>0 do
    begin
      if names[p]=ss then
        exit(p);
      p:=next[p];
    end;
    exit(0);
  end;

  function getid(const ss:ansistring):longint;
  var tmp,p:longint;
  begin
    tmp:=find(ss);
    if tmp>0 then
      exit(tmp);

    tmp:=BKDR(ss);
    inc(hcount);
    names[hcount]:=ss;
    next[hcount]:=hash[tmp];
    hash[tmp]:=hcount;
    exit(hcount);
  end;

  procedure dfs(const nowi,sum:longint);
  var
    i:longint;
  begin
    if sum>maxans then
      maxans:=sum;
    for i:=nowi +1 to k do
    begin
      if not (used[team[i,1]] or used[team[i,2]] or used[team[i,3]]) then
      begin
        used[team[i,1]]:=true;
        used[team[i,2]]:=true;
        used[team[i,3]]:=true;
        dfs(i,sum+1);
        used[team[i,1]]:=false;
        used[team[i,2]]:=false;
        used[team[i,3]]:=false;
      end;
    end;
  end;

  procedure readdata;
  var
    i:longint;
    rd,tmp:ansistring;
  begin
    readln(k);
    for i:=1 to k do
    begin
      readln(rd);
      tmp:=copy(rd,1,pos(' ',rd)-1);
      team[i,1]:=getid(tmp);
      delete(rd,1,pos(' ',rd));
      tmp:=copy(rd,1,pos(' ',rd)-1);
      team[i,2]:=getid(tmp);
      delete(rd,1,pos(' ',rd));
      team[i,3]:=getid(rd);
    end;
  end;

  procedure main;

  begin
    maxans:=0;
    dfs(0,0);
    writeln(maxans);
  end;


begin
  readdata;
  main;
end.
