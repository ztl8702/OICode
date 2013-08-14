program p1583;
const
  dx:array[1..9]of shortint=(+0,-1,-1,+0,+1,+1,+1,+0,-1);
  dy:array[1..9]of shortint=(+0,+0,+1,+1,+1,+0,-1,-1,-1);
var
  N,M,T:longint;
  map:array[0..10,0..10]of longint;
  hi:array[0..10,0..10]of longint;
  ans:longint;

  procedure dfs(const x,y,sum:longint);
  var
    i,j:longint;
  begin
    if sum>ans then
      ans:=sum;
    for i:=1 to 9 do
      inc(hi[x+dx[i],y+dy[i]]);
    for i:=y+2 to m do
      if hi[x,i]=0 then
        dfs(x,i,sum+map[x,i]);
    for i:=x+1 to n do
      for j:=1 to m do
        if hi[i,j]=0 then
          dfs(i,j,sum+map[i,j]);
    for i:=1 to 9 do
      dec(hi[x+dx[i],y+dy[i]]);
  end;

  procedure processonce;
  var
    i,j:longint;
  begin
    ans:=-1;
    fillchar(hi,sizeof(hi),63);
    readln(n,m);
    for i:=1 to n do
    begin
      for j:=1 to m do
      begin
        read(map[i,j]);
        hi[i,j]:=0;
      end;
      readln;
    end;
    for i:=1 to n do
      for j:=1 to m do
        dfs(i,j,map[i,j]);
    writeln(ans);
  end;
var
  ii:longint;
begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'p1583.in');
  reset(input);
  assign(output,'p1583.out');
  rewrite(output);
  {$ENDIF}
  readln(t);
  for ii:=1 to t do
    processonce;
  close(output);
  close(input);
end.
