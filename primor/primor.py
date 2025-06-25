import math

divisores = []
n = int(input("Primo? "))

for i in range(1, int(math.sqrt(n))):
    if (n % i == 0):
        divisores.append(i)
        divisores.append(n//i)

divisores.sort()
print(f"Divisores: {divisores}")

if (len(divisores) <= 2):
    print(f"{n} é primo")
else:
    print(f"{n} não é primo")
