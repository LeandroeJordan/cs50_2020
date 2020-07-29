from cs50 import get_int
from cs50 import get_string
import math


def main():

    Slen = 0
    text = ""
    # loop para input das frases
    while True:
        text = get_string("Text: ")
        if len(text) > 0:
            Slen = len(text)
            break

    # Defining init values to vareble
    i = 0
    cletters = 0
    cwords = 0
    csentences = 0

    # obter tamanho de letters, sentences, words

    for char in text:
        if char.isalpha():
            cletters = cletters + 1
        elif char == ' ':
            cwords = cwords + 1
        elif char == '!' or char == '.' or char == '?':
            csentences = csentences + 1

    cwords = cwords + 1

    # Calculate index
    index = 0.0588 * ((cletters * 100) / cwords) - 0.296 * ((csentences * 100) / cwords) - 15.8
    grade = round(index)
    # print result
    if grade <= 1:
        print("Before Grade 1")
    elif (grade < 16):
        print("Grade ", grade)
    else:
        print("Grade 16+")


main()