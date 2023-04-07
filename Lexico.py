#import ply.lex as lex
import re
import codecs
import os
import sys
#import Reserved_words
#import Tokens

tokens = ['ID','NUMBER','PLUS','MINUS','TIMES','DIVIDE',
		'ASSIGN','NE','LT','LTE','GT','GTE',
		'LPARENT', 'RPARENT','LBRACKET','RBRACKET','COMMA','SEMICOLOM',
		'DOT','UPDATE'
		]
reservadas = ['PROC','DEF','ALTER','NOT','MOVER','ALEATORIO','ISTRUE',
              'REPEAT','UNTIL','WHILE','CASE','WHEN','ELSE','THEN','PRINT','CALL']


tokens = tokens + reservadas

t_ignore = ' \t'
t_PLUS = r'\+'
t_MINUS = r'\-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
#t_ASSIGN = r'='
t_COMPARE = r'=='
t_NE = r'<>'
t_LT = r'<'
t_LTE = r'<='
t_GT = r'>'
t_GTE = r'>='
t_LPARENT = r'\('
t_RPARENT = r'\)'
t_LBRACKET = r'\{'
t_RBRACKET = r'\}'
t_COMMA = r','
t_SEMICOLOM= r';'
#t_DOT = r'\.'
t_TRUE = r'True'
t_FALSE = r'False'
t_ISTRUE = r'IsTrue'
#t_TYPE = r'type'
t_PRINT = r'=>'
#t_FOR = r'For'
#t_IF = r'If'
t_ELSE = r'Else'
t_DEF = r'Def'
t_PRIN = r'@Principal'
t_NOT = r'Not'

def t_COMMENT (t):
    r'\--.*'
    pass

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

def t_Proc(t):
    r'[Proc][@][a-zA-Z0-9_#]{2,9}'
    if t.value.upper() in reservadas:
        t.value = t.value.upper
        t.type = t.value
    return t

def t_STRING (t):
    r'\".*?\"'
    t.value = str(t.value)
    return t


def t_error (t):
    print ("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)



    #############   codigo para testear el analizador lexico    ##################

def buscarFicheros(directorio):
	ficheros = []
	numArchivo = ''
	respuesta = False
	cont = 1

	for base, dirs, files in os.walk(directorio):
		ficheros.append(files)

	for file in files:
		print( str(cont)+". "+file)
		cont = cont+1

	while respuesta == False:
		numArchivo = input('\nNumero del test: ')
		for file in files:
			if file == files[int(numArchivo)-1]:
				respuesta = True
				break

	print ("Has escogido \"%s\" \n" %files[int(numArchivo)-1])

	return files[int(numArchivo)-1]

directorio = '/Users/sebas/Documents/Compiladores/pl0/analizador version 1/test/'
archivo = buscarFicheros(directorio)
test = directorio+archivo
fp = codecs.open(test,"r","utf-8")
cadena = fp.read()
fp.close()

analizador = lex.lex()

analizador.input(cadena)

while True:
	tok = analizador.token()
	if not tok : break
	print( tok)