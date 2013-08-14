program p1196;

var
  mid, last: string;

  procedure work(const mi, li: string);
  var
    po, len: longint;
  begin
    len := length(li);
    Write(li[len]);
    po := pos(li[len], mi);
    if po > 1 then
      work(copy(mi, 1, po - 1), copy(li, 1, po - 1));
    if po < len then
      work(copy(mi, po + 1, len - po), copy(li, po, len - po));
  end;

begin
  readln(mid);
  readln(last);
  work(mid, last);
  writeln;
  readln;
end.

