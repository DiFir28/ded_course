file_path = "Onegin.txt"

with open(file_path, "r", encoding="utf-8") as file:
    lines = file.readlines()

# Remove the newline character
lengths = [len(line.rstrip("\n")) for line in lines]

if lengths:
    max_length = max(lengths)
    average_length = sum(lengths) / len(lengths)

    print(f"Max symbols in one line: {max_length}")
    print(f"Average symbols in one line: {average_length:.2f}")
else:
    print("File is empty")