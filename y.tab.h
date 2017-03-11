/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING_LITERAL = 259,
    INT_LITERAL = 260,
    CREATE = 261,
    TABLE = 262,
    INSERT = 263,
    INTO = 264,
    SELECT = 265,
    FROM = 266,
    WHERE = 267,
    UPDATE = 268,
    PRIMARY = 269,
    INDEX = 270,
    FOREIGN = 271,
    KEY = 272,
    DEFAULT = 273,
    NOT = 274,
    NULL_TOKEN = 275,
    AND = 276,
    OR = 277,
    XOR = 278,
    ALL = 279,
    SOME = 280,
    ANY = 281,
    BIT = 282,
    INT = 283,
    INTEGER = 284,
    BIGINT = 285,
    REAL = 286,
    DOUBLE = 287,
    FLOAT = 288,
    DECIMAL = 289,
    COMPARATOR = 290,
    REFERENCES = 291,
    ORDER = 292,
    BY = 293,
    DELETE = 294,
    DATATYPE = 295,
    VALUES = 296,
    AUTO_INCREMENT = 297,
    ASC = 298,
    DESC = 299,
    UNIQUE = 300,
    IN = 301,
    TRUE = 302,
    FALSE = 303,
    DISTINCT = 304,
    SET = 305,
    DROP = 306,
    ALTER = 307,
    ADD = 308,
    COLUMN = 309,
    ALL_COLUMN = 310,
    BRACKET_OPEN = 311,
    BRACKET_CLOSE = 312,
    SEMICOLON = 313,
    COMMA = 314,
    INVALID = 315
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING_LITERAL 259
#define INT_LITERAL 260
#define CREATE 261
#define TABLE 262
#define INSERT 263
#define INTO 264
#define SELECT 265
#define FROM 266
#define WHERE 267
#define UPDATE 268
#define PRIMARY 269
#define INDEX 270
#define FOREIGN 271
#define KEY 272
#define DEFAULT 273
#define NOT 274
#define NULL_TOKEN 275
#define AND 276
#define OR 277
#define XOR 278
#define ALL 279
#define SOME 280
#define ANY 281
#define BIT 282
#define INT 283
#define INTEGER 284
#define BIGINT 285
#define REAL 286
#define DOUBLE 287
#define FLOAT 288
#define DECIMAL 289
#define COMPARATOR 290
#define REFERENCES 291
#define ORDER 292
#define BY 293
#define DELETE 294
#define DATATYPE 295
#define VALUES 296
#define AUTO_INCREMENT 297
#define ASC 298
#define DESC 299
#define UNIQUE 300
#define IN 301
#define TRUE 302
#define FALSE 303
#define DISTINCT 304
#define SET 305
#define DROP 306
#define ALTER 307
#define ADD 308
#define COLUMN 309
#define ALL_COLUMN 310
#define BRACKET_OPEN 311
#define BRACKET_CLOSE 312
#define SEMICOLON 313
#define COMMA 314
#define INVALID 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 10 "sql.y" /* yacc.c:1909  */

	int intval;
	double floatval;
	char *strval;
	int subtok;

#line 181 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
