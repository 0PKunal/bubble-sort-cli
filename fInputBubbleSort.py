def bubbleSort(data):
    n = len(data)
    for i in range(n - 1):
        flag = False
        for j in range(n - i - 1):
            if data[j] > data[j + 1]:
                data[j], data[j + 1] = data[j + 1], data[j]
                flag = True
        if not flag:
            break

def main():
    n = int(input("\nEnter the number of elements to be sorted: "))
    raw_data = []
    
    print("\nEnter the elements to be sorted:")
    for _ in range(n):
        raw_data.append(float(input()))
    
    bubbleSort(raw_data)
    
    print("\nThe sorted elements are:")
    for num in raw_data:
        print(f"{num:4.2f}", end=' ')
    print("\n")

if __name__ == "__main__":
    main()
