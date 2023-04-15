import ply.lex as lex
import re
import codecs
import os
import sys
#import Reserved_words
#import Tokens

tokens = ['ID','PLUS','MINUS','TIMES','DIVIDE',"BOOLEANTP","INTEGERTP",
		'ASSIGN','NE','LT','LTE','GT','GTE',"VAR","IF",
		'LPARENT', 'RPARENT','COMMA','SEMICOLOM',
		'TRUE','FALSE','COMPARE',"COMMENT","STRING","BOOLEAN", "INTEGER",
        'ATR','ADL','ADE','AIZ','IZQ','DER','DDE','DIZ','BREAK'
		]
reservadas = ['PROC','DEF','ALTER','NOT','MOVER','ALEATORIO','ISTRUE',
              'REPEAT','UNTIL','WHILE','CASE','WHEN','ELSE','THEN','PRINT','CALL','PRINCIPAL']


tokens = tokens + reservadas

t_ignore = ' \t'
t_PLUS = r'\+'
t_MINUS = r'\-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
t_COMPARE = r'=='
t_ASSIGN = r'='
t_NE = r'<>'
t_LTE = r'<='
t_LT = r'<'
t_GTE = r'>='
t_GT = r'>'
t_LPARENT = r'\('
t_RPARENT = r'\)'
t_COMMA = r','
t_SEMICOLOM= r';'
t_BOOLEANTP = r'Boolean'
t_INTEGERTP = r'Integer'
t_TRUE = r'True'
t_FALSE = r'False'
t_ISTRUE = r'IsTrue'
t_ALTER = r'Alter'
t_PRINT = r'=>'
t_BREAK = r'Break'
t_UNTIL = r'Until'
t_IF = r'If'
t_ELSE = r'Else'
t_DEF = r'Def'
t_PRINCIPAL = r'@Principal'
t_NOT = r'Not'
t_MOVER = r'Mover'
t_CASE = r'Case'
t_THEN = r'Then'
t_PROC = r'Proc'
t_ATR = r'ATR'
t_ADL = r'ADL'
t_ADE = r'ADE'
t_AIZ = r'AIZ'
t_IZQ = r'IZQ'
t_DER = r'DER'
t_DDE = r'DDE'
t_DIZ = r'DIZ'
t_WHEN = r'When'
t_ALEATORIO = r'Aleatorio'
t_WHILE = r'While'



def t_comment (t):
    r'\--.*'
    t.type = 'COMMENT'
    return t

#def t_Proc(t):
 #   r'[Proc][@][a-zA-Z0-9_#]{2,9}'
  #  t.type = "PROC"
   # return t

def t_ID(t):
    r'[@][a-zA-Z0-9_#]{2,9}'
    if t.value.upper() in reservadas:
        t.value = t.value.upper
        t.type = t.value
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def t_space(t):
    r'\s+'



def t_STRING (t):
    r'\".*?\"'
    t.value = str(t.value)
    return t

def t_INTEGER (t):
	r'\d+'
	t.value = int(t.value)
	return t

def t_BOOLEAN (t):
    r'True | False'
    return t

def t_error (t):
    print ("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)



    #############   codigo para testear el analizador lexico    ##################



directorio = './test/'

test = directorio+"lexTest.pl0"
fp = codecs.open(test,"r","utf-8")
cadena = fp.read()
fp.close()

analizador = lex.lex()

#analizador.input(cadena)

#while True:
#	tok = analizador.token()
#	if not tok : break
#	print( tok)