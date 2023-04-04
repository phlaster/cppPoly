#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QWidget window;   
    window.resize(250, 150);
    window.setWindowTitle(argv[1]);
    window.show();

    return app.exec();
}
