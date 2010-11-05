// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "Image3D.hh"
#include "vistalDataImageDouble3.h"
#include "itkImage3D.hh"

#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// vistalDataImageDouble3Private
// /////////////////////////////////////////////////////////////////

class vistalDataImageDouble3Private
{
public:
  vistal::Image3D<double> * image;
	itkImage3D<double> * itkConverter;
};

// /////////////////////////////////////////////////////////////////
// vistalDataImageDouble3
// /////////////////////////////////////////////////////////////////

vistalDataImageDouble3::vistalDataImageDouble3(void) : dtkAbstractData(), d(new vistalDataImageDouble3Private)
{
  d->image = 0;
	d->itkConverter = 0;
}

vistalDataImageDouble3::~vistalDataImageDouble3(void)
{

}

bool vistalDataImageDouble3::registered(void)
{
    return dtkAbstractDataFactory::instance()->registerDataType("vistalDataImageDouble3", createVistalDataImageDouble3);
}

QString vistalDataImageDouble3::description(void) const
{
    return "vistalDataImageDouble3";
}

void *vistalDataImageDouble3::data()
{
  return d->image;
}

void *vistalDataImageDouble3::output()
{
	if (!d->itkConverter)
		d->itkConverter = new itkImage3D<double>;

	if (!d->image)
		return 0;

	d->itkConverter->SetImage3D(*d->image);

	return d->itkConverter->GetOutput();
}

void vistalDataImageDouble3::setData(void* data)
{
  d->image = static_cast<vistal::Image3D<double> *> (data);
}

int vistalDataImageDouble3::xDimension(void)
{
  if (d->image != NULL)
    return d->image->nbx;
  else
    return -1;
}

int vistalDataImageDouble3::yDimension(void)
{
  if (d->image != NULL)
    return d->image->nby;
  else
    return -1;
}

int vistalDataImageDouble3::zDimension(void)
{
  if (d->image != NULL)
    return d->image->nbz;
  else
    return -1;
}

int vistalDataImageDouble3::tDimension(void)
{
  if (d->image != NULL)
    return d->image->nbt;
  else
    return -1;
}


// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractData *createVistalDataImageDouble3(void)
{
    return new vistalDataImageDouble3;
}
