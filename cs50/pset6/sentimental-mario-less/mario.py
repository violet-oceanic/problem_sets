while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height <= 8:
            break
    except:
        print("Must be integer between 1 and 8")
        pass

for n in range(1,height + 1):
    print(f"{" " * (height - n)}", end="")
    print(f"{"#" * n}")
    #print()