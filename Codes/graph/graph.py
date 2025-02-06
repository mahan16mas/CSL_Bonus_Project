import matplotlib.pyplot as plt

def read_data(file_name):
    with open(file_name, 'r') as file:
        return [int(line.strip()) / 1e6 for line in file]

def show_graph(x, y1, y2, text):
    plt.figure(figsize=(8, 5))  # Set figure size
    plt.plot(x, y1, label=f'{text} sort with c', color='blue', linestyle='-', marker='.')
    plt.plot(x, y2, label=f'{text} sort with asm', color='red', linestyle='--',
             marker='.')

    plt.xlabel('size of input')
    plt.ylabel('time of processing')
    plt.title('sort in c and asm')

    plt.legend()

    plt.grid(True)

    plt.show()


x = list(range(1, 100000, 1000))
show_graph(x, read_data("bubble_sort_time.txt"),read_data("asm_bubble_sort_time.txt"), "bubble")
show_graph(x, read_data("gnome_sort_time.txt"), read_data("asm_gnome_sort_time.txt"), "gnome")

