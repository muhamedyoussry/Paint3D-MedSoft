#include <mainwindow.h>
#include "ui_mainwindow.h"

#include <QImage>
#include <QFileDialog>
#include <QString>
#include <about.h>
#include <qbytearray.h>
#include <qvariant.h>

#include <vtkNew.h>
#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkTextActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkVersion.h>
#include <vtkTextProperty.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	// set buttons Icon
	QPixmap cubePixmap("assets/cube.png");
	QIcon cubeButtonIcon(cubePixmap);
	ui->cubeButton->setIcon(cubeButtonIcon);
	// set sphere Button Icon
	QPixmap spherePixmap("assets/Sphere.png");
	QIcon sphereButtonIcon(spherePixmap);
	ui->sphereButton->setIcon(sphereButtonIcon);
	// set cylinder Button Icon
	QPixmap cylinderPixmap("assets/cylinder.png");
	QIcon cylinderButtonIcon(cylinderPixmap);
	ui->cylinderButton->setIcon(cylinderButtonIcon);
	// set cone Button Icon
	QPixmap conePixmap("assets/cone.png");
	QIcon coneButtonIcon(conePixmap);
	ui->coneButton->setIcon(coneButtonIcon);
	// set pyramid Button Icon
	QPixmap pyramidPixmap("assets/pyramid.png");
	QIcon pyramidButtonIcon(pyramidPixmap);
	ui->pyramidButton->setIcon(pyramidButtonIcon);
	// set text Button Icon
	QPixmap textPixmap("assets/text.png");
	QIcon textButtonIcon(textPixmap);
	ui->textButton->setIcon(textButtonIcon);


	// edit some User Interface properties
	ui->pyramidButton->setEnabled(false);
	ui->textEdit->setPlaceholderText("Leave your sign on the paint, by writing your name here and inserting a text.");


	// Create a renderer, render window, and interactor
	mInteractor->SetInteractorStyle(mInteractorStyle);
	mInteractor->Initialize();

	ui->openGLWidget->setRenderWindow(renderWindow);
	renderWindow->SetInteractor(mInteractor);
	ui->openGLWidget->renderWindow()->AddRenderer(renderer);


	// Add the actors to the scene
	renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

	// Render and interact
	ui->openGLWidget->renderWindow()->SetWindowName(
		"Paint3D | MedSoft");


	// Signal and Slots checked
	buttonsClicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_triggered()
{
    QImage img = ui->openGLWidget->grabFramebuffer();
    QString fileName =  QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));
    if (!fileName.isEmpty())
    {
      img.save(fileName);
    }
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}


void MainWindow::on_actionAbout_triggered()
{
    About *aboutDialog = new About(this);
    aboutDialog->show();
}

void MainWindow::onDrawCube() {
	// Cube
	vtkNew<vtkCubeSource> cubeSource;
	cubeSource->Update();
	vtkNew<vtkPolyDataMapper> cubeMapper;
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
	vtkNew<vtkActor> cubeActor;
	cubeActor->SetMapper(cubeMapper);

	// pick the color from the combo box
	QString colorVariant = ui->colorComboBox->currentText();
	vtkStdString colorStd = colorVariant.toStdString();

	cubeActor->GetProperty()->SetColor(colors->GetColor4d(colorStd).GetData());
	cubeActor->SetPosition(0, 0, -10);

	renderer->AddActor(cubeActor);
	renderer->Render();
}

void MainWindow::onDrawSphere() {
	// Sphere
	vtkNew<vtkSphereSource> sphereSource;
	sphereSource->Update();
	vtkNew<vtkPolyDataMapper> sphereMapper;
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkNew<vtkActor> sphereActor;
	sphereActor->SetMapper(sphereMapper);

	// pick the color from the combo box
	QString colorVariant = ui->colorComboBox->currentText();
	vtkStdString colorStd = colorVariant.toStdString();

	sphereActor->GetProperty()->SetColor(colors->GetColor4d(colorStd).GetData());
	sphereActor->SetPosition(0, 0, -10);

	renderer->AddActor(sphereActor);
	renderer->Render();

}


void MainWindow::onDrawCylinder() {
	// Cylinder
	vtkNew<vtkCylinderSource> cylinderSource;
	cylinderSource->Update();
	vtkNew<vtkPolyDataMapper> cylinderMapper;
	cylinderMapper->SetInputConnection(cylinderSource->GetOutputPort());
	vtkNew<vtkActor> cylinderActor;
	cylinderActor->SetMapper(cylinderMapper);

	// pick the color from the combo box
	QString colorVariant = ui->colorComboBox->currentText();
	vtkStdString colorStd = colorVariant.toStdString();

	cylinderActor->GetProperty()->SetColor(colors->GetColor4d(colorStd).GetData());
	cylinderActor->SetPosition(0, 0, -10);

	renderer->AddActor(cylinderActor);
	renderer->Render();
}
void MainWindow::onDrawCone() {
	// Cone
	vtkNew<vtkConeSource> coneSource;
	coneSource->Update();
	vtkNew<vtkPolyDataMapper> coneMapper;
	coneMapper->SetInputConnection(coneSource->GetOutputPort());
	vtkNew<vtkActor> coneActor;
	coneActor->SetMapper(coneMapper);

	// pick the color from the combo box
	QString colorVariant = ui->colorComboBox->currentText();
	vtkStdString colorStd = colorVariant.toStdString();

	coneActor->GetProperty()->SetColor(colors->GetColor4d(colorStd).GetData());
	coneActor->SetPosition(0, 0, -10);

	renderer->AddActor(coneActor);
	renderer->Render();
}
void MainWindow::onDrawPyramid() {

}
void MainWindow::onDrawText() {
	// Text
	vtkNew<vtkTextActor> txt;

	// get the input from the text edit
	QString text = ui->textEdit->toPlainText();
	QByteArray textArr = text.toLocal8Bit();
	const char *NameSign = textArr.data();
	txt->SetInput(NameSign);

	// edit text properties
	vtkTextProperty* txtprop = txt->GetTextProperty();
	txtprop->SetFontFamilyToArial();
	txtprop->BoldOn();
	txtprop->SetFontSize(36);
	txtprop->ShadowOn();
	txtprop->SetShadowOffset(4, 4);

	// pick the color from the combo box
	QString colorVariant = ui->colorComboBox->currentText();
	vtkStdString colorStd = colorVariant.toStdString();

	txtprop->SetColor(colors->GetColor3d(colorStd).GetData());

	// Assign actor to the renderer.
	renderer->AddActor(txt);
	renderer->Render();

}

void MainWindow::buttonsClicked() {
	connect(ui->cubeButton, SIGNAL(clicked()), this, SLOT(onDrawCube()));
	connect(ui->sphereButton, SIGNAL(clicked()), this, SLOT(onDrawSphere()));
	connect(ui->cylinderButton, SIGNAL(clicked()), this, SLOT(onDrawCylinder()));
	connect(ui->coneButton, SIGNAL(clicked()), this, SLOT(onDrawCone()));
	connect(ui->pyramidButton, SIGNAL(clicked()), this, SLOT(onDrawPyramid()));
	connect(ui->textButton, SIGNAL(clicked()), this, SLOT(onDrawText()));
}