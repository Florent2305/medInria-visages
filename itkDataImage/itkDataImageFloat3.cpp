#include "medItk.h"

#include "itkDataImageFloat3.h"

#include <itkVector.h>
#include <itkImage.h>
#include <itkMinimumMaximumImageCalculator.h>
#include <itkScalarImageToHistogramGenerator.h>
#include <itkRGBPixel.h>
#include <itkGreyColormapFunctor.h>
#include <itkScalarToRGBColormapImageFilter.h>
#include <itkExtractImageFilter.h>
#include <itkShrinkImageFilter.h>

#include <dtkCore/dtkAbstractDataFactory.h>

#include <QtGui>

#include "medITKDataImageMacros.h"

medImplementITKDataImage (float,          3, Float3);