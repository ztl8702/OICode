program p1500;
type
  TBlock=array[0..9]of integer;
  PBlock=^TBlock;
const
  size=370000;
  drt:array[1..9,0..4]of shortint=((2,2,4,0,0),
                                   (3,1,3,5,0),
                                   (2,2,6,0,0),
                                   (3,1,5,7,0),
                                   (4,2,4,6,8),
                                   (3,3,5,9,0),
                                   (2,4,8,0,0),
                                   (3,5,7,9,0),
                                   (2,6,8,0,0));
  tar1:TBlock=(1,0,1,2,3,4,5,6,7,8);
  tar2:TBlock=(5,1,2,3,8,0,4,7,6,5);
var
  hash:array[0..400000]of boolean;
  start:TBlock;
  Q:array[0..size]of TBlock;
  dep:array[0..size]of longint;

  function KT(const b:TBlock):longint;
  var
    sum,i,j:longint;
    tt:longint;
  begin
    tt:=1;
    sum:=0;
    for i:=8 downto 1 do
    begin
      tt:=tt*(9-i);
      for j:=i+1 to 9 do
        if b[j]<b[i] then
          inc(sum,tt);
    end;
    exit(sum);
  end;

  function change(const b:TBlock;const x,y:longint):TBlock;
  var
    tmp:TBlock;
    m:longint;
  begin
    tmp:=b;
    m:=tmp[x];
    tmp[x]:=tmp[y];
    tmp[y]:=m;
    if tmp[x]=0 then
      tmp[0]:=x;
    if tmp[y]=0 then
      tmp[0]:=y;
    exit(tmp);
  end;

  function compare(const a,b:PBlock):boolean;
  var
    i:longint;
  begin
    for i:=1 to 9 do
      if a^[i]<>b^[i] then
        exit(false);
    exit(true);
  end;

  procedure bfs();
  var
    h,t,i,hi:longint;
    now:PBlock;
    new:TBlock;
  begin
    h:=0;
    t:=1;
    Q[t]:=start;
    dep[t]:=0;
    hash[KT(Q[t])]:=true;
    if compare(@start,@tar1)or compare(@start,@tar2) then
    begin
      writeln(0);
      exit;
    end;
    repeat
      h:=(h+1) mod size;
      now:=@Q[h];
      for i:=1 to drt[now^[0],0] do
      begin
        new:=Change(now^,now^[0],drt[now^[0],i]);
        hi:=KT(new);
        if not hash[hi] then
        begin
          hash[hi]:=true;
          t:=(t+1) mod size;
          Q[t]:=new;
          dep[t]:=dep[h]+1;
          if compare(@new,@tar1) or compare(@new,@tar2) then
          begin
            writeln(dep[t]);
            exit;
          end;
        end;
      end;
    until h>=t;
    writeln('-1');
  end;

  procedure readdata;
  var
    i:longint;
  begin
    for i:=1 to 9 do
    begin
      read(Start[i]);
      if start[i]=0 then
        start[0]:=i;
    end;
  end;

begin
  readdata;
  bfs;
end.