from cs50 import get_int


def main():

    cardnum = int(input("Number: "))
    number = cardnum
    contdig = 0
    numbers = []
   # Carregar o array de numeros de cartoes separando os digitos
    while number != 0:
        numbers.append(int(number % 10))
        number = number // 10
        contdig += 1
    lencard = len(numbers)
    # Calculando os produtos dos numeros * 2
    prod = 0
    i = 1
    while i <= (lencard - 1):
        if ((numbers[i] * 2) >= 10):
            prod = prod + (((numbers[i] * 2) % 10) + 1)
        else:
            prod = prod + (numbers[i] * 2)
        i = i + 2
    sum = 0

    # Fazendo o somatório dos digitos restantes com o produto
    ind = 0
    while ind <= (lencard - 1):
        sum = sum + numbers[ind]
        ind = ind + 2
    sum = sum + prod

    # Imprimindo o resultado final
    sum = sum % 10
    if sum == 0 and contdig > 12:
        if numbers[lencard - 1] == 4:
            print("VISA")
        elif numbers[lencard - 1] == 5 and numbers[lencard - 2] <= 5:
            print("MASTERCARD")
        elif (numbers[lencard - 1] == 3 and (numbers[lencard - 2] == 4 or numbers[lencard - 2] == 7)):
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")


# execution Main function
main()
