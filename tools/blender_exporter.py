import bpy
import struct
import sys

def save(filepath):
    # Detect early signs of failure
    # If no meshes, abort
    if len(bpy.data.meshes) < 1 or len(bpy.data.meshes[0].uv_textures) < 1 or len(bpy.data.meshes[0].uv_textures[0].data) < len(bpy.data.meshes[0].faces):
        return {'FINISHED'}
    
    file = open(filepath, "wb")
    
    # Assume we're exporting the first mesh
    mesh = bpy.data.meshes[0]
    
    # Get the number of verts (and uvs)
    vertUVs = {}
    numVerts = 0
    for i in range(len(mesh.faces)):
        for j in range(len(mesh.faces[i].vertices)):
            vert = mesh.faces[i].vertices[j]
            try:
                notInDict = True
                for pair in vertUVs[vert]:
                    if pair == mesh.uv_textures[0].data[i].uv[j][:]:
                        notInDict = False
                        break
                if notInDict:
                   vertUVs[vert].append(mesh.uv_textures[0].data[i].uv[j][:])
                   numVerts+=1
            except KeyError:
                vertUVs[vert] = [mesh.uv_textures[0].data[i].uv[j][:]]
                numVerts+=1

    # Output num vertexes
    file.write(struct.pack("H", numVerts))
    
    # Output num indices
    faceCount = 0
    for face in mesh.faces:
        if len(face.vertices) < 3:
            continue
        faceCount += len(face.vertices) - 2
    indiceCount = faceCount*3
    file.write(struct.pack("H", indiceCount))
    
    # Output vertex data
    vertUVindices = {}
    i = 0
    for j in range(len(mesh.vertices)):
        vert = mesh.vertices[j]
        for vertUV in vertUVs[j]:
            # Coordinates and normal
            file.write(struct.pack("ffffff", vert.co[0], vert.co[1], vert.co[2], vert.normal[0], vert.normal[1], vert.normal[2]))
            # UV data
            file.write(struct.pack("ff", vertUV[0], vertUV[1]))
            # For writing indices out
            vertUVindices[j] = i
            i+=1 
    
    # Output incides
    for i in range(len(mesh.faces)):
        face = mesh.faces[i]
        if len(face.vertices) < 3:
            continue
        vert0 = face.vertices[0]
        vert0index = vert0
        j = 0
        for pair in vertUVs[face.vertices[0]]:
            if pair == mesh.uv_textures[0].data[i].uv[0][:]:
                vert0 = vertUVindices[face.vertices[0]] + j
                break
            j+=1
        prevVert = face.vertices[1]
        prevVertIndex = prevVert
        j = 0
        for pair in vertUVs[face.vertices[1]]:
            if pair == mesh.uv_textures[0].data[i].uv[1][:]:
                prevVert = vertUVindices[face.vertices[1]] + j
                break
            j+=1
        for k in range(len(face.vertices)):
            vert = face.vertices[k]
            if vert == vert0index or vert == prevVertIndex:
                continue
            j = 0
            for pair in vertUVs[face.vertices[k]]:
                if pair == mesh.uv_textures[0].data[i].uv[k][:]:
                    vert = vertUVindices[face.vertices[k]] + j
                    break
                j+=1
            file.write(struct.pack("HHH", vert0, prevVert, vert))
            prevVert = vert
    file.flush()
    file.close()
    return {'FINISHED'}

if __name__ == '__main__':
     save(sys.argv[6])
