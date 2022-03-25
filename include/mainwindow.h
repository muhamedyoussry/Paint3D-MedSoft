#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkNew.h>
#include <vtkNamedColors.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h>
#include <vtkInteractorStyleTrackballActor.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionAbout_triggered();

private:
	Ui::MainWindow *ui;
	vtkNew<vtkNamedColors> colors;
	vtkNew<vtkRenderer> renderer;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkNew<QVTKInteractor> mInteractor;
	vtkNew<vtkInteractorStyleTrackballActor> mInteractorStyle;


public slots:
	void onDrawCube();
	void onDrawSphere();
	void onDrawCylinder();
	void onDrawCone();
	void onDrawPyramid();
	void onDrawText();
	void buttonsClicked();
};
#endif // MAINWINDOW_H
