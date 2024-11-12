#include "trackconfigdialog.h"
#include "ui_trackconfigdialog.h"

TrackConfigDialog::TrackConfigDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TrackConfigDialog)
{
  this->_vision = &this->_vision->singleton();
  ui->setupUi(this);
  this->init();

  this->_updateFrameTimer = new QTimer(this);
  connect(this->_updateFrameTimer,SIGNAL(timeout()),this,SLOT(updateFrame()));
  this->_updateFrameTimer->start(30);

}

TrackConfigDialog::~TrackConfigDialog()
{
  this->_updateFrameTimer->stop();
  delete this->_updateFrameTimer;
  delete ui;
}

void TrackConfigDialog::on_treeWidget_activated(const QModelIndex &index)
{
  this->ui->frame_KMeans->hide();
  this->_parentIndex = index.parent().row();
  this->_index = index.row();
  if(this->_parentIndex == DETECTION) {
    switch (this->_index) {
    case WHEREARETHOSE:
      this->_vision->setDetectionAlgorithm(WHEREARE_LABEL);

      break;
    case NONE:
      break;
    }
  }
  if(this->_parentIndex == TRACKING) {

  }

  this->showFrame();
}



void TrackConfigDialog::on_verticalSlider__MinSize_valueChanged(int value)
{
  this->ui->label_MinSize->setText(QString::number(value));
  this->setIntoPossitionProcessing(MINSIZE,value);
}

void TrackConfigDialog::on_verticalSlider__MaxSize_valueChanged(int value)
{
  this->ui->label_MaxSize->setText(QString::number(value));
  this->setIntoPossitionProcessing(MAXSIZE,value);
}

void TrackConfigDialog::on_verticalSlider__MinTeamSize_valueChanged(int value)
{
  this->ui->label_MinTeamSize->setText(QString::number(value));
  this->setIntoPossitionProcessing(MINTEAMSIZE,value);
}

void TrackConfigDialog::on_verticalSlider__MaxTeamSize_valueChanged(int value)
{
  this->ui->label_MaxTeamSize->setText(QString::number(value));
  this->setIntoPossitionProcessing(MAXTEAMSIZE,value);
}


void TrackConfigDialog::on_verticalSlider__MinSizeBall_valueChanged(int value)
{
  this->ui->label_MinBall->setText(QString::number(value));
  this->setIntoPossitionProcessing(MINSIZEBALL,value);
}

void TrackConfigDialog::on_verticalSlider__MaxSizeBall_valueChanged(int value)
{
  this->ui->label_MaxBall->setText(QString::number(value));
  this->setIntoPossitionProcessing(MAXSIZEBALL,value);
}

void TrackConfigDialog::readXML()
{
  cv::FileStorage fs(POSITION_PROCESSING_FILE,cv::FileStorage::READ);

  if(!fs.isOpened())
  {
    std::cout<<"Position Processing UI Xml - Position: Error diretorio";
    return;
  }
  cv::FileNode node = fs[DEFAULT];

  this->ui->verticalSlider__MinSize->setValue((int)node[MINSIZE]);
  this->on_verticalSlider__MinSize_valueChanged((int)node[MINSIZE]);
  this->ui->verticalSlider__MaxSize->setValue((int)node[MAXSIZE]);
  this->on_verticalSlider__MaxSize_valueChanged((int)node[MAXSIZE]);
  this->ui->verticalSlider__MaxTeamSize->setValue((int)node[MAXTEAMSIZE]);
  this->on_verticalSlider__MaxTeamSize_valueChanged((int)node[MAXTEAMSIZE]);
  this->ui->verticalSlider__MinTeamSize->setValue((int)node[MINTEAMSIZE]);
  this->on_verticalSlider__MinTeamSize_valueChanged((int)node[MINTEAMSIZE]);
  this->ui->verticalSlider__MinSizeBall->setValue((int)node[MINSIZEBALL]);
  this->on_verticalSlider__MinSizeBall_valueChanged((int)node[MINSIZEBALL]);
  this->ui->verticalSlider__MaxSizeBall->setValue((int)node[MAXSIZEBALL]);
  this->on_verticalSlider__MaxSizeBall_valueChanged((int)node[MAXSIZEBALL]);
  this->ui->comboBox_EnemySearch->setCurrentIndex((int) node[ENEMYSEARCH]);

  fs.release();


  fs.open(KMEANS_FILE,cv::FileStorage::READ);
  if(!fs.isOpened())
  {
    std::cout<<"Position Processing UI Xml - kmeans: Error diretorio";
    return;
  }
  node = fs[NUMCLUSTERS];

  this->on_verticalSlider_orange_valueChanged((int)node["clustersPerColor1"]);
  this->ui->verticalSlider_orange->setValue((int)node["clustersPerColor1"]);

  this->on_verticalSlider_blue_valueChanged((int)node["clustersPerColor2"]);
  this->ui->verticalSlider_blue->setValue((int)node["clustersPerColor2"]);

  this->on_verticalSlider_yellow_valueChanged((int)node["clustersPerColor3"]);
  this->ui->verticalSlider_yellow->setValue((int)node["clustersPerColor3"]);

  this->on_verticalSlider_red_valueChanged((int)node["clustersPerColor4"]);
  this->ui->verticalSlider_red->setValue((int)node["clustersPerColor4"]);

  this->on_verticalSlider_green_valueChanged((int)node["clustersPerColor5"]);
  this->ui->verticalSlider_green->setValue((int)node["clustersPerColor5"]);

  this->on_verticalSlider_pink_valueChanged((int)node["clustersPerColor6"]);
  this->ui->verticalSlider_pink->setValue((int)node["clustersPerColor6"]);

  this->on_verticalSlider_light_blue_valueChanged((int)node["clustersPerColor7"]);
  this->ui->verticalSlider_light_blue->setValue((int)node["clustersPerColor7"]);

  this->on_verticalSlider_purple_valueChanged((int)node["clustersPerColor8"]);
  this->ui->verticalSlider_purple->setValue((int)node["clustersPerColor8"]);

  this->on_verticalSlider_unknown_valueChanged((int)node["clustersPerColor9"]);
  this->ui->verticalSlider_unknown->setValue((int)node["clustersPerColor9"]);
  fs.release();
}

void TrackConfigDialog::showFrame()
{
  cv::Size newSize(this->ui->videoLabel->width(), this->ui->videoLabel->height());
  if(this->_PositionFrame.empty() || this->_PositionFrame.cols < 1 || this->_PositionFrame.rows <1)
  {
    this->_PositionFrame = cv::Mat::zeros(newSize,CV_8UC3);
  }
  cv::resize(this->_PositionFrame, this->_PositionFrame, newSize);
  cv::cvtColor(this->_PositionFrame, this->_PositionFrame, cv::COLOR_BGR2RGB);
  QImage qimg((uchar*)this->_PositionFrame.data, this->_PositionFrame.cols, this->_PositionFrame.rows, this->_PositionFrame.step, QImage::Format_RGB888);

  this->ui->videoLabel->setPixmap(QPixmap::fromImage(qimg));


}

void TrackConfigDialog::updateFrame()
{
//  CameraManager::singleton().getCurrentFrame(this->_PositionFrame);
  Vision::singleton().getDetectionFrame(this->_PositionFrame);
  this->showFrame();
}

void TrackConfigDialog::init()
{
  this->ui->frame_KMeans->hide();
  this->readXML();
  this->_parentIndex = DETECTION;
  this->_index = WHEREARETHOSE;
  _paletteColor[OrangeCOL].setColor( backgroundRole(), QColor(QString("orange")) );
  for(int i = NoCOL ; i < NUMBEROFCOLOR-1 ; i++) {
    _paletteColor[i].setColor( backgroundRole(), QColor(colorLabel[i]) );
  }
  ui->frame_orange->setPalette( _paletteColor[OrangeCOL] );
  ui->frame_orange->setAutoFillBackground( true );
  ui->frame_blue->setPalette( _paletteColor[BlueCOL] );
  ui->frame_blue->setAutoFillBackground( true );
  ui->frame_yellow->setPalette( _paletteColor[YellowCOL] );
  ui->frame_yellow->setAutoFillBackground( true );
  ui->frame_red->setPalette( _paletteColor[RedCOL] );
  ui->frame_red->setAutoFillBackground( true );
  ui->frame_green->setPalette( _paletteColor[GreenCOL] );
  ui->frame_green->setAutoFillBackground( true );
  ui->frame_pink->setPalette( _paletteColor[PinkCOL] );
  ui->frame_pink->setAutoFillBackground( true );
  ui->frame_light_blue->setPalette( _paletteColor[LightBlueCOL] );
  ui->frame_light_blue->setAutoFillBackground( true );
  ui->frame_purple->setPalette( _paletteColor[PurpleCOL] );
  ui->frame_purple->setAutoFillBackground( true );
  ui->frame_unknown->setPalette( _paletteColor[BrownCOL] );
  ui->frame_unknown->setAutoFillBackground( true );
}

void TrackConfigDialog::setIntoPossitionProcessing(std::string str, int value)
{
  if(this->_parentIndex == DETECTION) {
    this->_vision->setDetectionParam(str,value);
  }
  if(this->_parentIndex == TRACKING) {
    this->_vision->setTrackParam(str,value);
  }
}

void TrackConfigDialog::on_verticalSlider_orange_valueChanged(int value)
{
  this->ui->label_orange->setText(QString::number(value));
  this->setIntoPossitionProcessing(Orangek,value);
}

void TrackConfigDialog::on_verticalSlider_blue_valueChanged(int value)
{
  this->ui->label_blue->setText(QString::number(value));
  this->setIntoPossitionProcessing(Bluek,value);
}

void TrackConfigDialog::on_verticalSlider_yellow_valueChanged(int value)
{
  this->ui->label_yellow->setText(QString::number(value));
  this->setIntoPossitionProcessing(Yellowk,value);

}

void TrackConfigDialog::on_verticalSlider_red_valueChanged(int value)
{
  this->ui->label_red->setText(QString::number(value));
  this->setIntoPossitionProcessing(Redk,value);

}

void TrackConfigDialog::on_verticalSlider_green_valueChanged(int value)
{
  this->ui->label_green->setText(QString::number(value));
  this->setIntoPossitionProcessing(Greenk,value);

}

void TrackConfigDialog::on_verticalSlider_pink_valueChanged(int value)
{
  this->ui->label_pink->setText(QString::number(value));
  this->setIntoPossitionProcessing(Pinkk,value);

}

void TrackConfigDialog::on_verticalSlider_light_blue_valueChanged(int value)
{
  this->ui->label_light_blue->setText(QString::number(value));
  this->setIntoPossitionProcessing(LightBluek,value);

}

void TrackConfigDialog::on_verticalSlider_purple_valueChanged(int value)
{
  this->ui->label_purple->setText(QString::number(value));
  this->setIntoPossitionProcessing(Purplek,value);

}

void TrackConfigDialog::on_verticalSlider_unknown_valueChanged(int value)
{
  this->ui->label_unknown->setText(QString::number(value));
  this->setIntoPossitionProcessing(Brownk,value);

}

void TrackConfigDialog::on_pushButton_Reset_clicked()
{
  this->readXML();
}

void TrackConfigDialog::on_comboBox_EnemySearch_currentIndexChanged(int index)
{
  this->setIntoPossitionProcessing(ENEMYSEARCH,index);
}
