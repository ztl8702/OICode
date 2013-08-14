program p1117;
Const
  FINC=1;
  FDEC=-1;
type
  TPoint=record
    v,t:longint;
    order:longint;
  end;
var
  n:longint;
  cards:array[0..10,0..100]of TPoint;
  colors:array[0..1,0..10]of longint;
  vst:array[0..1,0..10]of boolean;
  tail:array[0..2000]of longint;
  len:longint;
  colcount:longint;
  a,b:array[0..2000] of TPoint;
 // len:array[0..2000,0..2000]of longint;
  ans,intsize:longint;

  procedure SortCard(const col,l,r,flag:longint);
  var
    i,j,mid:longint;
    x:TPoint;
  begin
    i:=l;
    j:=r;
    mid:=cards[col,(l+r) shr 1].v;
    repeat
      while mid*flag>cards[col,i].v*flag do
        inc(i);
      while mid*flag<cards[col,j].v*flag do
        dec(j);
      if i<=j then
      begin
        x:=cards[col,i];
        cards[col,i]:=cards[col,j];
        cards[col,j]:=x;
        inc(i);
        dec(j);
      end;
    until i>j;
    if l<j then
      SortCard(col,l,j,flag);
    if i<r then
      SortCard(col,i,r,flag);

  end;

  function Max(const a,b:longint):longint;
  begin
    if a>b then exit(a)
    else exit(b);
  end;

  function FindInTail(const l,r,tar:longint):longint;
  var
    i,j,mid:longint;
  begin
    i:=l;
    j:=r;
    while (i<=j) do
    begin
      mid:=(i+j)shr 1;
      if tail[mid]=tar then
        exit(mid)
      else
      if tail[mid]>tar then
        j:=mid-1
      else
        i:=mid+1;
    end;
    if tail[l]<tar then
      exit(i)
    else
      exit(i);
  end;

  function LIS:longint;
  var
    i,j:longint;
  begin
    len:=0;
    for i:=1 to n do
    begin
      j:=FindInTail(1,len,b[i].order);
      if j<=len then
        Tail[j]:=b[i].order
      else
      begin
        inc(len);
        Tail[len]:=b[i].order;
      end;
    end;
    exit(len);
  end;

  procedure ReadData;
  var i:longint;
  begin
    readln(n);
    for i:=1 to n do
    begin
      readln(a[i].v,a[i].t);
      a[i].order:=i;
    end;
  end;

  Procedure pcard;
  var i:longint;
  begin
     for i:=1 to n do
     begin
       inc(cards[a[i].t,0].v);
       cards[a[i].t,cards[a[i].t,0].v]:=a[i];
     end;
     for i:=1 to 10 do
       if cards[i,0].v>0 then
       begin
         if cards[i,0].v>1 then SortCard(i,1,cards[i,0].v,FINC);
         inc(colors[ord(odd(i)),0]);
         colors[ord(odd(i)),colors[ord(odd(i)),0]]:=i;
       end;
  end;

  function movec(const colid,po:longint):longint;
  begin
    move(cards[colid,1],b[po],intsize*cards[colid,0].v);
    exit(cards[colid,0].v);
  end;

  procedure doing(const flag:boolean;len:longint);
  var
    i,tmp:longint;
  begin
    if len>=n then
    begin
      ans:=max(ans,LIS);
      exit;
    end;
    for i:= 1 to colors[ord(flag),0] do
      if not vst[ord(flag),i] then
      begin
        vst[ord(flag),i]:=true;
        tmp:= movec(colors[ord(flag),i],len+1);
        doing(not flag,len+tmp);
        vst[ord(flag),i]:=false;
      end;
  end;

  procedure Main;
  var i:longint;
  begin
    ans:=0;
    fillchar(vst,sizeof(vst),false);
    doing(false,0);
    fillchar(vst,sizeof(vst),false);
    doing(true,0);
    for i:=1 to 10 do
      if cards[i,0].v>1 then
        SortCard(i,1,cards[i,0].v,FDEC);
    fillchar(vst,sizeof(vst),false);
    doing(false,0);
    fillchar(vst,sizeof(vst),false);
    doing(true,0);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'oj1117.in');
  reset(input);
  assign(output,'oj1117.out');
  rewrite(output);
  {$ENDIF}
  intsize:=sizeof(a[1]);
  ReadData;
  Pcard;
  Main;
  writeln(n-ans);
end.
