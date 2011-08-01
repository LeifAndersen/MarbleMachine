#include <QtGui/QApplication>
#include <QtGui>
#include "Mapper.h"

class TextureMapper : public QApplication {
public:
    TextureMapper(int& argc, char ** argv) : QApplication(argc, argv) { }
    virtual ~TextureMapper() { }

    // For teh debugz
    bool notify(QObject * rec, QEvent * ev)
    {
        try
        {
            return QApplication::notify(rec,ev);
        }
        catch(...)
        {
            QMessageBox::warning(0,
                                 tr("An unexpected error occurred"),
                                 tr("This is likely a bug."));
        }
        return false;
    }
};

int main(int argc, char *argv[])
{
    TextureMapper a(argc, argv);
    Mapper w;
    w.setWindowTitle("GravityWell Texture Mapper v0.4");
    w.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    w.show();

    return a.exec();
}
