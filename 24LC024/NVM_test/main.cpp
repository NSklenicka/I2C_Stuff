#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    throw std::runtime_error("alkd");

    return a.exec();
}
