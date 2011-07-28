import sys
import os
import struct

WIDTH = 2048
HEIGHT = 2048

def write_coords(coords, fout):
        (top_left, trash, bottom_right) = coords.partition(';')
        (top_left_x, trash, top_left_y) = top_left.partition(',')
        (bottom_right_x, trash, bottom_right_y) = bottom_right.partition(',')
        x0 = float(top_left_x)     *  2 / WIDTH   - 1
        x1 = float(bottom_right_x) *  2 / WIDTH   - 1
        y0 = float(top_left_y)     * -2 / HEIGHT  + 1
        y1 = float(bottom_right_y) * -2 / HEIGHT  + 1

        # Write the data
        fout.write(struct.pack('ffffffff', -1,  1, 0, 0, 0, 1, x0, y0))
        fout.write(struct.pack('ffffffff',  1,  1, 0, 0, 0, 1, x1, y0))
        fout.write(struct.pack('ffffffff',  1, -1, 0, 0, 0, 1, x1, y1))
        fout.write(struct.pack('ffffffff', -1, -1, 0, 0, 0, 1, x0, y1))


def save(infile_path, outfile_dir):
    fin = open(infile_path, 'r')
    for line in fin:
        # Get the file path
        (output_file, trash, coords) = line.partition(':')
        outfile_path = outfile_dir + output_file + "_button.mp3"
        fout = open(outfile_path, 'wb')
        
        # Get the data
        (button_up, trash, rest) = coords.partition(':')
        (button_down, trash, button_hover) = rest.partition(':')
        
        # Write the data
        write_coords(button_up, fout)
        write_coords(button_down, fout)
        write_coords(button_hover, fout)
        fout.flush()
        fout.close()
    fin.close()
    return {'FINISHED'}

if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
