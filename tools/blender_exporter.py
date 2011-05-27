import bpy
import struct
from bpy.props import StringProperty, FloatProperty, BoolProperty, EnumProperty
from io_utils import ExportHelper

bl_info = {
    "name": "Marble Machine Exporter",
    "description": "Exports blend file to marble machine (.mp3) format",
    "author": "Leif Andersen",
    "version": (0,1),
    "blender": (2, 5, 7),
    "api": 31236,
    "location": "File > Export > Marble Machine",
    "warning": '', # used for warning icon and text in addons panel
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export "}

def save(operator,
         context, filepath="",
         use_selection=True,
         global_matrix=None,
         ):
    # Detect early signs of failure
    # If no meshes, abort
    if len(bpy.data.meshes) < 1 or len(bpy.data.meshes[0].uv_textures) < 1 or len(bpy.data.meshes[0].uv_textures[0].data) < len(bpy.data.meshes[0].faces):
        return {'FINISHED'}
    
    file = open(filepath, "wb")
    
    # Assume we're exporting the first mesh
    mesh = bpy.data.meshes[0]
    
    # Output num vertexes
    file.write(struct.pack("H", len(mesh.vertices)))
    
    # Output num indices
    faceCount = 0
    for face in mesh.faces:
        if len(face.vertices) < 3:
            continue
        faceCount += len(face.vertices) - 2
    indiceCount = faceCount*3
    file.write(struct.pack("H", indiceCount))
    
    # Output vertex data
    for vert in mesh.vertices:
        file.write(struct.pack("ffffff", vert.co[0], vert.co[1], vert.co[2], vert.normal[0], vert.normal[1], vert.normal[2]))
        # Just fart something out for now
        file.write(struct.pack("f", 0.0))
        file.write(struct.pack("f", 0.0))
    
    # Output incides
    for face in mesh.faces:
        if len(face.vertices) < 3:
            continue
        vert0 = face.vertices[0]
        prevVert = face.vertices[1]
        for vert in face.vertices:
            if vert == vert0 or vert == prevVert:
                continue
            file.write(struct.pack("HHH", vert0, prevVert, vert))
            prevVert = vert
    file.flush()
    file.close()
    return {'FINISHED'}

# Add to a menu
class ExportMarbleMachine(bpy.types.Operator, ExportHelper):
    bl_idname = "export_scene.marble_machine"
    bl_label = 'Export Marble Machine'

    filename_ext = ".mp3"
    filter_glob = StringProperty(default="*.mp3", options={'HIDDEN'})

    def execute(self, context):
        keywords = self.as_keywords(ignore=("axis_forward", "axis_up", "filter_glob", "check_existing"))
        return save(self, context, **keywords)

def menu_func_export(self, context):
    self.layout.operator(ExportMarbleMachine.bl_idname, text="Marble Machine")


def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()
