#include <QApplication>

#include "view/3d_viewer/widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Model model;
  Controller *controller = Controller::Instance();
  controller->SetModel(&model);
  Widget view(controller);
  view.setWindowTitle("3dViewer v2.0");
  view.show();
  return a.exec();
}
