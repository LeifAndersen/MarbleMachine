#include <QtGui/QApplication>
#include "Editor.h"

class GravityWellLevelEditor : public QApplication {
public:
    GravityWellLevelEditor(int& argc, char ** argv) : QApplication(argc, argv) { }
    virtual ~GravityWellLevelEditor() { }

    // For teh debugz
    bool notify(QObject * rec, QEvent * ev)
    {
        try
        {
            return QApplication::notify(rec,ev);
        }
        catch(boost::bad_lexical_cast)
        {
            QMessageBox::warning(0,
                                 tr("An unexpected error occurred"),
                                 tr("Bad lexical cast.  Something corrupted the saved level."));
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
    GravityWellLevelEditor a(argc, argv);
    Editor w;
    w.setWindowTitle("GravityWell Level Editor v1.0");
    w.show();

    return a.exec();
}
