import matplotlib.pyplot as plt
import matplotlib.animation as animation
import argparse

def parse_number(x):
    try:
        return int(x)
    except ValueError:
        return float(x)

def bubble_sort_visual(data):
    """
    Bubble sort generator that yields (current_data, indices_being_compared, sorted_index)
    'sorted_index' marks the start of the already sorted portion.
    """
    n = len(data)
    
    # Dynamically adjust skip for speed
    skip = max(1, len(data) // 50)
    count = 0

    for i in range(n):
        for j in range(n - i - 1):
            count += 1
            if count % skip == 0:
                yield data, [j, j+1], n - i
            if data[j] > data[j + 1]:
                data[j], data[j + 1] = data[j + 1], data[j]
                if count % skip == 0:
                    yield data, [j, j+1], n - i

    # Final pass: everything sorted
    yield data, [], 0

# CLI argument parsing
parser = argparse.ArgumentParser(description="Bubble sort visualization.")
parser.add_argument("file", help="Path to the input file containing numbers")
args = parser.parse_args()
file_path = args.file

with open(file_path, "r") as file:
    content = file.read()

data = [parse_number(x) for x in content.replace(',', ' ').split()]

# Setup plot
fig, ax = plt.subplots()
fig.patch.set_facecolor('black')
ax.set_facecolor('black')

bar_rects = ax.bar(range(len(data)), data, align="edge", color='green', edgecolor='black')
ax.set_title("Bubble Sort Visualization", color='white')
ax.set_xlabel("Index", color='white')
ax.set_ylabel("Value", color='white')
ax.tick_params(colors='white')
ax.set_ylim(0, max(data) * 1.1)

def update_plot(frame):
    current_data, highlight, sorted_index = frame
    n = len(current_data)
    for i, rect in enumerate(bar_rects):
        rect.set_height(current_data[i])
        if i >= sorted_index:
            rect.set_color("cyan")  # Already sorted portion
        elif i in highlight:
            rect.set_color("white")  # Currently moving bars
        else:
            rect.set_color("green")  # Unsorted bars
    return bar_rects

ani = animation.FuncAnimation(
    fig,
    update_plot,
    frames=bubble_sort_visual(data),
    interval=50,
    repeat=False
)

plt.show()
