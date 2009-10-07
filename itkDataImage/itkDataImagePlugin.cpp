// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "itkDataImage.h"
#include "itkDataImagePlugin.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// itkDataImagePluginPrivate
// /////////////////////////////////////////////////////////////////

class itkDataImagePluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// itkDataImagePlugin
// /////////////////////////////////////////////////////////////////

itkDataImagePlugin::itkDataImagePlugin(QObject *parent) : dtkPlugin(parent), d(new itkDataImagePluginPrivate)
{

}

itkDataImagePlugin::~itkDataImagePlugin(void)
{
    delete d;

    d = NULL;
}

bool itkDataImagePlugin::initialize(void)
{
  if(!itkDataImageChar3::registered()) qDebug() << "Unable to register itkDataImageChar3 type";
  if(!itkDataImageUChar3::registered()) qDebug() << "Unable to register itkDataImageUChar3 type";
  if(!itkDataImageShort3::registered()) qDebug() << "Unable to register itkDataImageShort3 type";
  if(!itkDataImageUShort3::registered()) qDebug() << "Unable to register itkDataImageUShort3 type";
  if(!itkDataImageInt3::registered()) qDebug() << "Unable to register itkDataImageInt3 type";
  if(!itkDataImageUInt3::registered()) qDebug() << "Unable to register itkDataImageUInt3 type";
  if(!itkDataImageLong3::registered()) qDebug() << "Unable to register itkDataImageLong3 type";
  if(!itkDataImageULong3::registered()) qDebug() << "Unable to register itkDataImageULong3 type";
  if(!itkDataImageFloat3::registered()) qDebug() << "Unable to register itkDataImageFloat3 type";
  if(!itkDataImageDouble3::registered()) qDebug() << "Unable to register itkDataImageDouble3 type";
  
  return true;
}

bool itkDataImagePlugin::uninitialize(void)
{
    return true;
}

QString itkDataImagePlugin::name(void) const
{
    return "itkDataImagePlugin";
}

QString itkDataImagePlugin::description(void) const
{
    return "Plugin containing all types of ITK images";
}

QStringList itkDataImagePlugin::tags(void) const
{
  return QStringList() << "itk" << "data" << "image";
}

QStringList itkDataImagePlugin::types(void) const
{
  return QStringList() << "itkDataImageChar3"
		       << "itkDataImageUChar3"
		       << "itkDataImageShort3"
		       << "itkDataImageUShort3"
		       << "itkDataImageInt3"
		       << "itkDataImageUInt3"
		       << "itkDataImageLong3"
		       << "itkDataImageULong3"
		       << "itkDataImageFloat3"
		       << "itkDataImageDouble3";
}

Q_EXPORT_PLUGIN2(itkDataImagePlugin, itkDataImagePlugin)