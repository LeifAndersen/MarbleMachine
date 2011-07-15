import sys
import struct

WIDTH = 1024
HEIGHT = 1024

def save(input_path, output_path):
    fin = open(input_path, "r")
    fout = open(output_path, "wb")
    for line in fin:
        (top_left, trash, bottom_right) = line.partition(';')
        (top_left_x, trash, top_left_y) = top_left.partition(',')
        (bottom_right_x, trash, bottom_right_y) = bottom_right.partition(',')
        x0 = float(top_left_x) / WIDTH
        x1 = float(bottom_right_x) / WIDTH
        y0 = float(top_left_y) / WIDTH
        y1 = float(bottom_right_y) / WIDTH
        fout.write(struct.pack('ffffffff', x0, y0, x1, y0, x0, y1, x1, y1))
    fout.flush()
    fout.close()
    fin.close()
    return {'FINISHED'}

if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
