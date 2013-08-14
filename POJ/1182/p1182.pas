program p1182;
{Food-chain}
const
  TYPE_A=-1;
  TYPE_B=-2;
  TYPE_C=-3;
  DEFINED=[TYPE_A,TYPE_B,TYPE_C];
  caneat:array[1..3,1..3]of boolean=((false,true,false),
                                     (false,false,true),
                                     (true,false,false));
  food:array[1..3]of shortint=(2,3,1);
  anmy:array[1..3]of shortint=(3,1,2);
type
  TEg=record
    b,next:longint;
  end;
var
  N,K:longint;
  father:array[-5..50005]of longint;
  start:array[-5..50005]of longint;
  es:array[0..100000]of TEg;
  ecount:longint;
  fakecount:longint;
  {UF Set}

  function getfather(const a:longint):longint;
  begin
    if father[a]<>a then
      father[a]:=getfather(father[a]);
    exit(father[a]);
  end;

  function issame(const a,b:longint):boolean;
  begin
    exit(boolean(getfather(a)=getfather(b)));
  end;

  procedure union(const a,b:longint);
  var
    fa,fb:longint;
  begin
    fa:=getfather(a);
    fb:=getfather(b);
    father[fa]:=fb;
  end;

  {GRAPH}
  procedure addedge(const a,b:longint);
  begin
    inc(ecount);
    es[ecount].b:=b;
    es[ecount].next:=start[a];
    start[a]:=ecount;
  end;

  function connected(const a,b:longint):boolean;
  var
    j:longint;
  begin
    j:=start[a];
    while j<>0 do
    begin
      if es[j].b=b then
        exit(true);
      j:=es[j].next;
    end;
    exit(false);
  end;

  function dis(const a,b:longint):longint;
  var
    vst:array[0..50005]of boolean;
    mindis:longint;
    procedure dfs(const now,sum:longint);
    var
      j:longint;
    begin
      vst[now]:=true;
      if now=b then
      begin
        if sum<mindis then
          mindis:=sum;
        exit;
      end;
      if sum>=mindis then
        exit;

      j:=start[now];
      while j<>0 do
      begin
        if not vst[es[j].b] then
          dfs(es[j].b,sum+1);
        j:=es[now].next;
      end;
      vst[now]:=false;
    end;

  begin
    fillchar(vst,sizeof(vst),false);
    mindis:=maxlongint;
    dfs(a,0);
    if mindis=maxlongint then
      exit(0)
    else
      exit(mindis);
  end;

  {MAIN SECTION}
  procedure main;
  var
    i,a,b,c:longint;
  begin
    readln(n,k);
    for i:=-3 to n do
      father[i]:=i;
    ecount:=0;
    fakecount:=0;

    for i:=1 to k do
    begin
      writeln('---',fakecount);
      readln(a,b,c);
      if (b>N)or(c>N) then
        inc(fakecount)
      else
        case a of
          1:
          begin
            if (GetFather(b) in DEFINED)and(GetFather(c) in DEFINED) then
              if GetFather(b)<>GetFather(c) then
              begin
                inc(fakecount);
                continue;
              end;
            if (dis(GetFather(b),GetFather(c) mod 3))<>0 then
              inc(fakecount)
            else
              Union(b,c);
          end;
          2:
          begin
            if (GetFather(b) in DEFINED)and(GetFather(c) in DEFINED) then
              if not caneat[GetFather(b),GetFather(c)]then
              begin
                inc(fakecount);
                continue;
              end;
            if GetFather(b)=GetFather(c) then
            begin
              inc(fakecount);
              continue;
            end;
            if GetFather(b) in DEFINED then
            begin
              Union(c,-food[-GetFather(b)]);
              continue;
            end;
            if GetFather(c) in DEFINED then
            begin
              Union(b,-anmy[-GetFather(c)]);
              continue;
            end;
            addedge(GetFather(b),GetFather(c));
            addedge(GetFather(c),GetFather(b));
          end;
        end;

    end;

  end;

begin
  main;
  writeln(fakecount);
end.