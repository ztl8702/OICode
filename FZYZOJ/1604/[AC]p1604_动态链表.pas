program p1604;
type
  PStudent=^TStudent;
  TStudent=record
    id:longint;
    l,r:PStudent;
  end;
var
  n,m:longint;
  s:array[0..100005]of PStudent;
  vst:array[0..100005]of boolean;
  start,final:PStudent;

  procedure add(b:PStudent;const ni:longint); //AddToRight
  begin
    vst[ni]:=true;
    new(s[ni]);
    s[ni]^.id:=ni;
    s[ni]^.l:=b;
    s[ni]^.r:=b^.r;
    if b^.r<>nil then
      b^.r^.l:=s[ni];
    b^.r:=s[ni];
  end;

  procedure delete(const ii:longint);
  begin
    if s[ii]^.l<>nil then
      s[ii]^.l^.r:=s[ii]^.r;
    if s[ii]^.r<>nil then
      s[ii]^.r^.l:=s[ii]^.l;
    dispose(s[ii]);
    vst[ii]:=false;
  end;

  procedure main;
  var
    x1,x2,i:longint;
    p:PStudent;
  begin

    readln(n);
    new(s[1]);
    new(start);
    new(final);
    start^.l:=nil;
    start^.r:=s[1];
    final^.l:=s[1];
    final^.r:=nil;
    vst[1]:=true;
    s[1]^.id:=1;
    s[1]^.l:=start;
    s[1]^.r:=final;
    for i:=2 to n do
    begin
      readln(x2,x1);
      if x1=1 then
        add(s[x2],i)
      else
        add(s[x2]^.l,i);
    end;
    readln(m);
    for i:=1 to m do
    begin
      readln(x1);
      if vst[x1] then
        delete(x1);
    end;
    if start^.r<>final then
    begin
      p:=start^.r;
      while p^.r<>final do
      begin
        write(p^.id,' ');
        p:=p^.r;
      end;
      writeln(p^.id);
    end;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'p1604.in');
  reset(input);
  assign(output,'p1604.out');
  rewrite(output);
  {$ENDIF}
  main;
end.
