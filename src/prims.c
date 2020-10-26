/*
    module  : prims.c
    version : 1.2
    date    : 10/26/20
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "data.h"
#include "chars.h"
#include "ident.h"
#include "symbol.h"
#include "print.h"
#include "lookup.h"
#include "prims.h"

#define MAX_LIT		10
#define MAX_WRD		(stop_ - mul_ + 1)

enum {
    LITERAL,
    OPERAND,
    OPERATOR,
    PREDICATE,
    COMBINATOR,
    MISCELLANEOUS
};

static int init = 0;

static struct opcode {
    char *name;
    int type, line;
    char *msg1, *msg2;
} literal1[MAX_LIT], wordlist[MAX_WRD];

static void elit(char *name, int type, int line, char *msg1, char *msg2)
{
    int i = line;

    assert(i < MAX_LIT);
    literal1[i].name = name;
    literal1[i].type = type;
    literal1[i].line = line;
    literal1[i].msg1 = msg1;
    literal1[i].msg2 = msg2;
}

static void ewrd(char *name, int type, int line, char *msg1, char *msg2)
{
    int i = line - mul_;

    assert(i < MAX_WRD);
    wordlist[i].name = name;
    wordlist[i].type = type;
    wordlist[i].line = line;
    wordlist[i].msg1 = msg1;
    wordlist[i].msg2 = msg2;
}

static void initprims()
{
    elit(" truth value type", LITERAL, typ_logical, "->  B", "The logical type, or the type of truth values.\nIt has just two literals: true and false.");
    elit(" character type", LITERAL, typ_char, "->  C", "The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed.");
    elit(" integer type", LITERAL, typ_integer, "->  I", "The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42.");
    elit(" set type", LITERAL, typ_set, "->  {...}", "The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}.");
    elit(" string type", LITERAL, typ_string, "->  \"...\"", "The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted.");
    elit(" list type", LITERAL, typ_list, "->  [...]", "The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *].");
    elit(" float type", LITERAL, typ_float, "->  F", "The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2).");
    elit(" file type", LITERAL, typ_file, "->  FILE:", "The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr.");

    ewrd("false", OPERAND, false_, "->  false", "Pushes the value false.");
    ewrd("true", OPERAND, true_, "->  true", "Pushes the value true.");
    ewrd("maxint", OPERAND, maxint_, "->  maxint", "Pushes largest integer (platform dependent). Typically it is 32 bits.");
    ewrd("setsize", OPERAND, setsize_, "->  setsize", "Pushes the maximum number of elements in a set (platform dependent).\nTypically it is 32, and set members are in the range 0..31.");
    ewrd("stack", OPERAND, stack_, ".. X Y Z  ->  .. X Y Z [Z Y X ..]", "Pushes the stack as a list.");
    ewrd("__symtabmax", OPERAND, __symtabmax_, "->", "Pushes value of maximum size of the symbol table.");
    ewrd("__symtabindex", OPERAND, __symtabindex_, "->", "Pushes current size of the symbol table.");
    ewrd("__dump", OPERAND, __dump_, "->", "debugging only: pushes the dump as a list.");
    ewrd("conts", OPERAND, conts_, "->  [[P] [Q] ..]", "Pushes current continuations. Buggy, do not use.");
    ewrd("autoput", OPERAND, autoput_, "->  I", "Pushes current value of flag for automatic output, I = 0..2.");
    ewrd("undeferror", OPERAND, undeferror_, "->  I", "Pushes current value of undefined-is-error flag.");
    ewrd("undefs", OPERAND, undefs_, "->", "Push a list of all undefined symbols in the current symbol table.");
    ewrd("echo", OPERAND, echo_, "->  I", "Pushes value of echo flag, I = 0..3.");
    ewrd("clock", OPERAND, clock_, "->  I", "Pushes the integer value of current CPU usage in hundreds of a second.");
    ewrd("time", OPERAND, time_, "->  I", "Pushes the current time (in seconds since the Epoch).");
    ewrd("rand", OPERAND, rand_, "->  I", "I is a random integer.");
    ewrd("__memorymax", OPERAND, __memorymax_, "->", "Pushes value of total size of memory.");
    ewrd("stdin", OPERAND, stdin_, "->  S", "Pushes the standard input stream.");
    ewrd("stdout", OPERAND, stdout_, "->  S", "Pushes the standard output stream.");
    ewrd("stderr", OPERAND, stderr_, "->  S", "Pushes the standard error stream.");
    ewrd("id", OPERATOR, id_, "->", "Identity function, does nothing.\nAny program of the form  P id Q  is equivalent to just  P Q.");
    ewrd("dup", OPERATOR, dup_, "X  ->  X X", "Pushes an extra copy of X onto stack.");
    ewrd("swap", OPERATOR, swap_, "X Y  ->  Y X", "Interchanges X and Y on top of the stack.");
    ewrd("rollup", OPERATOR, rollup_, "X Y Z  ->  Z X Y", "Moves X and Y up, moves Z down.");
    ewrd("rolldown", OPERATOR, rolldown_, "X Y Z  ->  Y Z X", "Moves Y and Z down, moves X up.");
    ewrd("rotate", OPERATOR, rotate_, "X Y Z  ->  Z Y X", "Interchanges X and Z.");
    ewrd("popd", OPERATOR, popd_, "Y Z  ->  Z", "As if defined by:   popd  ==  [pop] dip");
    ewrd("dupd", OPERATOR, dupd_, "Y Z  ->  Y Y Z", "As if defined by:   dupd  ==  [dup] dip");
    ewrd("swapd", OPERATOR, swapd_, "X Y Z  ->  Y X Z", "As if defined by:   swapd  ==  [swap] dip");
    ewrd("rollupd", OPERATOR, rollupd_, "X Y Z W  ->  Z X Y W", "As if defined by:   rollupd  ==  [rollup] dip");
    ewrd("rolldownd", OPERATOR, rolldownd_, "X Y Z W  ->  Y Z X W", "As if defined by:   rolldownd  ==  [rolldown] dip");
    ewrd("rotated", OPERATOR, rotated_, "X Y Z W  ->  Z Y X W", "As if defined by:   rotated  ==  [rotate] dip");
    ewrd("pop", OPERATOR, pop_, "X  ->", "Removes X from top of the stack.");
    ewrd("choice", OPERATOR, choice_, "B T F  ->  X", "If B is true, then X = T else X = F.");
    ewrd("or", OPERATOR, or_, "X Y  ->  Z", "Z is the union of sets X and Y, logical disjunction for truth values.");
    ewrd("xor", OPERATOR, xor_, "X Y  ->  Z", "Z is the symmetric difference of sets X and Y,\nlogical exclusive disjunction for truth values.");
    ewrd("and", OPERATOR, and_, "X Y  ->  Z", "Z is the intersection of sets X and Y, logical conjunction for truth values.");
    ewrd("not", OPERATOR, not_, "X  ->  Y", "Y is the complement of set X, logical negation for truth values.");
    ewrd("+", OPERATOR, add_, "M I  ->  N", "Numeric N is the result of adding integer I to numeric M.\nAlso supports float.");
    ewrd("-", OPERATOR, sub_, "M I  ->  N", "Numeric N is the result of subtracting integer I from numeric M.\nAlso supports float.");
    ewrd("*", OPERATOR, mul_, "I J  ->  K", "Integer K is the product of integers I and J.  Also supports float.");
    ewrd("/", OPERATOR, divide_, "I J  ->  K", "Integer K is the (rounded) ratio of integers I and J.  Also supports float.");
    ewrd("rem", OPERATOR, rem_, "I J  ->  K", "Integer K is the remainder of dividing I by J.  Also supports float.");
    ewrd("mod", OPERATOR, rem_, "I J  ->  K", "Integer K is the remainder of dividing I by J.  Also supports float.\nSame as rem.");
    ewrd("div", OPERATOR, div_, "I J  ->  K L", "Integers K and L are the quotient and remainder of dividing I by J.");
    ewrd("sign", OPERATOR, sign_, "N1  ->  N2", "Integer N2 is the sign (-1 or 0 or +1) of integer N1,\nor float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.");
    ewrd("neg", OPERATOR, neg_, "I  ->  J", "Integer J is the negative of integer I.  Also supports float.");
    ewrd("ord", OPERATOR, ord_, "C  ->  I", "Integer I is the Ascii value of character C (or logical or integer).");
    ewrd("chr", OPERATOR, chr_, "I  ->  C", "C is the character whose Ascii value is integer I (or logical or character).");
    ewrd("abs", OPERATOR, abs_, "N1  ->  N2", "Integer N2 is the absolute value (0, 1, 2..) of integer N1,\nor float N2 is the absolute value (0.0 ..) of float N1.");
    ewrd("acos", OPERATOR, acos_, "F  ->  G", "G is the arc cosine of F.");
    ewrd("asin", OPERATOR, asin_, "F  ->  G", "G is the arc sine of F.");
    ewrd("atan", OPERATOR, atan_, "F  ->  G", "G is the arc tangent of F.");
    ewrd("atan2", OPERATOR, atan2_, "F G  ->  H", "H is the arc tangent of F / G.");
    ewrd("ceil", OPERATOR, ceil_, "F  ->  G", "G is the float ceiling of F.");
    ewrd("cos", OPERATOR, cos_, "F  ->  G", "G is the cosine of F.");
    ewrd("cosh", OPERATOR, cosh_, "F  ->  G", "G is the hyperbolic cosine of F.");
    ewrd("exp", OPERATOR, exp_, "F  ->  G", "G is e (2.718281828...) raised to the Fth power.");
    ewrd("floor", OPERATOR, floor_, "F  ->  G", "G is the floor of F.");
    ewrd("frexp", OPERATOR, frexp_, "F  ->  G I", "G is the mantissa and I is the exponent of F.\nUnless F = 0, 0.5 <= abs(G) < 1.0.");
    ewrd("ldexp", OPERATOR, ldexp_, "F I  ->  G", "G is F times 2 to the Ith power.");
    ewrd("log", OPERATOR, log_, "F  ->  G", "G is the natural logarithm of F.");
    ewrd("log10", OPERATOR, log10_, "F  ->  G", "G is the common logarithm of F.");
    ewrd("modf", OPERATOR, modf_, "F  ->  G H", "G is the fractional part and H is the integer part\n(but expressed as a float) of F.");
    ewrd("pow", OPERATOR, pow_, "F G  ->  H", "H is F raised to the Gth power.");
    ewrd("sin", OPERATOR, sin_, "F  ->  G", "G is the sine of F.");
    ewrd("sinh", OPERATOR, sinh_, "F  ->  G", "G is the hyperbolic sine of F.");
    ewrd("sqrt", OPERATOR, sqrt_, "F  ->  G", "G is the square root of F.");
    ewrd("tan", OPERATOR, tan_, "F  ->  G", "G is the tangent of F.");
    ewrd("tanh", OPERATOR, tanh_, "F  ->  G", "G is the hyperbolic tangent of F.");
    ewrd("trunc", OPERATOR, trunc_, "F  ->  I", "I is an integer equal to the float F truncated toward zero.");
    ewrd("localtime", OPERATOR, localtime_, "I  ->  T", "Converts a time I into a list T representing local time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is a Boolean flagging daylight savings/summer time;\nweekday is 1 = Monday ... 7 = Sunday.");
    ewrd("gmtime", OPERATOR, gmtime_, "I  ->  T", "Converts a time I into a list T representing universal time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is false; weekday is 1 = Monday ... 7 = Sunday.");
    ewrd("mktime", OPERATOR, mktime_, "T  ->  I", "Converts a list T representing local time into a time I.\nT is in the format generated by localtime.");
    ewrd("strftime", OPERATOR, strftime_, "T S1  ->  S2", "Formats a list T in the format of localtime or gmtime\nusing string S1 and pushes the result S2.");
    ewrd("strtod", OPERATOR, strtod_, "S  ->  R", "String S is converted to the float R.");
    ewrd("format", OPERATOR, format_, "N C I J  ->  S", "S is the formatted version of N in mode C\n('d or 'i = decimal, 'o = octal, 'x or\n'X = hex with lower or upper case letters)\nwith maximum width I and minimum width J.");
    ewrd("formatf", OPERATOR, formatf_, "F C I J  ->  S", "S is the formatted version of F in mode C\n('e or 'E = exponential, 'f = fractional,\n'g or G = general with lower or upper case letters)\nwith maximum width I and precision J.");
    ewrd("strtol", OPERATOR, strtol_, "S I  ->  J", "String S is converted to the integer J using base I.\nIf I = 0, assumes base 10,\nbut leading \"0\" means base 8 and leading \"0x\" means base 16.");
    ewrd("srand", OPERATOR, srand_, "I  ->", "Sets the random integer seed to integer I.");
    ewrd("pred", OPERATOR, pred_, "M  ->  N", "Numeric N is the predecessor of numeric M.");
    ewrd("succ", OPERATOR, succ_, "M  ->  N", "Numeric N is the successor of numeric M.");
    ewrd("max", OPERATOR, max_, "N1 N2  ->  N", "N is the maximum of numeric values N1 and N2.  Also supports float.");
    ewrd("min", OPERATOR, min_, "N1 N2  ->  N", "N is the minimum of numeric values N1 and N2.  Also supports float.");
    ewrd("fclose", OPERATOR, fclose_, "S  ->", "Stream S is closed and removed from the stack.");
    ewrd("feof", OPERATOR, feof_, "S  ->  S B", "B is the end-of-file status of stream S.");
    ewrd("ferror", OPERATOR, ferror_, "S  ->  S B", "B is the error status of stream S.");
    ewrd("fflush", OPERATOR, fflush_, "S  ->  S", "Flush stream S, forcing all buffered output to be written.");
    ewrd("fgetch", OPERATOR, fgetch_, "S  ->  S C", "C is the next available character from stream S.");
    ewrd("fgets", OPERATOR, fgets_, "S  ->  S L", "L is the next available line (as a string) from stream S.");
    ewrd("fopen", OPERATOR, fopen_, "P M  ->  S", "The file system object with pathname P is opened with mode M (r,  w,  a,  etc.)\nand stream object S is pushed; if the open fails, file:NULL is pushed.");
    ewrd("fread", OPERATOR, fread_, "S I  ->  L", "I bytes are read from the current position of stream S\nand returned as a list of I integers.");
    ewrd("fwrite", OPERATOR, fwrite_, "S L  ->  S", "A list of integers are written as bytes to the current position of stream S.");
    ewrd("fremove", OPERATOR, fremove_, "P  ->  B", "The file system object with pathname P is removed from the file system.\nB is a boolean indicating success or failure.");
    ewrd("frename", OPERATOR, frename_, "P1 P2  ->  B", "The file system object with pathname P1 is renamed to P2.\nB is a boolean indicating success or failure.");
    ewrd("fput", OPERATOR, fput_, "S X  ->  S", "Writes X to stream S, pops X off stack.");
    ewrd("fputch", OPERATOR, fputch_, "S C  ->  S", "The character C is written to the current position of stream S.");
    ewrd("fputchars", OPERATOR, fputchars_, "S \"abc..\"  ->  S", "The string abc.. (no quotes) is written to the current position of stream S.");
    ewrd("fputstring", OPERATOR, fputstring_, "S \"abc..\"  ->  S", "== fputchars,  as a temporary alternative.");
    ewrd("fseek", OPERATOR, fseek_, "S P W  ->  S B", "Stream S is repositioned to position P relative to whence-point W,\nwhere W = 0,  1,  2 for beginning, current position, end respectively.");
    ewrd("ftell", OPERATOR, ftell_, "S  ->  S I", "I is the current position of stream S.");
    ewrd("unstack", OPERATOR, unstack_, "[X Y ..]  ->  .. Y X", "The list [X Y ..] becomes the new stack.");
    ewrd("cons", OPERATOR, cons_, "X A  ->  B", "Aggregate B is A with a new member X (first member for sequences).");
    ewrd("swons", OPERATOR, swons_, "A X  ->  B", "Aggregate B is A with a new member X (first member for sequences).");
    ewrd("first", OPERATOR, first_, "A  ->  F", "F is the first member of the non-empty aggregate A.");
    ewrd("rest", OPERATOR, rest_, "A  ->  R", "R is the non-empty aggregate A with its first member removed.");
    ewrd("compare", OPERATOR, compare_, "A B  ->  I", "I (=-1, 0, +1) is the comparison of aggregates A and B.\nThe values correspond to the predicates <=, =, >=.");
    ewrd("at", OPERATOR, at_, "A I  ->  X", "X (= A[I]) is the member of A at position I.");
    ewrd("of", OPERATOR, of_, "I A  ->  X", "X (= A[I]) is the I-th member of aggregate A.");
    ewrd("size", OPERATOR, size_, "A  ->  I", "Integer I is the number of elements of aggregate A.");
    ewrd("opcase", OPERATOR, opcase_, "X [..[X Xs]..]  ->  X [Xs]", "Indexing on type of X, returns the list [Xs].");
    ewrd("case", OPERATOR, case_, "X [..[X Y]..]  ->  Y i", "Indexing on the value of X, execute the matching Y.");
    ewrd("uncons", OPERATOR, uncons_, "A  ->  F R", "F and R are the first and the rest of non-empty aggregate A.");
    ewrd("unswons", OPERATOR, unswons_, "A  ->  R F", "R and F are the rest and the first of non-empty aggregate A.");
    ewrd("drop", OPERATOR, drop_, "A N  ->  B", "Aggregate B is the result of deleting the first N elements of A.");
    ewrd("take", OPERATOR, take_, "A N  ->  B", "Aggregate B is the result of retaining just the first N elements of A.");
    ewrd("concat", OPERATOR, concat_, "S T  ->  U", "Sequence U is the concatenation of sequences S and T.");
    ewrd("enconcat", OPERATOR, enconcat_, "X S T  ->  U", "Sequence U is the concatenation of sequences S and T\nwith X inserted between S and T (== swapd cons concat).");
    ewrd("name", OPERATOR, name_, "sym  ->  \"sym\"", "For operators and combinators, the string \"sym\" is the name of item sym,\nfor literals sym the result string is its type.");
    ewrd("intern", OPERATOR, intern_, "\"sym\"  ->  sym", "Pushes the item whose name is \"sym\".");
    ewrd("body", OPERATOR, body_, "U  ->  [P]", "Quotation [P] is the body of user-defined symbol U.");
    ewrd("null", PREDICATE, null_, "X  ->  B", "Tests for 0 aggregate X or zero numeric.");
    ewrd("small", PREDICATE, small_, "X  ->  B", "Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.");
    ewrd(">=", PREDICATE, geq_, "X Y  ->  B", "Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than or equal to Y.  Also supports float.");
    ewrd(">", PREDICATE, gtr_, "X Y  ->  B", "Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than Y.  Also supports float.");
    ewrd("<=", PREDICATE, leq_, "X Y  ->  B", "Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than or equal to Y.  Also supports float.");
    ewrd("<", PREDICATE, lss_, "X Y  ->  B", "Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than Y.  Also supports float.");
    ewrd("!=", PREDICATE, neq_, "X Y  ->  B", "Either both X and Y are numeric or both are strings or symbols.\nTests whether X not equal to Y.  Also supports float.");
    ewrd("=", PREDICATE, eql_, "X Y  ->  B", "Either both X and Y are numeric or both are strings or symbols.\nTests whether X equal to Y.  Also supports float.");
    ewrd("equal", PREDICATE, equal_, "T U  ->  B", "(Recursively) tests whether trees T and U are identical.");
    ewrd("has", PREDICATE, has_, "A X  ->  B", "Tests whether aggregate A has X as a member.");
    ewrd("in", PREDICATE, in_, "X A  ->  B", "Tests whether X is a member of aggregate A.");
    ewrd("integer", PREDICATE, integer_, "X  ->  B", "Tests whether X is an integer.");
    ewrd("char", PREDICATE, char_, "X  ->  B", "Tests whether X is a character.");
    ewrd("logical", PREDICATE, logical_, "X  ->  B", "Tests whether X is a logical.");
    ewrd("set", PREDICATE, set_, "X  ->  B", "Tests whether X is a set.");
    ewrd("string", PREDICATE, string_, "X  ->  B", "Tests whether X is a string.");
    ewrd("leaf", PREDICATE, leaf_, "X  ->  B", "Tests whether X is not a list.");
    ewrd("list", PREDICATE, list_, "X  ->  B", "Tests whether X is a list.");
    ewrd("user", PREDICATE, user_, "X  ->  B", "Tests whether X is a user-defined symbol.");
    ewrd("float", PREDICATE, float_, "R  ->  B", "Tests whether R is a float.");
    ewrd("file", PREDICATE, file_, "F  ->  B", "Tests whether F is a file.");
    ewrd("i", COMBINATOR, i_, "[P]  ->  ...", "Executes P. So,  [P] i  ==  P.");
    ewrd("x", COMBINATOR, x_, "[P] i  ->  ...", "Executes P without popping [P]. So,  [P] x  ==  [P] P.");
    ewrd("dip", COMBINATOR, dip_, "X [P]  ->  ...  X", "Saves X, executes P, pushes X back.");
    ewrd("app1", COMBINATOR, app1_, "X [P]  ->  R", "Executes P, pushes result R on stack with X.");
    ewrd("app11", COMBINATOR, app11_, "X Y [P]  ->  R", "Executes P, pushes result R on stack.");
    ewrd("app12", COMBINATOR, app12_, "X Y1 Y2 [P]  ->  R1 R2", "Executes P twice, with Y1 and Y2, returns R1 and R2.");
    ewrd("construct", COMBINATOR, construct_, "[P] [[P1] [P2] ..]  ->  R1 R2 ..", "Saves state of stack and then executes [P].\nThen executes each [Pi] to give Ri pushed onto saved stack.");
    ewrd("nullary", COMBINATOR, nullary_, "[P]  ->  R", "Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes, none are removed from the stack.");
    ewrd("unary", COMBINATOR, unary_, "X [P]  ->  R", "Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly one is removed from the stack.");
    ewrd("unary2", COMBINATOR, unary2_, "X1 X2 [P]  ->  R1 R2", "Executes P twice, with X1 and X2 on top of the stack.\nReturns the two values R1 and R2.");
    ewrd("unary3", COMBINATOR, unary3_, "X1 X2 X3 [P]  ->  R1 R2 R3", "Executes P three times, with Xi, returns Ri (i = 1..3).");
    ewrd("unary4", COMBINATOR, unary4_, "X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4", "Executes P four times, with Xi, returns Ri (i = 1..4).");
    ewrd("app2", COMBINATOR, app2_, "X1 X2 [P]  ->  R1 R2", "Obsolescent.  == unary2");
    ewrd("app3", COMBINATOR, app3_, "X1 X2 X3 [P]  ->  R1 R2 R3", "Obsolescent.  == unary3");
    ewrd("app4", COMBINATOR, app4_, "X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4", "Obsolescent.  == unary4");
    ewrd("binary", COMBINATOR, binary_, "X Y [P]  ->  R", "Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly two are removed from the stack.");
    ewrd("ternary", COMBINATOR, ternary_, "X Y Z [P]  ->  R", "Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes, \nexactly three are removed from the stack.");
    ewrd("cleave", COMBINATOR, cleave_, "X [P1] [P2]  ->  R1 R2", "Executes P1 and P2, each with X on top, producing two results.");
    ewrd("branch", COMBINATOR, branch_, "B [T] [F]  ->  ...", "If B is true, then executes T else executes F.");
    ewrd("ifte", COMBINATOR, ifte_, "[B] [T] [F]  ->  ...", "Executes B. If that yields true, then executes T else executes F.");
    ewrd("ifinteger", COMBINATOR, ifinteger_, "X [T] [E]  ->  ...", "If X is an integer, executes T else executes E.");
    ewrd("ifchar", COMBINATOR, ifchar_, "X [T] [E]  ->  ...", "If X is a character, executes T else executes E.");
    ewrd("iflogical", COMBINATOR, iflogical_, "X [T] [E]  ->  ...", "If X is a logical or truth value, executes T else executes E.");
    ewrd("ifset", COMBINATOR, ifset_, "X [T] [E]  ->  ...", "If X is a set, executes T else executes E.");
    ewrd("ifstring", COMBINATOR, ifstring_, "X [T] [E]  ->  ...", "If X is a string, executes T else executes E.");
    ewrd("iflist", COMBINATOR, iflist_, "X [T] [E]  ->  ...", "If X is a list, executes T else executes E.");
    ewrd("iffloat", COMBINATOR, iffloat_, "X [T] [E]  ->  ...", "If X is a float, executes T else executes E.");
    ewrd("iffile", COMBINATOR, iffile_, "X [T] [E]  ->  ...", "If X is a file, executes T else executes E.");
    ewrd("cond", COMBINATOR, cond_, "[..[[Bi] Ti]..[D]]  ->  ...", "Tries each Bi. If that yields true, then executes Ti and exits.\nIf no Bi yields true, executes default D.");
    ewrd("while", COMBINATOR, while_, "[B] [D]  ->  ...", "While executing B yields true executes D.");
    ewrd("linrec", COMBINATOR, linrec_, "[P] [T] [R1] [R2]  ->  ...", "Executes P. If that yields true, executes T.\nElse executes R1, recurses, executes R2.");
    ewrd("tailrec", COMBINATOR, tailrec_, "[P] [T] [R1]  ->  ...", "Executes P. If that yields true, executes T.\nElse executes R1, recurses.");
    ewrd("binrec", COMBINATOR, binrec_, "[P] [T] [R1] [R2]  ->  ...", "Executes P. If that yields true, executes T.\nElse uses R1 to produce two intermediates, recurses on both,\nthen executes R2 to combines their results.");
    ewrd("genrec", COMBINATOR, genrec_, "[B] [T] [R1] [R2]  ->  ...", "Executes B, if that yields true, executes T.\nElse executes R1 and then [[[B] [T] [R1] R2] genrec] R2.");
    ewrd("condnestrec", COMBINATOR, condnestrec_, "[ [C1] [C2] .. [D] ]  ->  ...", "A generalisation of condlinrec.\nEach [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form\n[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].\nFor the case taken, executes each [Ri] and recurses between any two\nconsecutive [Ri] (n > 3 would be exceptional).");
    ewrd("condlinrec", COMBINATOR, condlinrec_, "[ [C1] [C2] .. [D] ]  ->  ...", "Each [Ci] is of the form [[B] [T]] or [[B] [R1] [R2]].\nTries each B. If that yields true and there is just a [T], executes T and exit.\nIf there are [R1] and [R2], executes R1, recurses, executes R2.\nSubsequent case are ignored. If no B yields true, then [D] is used.\nIt is then of the form [[T]] or [[R1] [R2]]. For the former, executes T.\nFor the latter executes R1, recurses, executes R2.");
    ewrd("step", COMBINATOR, step_, "A [P]  ->  ...", "Sequentially putting members of aggregate A onto stack,\nexecutes P for each member of A.");
    ewrd("fold", COMBINATOR, fold_, "A V0 [P]  ->  V", "Starting with value V0, sequentially pushes members of aggregate A\nand combines with binary operator P to produce value V.");
    ewrd("map", COMBINATOR, map_, "A [P]  ->  B", "Executes P on each member of aggregate A,\ncollects results in sametype aggregate B.");
    ewrd("times", COMBINATOR, times_, "N [P]  ->  ...", "N times executes P.");
    ewrd("infra", COMBINATOR, infra_, "L1 [P]  ->  L2", "Using list L1 as stack, executes P and returns a new list L2.\nThe first element of L1 is used as the top of stack,\nand after execution of P the top of stack becomes the first element of L2.");
    ewrd("primrec", COMBINATOR, primrec_, "X [I] [C]  ->  R", "Executes I to obtain an initial value R0.\nFor integer X uses increasing positive integers to X, combines by C for new R.\nFor aggregate X uses successive members and combines by C for new R.");
    ewrd("filter", COMBINATOR, filter_, "A [B]  ->  A1", "Uses test B to filter aggregate A producing sametype aggregate A1.");
    ewrd("split", COMBINATOR, split_, "A [B]  ->  A1 A2", "Uses test B to split aggregate A into sametype aggregates A1 and A2.");
    ewrd("some", COMBINATOR, some_, "A [B]  ->  X", "Applies test B to members of aggregate A, X = true if some pass.");
    ewrd("all", COMBINATOR, all_, "A [B]  ->  X", "Applies test B to members of aggregate A, X = true if all pass.");
    ewrd("treestep", COMBINATOR, treestep_, "T [P]  ->  ...", "Recursively traverses leaves of tree T, executes P for each leaf.");
    ewrd("treerec", COMBINATOR, treerec_, "T [O] [C]  ->  ...", "T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.");
    ewrd("treegenrec", COMBINATOR, treegenrec_, "T [O1] [O2] [C]  ->  ...", "T is a tree. If T is a leaf, executes O1.\nElse executes O2 and then [[[O1] [O2] C] treegenrec] C.");
    ewrd("help", MISCELLANEOUS, help_, "->", "Lists all defined symbols, including those from library files.\nThen lists all primitives of raw Joy.\n(There is a variant: \"_help\" which lists hidden symbols).");
    ewrd("_help", MISCELLANEOUS, _help_, "->", "Lists all hidden symbols in library and then all hidden built-in symbols.");
    ewrd("helpdetail", MISCELLANEOUS, helpdetail_, "[ S1 S2 .. ]  ->", "Gives brief help on each symbol S in the list.");
    ewrd("manual", MISCELLANEOUS, manual_, "->", "Writes this manual of all Joy primitives to output file.");
    ewrd("__html_manual", MISCELLANEOUS, __html_manual_, "->", "Writes this manual of all Joy primitives to output file in HTML style.");
    ewrd("__latex_manual", MISCELLANEOUS, __latex_manual_, "->", "Writes this manual of all Joy primitives to output file in Latex style\nbut without the head and tail.");
    ewrd("__manual_list", MISCELLANEOUS, __manual_list_, "->  L", "Pushes a list L of lists (one per operator) of three documentation strings.");
    ewrd("__settracegc", MISCELLANEOUS, __settracegc_, "I  ->", "Sets value of flag for tracing garbage collection to I (= 0..5).");
    ewrd("setautoput", MISCELLANEOUS, setautoput_, "I  ->", "Sets value of flag for automatic put to I (if I = 0, none;\nif I = 1, put; if I = 2, stack).");
    ewrd("setundeferror", MISCELLANEOUS, setundeferror_, "I  ->", "Sets flag that controls behavior of undefined functions\n(0 = no error, 1 = error).");
    ewrd("setecho", MISCELLANEOUS, setecho_, "I  ->", "Sets value of echo flag for listing.\nI = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.");
    ewrd("gc", MISCELLANEOUS, gc_, "->", "Initiates garbage collection.");
    ewrd("system", MISCELLANEOUS, system_, "\"command\"  ->", "Escapes to shell, executes string \"command\".\nThe string may cause execution of another program.\nWhen that has finished, the process returns to Joy.");
    ewrd("getenv", MISCELLANEOUS, getenv_, "\"variable\"  ->  \"value\"", "Retrieves the value of the environment variable \"variable\".");
    ewrd("argv", MISCELLANEOUS, argv_, "->  A", "Creates an aggregate A containing the interpreter's command line arguments.");
    ewrd("argc", MISCELLANEOUS, argc_, "->  I", "Pushes the number of command line arguments. This is quivalent to 'argv size'.");
    ewrd("__memoryindex", MISCELLANEOUS, __memoryindex_, "->", "Pushes current value of memory.");
    ewrd("get", MISCELLANEOUS, get_, "->  F", "Reads a factor from input and pushes it onto stack.");
    ewrd("put", MISCELLANEOUS, put_, "X  ->", "Writes X to output, pops X off stack.");
    ewrd("putch", MISCELLANEOUS, putch_, "N  ->", "N : numeric, writes character whose ASCII is N.");
    ewrd("putchars", MISCELLANEOUS, putchars_, "\"abc..\"  ->", "Writes abc.. (without quotes)");
    ewrd("include", MISCELLANEOUS, include_, "\"filnam.ext\"  ->", "Transfers input to file whose name is \"filnam.ext\".\nOn end-of-file returns to previous input file.");
    ewrd("abort", MISCELLANEOUS, abort_, "->", "Aborts execution of current Joy program, returns to Joy main cycle.");
    ewrd("quit", MISCELLANEOUS, quit_, "->", "Exit from Joy.");
    ewrd("nothing", OPERAND, nothing_, "->  nothing", "Pushing the value nothing.");
    ewrd("index", OPERATOR, index_, "B L  ->  X", "X (= L[B]) is the 1st or 2nd member of list L.");
    ewrd("select", OPERATOR, select_, "X [..[X Xs]..]  ->  X [Xs]", "Indexing on type of X, returns the list [Xs].");
    ewrd("sametype", PREDICATE, sametype_, "X Y  ->  B", "Tests whether X has the same type as Y.");
    ewrd("getch", MISCELLANEOUS, getch_, "->  N", "Reads a character from input and puts it onto stack.");
    ewrd("__setlisting", MISCELLANEOUS, __setlisting_, "I  ->", "Sets value of flag for listing to I (= 0..9).");
    ewrd("__setstats", MISCELLANEOUS, __setstats_, "I  ->", "Sets value of flag for statistics to I (= 0..1).");
    ewrd("__settrace", MISCELLANEOUS, __settrace_, "I  ->", "Sets value of flag for tracing execution to I (= 0..2).");
    ewrd("builtin", PREDICATE, builtin_, "X  ->  B", "Tests whether X is a builtin symbol.");
    ewrd("fget", OPERATOR, fget_, "S  ->  S F", "Reads a factor from stream S and pushes it onto stack.");
    ewrd("mod", OPERATOR, rem_, "I J  ->  K", "Integer K is the remainder of dividing I by J.  Also supports float.\nSame as rem.");
}

static void plain_line(struct opcode *cur)
{
    int dot, leng;

    if (!cur || !cur->name)
	return;
    leng = *cur->name == SPACE ? -17 : -13;
    dot = cur->msg1[strlen(cur->msg1) - 1] == '.';
    printf("\n%*s :  %s", leng, cur->name, cur->msg1);
    if (!dot)
	putchar('.');
    printf("\n%s\n", cur->msg2);
}

static void print_html(char *str)
{
    for ( ; *str; str++) {
	switch (*str) {
	case '&' :
	    printf("&amp;");
	    break;
#if 0
	case '-' :
	    printf("&mdash;");
	    break;
#endif
	case '<' :
	    printf("&lt;");
	    break;

	case '>' :
	    printf("&gt;");
	    break;

	case '\n':
	    printf("<br>");
	    /* continue */

	default  :
	    printf("%c", *str);
	    break;
	}
    }
}

static void html_line(struct opcode *cur)
{
    if (!cur || !cur->name)
	return;
    printf("<tr><td><b>");
    print_html(cur->name);
    printf("</b></td><td>: ");
    printf("<font color=darkblue>");
    print_html(cur->msg1);
    printf("</font></td></tr>\n");
    printf("<tr><td></td><td><font color=darkred>");
    print_html(cur->msg2);
    printf("</font></td></tr><tr><td><br></td></tr>\n");
}

static void latex_line(struct opcode *cur)
{
    int ch, i;

    if (!cur || !cur->name)
	return;
    printf("\\litem{\\bf ");
    for (i = 0; (ch = cur->name[i]) != 0; i++)
	switch (ch) {
	case '<' :
	    printf("$<$");
	    break;

	case '>' :
	    printf("$>$");
	    break;

	default  :
	    putchar(ch);
	    break;
	}
    printf("}\\verb#:  %s#\\\\\n{\\small\\verb#", cur->msg1);
    for (i = 0; (ch = cur->msg2[i]) != 0; i++)
	if (ch == '\n')
	    printf("#\\\\\n\\verb#");
	else
	    putchar(ch);
    printf("#}\n\n");
}

void make_manual(int style)
{
    time_t t;
    struct tm *tm;
    int h, i, j, lo, hi;

    static struct {
	char *name;
	int type;
    } header[] = {
	{ "literal", LITERAL },
	{ "operand", OPERAND },
	{ "operator", OPERATOR },
	{ "predicate", PREDICATE },
	{ "combinator", COMBINATOR },
	{ "miscellaneous", MISCELLANEOUS }
    };

    if (!init) {
	init = 1;
	initprims();
    }
    if (style == HTML) {
	t = time(0);
	tm = localtime(&t);

	printf("<html><body><h1>Primitives of Joy</h1>\n");
	printf("<table><tr><td><b>Latest update: ");
	printf("%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1,
				 tm->tm_mday);
	printf("</b></td></tr></table><br><br><table>\n");
    }

    for (h = 0; h < (int)(sizeof(header) / sizeof(header[0])); h++) {

	if (style == PLAIN)
	    printf("\n\n%s\n", header[h].name);
	else if (style == LATEX)
	    printf("\n\n\\chapter{%s}\n\n", header[h].name);
	else
	    printf("<tr><td><h2>%s</h2></td></tr>\n", header[h].name);
	if (!h)
	    for (i = 1; i < MAX_LIT; i++)
		if (style == PLAIN)
		    plain_line(&literal1[i]);
		else if (style == LATEX)
		    latex_line(&literal1[i]);
		else
		    html_line(&literal1[i]);
	else {
	    lo = hi = 0;
	    for (i = 0; i < MAX_WRD; i++)
		if (header[h].type == wordlist[i].type) {
		    if (lo > wordlist[i].line || !lo)
			lo = wordlist[i].line;
		    if (hi < wordlist[i].line)
			hi = wordlist[i].line;
		}
	    for (j = lo; j <= hi; j++)
		for (i = 0; i < MAX_WRD; i++)
		    if (header[h].type == wordlist[i].type &&
				     j == wordlist[i].line) {
			if (*wordlist[i].name == '_')
			    continue;
			if (style == PLAIN)
			    plain_line(&wordlist[i]);
			else if (style == LATEX)
			    latex_line(&wordlist[i]);
			else
			    html_line(&wordlist[i]);
		    }
	}
    }
}

void manual_list()
{
    data_t *cur;
    int i, j = 0;

    if (!init) {
	init = 1;
	initprims();
    }
    cur = get(4 * (MAX_LIT + MAX_WRD));
    cur->op = typ_list;
    cur->list = &cur[1];
    cur->next = stack;
    stack = cur;
    for (i = 1; i < MAX_LIT; i++) {
	j++;
	cur[j].op = typ_list;
	cur[j].list = &cur[j + 1];
	cur[j].next = &cur[j + 4];
	j++;
	cur[j].op = typ_string;
	cur[j].str = literal1[i].name;
	cur[j].next = &cur[j + 1];
	j++;
	cur[j].op = typ_string;
	cur[j].str = literal1[i].msg1;
	cur[j].next = &cur[j + 1];
	j++;
	cur[j].op = typ_string;
	cur[j].str = literal1[i].msg2;
	cur[j].next = 0;
    }
    for (i = 0; i < MAX_WRD; i++) {
	if (!wordlist[i].line)
	    continue;
	j++;
	cur[j].op = typ_list;
	cur[j].list = &cur[j + 1];
	cur[j].next = i + 1 == MAX_WRD ? 0 : &cur[j + 4];
	j++;
	cur[j].op = typ_string;
	cur[j].str = wordlist[i].name;
	cur[j].next = &cur[j + 1];
	j++;
	cur[j].op = typ_string;
	cur[j].str = wordlist[i].msg1;
	cur[j].next = &cur[j + 1];
	j++;
	cur[j].op = typ_string;
	cur[j].str = wordlist[i].msg2;
	cur[j].next = 0;
    }
}

/*
    Als op != typ_symbol, gebruik op als index in literal.
    Als op == typ_symbol, gebruik lineaire zoek in wordlist. Indien niet
    gevonden, gebruik lookup om de library functie af te drukken.
*/
void helpdetail()
{
    int i, op;
    data_t *cur;
    struct opcode *h;

    if (!init) {
	init = 1;
	initprims();
    }
    for (cur = stack->list; cur; cur = cur->next) {
	if ((op = cur->op) != typ_symbol)
	    h = &literal1[op];
	else {
	    h = 0;
	    for (i = 0; i < MAX_WRD; i++) {
		if (!wordlist[i].line)
		    continue;
		if (!strcmp(cur->str, wordlist[i].name)) {
		    h = &wordlist[i];
		    break;
		}
	    }
	}
	if (h)
	    plain_line(h);
	else {
	    printf("\n%s == ", cur->str);
	    if ((i = lookup1(cur->str)) != -1)
		printterm((data_t *)joy_table[i].value, stdout);
	    printf("\n");
	}
    }
    stack = stack->next;
}
