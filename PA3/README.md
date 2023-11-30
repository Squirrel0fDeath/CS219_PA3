# How to Run
Utilizing the terminal, open the folder directory in your computers terminal.
Run the 'make' command in the terminal while still inside the folder's directory location.
Run the newly created 'main.exe' file by typing './main' into the terminal.

# Operation Process
The program reads the 'Programming-Project-2.txt' file, one line at a time. The 'Programming-Project-1.txt' file is provided in the .zip file submitted. If it is not present in current directory, the file program will not show any results, but will provide the option to close the program.
For each read line, the program checks if the first 3 characters of the provided line is equal to a given Assembly command.
Since we are only looking for the 'ADD' command, this is currently the only command it looks for.

The program then searches for the first instance of '0x', indicating the beginning of the first hex number provided as a parameter.
Once the first hex number is found, all previous characters are removed from the line initially taken from the file.
The remaining string, minus the Assembly command, is saved to a string variable, removing all whitespace from the remaining string.

Next, the first two characters are removed from the string, '0x'.
A second string is initialized, using the next found position of '0x' to find the second hex number.
The length of the second string is used to remove the second hex number from the first hex number string. 
Next, the second string has it's '0x' removed, leaving the two string variables remaining only containing convertable hex values.
If the instruction is 'NOT', it skips over the operation maniuplating the second hex number.
If the second operand is not a hex number, it does not require further manipulation, stoi() is used.

The operands are then converted into bitset<32> variables to allow for easy program manipulation. 

It converts the bitset<32> variables into hex via manually substring manuplation.

It then provides the original instruction, result, and set flags to the output file located within the folder.

The program uses a templated instruction class file to determine what operations it needs to perform. The instruction operations are private, and cannot be directly called. All it needs is the instruction OPCODE, and two parameters. The provided OPCODE is read by the class' "read_instruction" method to call its private instruction methods as needed.

# Result
Result output shows the line feed to the program on the first line.
The second line shows the result of the operation.
The third line is a true or false for if the operation caused overflow.

The next result is separated by whitespace before repeating until the program finishes reading the entire file.
Results shown are correct. The results for NCZV flags are probably correct.

