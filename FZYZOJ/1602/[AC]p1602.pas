program p1602;
var
  m:longint;
  base:array[0..15]of longint;
  ten:array[0..9]of longint;
  X,S:longint;

  procedure readdata;
  var
    i:longint;
  begin
    readln(m);
    for i:=0 to m-1 do
      read(base[i]);
    readln;
    readln(X);
    readln(S);
  end;

  procedure XToDecimal(xx:longint);
  var
    tmp:longint;
    i,tp:longint;
  begin
    tmp:=0;
    tp:=1;
    while xx>0 do
    begin
      inc(tmp,ten[xx mod 10]*tp);
      tp:=tp*m;
      xx:=xx div 10;
    end;
    writeln(tmp);
  end;

  var
    rm:array[0..20]of longint;

  procedure DToX(dd:longint);
  var
    len,i:longint;
  begin
    len:=0;
    while dd>0 do
    begin
      inc(len);
      rm[len]:=dd mod m;
      dd:=dd div m;
    end;
    for i:=len downto 1 do
      write(base[rm[i]]);
    writeln;
  end;

  procedure main;
  var
    i,j,t,newn:longint;
  begin
    j:=m-2;
    repeat
      newn:=-1;
      for i:=0 to j do
        if base[i]>base[i+1] then
        begin
          t:=base[i];
          base[i]:=base[i+1];
          base[i+1]:=t;
          newn:=i;
        end;
      j:=newn-1;
    until j<0;
    for i:=0 to m-1 do
      ten[base[i]]:=i;
    XToDecimal(x);
    DToX(s);
  end;

begin
  {$IFDEF LOCAL_JUDGE}
  assign(input,'p1602.in');
  reset(input);
  assign(output,'p1602.out');
  rewrite(output);
  {$ENDIF}
  readdata;
  main;
  close(input);
  close(output);
end.