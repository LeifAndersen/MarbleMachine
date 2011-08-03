import sys
import os
import struct

WIDTH = 2048
HEIGHT = 2048

class State:
    x0 = 0
    x1 = 0
    y0 = 0
    y1 = 0

def parse_state(line, state):
    (top_left, trash, bottom_right) = line.partition(';')
    (x0, trash, y0) = top_left.partition(',')
    (x1, trash, y1) = bottom_right.partition(',')
    state.x0 =  float(x0) / WIDTH
    state.x1 =  float(x1) / WIDTH
    state.y0 = -float(y0) / HEIGHT
    state.y1 = -float(y1) / HEIGHT

def write_state(fout, state):
    fout.write(struct.pack('ffffffff', -1,  1, 0, 0, 0, 1, state.x0, state.y0))
    fout.write(struct.pack('ffffffff',  1,  1, 0, 0, 0, 1, state.x1, state.y0))
    fout.write(struct.pack('ffffffff',  1, -1, 0, 0, 0, 1, state.x1, state.y1))
    fout.write(struct.pack('ffffffff', -1, -1, 0, 0, 0, 1, state.x0, state.y1))

def save(infile_path, outfile_path):
    fin = open(infile_path, 'r')
    fout = open(outfile_path, 'wb')
    name = ""
    texture = ""
    up = State()
    down = State()
    hover = State()

    for line in fin:
        (label, trash, data) = line.partition(':')
        if labal == 'name':
            name = data
        elif label == 'up_coords':
            parse_state(data, up)
        elif label == 'down_coords':
            parse_state(data, down)
        elif label == 'hover_coords':
            parse_state(data, hover)
        elif label == 'texture':
            texture = data
        elif label == 'width':
            WIDTH = data
        elif label == 'height':
            HEIGHT = data

    write_state(fout, up)
    write_state(fout, down)
    write_state(fout, hover)
    fin.close()
    fout.flush()
    fout.close()
    return {'FINISHED'}

if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
