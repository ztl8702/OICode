program fence; //OJ_1347
const
  maxn = 100;
  maxM = 1000;
type
  TEg = record
    a, b, w, Next: longint;
  end;
var
  eg:      array[0..MaxM] of TEg;
  ecount:  longint;
  start, eq: array[0..2 * MaxN] of longint;
  isright: array[0..MaxN, 0..MaxN] of boolean;
  link:    array[0..MaxN, 0..1, 0..MaxN] of longint;
  ab:      array[0..2 * MaxN] of boolean;

  procedure AddEdge(const a, b, w: longint);
  begin
    Inc(ecount);
    eg[ecount].a    := a;
    eg[ecount].b    := b;
    eg[ecount].w    := w;
    eg[ecount].Next := start[eg[ecount].a];
    start[eg[ecount].a] := ecount;
  end;


  procedure expand(const nowi:longint;left:boolean);
  var
    i,tar,nid,tid:longint;
  begin
    nid:=nowi*2-ord(left);
    for i:=1 to link[nowi,ord(not left),0]  do
    begin
      tar:=link[nowi,ord(not left),i];
      tid:=tar*2-ord(isright[nowi,tar]);
      eq[
      AddEdge(nid,tid,len[tar]);
      AddEdge(tid,nid,len[tar]);
    end;
  end;

  procedure ReadData;
  var
    i, j, n1s, n2s, now, len: longint;
  begin
    readln(n);
    for i := 1 to n do
    begin
      Read(now, len);
      readln(link[now, 0, 0], link[now, 1, 0]);
      for j := 1 to link[now, 0, 0] do
      begin
        Read(link[now, 0, j]);
        isright[link[now, 0, j],now ] := False;
      end;
      for j := 1 to link[now, 1, 0] do
      begin
        Read(link[now, 1, j]);
        isright[link[now, 1, j],now ] := True;
      end;
    end;
    for i := 1 to n do
    begin
      AddEdge()
    end;
  end;

begin
end.

