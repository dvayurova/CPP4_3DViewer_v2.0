#ifndef WIDGET_H
#define WIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#include "../../controller/controller_singleton.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

namespace s21 {
class Widget : public QOpenGLWidget {
  Q_OBJECT

public:
  Widget(Controller *c, QWidget *parent = nullptr);
  ~Widget();

private:
  Ui::Widget *ui;
  Controller *controller_;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void draw();

  void LabelSettings();
  void ConnectLabels();
  void SetDefaultValues();
  static constexpr double kStepDown = -0.01;
  static constexpr double kStepUp = 0.01;
  int file_exists;

private slots:
  void on_pushButton_clicked();
  void on_button_scale_down_clicked();
  void on_button_scale_up_clicked();
  void on_label_scale_textEdited(const QString &arg1);
  void on_label_x_move_textEdited(const QString &arg1);
  void on_label_y_move_textEdited(const QString &arg1);
  void on_label_z_move_textEdited(const QString &arg1);
  void on_x_rotation_valueChanged(int value);
  void on_y_rotation_valueChanged(int value);
  void on_z_rotation_valueChanged(int value);
  void on_x_move_down_clicked();
  void on_x_move_up_clicked();
  void on_y_move_down_clicked();
  void on_y_move_up_clicked();
  void on_z_move_down_clicked();
  void on_z_move_up_clicked();
};

} // namespace s21
#endif // WIDGET_H
