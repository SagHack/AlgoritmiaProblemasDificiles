def process_file(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    output_lines = []
    for line in lines:
        # Parse the nodes
        node1, node2 = map(int, line.strip().split())

        # Calculate the absolute difference
        diff = abs(node1 - node2)

        # Append the original line and the new values
        output_lines.append(f"{node1} {node2} {diff} 0.5 0.5\n")

    with open(output_file, 'w') as f:
        f.writelines(output_lines)

if __name__ == "__main__":
    input_file_path = "entrada1.txt"  # Change this to your input file path
    output_file_path = "output1.txt"  # Change this to your output file path

    process_file(input_file_path, output_file_path)
    print(f"File processed and saved to {output_file_path}")
