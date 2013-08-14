program project1;
type
  TEg=record
    a,b,next:longint;
  end;

  TLink=record
    id:longint;
    next,last:longint;
  end;

const
  MaxN = 300 + 1;

var
  father: array[0..MaxN] of longint;
  cut:array[0..MaxN]of boolean;
  eg:array[0..MaxN,0..MaxN]of longint;
  open:array[0..MaxN]of longint;
  poi:array[0..MaxN]of TLink;
  vst:array[0..MaxN]of boolean;
  n:longint;
  procedure toposort;
  var
    h,t,i,now:longint;
  begin
    h:=0;
    t:=1;
    open[1]:=1;
    fillchar(vst,sizeof(vst),false);
    vst[open[1]]:=true;
    poi[i].next:=0;
    poi[i].last:=0;
    repeat
      inc(h);
      now:=open[h];
      for i:=1 to eg[now,0] do
      begin
        if not vst[eg[now,i]] then
        begin
          inc(t);
          open[t]:=eg[now,i];
          vst[open[t]]:=true;

          poi[poi[now].last].next:=eg[now,i];
          poi[now.last]:=poi[eg[now,i]].last;
        end;
      end;
    until h>=t;
  end;

  procedure ReadData;
  var
    i,a,b:longint;
  begin
    readln(n);
    for i:=1 to n do
    begin
      readln(a,b);
      inc(eg[a,0]);
      eg[a,eg[a,0]]:=b;
      inc(eg[b,0]);
      eg[b,eg[b,0]]:=a;
    end;
  end;

begin
  ReadData;
  topoSort;


end.

