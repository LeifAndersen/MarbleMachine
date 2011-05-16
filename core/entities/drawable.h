#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{
public:
    Drawable();
    static void loadData();
    virtual void draw();
private:
    static std::vector<int> verts;
    static std::vector<int> triangle_faces;
};

#endif // DRAWABLE_H
