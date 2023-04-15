import ply.yacc as yacc
import os
import codecs
import re

#import Statement_Module    , analizador
from Lexico import tokens
from sys import stdin
#from Statement_Module import *



precedence = (
	
    ('right', 'ASSIGN', 'COMPARE',),
    ('left', 'NE'),
    ('left', 'LT', 'LTE', 'GT', 'GTE'),
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'DIVIDE'),
    ('left', 'LPARENT', 'RPARENT',),
)

#Variables for error detection
syntax_eror = False
semantic_error = False

def p_program(p):
	'''program : FCOMMENT block '''
	print ("program")
	#p[0] = program(p[1],"program")'''

def p_block1(p):
	'''block :  varDecl statement principal'''
	print ("block")

def p_principal1(p):
	'''principal : PRINCIPAL LPARENT varDecl RPARENT SEMICOLOM block
					| PRINCIPAL LPARENT statement RPARENT SEMICOLOM block
					'''

def p_principal2(p):
	'''principal : empty'''

def p_varDecl1(p):
	'''varDecl : DEF LPARENT ID COMMA DATATYPE RPARENT SEMICOLOM block
				| DEF LPARENT ID COMMA DATATYPE COMMA expression RPARENT SEMICOLOM block''' 
	print ("varDecl")

def p_varDeclEmpty(p):
	'''varDecl : empty'''
	print ("nulo")

def p_identList1(p):
	'''identList : ID'''
	print ("identList 1")

def p_identList2(p):
	'''identList : identList COMMA ID'''
	print ("identList 2")


def p_statement1(p):
	'''statement : ALTER LPARENT ID COMMA expression RPARENT SEMICOLOM block'''
	print ("statement 1")

def p_statement2(p):
	'''statement : CALL LPARENT ID RPARENT block'''
	print ("statement 2")

def p_statement3(p):
	'''statement : ISTRUE LPARENT ID RPARENT SEMICOLOM block'''
	print ("statement 3")

def p_statement4(p):
	'''statement : IF condition LPARENT statement RPARENT block'''
	print ("statement 4")

def p_statement5(p):
	'''statement : WHILE condition LPARENT statement RPARENT SEMICOLOM block'''
	print ("statement 5")

def p_statement6(p):
	'''statement : PROC ID LPARENT varDecl RPARENT SEMICOLOM block
				| PROC ID LPARENT statement RPARENT SEMICOLOM block'''
	print ("statement 6")

def p_statement7(p):
	'''statement : print block'''
	print ("statement 7")

	
def p_statement8(p):
	'''statement : MOVER LPARENT movimiento RPARENT SEMICOLOM block'''
	print ("statement 8")

def p_statement9(p):
	'''statement : comment block'''
	print ("statement 9")

def p_statement10(p):
	'''statement : ID LPARENT ID  RPARENT SEMICOLOM block
					| ID LPARENT statement RPARENT SEMICOLOM block
					| ID LPARENT BOOLEAN RPARENT SEMICOLOM block
					| ID LPARENT expression RPARENT SEMICOLOM block'''
	print ("statement ID ASSIGN")

#def p_statement11(p):
	#'''statement : ID LPARENT expression RPARENT SEMICOLOM statement'''
	###print ("statement 11")

#def p_statement12(p):
#	'''statement : ID LPARENT statement RPARENT SEMICOLOM statement
#					| ID LPARENT BOOLEAN RPARENT SEMICOLOM statement
#					| ID LPARENT expression RPARENT SEMICOLOM statement'''
#	print ("statement 12")
	
#def p_statement13(p):
#	'''statement : ID LPARENT BOOLEAN RPARENT SEMICOLOM statement'''
#	print ("statement 10")

def p_statement11(p):
	'''statement : NOT LPARENT ID RPARENT SEMICOLOM block'''
	print ("statement NOT")

def p_statement12(p):
	'''statement : ALEATORIO LPARENT RPARENT SEMICOLOM block'''
	print ("statement ALEATORIO")

def p_statement13(p):
	'''statement : REPEAT LPARENT block RPARENT SEMICOLOM block'''
	print ("statement REPEAT")

def p_statement14(p):
	'''statement : BREAK'''
	print ("statement BREAK")

def p_statement15(p):
	'''statement : UNTIL LPARENT block RPARENT condition SEMICOLOM block'''
	print ("statement REPEAT")

def p_statement16(p):
	'''statement : CASE WHEN LPARENT condition RPARENT THEN LPARENT block RPARENT SEMICOLOM block
						| CASE WHEN LPARENT condition RPARENT THEN LPARENT block RPARENT ELSE LPARENT block RPARENT SEMICOLOM block '''
	print ("statement Case Condition")

def p_statement17(p):
	'''statement : CASE ID whenloop SEMICOLOM block
				| CASE ID whenloop ELSE LPARENT block RPARENT SEMICOLOM block '''
	print ("statement Case @var")

def p_statementEmpty(p):
	'''statement : empty'''
	print ("nulo")

def p_whenloop1(p):
	'''whenloop : WHEN condition THEN LPARENT block RPARENT whenloop'''

def p_whenloop2(p):
	'''whenloop : empty'''


def p_print1(p):
	'''print : PRINT LPARENT ID RPARENT SEMICOLOM block
			| PRINT LPARENT STRING RPARENT SEMICOLOM block
			| PRINT LPARENT expression RPARENT SEMICOLOM block'''
	print("print")



def p_condition1(p):
	'''condition : expression'''
	print ("condition 1")

def p_condition2(p):
	'''condition : expression relation expression'''
	print ("condition 2")

def p_movimiento1(p):
	'''movimiento : ATR'''
	print("movimiento ATR")

def p_movimiento2(p):
	'''movimiento : ADL'''
	print("movimiento ADL")

def p_movimiento3(p):
	'''movimiento : ADE'''
	print("movimiento ADE")

def p_movimiento4(p):
	'''movimiento : AIZ'''
	print("movimiento AIZ")

def p_movimiento5(p):
	'''movimiento : IZQ'''
	print("movimiento IZQ")

def p_movimiento6(p):
	'''movimiento : DER'''
	print("movimiento DER")

def p_movimiento7(p):
	'''movimiento : DDE'''
	print("movimiento DDE")

def p_movimiento8(p):
	'''movimiento : DIZ'''
	print("movimiento DIZ")

def p_relation1(p):
	'''relation : ASSIGN'''
	print ("relation 1")

def p_relation2(p):
	'''relation : NE'''
	print ("relation 2")

def p_relation3(p):
	'''relation : LT'''
	print ("relation 3")

def p_relation4(p):
	'''relation : GT'''
	print ("relation 4")

def p_relation5(p):
	'''relation : LTE'''
	print ("relation 5")

def p_relation6(p):
	'''relation : GTE'''
	print ("relation 6")

def p_expression1(p):
	'''expression : term'''
	print ("expresion 1")

def p_expression2(p):
	'''expression : addingOperator term'''
	print ("expresion 2")

def p_expression3(p):
	'''expression : expression addingOperator term'''
	print ("expresion 3")

def p_addingOperator1(p):
	'''addingOperator : PLUS'''
	print ("addingOperator 1")

def p_addingOperator2(p):
	'''addingOperator : MINUS'''
	print ("addingOperator 1")

def p_term1(p):
	'''term : factor'''
	print ("term 1")

def p_term2(p):
	'''term : term multiplyingOperator factor'''
	print ("term 1")

def p_multiplyingOperator1(p):
	'''multiplyingOperator : TIMES'''
	print ("multiplyingOperator 1")

def p_multiplyingOperator2(p):
	'''multiplyingOperator : DIVIDE'''
	print ("multiplyingOperator 2")

def p_DATATYPE1(p):
	'''DATATYPE : INTEGERTP'''
	print ("DATATYPE INT")
	
def p_DATATYPE2(p):
	'''DATATYPE : BOOLEANTP'''
	print ("DATATYPE BOOL")

def p_factor1(p):
	'''factor : INTEGER
			| BOOLEAN
			| ID'''
	print ("factor int")


def p_factor2(p):
	'''factor : LPARENT expression RPARENT'''
	print ("factor 3")

def p_fcomment(p):
	'''FCOMMENT : COMMENT'''
	print("Fcomment")

def p_comment1(p):
	'''comment : COMMENT comment '''
	print("comment")

def p_comment2(p):
	'''comment : empty'''
#def p_block(p):
	#'''block : '''
	#print("block")

def p_empty(p):
	'''empty : '''
	pass

def p_error(p):
	if p == None:
		token = "end of file"
	else:
		pass
		token = str(p.type)+str(p.value)+" on line "+str(p.lineno)

	print("Syntax error: Unexpected "+token)
	#error = Error_Checker()
	#error.log_error(f"Syntax error: Unexpected {token}",2)



directorio = './test/'
archivo = 'yaccTest.pl0'
test = directorio+archivo
fp = codecs.open(test,"r","utf-8")
cadena = fp.read()
fp.close()

parser = yacc.yacc('SLR')
result = parser.parse(cadena)

print (result)