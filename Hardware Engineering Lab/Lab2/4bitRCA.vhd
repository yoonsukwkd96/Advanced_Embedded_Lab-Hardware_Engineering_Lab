library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity four_bitRCA is 
	port(A1 : in std_logic;
	     B1 : in std_logic;
	     A2 : in std_logic;
	     B2 : in std_logic;
	     A3 : in std_logic;
	     B3 : in std_logic;
	     A4 : in std_logic;
	     B4 : in std_logic;
	     cin : in std_logic;
	     S1 : out std_logic; -- sum
	     S2 : out std_logic;
	     S3 : out std_logic;
	     S4 : out std_logic;
	     C : out std_logic); -- carry
end four_bitRCA;

architecture four_bitRCALogic of four_bitRCA is
component full_adder is
port(bit1 : in std_logic;
     bit2 : in std_logic;
     Cin : in std_logic;
     S : out std_logic;	-- sum
     C : out std_logic); -- carry
end component;

signal C1, C2, C3 : std_logic;

begin 
FA1: full_adder
	port map (A1, B1, Cin, S1, C1);
FA2: full_adder 
	port map (A2, B2, C1, S2, C2);
FA3: full_adder
	port map (A3, B3, C2, S3, C3);
FA4: full_adder 
	port map (A4, B4, C3, S4, C);
end four_bitRCALogic;
