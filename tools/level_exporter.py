import struct
import sys

def save(infile_path, outfile_path):
    fin = open(infile_path)
    fout = open(outfile_path)
    for line in fin:
        pass
    fout.flush()
    fout.close()
    fin.close()


if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
