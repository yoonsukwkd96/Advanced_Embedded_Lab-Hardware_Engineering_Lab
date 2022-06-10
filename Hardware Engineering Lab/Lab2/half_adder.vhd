library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity half_adder is 
	port(bit1 : in std_logic;
	     bit2 : in std_logic;
	     S : out std_logic;	-- sum
	     C : out std_logic); -- carry
end half_adder;

architecture halfAdderLogic of half_adder is
begin 
	S <= bit1 xor bit2;
	C <= bit1 and bit2;
end halfAdderLogic;