// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "qtshanoirDataSource.h"
#include "qtshanoirDataSourceToolBox.h"

#include <medCore/medAbstractDataSourceFactory.h>
#include <medGui/medToolBox.h>

#include <QtShanoir.h>
#include <QtShanoirTreeWidget.h>
#include <QtShanoirSettingsWidget.h>

#include <dtkCore/dtkAbstractDataReader.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>


// /////////////////////////////////////////////////////////////////
// qtshanoirDataSourcePrivate
// /////////////////////////////////////////////////////////////////

class qtshanoirDataSourcePrivate
{
public:
  QtShanoirTreeWidget *mainWidget;
	QtShanoirSettingsWidget *rightWidget;
  
  QString lastSuccessfulReaderDescription;
  
  QList <medToolBox *> additional_toolboxes;
};

// /////////////////////////////////////////////////////////////////
// qtshanoirDataSource
// /////////////////////////////////////////////////////////////////

qtshanoirDataSource::qtshanoirDataSource(void) : medAbstractDataSource(), d(new qtshanoirDataSourcePrivate)
{
	d->mainWidget = NULL;
	d->rightWidget = NULL;

  d->additional_toolboxes.clear();
  d->additional_toolboxes.push_back(new qtshanoirDataSourceToolBox);
  
  connect(d->additional_toolboxes.back(),SIGNAL(importButtonPressed()),this,SLOT(onImportData()));
  connect(d->additional_toolboxes.back(),SIGNAL(findButtonPressed()),this,SLOT(find()));
}

QWidget *qtshanoirDataSource::mainViewWidget()
{
	if (d->mainWidget)
		return d->mainWidget;
	
	initWidgets(); 
	return d->mainWidget;
}

QWidget *qtshanoirDataSource::sourceSelectorWidget()
{
	if (d->rightWidget)
		return d->rightWidget;
	
	initWidgets(); 
	return d->rightWidget;	
}

void qtshanoirDataSource::initWidgets(void)
{
	if(d->mainWidget && d->rightWidget)
	  return;
  
	if(!d->mainWidget)
    d->mainWidget = new QtShanoirTreeWidget();
	
	if(!d->rightWidget)
		d->rightWidget = new QtShanoirSettingsWidget();
	
	QtShanoir::instance()->attachTreeWidget(d->mainWidget);
	QtShanoir::instance()->init();     
}

qtshanoirDataSource::~qtshanoirDataSource(void)
{
	delete d;  
	d = NULL;
}

bool qtshanoirDataSource::registered(void)
{
  return medAbstractDataSourceFactory::instance()->registerDataSource("qtshanoirDataSource", createQtshanoirDataSource);
}

QString qtshanoirDataSource::description(void) const
{
  return "qtshanoirDataSource";
}

QString qtshanoirDataSource::tabName()
{
	return QString("Shanoir");
}

void qtshanoirDataSource::onImportData()
{
	QString tmpDirName = QDir::tempPath();	
	
	connect(QtShanoir::instance(),SIGNAL(downloadFinished(QString,QString)),this,SLOT(onDownloadFinished(QString,QString)));
	
  QtShanoir::instance()->setDownloadMetadata(Qt::Checked);
	QtShanoir::instance()->downloadToDir(tmpDirName);
}

void qtshanoirDataSource::onDownloadFinished(QString fileName, QString xmlName)
{
  //emit dataReceived(fileName);
  
  QFileInfo fileInfo(fileName);
  
  dtkAbstractData* data = 0;
  
  dtkAbstractDataReader* dataReader = this->getSuitableReader(QStringList(fileInfo.filePath()));

  if (dataReader)
  {
    qDebug() << dataReader->description();
    dataReader->read(fileInfo.filePath());
    //dataReader->read();
    data = dataReader->data();
    delete dataReader;
  }
  else
  {
    qWarning() << "No suitable reader found for file: " << fileInfo.filePath() << " unable to import Shanoir data!";
    emit dataReceivingFailed(fileInfo.filePath());
    return;
  }
  
  // Now populate basic data attributes
  QDomDocument xmlData;
  
  QFile fileXML(xmlName);
  fileXML.open(QFile::ReadOnly);
  
  xmlData.setContent(&fileXML);
  xmlData.appendChild(xmlData.firstChild().firstChildElement("SOAP-ENV:Body").firstChild());
  xmlData.removeChild(xmlData.firstChild());

  QDomNode realXMLRoot = xmlData.firstChild().firstChild();
  
  fileXML.close();
  
  data->addMetaData(tr("StudyDescription"),realXMLRoot.firstChildElement("study").firstChild().nodeValue());
  data->addMetaData(tr("PatientName"),realXMLRoot.firstChildElement("subject").firstChildElement("name").firstChild().nodeValue());
  data->addMetaData(tr("SeriesDescription"),realXMLRoot.firstChildElement("name").firstChild().nodeValue());
  
  emit dataReceived(data);
}

dtkAbstractDataReader* qtshanoirDataSource::getSuitableReader(QStringList filename)
{
  typedef dtkAbstractDataFactory::dtkAbstractDataTypeHandler dtkAbstractDataTypeHandler;
  QList<dtkAbstractDataTypeHandler> readers = dtkAbstractDataFactory::instance()->readers();
  
  // cycle through readers to see if the last used reader can handle the file
  for (int i=0; i<readers.size(); i++) {
    dtkAbstractDataReader* dataReader = dtkAbstractDataFactory::instance()->reader(readers[i].first, readers[i].second);
    if (d->lastSuccessfulReaderDescription == dataReader->description() && dataReader->canRead( filename ))
      return dataReader;
    else
      delete dataReader;
  }
  
  for (int i=0; i<readers.size(); i++) {
    dtkAbstractDataReader* dataReader = dtkAbstractDataFactory::instance()->reader(readers[i].first, readers[i].second);
    if (dataReader->canRead( filename )){
      d->lastSuccessfulReaderDescription = dataReader->description();
      return dataReader;
    }
    else
      delete dataReader;
  }

  return NULL;
}

void qtshanoirDataSource::find()
{
	QtShanoir::instance()->find();  
}

QList<medToolBox*> qtshanoirDataSource::getToolboxes()
{  
  return d->additional_toolboxes;
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

medAbstractDataSource *createQtshanoirDataSource(void)
{
  return new qtshanoirDataSource;
}



