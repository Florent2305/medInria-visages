// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalDataImageToItkDataImageDouble3Converter.h"
#include "itkImage3D.hh"
#include "Image3D.hh"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// vistalDataImageToItkDataImageFloatConverterPrivate
// /////////////////////////////////////////////////////////////////

class vistalDataImageToItkDataImageDouble3ConverterPrivate
{
    public:
        itkImage3D<double> * double3Converter;

        dtkAbstractData * output;

};

// /////////////////////////////////////////////////////////////////
// vistalDataImageToItkDataImageFloatConverter
// /////////////////////////////////////////////////////////////////

vistalDataImageToItkDataImageDouble3Converter::vistalDataImageToItkDataImageDouble3Converter(void) :
    dtkAbstractDataConverter(), d(new vistalDataImageToItkDataImageDouble3ConverterPrivate)
{
    d->output = dtkAbstractDataFactory::instance()->create("itkDataImageDouble3");

    d->double3Converter = NULL;
}

vistalDataImageToItkDataImageDouble3Converter::~vistalDataImageToItkDataImageDouble3Converter(void)
{

}

bool
vistalDataImageToItkDataImageDouble3Converter::registered(void)
{
    return dtkAbstractDataFactory::instance()->registerDataConverterType("vistalDataImageToItkDataImageFloatConverter", QStringList() << "vistalDataImageDouble3", "itkDataImageDouble3", createVistalDataImageToItkDataImageDouble3Converter);
}

QString
vistalDataImageToItkDataImageDouble3Converter::description(void) const
{
    return "vistalDataImageToItkDataImageDouble3Converter";
}

QStringList
vistalDataImageToItkDataImageDouble3Converter::fromTypes(void) const
{
    return QStringList() << "vistalDataImageDouble3";
}

QString
vistalDataImageToItkDataImageDouble3Converter::toType(void) const
{
    return "itkDataImageDouble3";
}

dtkAbstractData *
vistalDataImageToItkDataImageDouble3Converter::convert(void)
{
    if (!d->output)
        return NULL;

    dtkAbstractData *data = this->data();
    if (!data)
        return NULL;

    if (data->description() == "vistalDataImageFloat") {
        if ( vistal::Image3D<double>* image = static_cast<vistal::Image3D<double>*>( data->data() ) ) {
            if (d->double3Converter == NULL)
                d->double3Converter = new itkImage3D<double> ;
            d->double3Converter->SetImage3D(*image);
            d->output->setData(d->double3Converter->GetOutput());
        }
    }
    return d->output;
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataConverter *
createVistalDataImageToItkDataImageDouble3Converter(void)
{
    return new vistalDataImageToItkDataImageDouble3Converter;
}
