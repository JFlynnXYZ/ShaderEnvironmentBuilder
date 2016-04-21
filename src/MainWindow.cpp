#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QsciLexerGlsl.h"
#include "CebErrors.h"
#include "QString"
#include <QTextStream>

MainWindow::MainWindow(QWidget *_parent) : QMainWindow(_parent),
                                           m_ui(new Ui::MainWindow)
{
  // Setup ui from form creator (MainWindow.ui)
  m_ui->setupUi(this);
  // create parser in main window
  m_parForButton = new parserLib;
  // Create openGl and qsci widgets, pass in the parser
  m_gl=new  NGLScene(this, m_parForButton);

  m_gl->setSizePolicy(m_ui->m_f_gl_temp->sizePolicy());
  m_gl->setMinimumSize(m_ui->m_f_gl_temp->minimumSize());

  // add the openGl window to the interface
  m_ui->m_splitH_editContext->insertWidget(0, m_gl);

  // Delete the template frame from the form designer
  delete(m_ui->m_f_gl_temp);

  // Widget 1 (vertex)
  m_qsci1 = createQsciWidget(m_ui->m_tab_qsci_1);

  // Widget 2 (fragment)
  m_qsci2 = createQsciWidget(m_ui->m_tab_qsci_2);

  // Set the combo box values for the shader type
  m_ui->m_cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::VERTEX),
                                  "Vertex Shader");
  m_ui->m_cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::FRAGMENT),
                                  "Fragment Shader");
  m_ui->m_cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::COMPUTE),
                                  "Compute Shader");

  // Set the combo box initially to VERTEX
  m_ui->m_cb_shaderType->setCurrentIndex(static_cast<int>(
                                         ngl::ShaderType::VERTEX));
  // Camera Settings
   connect(m_ui->m_sldr_cameraAspect,SIGNAL(valueChanged(int)),m_gl,SLOT(setCameraFocalLength(int)));
 //connect(m_ui->m_comboBox_view, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(m_ui->m_cameraRoll(0.00));
   //void QTableWidget::itemChanged((QTableWidgetItem * m_ui->m_comboBox_view)), this, SLOT(m_ui->m_comboBox_view)
   //connect(m_ui->m_sldr_cameraAspect, SIGNAL(valueChanged(int)), m_ui, SLOT()
   connect(m_ui->m_cameraRoll, SIGNAL(valueChanged(double)), m_gl, SLOT(setCameraRoll(double)));
   connect(m_ui->m_cameraYaw, SIGNAL(valueChanged(double)), m_gl, SLOT(setCameraYaw(double)));
   connect(m_ui->m_comboBox_view, SIGNAL(currentTextChanged(QString)), m_gl, SLOT(setCameraShape(QString)));
   //connect(m_ui->m_btn_view, SIGNAL(clicked(bool), m_gl, SLOT(setCameraShape(string));
  // Load the text files into the corresponding tabs
  loadTextFileToTab("shaders/PhongVertex.glsl", *m_qsci1);
  loadTextFileToTab("shaders/PhongFragment.glsl", *m_qsci2);

  //std::cerr<<"Find number of active uniforms: "<<m_parForButton->m_num<<std::endl;

}

//----------------------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete m_ui;
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_btn_loadShader_clicked()
{

}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_btn_compileShader_clicked()
{
  QString vertSource, fragSource;
  vertSource = m_qsci1->text();
  fragSource = m_qsci2->text();
  m_gl->compileShader(vertSource, fragSource);
  m_parForButton->printUniforms(1);
  createButtons();
}

void MainWindow::printUniforms()
{
  m_parForButton->printUniforms(1);
}

void MainWindow::createButtons()
{
  for(unsigned int i=0;i<m_parForButton->m_num; ++i)
  {
    if(m_parForButton->m_uniformList[i]->getTypeName()=="vec4")
    {
      QString _tempName = QString::fromStdString(m_parForButton->m_uniformList[i]->getName());
      ngl::Vec4 _tempVec=m_parForButton->m_uniformList[i]->getVec4();
      Button *tempButton = new Button(_tempName, m_ui->vl_uniforms, _tempVec, m_ui->m_w_uniforms);

      m_buttonList.push_back(tempButton);
    }
  }
  std::cerr<<"THIS IS THE BUTTON LIST LENGTH: "<<m_buttonList.size()<<std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_tabs_qsci_currentChanged(int _index)
{
  // On switch of tab, change the combo box value to the corresponding tab type
  switch (_index)
  {
    case 0:
      m_ui->m_cb_shaderType->setCurrentIndex(static_cast<int>(
                                               ngl::ShaderType::VERTEX));
    break;

    case 1:
      m_ui->m_cb_shaderType->setCurrentIndex(static_cast<int>(
                                               ngl::ShaderType::FRAGMENT));
    break;

    default:
      std::cerr<< "ERROR: Tab id is not recognised\n";
  }

}

//----------------------------------------------------------------------------------------------------------------------
Cebitor *MainWindow::createQsciWidget(QWidget *_parent)
{
  // Create the QsciScintilla widget
  Cebitor* qsci = new Cebitor(_parent);
  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(qsci);
  _parent->setLayout(layout);

  return qsci;
}
//----------------------------------------------------------------------------------------------------------------------
bool MainWindow::loadTextFileToTab(QString _path, Cebitor &_qsci)
{
  QString text;
  QFile file(_path);

  // Open the file as readonly and text and ensure it loaded correctly
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    // Raise an error if failed
    ceb_raise::QtFileError(file.error(), _path);
    return false;
  }

  // Fead the text into the tab if successful
  QTextStream in(&file);
  text = in.readAll();
  _qsci.setText(text);

  return true;
}

void MainWindow::updateTerminalText(QString _txt)
{
  m_ui->m_pte_terminal->setPlainText(_txt);
}
