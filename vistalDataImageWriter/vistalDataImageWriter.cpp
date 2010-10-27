// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalDataImageWriter.h"

#include "Image3D.hh"
#include "GIS.hh"
#include "vistalIO.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// vistalDataImageWriterPrivate
// /////////////////////////////////////////////////////////////////

class vistalDataImageWriterPrivate
{
    public:
};

// /////////////////////////////////////////////////////////////////
// vistalDataImageWriter
// /////////////////////////////////////////////////////////////////

vistalDataImageWriter::vistalDataImageWriter(void) :
    dtkAbstractDataWriter(), d(new vistalDataImageWriterPrivate)
{

}

vistalDataImageWriter::~vistalDataImageWriter(void)
{

}

bool
vistalDataImageWriter::registered(void)
{
    return dtkAbstractDataFactory::instance()->registerDataWriterType("vistalDataImageWriter", QStringList() << "vistalDataImageUChar3",createVistalDataImageWriter);
}

QString
vistalDataImageWriter::description(void) const
{
    return "vistalDataImageWriter";
}

QStringList
vistalDataImageWriter::handled() const
{
    return QStringList() << "vistalDataImageUChar3";
}

bool
vistalDataImageWriter::canWrite(QString path)
{
    return QFile(path).isWritable();
}

bool
vistalDataImageWriter::write(QString path)
{
    if (!this->data())
        return false;

    if (dtkAbstractData *dtkdata = this->data() ) {

        if (dtkdata->description() == "vistalDataImageUChar3") {
            vistal::Image3D<unsigned char> * image = static_cast<vistal::Image3D<unsigned char>*> (this->data()->output());
            if (image == NULL)
                return false;
            std::string tmp(path.toAscii().data());
            vistal::io::writeImage(tmp, *image);
        }
        else {
            qWarning() << "Unrecognized pixel type";
            return false;
        }
    }
    return true;
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter *
createVistalDataImageWriter(void)
{
    return new vistalDataImageWriter;
}
