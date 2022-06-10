library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity full_adder_tb is 
end full_adder_tb;

architecture tbLogic of full_adder_tb is 
	signal tb_bit1 : std_logic := '0';
	signal tb_bit2 : std_logic := '0';
	signal tb_cin : std_logic := '0';
	signal tb_S : std_logic;
	signal tb_C : std_logic;
begin

	DUT : entity work.full_adder
		port map(bit1 => tb_bit1,
			 bit2 => tb_bit2,
			 cin  => tb_cin,
			 S => tb_S,
			 C => tb_C);
	process is 
	begin
		tb_bit1 <= '0';
		tb_bit2 <= '0';
		tb_cin  <= '0';
		wait for 10 ns;
		tb_bit1 <= '0';
		tb_bit2 <= '1';
		tb_cin  <= '0';
		wait for 10 ns;
		tb_bit1 <= '1';
		tb_bit2 <= '0';
		tb_cin  <= '0';
		wait for 10 ns;
		tb_bit1 <= '1';
		tb_bit2 <= '1';
		tb_cin  <= '0';
		wait for 10 ns;

		tb_bit1 <= '1';
		tb_bit2 <= '1';
		tb_cin  <= '1';
		wait for 10 ns;
		tb_bit1 <= '1';
		tb_bit2 <= '0';
		tb_cin  <= '1';
		wait for 10 ns;
		tb_bit1 <= '0';
		tb_bit2 <= '1';
		tb_cin  <= '1';
		wait for 10 ns;
		tb_bit1 <= '0';
		tb_bit2 <= '0';
		tb_cin  <= '1';
		wait for 10 ns;
	end process;
end tbLogic;
