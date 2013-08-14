program p1005;
const
  MAXN=15;
  MAXM=100+5;
var
  vst:array[0..100000]of longint;
  Ba,Bb,Fa,Fb:array[0..MaxM]of longint;
  //Q,dep:array[0..80000]of longint;
  v:array[0..MAXM]of longint;
  n,m:longint;

  procedure dfs(const now,sum:longint);
  var
    i,new:longint;
  begin
    //writeln(now);
    if vst[now]<=sum then
      exit
    else
      vst[now]:=sum;
    if now=0 then
      exit;
    if vst[now]>=vst[0]  then
      exit;
    for i:=1 to m do
    begin
      if ((now or Ba[i])=now)and((now and Bb[i])=0) then
      begin
        new:=(now and (now xor Fb[i])) or Fa[i];
        dfs(new,sum+v[i]);
      end;
    end;
  end;

  procedure readdata;
  var
    i,j,code:longint;
    rd,tmp:ansistring;
  begin
    readln(n,m);
    for i:=1 to m do
    begin
      readln(rd);
      val(copy(rd,1,pos(' ',rd)-1),v[i],code);
      delete(rd,1,pos(' ',rd));
      tmp:=copy(rd,1,pos(' ',rd)-1);
      for j:=0 to n-1 do
        case tmp[j+1] of
          '+':Ba[i]:=Ba[i] or (1 shl j);
          '-':Bb[i]:=Bb[i] or (1 shl j);
        end;
      delete(rd,1,pos(' ',rd));
      for j:=0 to n-1 do
        case rd[j+1] of
          '+':Fa[i]:=Fa[i] or (1 shl j);
          '-':Fb[i]:=Fb[i] or (1 shl j);
        end;
    end;
  end;

  procedure main;
  var
    MaxInt:longint;
  begin
    fillchar(vst,sizeof(vst),127);
    MaxInt:=vst[0];
    dfs((1 shl n)-1,0);
    if vst[0]<MaxInt then
      writeln(vst[0])
    else
      writeln('0');
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'p1005.in');
  reset(input);
  assign(output,'p1005.out');
  rewrite(output);
  {$ENDIF}
  readdata;
  main;

end.

