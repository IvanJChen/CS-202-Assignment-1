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
int pad(std::string &str, int len) {
   int n = static_cast<int>(str.length());
   return len + std::abs(len - n);
}

/// This function dumps the list of symbols and their corresponding
/// memory addresses to the console.
/// \param labels an array of Symbol objects that contain the symbol
/// names and their memory addresses.
/// \param count the number of symbols in the \c labels array to process.
void dumpSymbols(Symbol labels[], int count) {
   std::cout << "Symbols" << std::endl;
   int padding = 0;
   for (int i = 0; i < count; ++i) {
      padding = pad(labels[i].name, MAX_CHARS);
      std::cout << "> " << "[" << labels[i].name << "] = "
                << labels[i].mem << std::endl;
   }
}

/// This function dumps the contents of an integer array (memory) to
/// the console in a formatted way.
/// \param memory an array of integers representing memory contents to
/// be printed.
/// \param count the number of elements in the \c memory array to process.
void dumpMemory(int memory[], int count) {
   std::cout << "Memory" << std::endl;
   std::cout.fill('0');
   for (int i = 0; i < count; ++i)
      std::cout << std::setw(8) << memory[i] << std::endl;
}

/// This function dumps a list of opcodes, printing each opcode's name
/// and associated code  in a formatted manner. The name is padded with
/// spaces to align the output.
/// \param opcodes an array of Opcode structures containing the opcode
/// names and codes.
/// \param count the number of opcodes in the array to be printed.
void dumpOpcodes(Opcode opcodes[], int count) {
   std::cout << "Opcodes" << std::endl;
   int padding = 0;
   for (int i = 0; i < count; ++i) {
      padding = pad(opcodes[i].name, MAX_CHARS);
      std::cout << "> " << opcodes[i].name
                << std::string(padding, ' ')
                << opcodes[i].code
                << std::endl;
   }
}

int main(int argc, char **argv) {

   // <---
   // YOUR CODE GOES HERE
   // check command-line arguments

   // create the table of opcodes
   // parse the list of opcodes
   // HINT: use the function breakOpcodes here!

   //
   //--------------------------------------------
   // PASS #1
   //
   // (1) Removing comments
   // (2) Remember labels
   // (3) Save instruction/opcode and address
   // (4) Write generated code to an output file
   //

   //
   // --------------------------------------------
   //
   // PASS #2
   //
   // (1) Read output file
   // (2) Replace numeric values and pack them into "words"
   //

   //
   // --------------------------------------------
   //
   // EXECUTION
   //
   // (1) Execute instructions in sequential order
   //
   // -->
   std::cout << "** Program terminated **" << std::endl;
   return EXIT_SUCCESS;
}