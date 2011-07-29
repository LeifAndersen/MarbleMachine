import struct
import sys

TEX_WIDTH  = 2048
TEX_HEIGHT = 2048

class Level:
    x = 1.0
    y = 1.0
    rad = 1.0

def save(infile_name, outfile_name):
    # Data structures
    fin = fopen(infile_name, 'r')
    fout = fopen(outfile_name, 'wb')
    name = ""
    levels = []
    x1 = 1.0
    x2 = 1.0
    y1 = 1.0
    y2 = 1.0
    width = 1
    height = 1

    # Read data
    for line in fin:
        (command, trash, data) = line.partition(':')
        if command == 'name':
            name = data
        elif command == 'width':
            width = float(data)
        elif command == 'height':
            height = float(data)
        elif command == 'coords':
            (topLeft, trash, bottomRight) = data.partition(';')
            (x,trash,y) = topLeft.partition(',')
            x0 = float(x) / TEX_WIDTH
            y0 = float(y) / TEX_HEIGHT
            (x,trash,y) = bottomRight.partition(',')
            x1 = float(x) / TEX_WIDTH
            y1 = float(y) / TEX_HEIGHT
        elif command == 'level':
            level = Level()
            (coords, trash, rad_str) = data.partition(';')
            (x, trash, y) = coords.partition(',')
            level.x = float(x) *  2 / width  - 1
            level.y = float(y) * -2 / height + 1
            level.rad = float(rad_str)
            levels.append(level)
            
    # Write the data
    fout.write(struct.pack('ffffffff', -1,  1, 0, 0, 0, 1, x0, y0))
    fout.write(struct.pack('ffffffff',  1,  1, 0, 0, 0, 1, x1, y0))
    fout.write(struct.pack('ffffffff',  1, -1, 0, 0, 0, 1, x1, y1))
    fout.write(struct.pack('ffffffff', -1, -1, 0, 0, 0, 1, x0, y1))
    fout.write(struct.pack('H', len(levels)))
    for level in levels:
        fout.write(struct.pack('fff', level.x, level.y, level.rad))
    fin.close()
    fout.flush()
    fout.close()

if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
