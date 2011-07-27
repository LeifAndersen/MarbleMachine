import struct
import sys


class Sector:
    x = 1.0
    y = 1.0
    rad = 1.0

def save(infile_name, outfile_name):
    fin = open(infile_name, 'r')
    fout = open(outfile_name, 'wb')
    sectors = []
    name = ""
    x0 = 1.0
    x1 = 1.0
    y0 = 1.0
    y1 = 1.0
    width = 1024
    height = 1024

    # Read the data
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
            x0 = float(x) *  2 / width  - 1
            y0 = float(y) * -2 / height + 1
            (x,trash,y) = bottomRight.partition(',')
            x1 = float(x) *  2 / width  - 1
            y1 = float(y) * -2 / height + 1
        elif command == 'sector':
            sector = Sector()
            (coords, trash, rad_str) = data.partition(';')
            (x, trash, y) = coords.partition(',')
            sector.x = float(x) *  2 / width  - 1
            sector.y = float(y) * -2 / height + 1
            sector.rad = float(rad_str) / width
            sectors.append(sector)

    # Write data
    fout.write(struct.pack('ffffffff', -1,  1, 0, 0, 0, 1, x0, y0))
    fout.write(struct.pack('ffffffff',  1,  1, 0, 0, 0, 1, x1, y0))
    fout.write(struct.pack('ffffffff',  1, -1, 0, 0, 0, 1, x1, y1))
    fout.write(struct.pack('ffffffff', -1, -1, 0, 0, 0, 1, x0, y1))
    fout.write(struct.pack('H', len(sectors)))
    for sector in sectors:
        fout.write(struct.pack('fff', sector.x, sector.y, sector.rad))
    fin.close()
    fout.flush()
    fout.close()

if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
