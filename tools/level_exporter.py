import struct
import sys

class entity:
    x = 1.0
    y = 1.0
    vx = 1.0
    vy = 1.0
    mass = 1.0
    radius = 1.0

def parse_line(line, ent):
    (coords, trash, rest) = data.partition(';')
    (velocity_coords, trash, rest) = rest.partition(';')
    (mass, trash, radius) = rest.partition(';')
    (x, trash, y) = coords.partition(',')
    (vx, trash, vy) = coords.partition(',')
    ent.x = float(x)
    ent.y = float(y)
    ent.vx = float(vx)
    ent.vy = float(vy)
    ent.mass = float(mass)
    ent.radius = float(radius)

def save(infile_path, outfile_path):
    # Data for parsing
    fin = open(infile_path)
    fout = open(outfile_path)
    name = ""
    ship = entity()
    goal = entity()
    planets = []

    # Get the data
    for line in fin:
        (data_type, trash, data) = line.partition(':')
        if data_type == 'ship':
            parse_line(data, ship)
        elif data_type == 'goal':
            parse_line(data, goal)
        elif data_type == 'planet':
            temp = entity()
            parse_line(data, temp)
            planets.append(temp)
        elif data_type == 'name':
            name = data

    # Write the data
    fout.write(struct.pack('ffffff', ship.x, ship.y, ship.vx, ship.vy, ship.mass, ship.radius))
    fout.write(struct.pack('ffffff', goal.x, goal.y, goal.vx, goal.vy, goal.mass, goal.radius))
    fout.write(struct.pack('H', len(planets))
    for planet in planets:
        fout.write(struct.pack('ffffff', planet.x, planet.x, planet.vx, planet.vy, planet.mass, planet.radius))
    fout.flush()
    fout.close()
    fin.close()


if __name__ == '__main__':
    save(sys.argv[5], sys.argv[6])
