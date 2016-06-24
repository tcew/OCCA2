#ifndef OCCA_OPENACC_DEFINES_HEADER
#define OCCA_OPENACC_DEFINES_HEADER

#include <acc.h>

#include "occa/defines/cpuMode.hpp"

//---[ Defines ]----------------------------------
#define OCCA_USING_SERIAL   0
#define OCCA_USING_OPENACC  1
#define OCCA_USING_OPENCL   0
#define OCCA_USING_CUDA     0
#define OCCA_USING_PTHREADS 0
//================================================

//---[ Loops ]------------------------------------                                                     
#define occaOuterFor2 for(int occaOuterId2 = 0; occaOuterId2 < occaOuterDim2; ++occaOuterId2)
#define occaOuterFor1 for(int occaOuterId1 = 0; occaOuterId1 < occaOuterDim1; ++occaOuterId1)
#define occaOuterFor0 for(int occaOuterId0 = 0; occaOuterId0 < occaOuterDim0; ++occaOuterId0)

#define occaOuterFor occaOuterFor2 occaOuterFor1 occaOuterFor0
// - - - - - - - - - - - - - - - - - - - - - - - -                                                     
#define occaInnerFor2 for(occaInnerId2 = 0; occaInnerId2 < occaInnerDim2; ++occaInnerId2)
#define occaInnerFor1 for(occaInnerId1 = 0; occaInnerId1 < occaInnerDim1; ++occaInnerId1)
#define occaInnerFor0 for(occaInnerId0 = 0; occaInnerId0 < occaInnerDim0; ++occaInnerId0)
#define occaInnerFor occaInnerFor2 occaInnerFor1 occaInnerFor0
// - - - - - - - - - - - - - - - - - - - - - - - -                                                     
#define occaGlobalFor0 occaOuterFor0 occaInnerFor0
//================================================  


//---[ Standard Functions ]-----------------------                                                     
#define occaLocalMemFence
#define occaGlobalMemFence

#define occaBarrier(FENCE)
#define occaInnerBarrier(FENCE) continue
#define occaOuterBarrier(FENCE)
// - - - - - - - - - - - - - - - - - - - - - - - -                                                     
#define occaContinue continue
// - - - - - - - - - - - - - - - - - - - - - - - -                                                     
#define occaDirectLoad(X) (*(X))
//================================================   



//---[ Atomics ]----------------------------------
template <class TM>
TM occaAtomicAdd(TM *ptr, const TM &update){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old   = *ptr;
    *ptr += update;
  }

  return old;
}

template <class TM>
TM occaAtomicSub(TM *ptr, const TM &update){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old   = *ptr;
    *ptr -= update;
  }

  return old;
}

template <class TM>
TM occaAtomicSwap(TM *ptr, const TM &update){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old  = *ptr;
    *ptr = update;
  }

  return old;
}

template <class TM>
TM occaAtomicInc(TM *ptr){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old = *ptr;
  ++(*ptr);
  }

  return old;
}

template <class TM>
TM occaAtomicDec(TM *ptr, const TM &update){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old = *ptr;
    --(*ptr);
  }

  return old;
}

template <class TM>
TM occaAtomicMin(TM *ptr, const TM &update){
  TM old;

#  pragma acc critical
  {
    old  = *ptr;
    *ptr = ((old < update) ? old : update);
  }

  return old;
}

template <class TM>
TM occaAtomicMax(TM *ptr, const TM &update){
  TM old;

#  pragma acc critical
  {
    old  = *ptr;
    *ptr = ((old < update) ? update : old);
  }

  return old;
}

template <class TM>
TM occaAtomicAnd(TM *ptr, const TM &update){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old   = *ptr;
    *ptr &= update;
  }

  return old;
}

template <class TM>
TM occaAtomicOr(TM *ptr, const TM &update){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old   = *ptr;
    *ptr |= update;
  }

  return old;
}

template <class TM>
TM occaAtomicXor(TM *ptr, const TM &update){
  TM old;

#ifdef OPENMP_3_1
#  pragma acc atomic capture
#else
#  pragma acc critical
#endif
  {
    old   = *ptr;
    *ptr ^= update;
  }

  return old;
}

template <class TM>
TM occaAtomicCAS(TM *ptr, const int comp, const TM &update){
  TM old;

#pragma acc critical
  {
    old = *ptr;
    if(comp)
      *ptr = update;
  }

  return old;
}

#define occaAtomicAdd64  occaAtomicAdd
#define occaAtomicSub64  occaAtomicSub
#define occaAtomicSwap64 occaAtomicSwap
#define occaAtomicInc64  occaAtomicInc
#define occaAtomicDec64  occaAtomicDec
//================================================


//---[ Misc ]-------------------------------------
#define occaParallelFor2 OCCA_PRAGMA("acc parallel for collapse(3) firstprivate(occaInnerId0,occaInnerId1,occaInnerId2)")
#define occaParallelFor1 OCCA_PRAGMA("acc parallel for collapse(2) firstprivate(occaInnerId0,occaInnerId1,occaInnerId2)")
#define occaParallelFor0 OCCA_PRAGMA("acc parallel for             firstprivate(occaInnerId0,occaInnerId1,occaInnerId2)")
#define occaParallelFor  OCCA_PRAGMA("acc parallel for             firstprivate(occaInnerId0,occaInnerId1,occaInnerId2)")
//================================================

#endif
