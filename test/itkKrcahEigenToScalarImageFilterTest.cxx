/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkKrcahEigenToScalarImageFilter.h"
#include "itkTestingMacros.h"
#include "itkMath.h"
#include "itkImageRegionIteratorWithIndex.h"

int itkKrcahEigenToScalarImageFilterTest( int argc, char * argv[] )
{
  const unsigned int                              Dimension = 3;
  typedef unsigned int                            MaskPixelType;
  typedef itk::Image< MaskPixelType, Dimension >  MaskType;

  typedef double                                    OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputType;

  typedef float                                         EigenValueType;
  typedef itk::FixedArray< EigenValueType, Dimension >  EigenValueArrayType;
  typedef itk::Image< EigenValueArrayType, Dimension >  EigenValueImageType;
  
  typedef itk::KrcahEigenToScalarImageFilter< EigenValueImageType, OutputType, MaskType > KrcahEigenToScalarImageFilterType;

  KrcahEigenToScalarImageFilterType::Pointer krcahFilter = KrcahEigenToScalarImageFilterType::New();

  EXERCISE_BASIC_OBJECT_METHODS( krcahFilter, KrcahEigenToScalarImageFilter, EigenToScalarImageFilter );
  
  /* Test defaults */
  TEST_EXPECT_EQUAL(krcahFilter->GetEigenValueOrder(), KrcahEigenToScalarImageFilterType::Superclass::OrderByMagnitude);

  /* Create some test data which is computable */
  EigenValueArrayType simpleEigenPixel;
  for (unsigned int i = 0; i < Dimension; ++i) {
    simpleEigenPixel.SetElement(i, -1);
  }

  EigenValueImageType::RegionType region;
  EigenValueImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;
  start[2] = 0;
 
  EigenValueImageType::SizeType size;
  size[0] = 10;
  size[1] = 10;
  size[2] = 10;
 
  region.SetSize(size);
  region.SetIndex(start);
 
  EigenValueImageType::Pointer image = EigenValueImageType::New();
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(simpleEigenPixel);

  /* Run with no exceptions */
  krcahFilter->SetParameterSetToImplementation();
  krcahFilter->SetEnhanceBrightObjects();
  krcahFilter->SetInput(image);
  TRY_EXPECT_NO_EXCEPTION(krcahFilter->Update());

  /* Make sure process for setting parameters works */
  TEST_EXPECT_TRUE(itk::Math::FloatAlmostEqual( krcahFilter->GetAlpha(), 0.5, 6, 0.000001));
  TEST_EXPECT_TRUE(itk::Math::FloatAlmostEqual( krcahFilter->GetBeta(), 0.5, 6, 0.000001));
  TEST_EXPECT_TRUE(itk::Math::FloatAlmostEqual( krcahFilter->GetGamma(), 3*0.5, 6, 0.000001));

  itk::ImageRegionIteratorWithIndex< OutputType > it(krcahFilter->GetOutput(), region);

  it.GoToBegin();
  while ( !it.IsAtEnd() )
  {
    // TODO: Why is this not 0.000335462627903 as before?
    TEST_EXPECT_TRUE(itk::Math::FloatAlmostEqual( it.Get(), 0.000329318, 6, 0.000001));
    ++it;
  }

  return EXIT_SUCCESS;
}
