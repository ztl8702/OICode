program p1413;
const
  MaxN=200+1;
  ERRMSG='No solution';
var
  like:array[0..MaxN,0..MaxN]of boolean;
  col,vst:array[0..MaxN]of boolean;
  f:array[0..MaxN,-MaxN .. MaxN]of boolean;
  count:array[0..1]of longint;
  diff:array[0..MaxN]of longint;
  n,bcount:longint;


  procedure dfs(const now:longint;const flag:boolean);
  var
    i:longint;
  begin
    col[now]:=flag;
    vst[now]:=true;
    inc(count[ord(flag)]);
    for i:=1 to n do
      if i<>now then
      if (not like[now,i])or(not like[i,now]) then
      begin
        if not vst[i] then
          dfs(i,not flag)
        else
        if col[i]=flag then
        begin
          writeln(ERRMSG);
          halt;
        end;
      end;

  end;

  procedure Process;
  var
    i,j:longint;

  begin
    fillchar(vst,sizeof(vst),false);
    bcount:=0;
    for i:=1 to n do
      if not vst[i] then
      begin
        inc(bcount);
        count[0]:=0;
        count[1]:=0;
        dfs(i,false);
        diff[bcount]:=abs(count[0]-count[1]);
      end;
      fillchar(f,sizeof(f),false);
      f[0,0]:=true;
      for i:=1 to bcount do
        for j:=-n to n do
          f[i,j]:=f[i-1,j-diff[i]] or f[i-1,j+diff[i]];
      for i:=0 to n do
        if f[bcount,i] or f[bcount,-i] then
        begin
          writeln(i);
          break;
        end;
  end;

  procedure ReadData;
  var
    i,j:longint;
  begin
    fillchar(like,sizeof(like),false);
    readln(n);
    for i:=1 to n do
    begin
      read(j);
      while j<>0 do
      begin
        like[i,j]:=true;
        read(j);
      end;
    end;
  end;

begin
{$IFNDEF ONLINE_JUDGE}
  assign(input,'OJ1413.in');
  reset(input);
  assign(output,'OJ1413.out');
  rewrite(output);
{$ENDIF}
  ReadData;
  process;


end.