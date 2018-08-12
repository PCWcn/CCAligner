/* config/lexer.l */
%{
#include "tok.h"
#include <cstdlib>


//extern void yyerror(const char *);  /* prints grammar violation message */

//extern int sym_type(const char *);  /* returns type from symbol table */

//#define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

static void comment(void);
static int check_type(void);


int nline;
int ncolumn = 0;

%}

O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\f]

%%

"\n"					{ nline++; ncolumn = 0;}

"/*"                                    { comment(); }
"//".*                                 { /* consume //-comment */}
"#".* 					{}
"import".*				{}


"as"					{ return(AS); }
"base"					{ return(BASE); }
"checked"				{ return(CHECKED); }
"decimal"				{ return(DECIMAL); }
"delegate"				{ return(DELEGATE); }
"event"					{ return(EVENT); }
"explicit"				{ return(EXPLICIT); }
"false"					{ return(FALS); }
"fixed"					{ return(FIXED); }
"foreach"				{ return(FEACH); }
"implicit"				{ return(IMPLICIT); }
"internal"				{ return(INTERNAL); }
"lock"					{ return(LOCK); }
"namespace"				{ return(NSPA); }
"null"					{ return(NUL); }
"object"				{ return(OBJECT); }
"operator"				{ return(OPRT); }
"override"				{ return(OVRD); }
"params"				{ return(PARAMS); }
"readonly"				{ return(REDY); }
"ref"					{ return(REF); }
"sbyte"					{ return(SBYTE); }
"sealed"				{ return(SEALED); }
"stackalloc"				{ return(STALLC); }
"string"				{ return(STRING); }
"true"					{ return(TRU); }
"typeof"				{ return(TYPEOF); }
"uint"					{ return(UINT); }
"ulong"					{ return(ULONG); }
"unchecked"				{ return(UCEKD); }
"unsafe"				{ return(USFE); }
"ushort"				{ return(USHORT); }
"using"					{ return(USING); }
"virtual"				{ return(VIR); }
"auto"					{ return(AUTO); }
"abstract"				{ return(ABS); }
"break"					{ return(BREAK); }
"case"					{ return(CASE); }
"char"					{ return(CHAR); }
"const"					{ return(CONST); }
"new"					{ return(NEW); }
"assert"				{ return(ASSERT); }
"continue"				{ return(CONTINUE); }
"default"				{ return(DEFAULT); }
"do"					{ return(DO); }
"double"				{ return(DOUBLE); }
"byte"					{ return(BYTE); }
"public"				{ return(PUBLIC); }
"throws"				{ return(THROWS); }
"instanceof"			{ return(INSOF); }
"transient"				{ return(TRANS); }
"catch"					{ return(CATCH); }
"extends"				{ return(EXTENDS); }
"try"					{ return(TRY); }
"final"					{ return(FINAL); }
"interface"				{ return(INTER); }
"class"					{ return(CLASS); }
"finally"				{ return(FINALLY); }
"strictfp"				{ return(STRICT); }
"native"				{ return(NATIVE); }
"super"					{ return(SUPER); }
"implements"			{ return(IMP); }
"protected"				{ return(PROT); }
"throw"					{ return(THROW); }
"else"					{ return(ELSE); }
"enum"					{ return(ENUM); }
"extern"				{ return(EXTERN); }
"float"					{ return(FLOAT); }
"synchronized"			{ return(SYN); }
"boolean"				{ return(BOOLEAN); }
"for"					{ return(FOR); }
"goto"					{ return(GOTO); }
"private"				{ return(PRI); }
"this"					{ return(THIS); }
"if"					{ return(IF); }
"inline"				{ return(INLINE); }
"int"					{ return(INT); }
"long"					{ return(LONG); }
"register"				{ return(REGISTER); }
"restrict"				{ return(RESTRICT); }
"return"				{ return(RETURN); }
"short"					{ return(SHORT); }
"signed"				{ return(SIGNED); }
"sizeof"				{ return(SIZEOF); }
"static"				{ return(STATIC); }
"struct"				{ return(STRUCT); }
"switch"				{ return(SWITCH); }
"typedef"				{ return(TYPEDEF); }
"union"					{ return(UNION); }
"unsigned"				{ return(UNSIGNED); }
"void"					{ return(VOID); }
"volatile"				{ return(VOLATILE); }
"while"					{ return(WHILE); }
"_Alignas"                              { return (ALIGNAS); }
"_Alignof"                              { return (ALIGNOF); }
"_Atomic"                               { return (ATOMIC); }
"_Bool"                                 { return (BOOL); }
"_Complex"                              { return (COMPLEX); }
"_Generic"                              { return (GENERIC); }
"_Imaginary"                            { return (IMAGINARY); }
"_Noreturn"                             { return (NORETURN); }
"_Static_assert"                        { return (STATIC_ASSERT); }
"_Thread_local"                         { return (THREAD_LOCAL); }
"__func__"                              { return (FUNC_NAME); }

{L}{A}*					{ var_val = yytext; return check_type(); }

{HP}{H}+{IS}?				{ return I_CONSTANT; }
{NZ}{D}*{IS}?				{ return I_CONSTANT; }
"0"{O}*{IS}?				{ return I_CONSTANT; }
{CP}?"'"([^'\\\n]|{ES})+"'"		{ return I_CONSTANT; }

{D}+{E}{FS}?				{ return F_CONSTANT; }
{D}*"."{D}+{E}?{FS}?			{ return F_CONSTANT; }
{D}+"."{E}?{FS}?			{ return F_CONSTANT; }
{HP}{H}+{P}{FS}?			{ return F_CONSTANT; }
{HP}{H}*"."{H}+{P}{FS}?			{ return F_CONSTANT; }
{HP}{H}+"."{P}{FS}?			{ return F_CONSTANT; }

({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{ return STRING_LITERAL; }

"..."					{ return ELLIPSIS; }
">>="					{ return RIGHT_ASSIGN; }
"<<="					{ return LEFT_ASSIGN; }
"+="					{ return ADD_ASSIGN; }
"-="					{ return SUB_ASSIGN; }
"*="					{ return MUL_ASSIGN; }
"/="					{ return DIV_ASSIGN; }
"%="					{ return MOD_ASSIGN; }
"&="					{ return AND_ASSIGN; }
"^="					{ return XOR_ASSIGN; }
"|="					{ return OR_ASSIGN; }
">>"					{ return RIGHT_OP; }
"<<"					{ return LEFT_OP; }
"++"					{ return INC_OP; }
"--"					{ return DEC_OP; }
"->"					{ return PTR_OP; }
"&&"					{ return AND_OP; }
"||"					{ return OR_OP; }
"<="					{ return LE_OP; }
">="					{ return GE_OP; }
"=="					{ return EQ_OP; }
"!="					{ return NE_OP; }
";"					{ return ';'; }
("{"|"<%")				{ return '{'; }
("}"|"%>")				{ return '}'; }
","					{ return ','; }
":"					{ return ':'; }
"="					{ return '='; }
"("					{ return '('; }
")"					{ return ')'; }
("["|"<:")				{ return '['; }
("]"|":>")				{ return ']'; }
"."					{ return '.'; }
"&"					{ return '&'; }
"!"					{ return '!'; }
"~"					{ return '~'; }
"-"					{ return '-'; }
"+"					{ return '+'; }
"*"					{ return '*'; }
"/"					{ return '/'; }
"%"					{ return '%'; }
"<"					{ return '<'; }
">"					{ return '>'; }
"^"					{ return '^'; }
"|"					{ return '|'; }
"?"					{ return '?'; }

{WS}+					{ /* whitespace separates tokens */ }
.					{ /* discard bad characters */ }

%%

int yywrap(void)        /* called at end of input */
{
    return 1;           /* terminate now */
}

static void comment(void)
{
    int c;
	int flag = 0;

    while ((c = yyinput()) != 0)
    { 
		flag = 0;
		if (c == '*')
        {
            while ((c = yyinput()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
			
			if (c == '\n')
			{
				//printf("cline: %d\n", nline);
				nline++;
				flag = 1;
			}
        }
		if (flag == 0 && c == '\n')
		{
			//printf("cline: %d\n", nline);
			nline ++;
		}
    }    
    //yyerror("unterminated comment");
}

static int check_type(void)
{
    
    //switch (sym_type(yytext))
    //{
    //case TYPEDEF_NAME:                /* previously defined */
    //    return TYPEDEF_NAME;
    //case ENUMERATION_CONSTANT:        /* previously defined */
    //    return ENUMERATION_CONSTANT;
    //default:                          /* includes undefined */
        return IDENTIFIER;
    //}
}
