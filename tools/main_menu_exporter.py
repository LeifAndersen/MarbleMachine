import struct
import sys

class Sector:
    x = 1.0
    y = 1.0
    rad = 1.0

def save(infline_name, outfile_name):
    fin = open(infile_name, 'r')
    fout = open(outfile_name, 'wb')
    sectors = []
    name = ""
    x1 = 1.0
    x2 = 1.0
    y1 = 1.0
    y2 = 1.0

    # Read the data
    for line in fin:
        (command, trash, data) = line.partition(':')

    if command == 'name':
        name = data
    elif command == 'coords':
        (topLeft, trash, bottomRight) = data.partition(';')
        (x,trash,y) = topLeft.partition(',')
        x0 = float(x)
        y0 = float(y)
        (x,trash,y) = bottomRight.partition(',')
        x1 = float(x)
        y1 = float(y)
    elif command == 'sector':
        sector = Sector()
        (coords, trash, rad_str) = data.partition(';')
        (x, trash, y) = coords.partition(',')
        level.x = float(x)
        level.y = float(y)
        level.num = float(level_num)
        level.rad = float(rad_str)
        levels.append(level)

    # Write data
    fout.write(struct.pack('ffffffff', -1,  1, 0, 0, 0, 1, x0, y0))
    fout.write(struct.pack('ffffffff',  1,  1, 0, 0, 0, 1, x1, y0))
    fout.write(struct.pack('ffffffff',  1, -1, 0, 0, 0, 1, x0, y1))
    fout.write(struct.pack('ffffffff', -1, -1, 0, 0, 0, 1, x1, y1))
    fout.write(struct.pack('H', len(levels)))
    for sector in sectors:
        fout.write(struct.pack('fff', sector.x, sector.y, sector.rad))
    fin.close()
    fout.flush()
    fout.close()

if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
