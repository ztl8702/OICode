program li;
const
  SPACE=' ';
  LBR='(';
  RBR=')';
  OAND='&';
  OOR='|';
  ONOT='!';
var
  a:ansistring;
  len,l:longint;
  k,v:array[0..200]of boolean;
  h:array[0..200]of longint;
  op:array[0..200]of char;
  pre,next:array[0..200]of longint;

  procedure anlaysis;
  var
    i:longint;
    hi:longint;
  begin
    i:=1;
    while (i<=length(a)) do
    begin
      while (i<=length(a))and(a[i]<>SPACE) do
        inc(i);
      if i<=length(a) then
        delete(a,i,1);
    end;
    hi:=0;
    len:=length(a);
    for i:=1 to len do
    begin
      case a[i] of
        LBR:inc(hi,3);
        RBR:dec(hi,3);
        ONOT,OAnd,OOr:
        begin
          inc(l);
          pre[l]:=l-1;
          next[l]:=l+1;
          k[l]:=true;
          op[l]:=a[i];
          case op[l] of
            ONot:h[l]:=hi+3;
            OAnd:h[l]:=hi+2;
            OOr:h[l]:=hi+1;
          end;
        end;
        'F','V':
        begin
          inc(l);
          pre[l]:=l-1;
          next[l]:=l+1;
          k[l]:=false;
          v[l]:=boolean(a[i]='V');
        end;
      end;
    end;
    next[l]:=-1;
    pre[1]:=0;
    next[0]:=1;
  end;

  procedure DeleteItem(const po:longint); inline;
  begin
    next[pre[po]]:=next[po];
    if next[po]<>-1 then
      pre[next[po]]:=pre[po];
    next[po]:=-1;
    pre[po]:=-1;
    dec(l);
  end;

  procedure calc;
  var
    i:longint;
    max,maxi:longint;
  begin
    while l>1 do
    begin
      max:=-maxlongint;
      maxi:=-1;
      i:=next[0];
      while i<>-1 do
      begin
        if k[i] then
          if h[i]>=max then
          begin
            max:=h[i];
            maxi:=i;
          end;
        i:=next[i];
      end;
      if maxi<>-1 then
        case op[maxi] of
          ONot:
          begin
            v[maxi]:=not v[next[maxi]];
            k[maxi]:=false;
            DeleteItem(next[maxi]);
          end;
          OAnd:
          begin
            v[maxi]:=v[pre[maxi]] and v[next[maxi]];
            k[maxi]:=false;
            DeleteItem(next[maxi]);
            DeleteItem(pre[maxi]);
          end;
          OOr:
          begin
            v[maxi]:=v[pre[maxi]] or v[next[maxi]];
            k[maxi]:=false;
            DeleteItem(next[maxi]);
            DeleteItem(pre[maxi]);
          end;
        end;
    end;
  end;

  procedure processOnce(const id:longint);
  begin
    l:=0;
    anlaysis;
    calc;
    write('Expression ',id,': ');
    if v[next[0]]=true then
      writeln('V')
    else
      writeln('F');
  end;
var
  count:longint;
begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'p1322.in');
  reset(input);
  assign(output,'p1322.out');
  rewrite(output);
  {$ENDIF}
  count:=1;
  while not eof do
  begin
    readln(a);
    processOnce(count);
    inc(count);
  end;
end.
