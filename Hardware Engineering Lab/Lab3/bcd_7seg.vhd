library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity bcd_7seg is 
	port(A, B, C, D : in STD_LOGIC;
	     ao, bo, co, do, eo, fo, go : out STD_LOGIC);
end bcd_7seg;

architecture bcd_7segLogic of bcd_7seg is 
begin
ao <= (A and not B and not C)or(not A and B and D)or(A and not D)or(not A and C)or(B and C)or(not B and not D);
bo <= (not A and not C and not D)or(not A and C and D)or(A and not C and D)or(not B and not C)or(not B and not D);
co <= (not A and not C)or(not A and D)or(not C and D)or(not A and B)or(A and not B);
do <= (not A and not B and not C)or(not B and C and D)or(B and not C and D)or(B and C and not D)or(A and not C);
eo <= (not B and not D)or(C and not D)or(A and C)or(A and B);
fo <= (not A and B and not C)or(not C and not D)or(B and not D)or(A and not B)or(A and C);
go <= (not A and B and not C)or(not B and C)or(C and not D)or(A and not B)or(A and D);
end bcd_7segLogic; 