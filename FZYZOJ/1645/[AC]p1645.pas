program msquare;
type
  TSQ=array[1..8]of shortint;
var
  Q:array[0..100000]of TSQ;
  vst:array[0..100000]of boolean;
  fa:array[0..100000]of longint;
  ch:array[0..100000]of  shortint;
  start:TSQ;
  tt:TSQ;
  Target:longint;

  function hash(const s:TSQ):longint;
  var
    i,j,t,ans:longint;
  begin
    ans:=0;
    for i:=1 to 7 do
    begin
      t:=0;
      for j:=i+1 to 8 do
        if s[j]<s[i] then
          inc(t);
      ans:=(ans+t) *(8-i);
    end;
    exit(ans);
  end;

  function ChangeA(const s:TSq):TSQ;
  var
    ans:TSQ;
  begin
    ans[1]:=s[8];
    ans[2]:=s[7];
    ans[3]:=s[6];
    ans[4]:=s[5];
    ans[5]:=s[4];
    ans[6]:=s[3];
    ans[7]:=s[2];
    ans[8]:=s[1];
    exit(ans);
  end;

  function ChangeB(const s:TSQ):TSQ;
  var
    a:TSQ;
  begin
    a[1]:=s[4]; a[2]:=s[1]; a[3]:=s[2]; a[4]:=s[3];
    a[8]:=s[5]; a[7]:=s[8]; a[6]:=s[7]; a[5]:=s[6];
    exit(a);
  end;

  function ChangeC(const s:TSQ):TSQ;
  var
    a:TSQ;
  begin
    a[1]:=s[1]; a[2]:=s[7]; a[3]:=s[2]; a[4]:=s[4];
    a[8]:=s[8]; a[7]:=s[6]; a[6]:=s[3]; a[5]:=s[5];
    exit(a);
  end;
  var
     arr:array[0..10000]of shortint;
  procedure outout(po:longint);
  var
    i:longint;

    acount:longint;
  begin
    acount:=0;
    i:=po;
    while i<>0 do
    begin
      inc(acount);
      arr[acount]:=ch[i];
      i:=fa[i];
    end;
    writeln(acount-1);
    for i:=acount-1 downto 1 do
      write(chr(arr[i]+64));
    writeln;

  end;

  procedure Search;
  var
    h,t:longint;
    now,new:TSQ;
    th:longint;
    procedure Change(const Kind:longint);
    begin
      case kind of
      1:new:=ChangeA(now);
      2:new:=ChangeB(now);
      3:new:=ChangeC(now);
      end;
      th:=hash(new);
      if not vst[th] then
      begin
        vst[th]:=true;
        inc(t);
        Q[t]:=new;
        fa[t]:=h;
        ch[t]:=Kind;
      end;
      if th=target then
      begin
        outout(t);
        halt;
      end;
    end;
  begin
    h:=0;
    t:=1;
    Q[t]:=Start;
    fa[t]:=0;
    ch[t]:=0;
    vst[hash(Q[t])]:=true;
    if hash(Q[t])=target then
    begin
      writeln(0);
      halt;
    end;
    repeat
      inc(h);
      now:=Q[h];
      Change(1);
      Change(2);
      Change(3);
    until h>=t;
    writeln('No Answer');

  end;
var
  i:longint;
begin

  for i:=1 to 8 do
  begin
    read(tt[i]);
    start[i]:=i;
  end;
  target:=hash(tt);
  Search;
end.
