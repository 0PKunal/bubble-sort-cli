import time
import argparse

def parse_number(x):
    """
    Convert a string to an integer or float automatically.
    
    Args:
        x (str): The string representation of a number.
    
    Returns:
        int or float: Converted number.
    """
    try:
        return int(x)
    except ValueError:
        return float(x)

def bubble_sort(data):
    """
    Sort a list of numbers using the Bubble Sort algorithm.
    
    Args:
        data (list): List of numbers to be sorted.
    
    Returns:
        list: Sorted list of numbers.
    """
    n = len(data)
    for i in range(n):
        # Last i elements are already in place
        for j in range(n - i - 1):
            if data[j] > data[j + 1]:
                # Swap if the element is greater than the next element
                data[j], data[j + 1] = data[j + 1], data[j]
    return data

# CLI argument parsing
parser = argparse.ArgumentParser(description="Bubble sort a list of numbers from a file.")
parser.add_argument("file", help="Path to the input file containing numbers")
args = parser.parse_args()
file_path = args.file

# Read numbers from file
with open(file_path, "r") as file:
    content = file.read()

# Split content by commas or spaces, then convert each to int or float
raw_data = [parse_number(x) for x in content.replace(',', ' ').split()]
original_numbers = raw_data.copy()

# Sort the data and measure execution time
start_time = time.time()
sorted_data = bubble_sort(raw_data)
end_time = time.time()

# Print results and metadata
print(f"\nOriginal data: {original_numbers}\n")
print(f"Sorted data: {sorted_data}\n")
print(f"Sorting took {end_time - start_time:.6f} seconds")
print(f"Sorting algorithm used: Bubble Sort")
print(f"Number of elements sorted: {len(sorted_data)}")
print(f"\nData source: {file_path}")
print(f"Data type: {type(raw_data[0]).__name__ if raw_data else 'N/A'}")
print(f"Data format: Comma and space-separated values")
print(f"Data order before sorting: Unsorted")
print(f"Data order after sorting: Sorted")
print(f"Data size: {len(raw_data)} elements\n")


