program P1647;

const
  MaxN   = 50000 + 5;
  MINNUM = -1000000000;
type
  TLine = record
    l, r: longint;
    tmax, lmax, rmax, sum: longint;
    a, b: longint;
  end;

  TSegTree = array[0..200005] of TLine;
var
  tree: TSegTree;
  a:    array[1..MaxN] of longint;
  N, M: longint;

  function max(const a, b: longint): longint;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  function max(const arr: array of longint): longint;
  var
    i:   longint;
    ans: longint;
  begin
    ans := -maxlongint;
    for i := 0 to length(arr) - 1 do
      if arr[i] > ans then
        ans := arr[i];
    exit(ans);
  end;

  {PIT SECTION}

  procedure maintain(const v: longint);
  begin
    tree[v].sum  := tree[v shl 1].sum + tree[(v shl 1) + 1].sum;
    tree[v].lmax := max(tree[v shl 1].lmax, tree[v shl 1].sum +
      tree[(v shl 1) + 1].lmax);
    tree[v].rmax := max(tree[(v shl 1) + 1].rmax, tree[(v shl 1) + 1].sum +
      tree[v shl 1].rmax);
    tree[v].tmax := max([{tree[v].lmax, tree[v].rmax,}  //Ignore ?
      tree[v shl 1].rmax + tree[(v shl 1) + 1].lmax, tree[v shl 1].tmax,
      tree[(v shl 1) + 1].tmax]);
  end;

  procedure build(const v, l, r: longint);
  begin
    tree[v].l := l;
    tree[v].r := r;
    if l < r then
    begin
      build(v shl 1, l, (l + r) shr 1);
      build((v shl 1) + 1, ((l + r) shr 1) + 1, r);
      maintain(v);
    end
    else
    begin
      tree[v].sum  := a[l];
      tree[v].lmax := a[l];
      tree[v].rmax := a[l];
      tree[v].tmax := a[l];
    end;
  end;

  procedure modify(const now, tar, Value: longint);
  var
    mid: longint;
  begin
    if (tree[now].l = tar) and (tree[now].r = tar) then
    begin
      tree[now].sum  := Value;
      tree[now].lmax := Value;
      tree[now].rmax := Value;
      tree[now].tmax := Value;
      exit;
    end;
    mid := (tree[now].l + tree[now].r) shr 1;
    if tar <= mid then
      modify(now shl 1, tar, Value)
    else
      modify((now shl 1) + 1, tar, Value);
    maintain(now);
  end;

type
  TReturn = record
    sum, tmax, lmax, rmax: longint;
  end;

  function reqmaxsum(const v, l, r: longint): TReturn;
  var
    ou, aa, bb: TReturn;
    mid: longint;
  begin
    if (l <= tree[v].l) and (tree[v].r <= r) then
    begin
      with ou do
      begin
        sum  := tree[v].sum;
        tmax := tree[v].tmax;
        lmax := tree[v].lmax;
        rmax := tree[v].rmax;
      end;
      exit(ou);
    end;
    mid := (tree[v].l + tree[v].r) shr 1;
    with aa do
    begin
      sum  := 0;
      tmax := MINNUM;
      lmax := MINNUM;
      rmax := MINNUM;
    end;

    with bb do
    begin
      sum  := 0;
      tmax := MINNUM;
      lmax := MINNUM;
      rmax := MINNUM;
    end;

    if (l <= mid) then
      aa := reqmaxsum(v shl 1, l, r);
    if (r > mid) then
      bb := reqmaxsum((v shl 1) + 1, l, r);

    ou.sum  := aa.sum + bb.sum;
    ou.lmax := max(aa.lmax, aa.sum + bb.lmax);
    ou.rmax := max(bb.rmax, bb.sum + aa.rmax);
    ou.tmax := max([ //Ignore ?
      aa.rmax + bb.lmax, aa.tmax, bb.tmax]);

    exit(ou);
  end;

  {MAIN SECTION}

  procedure main;
  var
    i, com, x, y: longint;
  begin
    readln(N);
    for i := 1 to N do
      Read(a[i]);
    readln;
    build(1, 1, N);
    readln(M);
    for i := 1 to M do
    begin
      readln(com, x, y);
      case com of
        0: modify(1, x, y);
        1: writeln(reqmaxsum(1, x, y).tmax);
      end;
    end;
  end;

var
  aa, bb: longint;
  res:    TReturn;
begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'p1647.in');
  Assign(output, 'p1647.out');
  reset(input);
  rewrite(output);
  {$ENDIF}
  main;
  readln;
end.

