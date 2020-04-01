procedure IniciaCampo;
begin
   cleardevice;
   setcolor(12);
   rectangle(20,17,620,462);
   rectangle(19,18,621,463);
   rectangle(410,2,600,15);
   setfillstyle(6,4);
   floodfill(320,10,12);
   setcolor(7); outtextxy(415,5,'Puntos:');
   outtextxy(520,5,'Nivel:');
   for c := 1 to 30 do begin
      ColaX[c] := 0; ColaY[c] := 0; end;
   setcolor(14);
   rectangle(106,68, 114,76); ColaX[3] := 8; ColaY[3] := 5;
   rectangle(118,68, 126,76); ColaX[2] := 9; ColaY[2] := 5;
   rectangle(130,68, 138,76); ColaX[1] := 10; ColaY[1] := 5;
   IncrmX := 1; IncrmY := 0; PosX := 11; PosY := 5; NumArray := 3;
   BolaX := 15; BolaY := 15; TipoMov := 'D'; basta := false;
   PtosTot := 0; PtosPar := 0; mejora := false;
end;