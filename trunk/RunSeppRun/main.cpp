/*
 * File:   main.cpp
 * Author: korn
 *
 * Created on 12 aprile 2010, 17.18
 */

#include <QtGui/QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    std::cout << "ciao\n";
    // create and show your widgets here

    return app.exec();
}
