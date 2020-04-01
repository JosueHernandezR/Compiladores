
;; Function main (main, funcdef_no=0, decl_uid=2248, cgraph_uid=0, symbol_order=0)

main ()
{
  int i;
  int D.2255;

  printf ("Hola mundo");
  i = 0;
  goto <D.2252>;
  <D.2251>:
  __builtin_puts (&"Soy un for"[0]);
  i = i + 1;
  <D.2252>:
  if (i <= 9) goto <D.2251>; else goto <D.2253>;
  <D.2253>:
  D.2255 = 0;
  goto <D.2256>;
  D.2255 = 0;
  goto <D.2256>;
  <D.2256>:
  return D.2255;
}


