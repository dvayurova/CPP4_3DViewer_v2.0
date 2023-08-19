#include "widget.h"

#include <iostream>

#include "ui_widget.h"

namespace s21 {

Widget::Widget(Controller *c, QWidget *parent)
    : QOpenGLWidget{parent}, ui(new Ui::Widget), controller_(c) {
  ui->setupUi(this);
  LabelSettings();

  file_exists = 0;
}

Widget::~Widget() {
  delete ui;
  //  delete int_validator;
  //  delete double_validator;
  //  delete scale_validator;
}

void Widget::on_pushButton_clicked() {
  QString str;
  str = QFileDialog::getOpenFileName(this, "Выбрать файл", "/Users",
                                     "All Files (*.obj)");
  ui->label_filename->setText(str);
  //  QByteArray s = str.toLocal8Bit();
  //  char *filename = s.data();
  std::string filename = str.toStdString();
  std::cout << "file = " << filename << std::endl;
  if (!filename.empty()) {
    if (controller_->ReadDataFile(filename)) {
      file_exists = 1;
      SetDefaultValues();
      controller_->Normalize();
      ui->label_Vertexes->setText(
          QString::number(controller_->GetVertexCount()));
      ui->label_edges->setText(QString::number(controller_->GetEdgesCount()));
      update();
    } else {
      ui->label_filename->setText("FILE NOT FOUND OR INCORRECT!(");
      file_exists = 0;
    }
  }
}

void Widget::SetDefaultValues() {
  ui->z_rotation->setValue(0);
  ui->y_rotation->setValue(0);
  ui->x_rotation->setValue(0);
  ui->label_x_rot->setText("0");
  ui->label_y_rot->setText("0");
  ui->label_z_rot->setText("0");
  ui->label_x_move->setText("0");
  ui->label_y_move->setText("0");
  ui->label_z_move->setText("0");
}

void Widget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Widget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Widget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (file_exists)
    draw();
}

void Widget::draw() {

  glVertexPointer(3, GL_DOUBLE, 0, controller_->GetVertexes());
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_LINES, controller_->GetFacetsCount(), GL_UNSIGNED_INT,
                 controller_->GetFacets());

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Widget::on_button_scale_down_clicked() {
  double scale_value = ui->label_scale->text().toDouble();
  if (file_exists && scale_value > 0.01) {
    scale_value += kStepDown;
    controller_->ChangeModel("scale", scale_value, 0);
    ui->label_scale->setText(QString::number(scale_value, 'f', 2));
    update();
  }
}

void Widget::on_button_scale_up_clicked() {
  if (file_exists) {
    double scale_value = ui->label_scale->text().toDouble() + kStepUp;
    controller_->ChangeModel("scale", scale_value, 0);
    ui->label_scale->setText(QString::number(scale_value, 'f', 2));
    update();
  }
}

void Widget::on_label_scale_textEdited(const QString &arg1) {
  double scale_value = arg1.toDouble();
  if (file_exists && scale_value > 0.01) {
    controller_->ChangeModel("scale", scale_value, 0);
    update();
  }
}

void Widget::on_x_rotation_valueChanged(int value) {
  controller_->ChangeModel("rotate", (double)value, kX);
  update();
}

void Widget::on_y_rotation_valueChanged(int value) {
  controller_->ChangeModel("rotate", (double)value, kY);
  update();
}

void Widget::on_z_rotation_valueChanged(int value) {
  controller_->ChangeModel("rotate", (double)value, kZ);
  update();
}

void Widget::on_label_x_move_textEdited(const QString &arg1) {
  controller_->ChangeModel("move", arg1.toDouble(), kX);
  update();
}

void Widget::on_label_y_move_textEdited(const QString &arg1) {
  controller_->ChangeModel("move", arg1.toDouble(), kY);
  update();
}

void Widget::on_label_z_move_textEdited(const QString &arg1) {
  controller_->ChangeModel("move", arg1.toDouble(), kZ);
  update();
}

void Widget::on_x_move_down_clicked() {
  double move_step = ui->label_x_move->text().toDouble() + kStepDown;
  controller_->ChangeModel("move", move_step, kX);

  ui->label_x_move->setText(QString::number(move_step));
  update();
}

void Widget::on_x_move_up_clicked() {
  double move_step = ui->label_x_move->text().toDouble() + kStepUp;
  controller_->ChangeModel("move", move_step, kX);
  ui->label_x_move->setText(QString::number(move_step));
  update();
}

void Widget::on_y_move_down_clicked() {
  double move_step = ui->label_y_move->text().toDouble() + kStepDown;
  controller_->ChangeModel("move", move_step, kY);
  ui->label_y_move->setText(QString::number(move_step));
  update();
}

void Widget::on_y_move_up_clicked() {
  double move_step = ui->label_y_move->text().toDouble() + kStepUp;
  controller_->ChangeModel("move", move_step, kY);
  ui->label_y_move->setText(QString::number(move_step));
  update();
}

void Widget::on_z_move_down_clicked() {
  double move_step = ui->label_z_move->text().toDouble() + kStepDown;
  controller_->ChangeModel("move", move_step, kZ);
  ui->label_z_move->setText(QString::number(move_step));
  update();
}

void Widget::on_z_move_up_clicked() {
  double move_step = ui->label_z_move->text().toDouble() + kStepUp;
  controller_->ChangeModel("move", move_step, kZ);
  ui->label_z_move->setText(QString::number(move_step));
  update();
}

void Widget::LabelSettings() {
  QIntValidator *int_validator = new QIntValidator(-180, 180, this);
  ui->label_x_rot->setValidator(int_validator);
  ui->label_y_rot->setValidator(int_validator);
  ui->label_z_rot->setValidator(int_validator);
  QDoubleValidator *double_validator = new QDoubleValidator(-1, 1, 2, this);
  double_validator->setNotation(QDoubleValidator::StandardNotation);
  ui->label_x_move->setValidator(double_validator);
  ui->label_y_move->setValidator(double_validator);
  ui->label_z_move->setValidator(double_validator);
  QDoubleValidator *scale_validator = new QDoubleValidator(0.01, 2.5, 2, this);
  scale_validator->setNotation(QDoubleValidator::StandardNotation);
  ui->label_scale->setValidator(scale_validator);
  ConnectLabels();
}

void Widget::ConnectLabels() {
  connect(ui->x_rotation, &QScrollBar::sliderMoved, this, [=] {
    ui->label_x_rot->setText(QString::number(ui->x_rotation->value()));
  });
  connect(ui->label_x_rot, &QLineEdit::textChanged, this,
          [=] { ui->x_rotation->setValue(ui->label_x_rot->text().toInt()); });

  connect(ui->y_rotation, &QScrollBar::sliderMoved, this, [=] {
    ui->label_y_rot->setText(QString::number(ui->y_rotation->value()));
  });
  connect(ui->label_y_rot, &QLineEdit::textChanged, this,
          [=] { ui->y_rotation->setValue(ui->label_y_rot->text().toInt()); });

  connect(ui->z_rotation, &QScrollBar::sliderMoved, this, [=] {
    ui->label_z_rot->setText(QString::number(ui->z_rotation->value()));
  });
  connect(ui->label_z_rot, &QLineEdit::textChanged, this,
          [=] { ui->z_rotation->setValue(ui->label_z_rot->text().toInt()); });
}

} // namespace s21