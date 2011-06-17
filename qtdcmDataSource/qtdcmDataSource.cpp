// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "qtdcmDataSource.h"

#include <medCore/medAbstractDataSourceFactory.h>
#include <medGui/medToolBox.h>

#include <QtDcm.h>
#include <QtDcmPreferencesWidget.h>
#include <QtDcmManager.h>
#include <QtDcmPreferences.h>

#include <dtkCore/dtkAbstractDataReader.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>

// /////////////////////////////////////////////////////////////////
// qtdcmDataSourcePrivate
// /////////////////////////////////////////////////////////////////

class qtdcmDataSourcePrivate
{
public:
    QtDCM * mainWidget;
    QtDcmPreferencesWidget * rightWidget;

    ~qtdcmDataSourcePrivate();
};

qtdcmDataSourcePrivate::~qtdcmDataSourcePrivate()
{
    delete mainWidget;
    delete rightWidget;
}

// /////////////////////////////////////////////////////////////////
// qtdcmDataSource
// /////////////////////////////////////////////////////////////////

qtdcmDataSource::qtdcmDataSource ( void ) : medAbstractDataSource(), d ( new qtdcmDataSourcePrivate )
{
    d->mainWidget = NULL;
    d->rightWidget = NULL;

}

qtdcmDataSource::~qtdcmDataSource ( void )
{
    delete d;
    d = NULL;
}

bool qtdcmDataSource::registered ( void )
{
    return medAbstractDataSourceFactory::instance()->registerDataSource ( "qtdcmDataSource", createQtdcmDataSource );
}

QString qtdcmDataSource::description ( void ) const
{
    return "qtdcmDataSource";
}

QWidget *qtdcmDataSource::mainViewWidget()
{
    if ( d->mainWidget )
        return d->mainWidget;

    initWidgets();
    return d->mainWidget;
}

QWidget *qtdcmDataSource::sourceSelectorWidget()
{
    if ( d->rightWidget )
        return d->rightWidget;

    initWidgets();
    return d->rightWidget;
}

QString qtdcmDataSource::tabName()
{
    return QString ( "Dicom" );
}

QList<medToolBox*> qtdcmDataSource::getToolboxes()
{
    return QList<medToolBox *> ();
}

void qtdcmDataSource::initWidgets ( void )
{
    if ( d->mainWidget && d->rightWidget )
        return;

    if ( !d->mainWidget )
    {
        d->mainWidget = new QtDCM();

        if ( !d->rightWidget )
        {
            d->rightWidget = new QtDcmPreferencesWidget();
            d->rightWidget->setPreferences(d->mainWidget->getManager()->getPreferences());
        }
    }
//     QtShanoir::instance()->attachTreeWidget(d->mainWidget);
//     QtShanoir::instance()->init();
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

medAbstractDataSource *createQtdcmDataSource ( void )
{
    return new qtdcmDataSource;
}
