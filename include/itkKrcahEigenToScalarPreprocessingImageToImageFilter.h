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

#ifndef itkKrcahEigenToScalarPreprocessingImageToImageFilter_h
#define itkKrcahEigenToScalarPreprocessingImageToImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkAddImageFilter.h"

namespace itk
{
/** \class KrcahEigenToScalarPreprocessingImageToImageFilter
 * \brief TODO
 * 
 * \sa KrcahEigenToScalarImageFilter
 * 
 * \author: Thomas Fitze
 * \ingroup BoneEnhancement
 */
template< typename TInputImage, typename TOutputImage = TInputImage >
class ITK_TEMPLATE_EXPORT KrcahEigenToScalarPreprocessingImageToImageFilter:
public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard Self typedef */
  typedef KrcahEigenToScalarPreprocessingImageToImageFilter Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage >   Superclass;
  typedef SmartPointer< Self >                              Pointer;
  typedef SmartPointer< const Self >                        ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(KrcahEigenToScalarPreprocessingImageToImageFilter, ImageToImageFilter);

  /** Image related typedefs. */
  typedef typename TInputImage::PixelType               PixelType;
  typedef typename NumericTraits< PixelType >::RealType RealType;

  /** Typedefs for internal filters */
  typedef DiscreteGaussianImageFilter<TInputImage, TInputImage>       GaussianFilterType;
  typedef SubtractImageFilter<TInputImage, TInputImage, TInputImage>  SubstractFilterType;
  typedef MultiplyImageFilter<TInputImage, TInputImage, TInputImage>  MultiplyFilterType;
  typedef AddImageFilter<TInputImage, TInputImage, TOutputImage>      AddFilterType;

  /** Flag to release data or not */
  itkSetMacro(ReleaseInternalFilterData, bool);
  itkGetConstMacro(ReleaseInternalFilterData, bool);
  itkBooleanMacro(ReleaseInternalFilterData);

  /** Flag to release data or not */
  itkSetMacro(Sigma, RealType);
  itkGetConstMacro(Sigma, RealType);

  /** Flag to release data or not */
  itkSetMacro(ScalingConstant, RealType);
  itkGetConstMacro(ScalingConstant, RealType);

protected:
  KrcahEigenToScalarPreprocessingImageToImageFilter();
  virtual ~KrcahEigenToScalarPreprocessingImageToImageFilter() {}

  /** Single threaded since we are connecting data */
  void GenerateData() ITK_OVERRIDE;

  void PrintSelf(std::ostream & os, Indent indent) const ITK_OVERRIDE;

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(KrcahEigenToScalarPreprocessingImageToImageFilter);

  /* Internal member variables */
  RealType  m_Sigma;
  RealType  m_ScalingConstant;
  bool      m_ReleaseInternalFilterData;

  /* Filter member variables */
  typename GaussianFilterType::Pointer  m_GaussianFilter;
  typename SubstractFilterType::Pointer m_SubtractFilter;
  typename MultiplyFilterType::Pointer  m_MultiplyFilter;
  typename AddFilterType::Pointer       m_AddFilter;
}; // end class
} // end namespace

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkKrcahEigenToScalarPreprocessingImageToImageFilter.hxx"
#endif

#endif // itkKrcahEigenToScalarPreprocessingImageToImageFilter_h