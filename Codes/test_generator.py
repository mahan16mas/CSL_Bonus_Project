import random

i = 1
while i <= 100000:
    with open(f"Samples/{int(i)}.txt", 'w') as file:
        file.write(str(i) + "\n")
        for _ in range(int(i)):
            file.write(str(random.randint(-2147483648, 2147483648)) + '\n')
    i += 1000