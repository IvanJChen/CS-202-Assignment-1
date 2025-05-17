/*
    Name: Ivan, Chen, 2002584402, CS 202, Assignment 1
    Description: Translating a Parrot Program
    Input: Parrot code test files
    Output: Reads through the commands in the output fike
    then executes the Parrot Program
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

/// Set to \c true for debugging.
#define CS202_DEBUG  false
/// Used to break a long string.
#define MULTI_LINE_STRING(a) #a

// Global constant variables
/// Default number of labels
const int LABEL_LEN = 100;
/// Default number of opcodes
const int OPCODE_LEN = 18;
/// Maximum number of characters allowed.
const int MAX_CHARS = 5;
/// Default size of array.
const int ARRAY_LEN = 1000;
/// List of opcodes needed for interpretation.
const char *OPCODE_LIST = MULTI_LINE_STRING(
       final
       read
       write
       load
       set
       plus
       minus
       times
       divide
       compare
       js
       jz
       j
       jl
       jle
       jg
       jge
       skip
);

/// <--
// YOUR CODE GOES HERE
// Write your structs here!!
/// -->
struct Symbol {
    std::string name;
    int mem;
};

struct Opcode {
    std::string name;
    int code;
};
/// This function splits a string of instructions into individual
/// words and code components, storing the results in \c opcodes.
/// \param inst a string of instructions.
/// \param opcodes an empty array of instructions.
/// \return void.
void breakOpcodes(std::string inst, Opcode opcodes[]) {
   int code = 0;
   std::string word = "";
   for (int i = 0; i < inst.length(); ++i)
      if (inst[i] == ' ') {
         opcodes[code] = {word, code};
         ++code;
         word = "";
      } else {
         word += inst[i];
      }
   opcodes[code] = {word, code};
}

/// This function checks if a given word matches any of the valid
/// opcodes in the opcodes array.
/// \param word the instruction to search for.
/// \param opcodes an array of instructions.
/// \return true if \c word is found in the array of \c opcodes.
bool isOpcode(std::string &word, Opcode opcodes[]) {
   for (int i = 0; i < OPCODE_LEN; ++i)
      if (opcodes[i].name == word)
         return true;
   return false;
}

/// This function retrieves the index of the opcode corresponding to
/// the given word.
/// \param word the instruction whose mnemonic value we need to search.
/// \param opcodes an array of instructions.
/// \return the mnemonic value or \c -1 if none is found.
int getOpcode(std::string &word, Opcode opcodes[]) {
   for (int i = 0; i < OPCODE_LEN; ++i)
      if (opcodes[i].name == word)
         return i;
   return -1;
}

/// This function retrieves the memory location associated with a
/// given symbol name.
/// \param name the name to search for.
/// \param labels an array of labels.
/// \param nextLabel the current label's location.
/// \return the location to \c jump to or \c -1.
int getLocation(std::string &name, Symbol labels[], int nextLabel) {
   for (int i = 0; i < nextLabel; ++i)
      if (labels[i].name == name)
         return labels[i].mem;
   return -1;
}

/// This function checks if a given string represents a valid number
/// (consists of only digits). It iterates through each character
/// in the string and returns false if any character is not a digit.
/// If all characters are digits, it returns true. This function
/// assumes that the input string is non-empty and does not handle
/// negative signs, decimals, or other number formats.
bool isNumber(std::string &str) {
   for (int i = 0; i < str.length(); ++i)
      if (!std::isdigit(str[i]))
         return false;
   return true;
}

/// This function calculates the padding length needed to achieve
/// a target string length.  It returns the total padding required
/// by comparing the current string length with the desired length
/// (len).  If the current string length (n) is less than len, the
/// function returns the difference (len - n). If the current string
/// length is greater than or equal to len, it returns the total
/// length (len + abs(len - n)),  ensuring the result is always at
/// least as large as the target length.
// int pad(std::string &str, int len) {
//    int n = static_cast<int>(str.length());
//    return len + std::abs(len - n);
// }

/// This function dumps the list of symbols and their corresponding
/// memory addresses to the console.
/// \param labels an array of Symbol objects that contain the symbol
/// names and their memory addresses.
/// \param count the number of symbols in the \c labels array to process.
// void dumpSymbols(Symbol labels[], int count) {
//    std::cout << "Symbols" << std::endl;
//     int padding = 0;
//    for (int i = 0; i < count; ++i) {
//       padding = pad(labels[i].name, MAX_CHARS);
//       std::cout << "> " << "[" << labels[i].name << "] = "
//                 << labels[i].mem << std::endl;
//    }
// }

/// This function dumps the contents of an integer array (memory) to
/// the console in a formatted way.
/// \param memory an array of integers representing memory contents to
/// be printed.
/// \param count the number of elements in the \c memory array to process
// void dumpMemory(int memory[], int count) {
//    std::cout << "Memory" << std::endl;
//    std::cout.fill('0');
//    for (int i = 0; i < count; ++i)
//       std::cout << std::setw(8) << memory[i] << std::endl;
// }

/// This function dumps a list of opcodes, printing each opcode's name
/// and associated code  in a formatted manner. The name is padded with
/// spaces to align the output.
/// \param opcodes an array of Opcode structures containing the opcode
/// names and codes.
/// \param count the number of opcodes in the array to be printed.
// void dumpOpcodes(Opcode opcodes[], int count) {
//    std::cout << "Opcodes" << std::endl;
//    int padding = 0;
//    for (int i = 0; i < count; ++i) {
//       padding = pad(opcodes[i].name, MAX_CHARS);
//       std::cout << "> " << opcodes[i].name
//                 << std::string(padding, ' ')
//                 << opcodes[i].code
//                 << std::endl;
//    }
// }

int main(int argc, char **argv) {

   // <---
   // YOUR CODE GOES HERE
   // check command-line arguments
   //Checks the # of arguments in command line
   if (argc <2){
      std::cout << "ERROR: invalid number of command-line arguments!";
      std::cout << "\n";
      std::cout << "Terminating program...";
      return 0;   
   }
   //Checks if the ifstream is open/good
   std::ifstream input(argv[1]);
   if (!input.good()) {
      //Similar to .open
      return 0;
   }

   // create the table of opcodes
   // parse the list of opcodes
   // HINT: use the function breakOpcodes here!
   Opcode opcodes[OPCODE_LEN];
   breakOpcodes(OPCODE_LIST, opcodes);
   //
   //--------------------------------------------
   // PASS #1
   //
   //Variables for removing comments
   Symbol symbols[LABEL_LEN];
   int memory[ARRAY_LEN] = {0};
   int nextSymbol = 0;
   int nextMemory = 0;
   int lineVal = 0;
   
   std::string line, currentLabel;
   std::ofstream output("output");
   // (1) Removing comments
   while (getline(input, line)) {
      //Removes the comment after ";"
      int index = line.find(";");
      if (line.empty() || line[0] == ';') {
         continue;  
      }
      if (index != -1) {
         line = line.substr(0, index);
      }
      std::istringstream iss(line);
      std::string temp, instruct, operand;
      iss >> temp;
   // (2) Remember labels
   // (3) Save instruct/opcode and address
   // This code here keeps the opcodes and removes the #
      if (!isOpcode(temp, opcodes)) {
            iss >> instruct >> operand;
         if (temp.find("#") == 0) { 
         // handles label first with #
            symbols[nextSymbol].name = temp.substr(1);
            symbols[nextSymbol].mem = lineVal;
            output << instruct << " " << operand;
            output << "\n";
            nextSymbol++;
         //If the word next to the opcode is final its valid
         }  else if(instruct !="final"){
            //Flags unknown opcode
            std::cout<<"ERROR: Unknown opcode '"<< temp <<"'.\n";
            return 0;
         } else{
         // handles labels first without #
            symbols[nextSymbol].name = temp;
            symbols[nextSymbol].mem = lineVal;
            nextSymbol++;
            output << instruct << " " << operand << std::endl;
         }
      } else {
         iss >> instruct;
         //Outputs everything after removing comments
         if (instruct[0] == '#') {
            instruct = instruct.substr(1);
            output << temp << " " << instruct << "\n";
         } else if (instruct == "") {
            output << temp << " " << std::endl;
         } else if (instruct != "") {
            output << temp << " " << instruct << "\n";
         }
      }  
      lineVal++;
   }
   output.close();
   input.close();
   // --------------------------------------------
   // PASS #2
   // (1) Read output file
   // (2) Replace numeric values and pack them into "words"
   //
   std::ifstream readFile("output");
   if (!readFile.good()) {
      return 0;
   }
   //Variables to parse
   int instructionPointer = 0, word = 0;
   std::string instr, operand, tempLine;
   //Parsing the output file
   while (getline(readFile, tempLine)) {
      std::stringstream ss(tempLine);
      ss >> instr;
      int opcodeValue = getOpcode(instr, opcodes);
      int operandValue = 0;
      if (ss >> operand) { 
         operandValue = getLocation(operand, symbols, nextSymbol);
         if (instr == "final"){
            operandValue = stoi(operand);
         }
         //Flagf the operation/label is invalid 
         else if   (operandValue == -1) {  
            std::cout<<"ERROR: Unknown Label '" << operand<<"'.\n";
            //Stops code if there is an error
            return 0;
         }
      }
      //Equation from assignment
      memory[nextMemory++] = ARRAY_LEN * opcodeValue + operandValue;
   }
   readFile.close();
   // dumpMemory(memory, nextMemory);
   //
   // --------------------------------------------
   //
   // EXECUTION
   //
   // (1) Execute instructions in sequential order
   //
   // -->
   // dumpSymbols(symbols, nextSymbol);
   // dumpMemory(memory, nextMemory);
   int r = 0;
   int operationcode = 0;
   int address = 0;
   std:: cout<<"Running Program...\n";
   while (instructionPointer < nextMemory) {
      //code for opcode value
      operationcode = memory[instructionPointer]/1000;
      //code for label address
      address = memory[instructionPointer]%1000;
      //Switch case for different inputs
      switch (operationcode) {
         case 1: // Read input
            std::cin >> r;
            //checks for valid inputs
            if (std::cin.fail()) {
               std::cout << "ERROR: invalid input!" << std::endl;
               std::cout << "Terminating program..." << std::endl;
               return 0;
            }
            std::cout << "read: " << r << std::endl; break;
         case 2:
            //write 
            std::cout << "result: " << r << std::endl; break;
         case 3:
            //load
            r = memory[address]; break;
         case 4:
            //set
            memory[address] = r; break;
         case 5:
            //plus
            r += memory[address]; break;
         case 6:
            //minus
            r -= memory[address]; break;
         case 7:
            //times
            r *= memory[address]; break;
         case 8:
            //divide
            r /= memory[address]; break;
         case 9:
            //compare
            r -= memory[address]; break;
         case 10:
            //js - jump if r is positive
            if (r > 0) {
               instructionPointer = address-1;
            }
            break;
         case 11:
            //jz - jumps if r is zero
            if (r == 0) {
               instructionPointer = address-1; 
            }
            break;
         case 12:
            //j - jumps uncoditionally
            instructionPointer = address-1; break;
         case 13:
            //jl - jumps if r is less than zero
            if (r < 0) {
               instructionPointer = address-1;
            }
            break;
         case 14:
            //jle - jumps if r is less than or equal to zero
            if (r <= 0) {
               instructionPointer = address-1;
            }
            break;
         case 15:
            //jg jumps if r is greater than zero
            if (r > 0) {
               instructionPointer = address-1;
            }
            break;
         case 16:
            //jge - jumps if greater or equal to zero
            if (r >= 0) {
               instructionPointer = address-1;
            }
            break;
         case 17:
            //skip - terminates program execution
            instructionPointer = nextMemory-1; break;
      }
      //updates the instruction pointer
      instructionPointer++;
   }
   //signals the end of the program
   std::cout << "** Program terminated **" << std::endl;
   return EXIT_SUCCESS;
}