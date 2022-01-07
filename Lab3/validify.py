
fout = open("Lab3Prob1.txt").readlines()
fin = open("input_sudoku.txt").readlines()

in_dict = {}
out_dict = {}


def discrepency(name, row, col, msg):
    print(f"Discrepency detected with board{name}: Row {row} Col {col}: {msg}")

def match_board():
    print("Performing board matching checks")
    for (name, board) in in_dict.items():
        for i in range(81):
            if board[i] != "0" and board[i] != out_dict[name][i]:
                discrepency(name, int(i/9), i%9, "")
    print("Board matching concluded\n")

def check_boards():
    print("Performing board rule checks")
    for (name, board) in out_dict.items():
        for i in range(81):
            row, col = int(i/9), i%9
            # check row
            for j in range(9):
                if j != col and board[row*9+j] == board[i]:
                    discrepency(name, row, col, "ROW HAS DUPLICATES")

            # check col
            for j in range(9):
                if j != row and board[j*9+col] == board[i]:
                    discrepency(name, row, col, "COL HAS DUPLICATES")
            row_block, col_block = int(i/9/3), int(i%9/3)
            
            # check block
            for j in range(3):
                for k in range(3):
                    if (row_block*3+j, col_block*3+k) != (row, col) and board[(row_block*3+j)*9+(col_block*3+k)] == board[i]:
                        discrepency(name, row, col, "BLOCK HAS DUPLICATES")
    print("Board rule checks concluded\n")

# Parse the output file
line_count = 0
name = ""
for line in fout:
    line = line.rstrip()
    if line_count %10 == 0:
        name = line.replace(" ","_")
    else:
        out_dict[name] = out_dict[name] + line if name in out_dict else line
    line_count += 1

# Parse the input file
line_count = 0
name = ""
for line in fin:
    line = line.rstrip()
    if line_count %10 == 0:
        name = line.replace(" ","_")
    else:
        in_dict[name] = in_dict[name] + line if name in in_dict else line
    line_count += 1


match_board()
check_boards()