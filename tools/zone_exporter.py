import struct
import sys

class level_obj:
    x = 1.0
    y = 1.0
    rad = 1.0
    num = 1

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

    # Read data
    for line in fin:
        (command, trash, data) = line.partition(':')
        if command == 'name':
            name = data
        else if command == 'coords':
            (topLeft, trash, bottomRight) = data.partition(';')
            (x,trash,y) = topLeft.partition(',')
            x0 = float(x)
            y0 = float(y)
            (x,trash,y) = bottomRight.partition(',')
            x1 = float(x)
            y1 = float(y)
        else if command == 'level':
            level = level_obj()
            (level_num, trash, rest) = data.partition(';')
            (coords, trash, rad_str) = rest.partition(';')
            (x, trash, y) = coords.partition(',')
            level.x = float(x)
            level.y = float(y)
            level.num = float(level_num)
            level.rad = float(rad_str)
            levels.append(level)
            
    # Write the data
    fout.write(struct.pack('ffffffff', -1,  1, 0, 0, 0, 1, x0, y0))
    fout.write(struct.pack('ffffffff',  1,  1, 0, 0, 0, 1, x1, y0))
    fout.write(struct.pack('ffffffff',  1, -1, 0, 0, 0, 1, x0, y1))
    fout.write(struct.pack('ffffffff', -1, -1, 0, 0, 0, 1, x1, y1))
    fout.write(struct.pack('H', len(levels))
    for level in levels:
        fout.write(struct.pack('H', level.num)
        fout.write(struct.pack('fff', level.x, level.y, level.rad)
    fin.close()
    fout.flush()
    fout.close()

if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
