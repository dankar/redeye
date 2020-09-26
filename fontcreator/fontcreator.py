import tkinter as tk

num_rows = 8
num_columns = 5

tiles = [[None for i in range(num_columns)] for i in range(num_rows)]

def left_mouse_callback(event):
    col_width = int(c.winfo_width()/num_columns)
    row_height = int(c.winfo_height()/num_rows)
    col = event.x//col_width
    row = event.y//row_height
    if not tiles[row][col]:
        tiles[row][col] = c.create_rectangle(col*col_width, row*row_height, (col+1)*col_width, (row+1)*row_height, fill="black")
    else:
        c.delete(tiles[row][col])
        tiles[row][col] = None
		
def middle_mouse_callback(event):
	for col in range(num_columns):
		data_byte = 0
		for row in range(num_rows):
			data_byte = data_byte | ((1 if tiles[row][col] else 0) << row)
			c.delete(tiles[row][col])
			tiles[row][col] = None
			
		print(hex(data_byte) + ', ', end = '')
	print('')
	
root = tk.Tk()
c = tk.Canvas(root, width=100*num_columns, height=100*num_rows, borderwidth=5, background='white')
c.pack()
c.bind("<Button-1>", left_mouse_callback)
c.bind("<Button-2>", middle_mouse_callback)

root.mainloop()