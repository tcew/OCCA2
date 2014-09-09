module occa
  use occaFTypes_m

  implicit none

  public ::                     &
    occaType_t,                 &
    occaDeviceSetCompiler,      &
    occaGetDevice,              &
    occaBuildKernelFromSource,  &
    occaBuildKernelFromBinary,  &
    occaBuildKernelFromLoopy,   &
    occaDeviceMalloc,           &
    occaDeviceFlush,            &
    occaDeviceFinish,           &
    occaDeviceGenStream,        &
    occaDeviceGetStream,        &
    occaDeviceSetStream,        &
    occaDeviceTagStream,        &
    occaDeviceTimeBetweenTags,  &
    occaDeviceStreamFree,       &
    occaDeviceFree,             &
    occaKernelPreferredDimSize, &
    occaKernelSetWorkingDims,   &
    occaKernelSetAllWorkingDims,&
    occaKernelTimeTaken,        &
    occaGenArgumentList,        &
    occaArgumentListClear,      &
    occaArgumentListFree,       &
    occaArgumentListAddArg,     &
    occaKernelRun_,             &
    occaKernelFree,             &
    occaGenKernelInfo,          &
    occaKernelInfoAddDefine,    &
    occaKernelInfoFree,         &
    occaCopyMemToMem,           &
    occaCopyPtrToMem,           &
    occaCopyMemToPtr,           &
    occaAsyncCopyMemToMem,      &
    occaAsyncCopyPtrToMem,      &
    occaAsyncCopyMemToPtr,      &
    occaMemorySwap,             &
    occaMemoryFree

! ---[ TypesCasting ]------------------
   interface occaType_t
    module procedure occaType_int4_c
    ! module procedure occaType_int8_c
    module procedure occaType_real4_c
    module procedure occaType_real8_c
    module procedure occaType_str_c
  end interface occaType_t

! ---[ Device ]-----------------------

  interface occaDeviceSetCompiler
    subroutine occaDeviceSetCompiler_fc(device, compiler)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: device
      character(len=*), intent(in)    :: compiler
    end subroutine occaDeviceSetCompiler_fc
  end interface occaDeviceSetCompiler

  interface occaDeviceSetCompilerFlags
    subroutine occaDeviceSetCompilerFlags_fc(device, compilerFlags)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: device
      character(len=*), intent(in)    :: compilerFlags
    end subroutine occaDeviceSetCompilerFlags_fc
  end interface occaDeviceSetCompilerFlags

  interface occaGetDevice
    module procedure occaGetDevice_func
  end interface occaGetDevice

  interface occaBuildKernelFromSource
    module procedure occaBuildKernelFromSource_func
  end interface occaBuildKernelFromSource

  interface occaBuildKernelFromBinary
    module procedure occaBuildKernelFromBinary_func
  end interface occaBuildKernelFromBinary

  interface occaBuildKernelFromLoopy
    module procedure occaBuildKernelFromLoopy_func
  end interface occaBuildKernelFromLoopy

  interface occaDeviceMalloc
    module procedure occaDeviceMalloc_null
    module procedure occaDeviceMalloc_int4
    module procedure occaDeviceMalloc_int8
    module procedure occaDeviceMalloc_real4
    module procedure occaDeviceMalloc_real8
    module procedure occaDeviceMalloc_char
  end interface occaDeviceMalloc

  interface occaDeviceFlush
    subroutine occaDeviceFlush_fc(device, compilerFlags)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: device
      character(len=*), intent(in)    :: compilerFlags
    end subroutine occaDeviceFlush_fc
  end interface occaDeviceFlush

  interface occaDeviceFinish
    subroutine occaDeviceFinish_fc(device)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: device
    end subroutine occaDeviceFinish_fc
  end interface occaDeviceFinish

  interface occaDeviceGenStream
    module procedure occaDeviceGenStream_func
  end interface occaDeviceGenStream

  interface occaDeviceGetStream
    module procedure occaDeviceGetStream_func
  end interface occaDeviceGetStream

  interface occaDeviceSetStream
    subroutine occaDeviceSetStream_fc(device, stream)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: device
      type(occaStream), intent(inout) :: stream
    end subroutine occaDeviceSetStream_fc
  end interface occaDeviceSetStream

  interface occaDeviceTimeBetweenTags
    module procedure occaDeviceTimeBetweenTags_func
  end interface occaDeviceTimeBetweenTags

  interface occaDeviceTagStream
    module procedure occaDeviceTagStream_func
  end interface occaDeviceTagStream

  interface occaDeviceStreamFree
    subroutine occaDeviceStreamFree_fc(device, stream)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: device
      type(occaStream), intent(inout) :: stream
    end subroutine occaDeviceStreamFree_fc
  end interface occaDeviceStreamFree

  interface occaDeviceFree
    subroutine occaDeviceFree_fc(device)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: device
    end subroutine occaDeviceFree_fc
  end interface occaDeviceFree

! ---[ Kernel ]-----------------------

  interface occaKernelPreferredDimSize
    module procedure occaKernelPreferredDimSize_func
  end interface occaKernelPreferredDimSize

  interface occaKernelSetWorkingDims
    subroutine occaKernelSetWorkingDims_fc(kernel, dims, items, groups)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: kernel
      integer(4),       intent(in)    :: dims
      type(occaDim),    intent(in)    :: items
      type(occaDim),    intent(in)    :: groups
    end subroutine occaKernelSetWorkingDims_fc
  end interface occaKernelSetWorkingDims

  interface occaKernelSetAllWorkingDims
    subroutine occaKernelSetAllWorkingDims_fc(kernel, dims, itemsX, itemsY, itemsZ, groupsX, groupsY, groupsZ)
      use occaFTypes_m

      implicit none
      type(occaDevice), intent(inout) :: kernel
      integer(4),       intent(in)    :: dims
      integer(8),       intent(in)    :: itemsX, itemsY, itemsZ
      integer(8),       intent(in)    :: groupsX, groupsY, groupsZ
    end subroutine occaKernelSetAllWorkingDims_fc
  end interface occaKernelSetAllWorkingDims

  interface occaKernelTimeTaken
    module procedure occaKernelTimeTaken_func
  end interface occaKernelTimeTaken

  interface occaGenArgumentList
    module procedure occaGenArgumentList_func
  end interface occaGenArgumentList

  interface occaArgumentListClear
    subroutine occaArgumentListClear_fc(list)
      use occaFTypes_m
      implicit none
      type(occaArgumentList), intent(inout) :: list
    end subroutine occaArgumentListClear_fc
  end interface occaArgumentListClear

  interface occaArgumentListFree
    subroutine occaArgumentListFree_fc(list)
      use occaFTypes_m
      implicit none
      type(occaArgumentList), intent(inout) :: list
    end subroutine occaArgumentListFree_fc
  end interface occaArgumentListFree

  interface occaArgumentListAddArg
    subroutine occaArgumentListAddArgMem_fc(kernel, idx, arg)
      use occaFTypes_m
      implicit none
      type(occaKernel), intent(inout) :: kernel
      integer(4),       intent(in)    :: idx
      type(occaMemory), intent(in)    :: arg
    end subroutine occaArgumentListAddArgMem_fc

    subroutine occaArgumentListAddArgType_fc(kernel, idx, arg)
      use occaFTypes_m
      implicit none
      type(occaKernel), intent(inout) :: kernel
      integer(4),       intent(in)    :: idx
      type(occaType),   intent(in)    :: arg
    end subroutine occaArgumentListAddArgType_fc
  end interface occaArgumentListAddArg

  interface occaKernelRun_
    subroutine occaKernelRun__fc(kernel, list)
      use occaFTypes_m
      implicit none
      type(occaKernel),       intent(inout) :: kernel
      type(occaArgumentList), intent(in)    :: list
    end subroutine occaKernelRun__fc
  end interface occaKernelRun_

  interface occaKernelFree
    subroutine occaKernelFree_fc(kernel)
      use occaFTypes_m
      implicit none
      type(occaKernel),       intent(inout) :: kernel
    end subroutine occaKernelFree_fc
  end interface occaKernelFree

  interface occaGenKernelInfo
    module procedure occaGenKernelInfo_func
  end interface occaGenKernelInfo

  interface occaKernelInfoAddDefine
    subroutine occaKernelInfoAddDefine_fc(info, macro, val)
      use occaFTypes_m
      implicit none
      type(occaKernelInfo), intent(inout) :: info
      character(len=*),     intent(in)    :: macro
      type(occaType),       intent(in)    :: val
    end subroutine occaKernelInfoAddDefine_fc
  end interface occaKernelInfoAddDefine

  interface occaKernelInfoFree
    subroutine occaKernelInfoFree_fc(info)
      use occaFTypes_m
      implicit none
      type(occaKernelInfo), intent(inout) :: info
    end subroutine occaKernelInfoFree_fc
  end interface occaKernelInfoFree

! ---[ Memory ]-----------------------

  interface occaCopyMemToMem
    subroutine occaCopyMemToMem_fc(dest, src, bytes, destOffset, srcOffset)
      use occaFTypes_m
      implicit none
      type(occaMemory), intent(out) :: dest
      type(occaMemory), intent(in)  :: src
      integer(8),       intent(in)  :: bytes
      integer(8),       intent(in)  :: destOffset
      integer(8),       intent(in)  :: srcOffset
    end subroutine occaCopyMemToMem_fc
  end interface occaCopyMemToMem

  interface occaCopyPtrToMem
    module procedure occaCopyPtrToMem_int4
    module procedure occaCopyPtrToMem_int8
    module procedure occaCopyPtrToMem_real4
    module procedure occaCopyPtrToMem_real8
    module procedure occaCopyPtrToMem_char
  end interface occaCopyPtrToMem

  interface occaCopyMemToPtr
    module procedure occaCopyMemToPtr_int4
    module procedure occaCopyMemToPtr_int8
    module procedure occaCopyMemToPtr_real4
    module procedure occaCopyMemToPtr_real8
    module procedure occaCopyMemToPtr_char
  end interface occaCopyMemToPtr

  interface occaAsyncCopyMemToMem
    subroutine occaAsyncCopyMemToMem_fc(dest, src, bytes, destOffset, srcOffset)
      use occaFTypes_m
      implicit none
      type(occaMemory), intent(out) :: dest
      type(occaMemory), intent(in)  :: src
      integer(8),       intent(in)  :: bytes
      integer(8),       intent(in)  :: destOffset
      integer(8),       intent(in)  :: srcOffset
    end subroutine occaAsyncCopyMemToMem_fc
  end interface occaAsyncCopyMemToMem

  interface occaAsyncCopyPtrToMem
    module procedure occaAsyncCopyPtrToMem_int4
    module procedure occaAsyncCopyPtrToMem_int8
    module procedure occaAsyncCopyPtrToMem_real4
    module procedure occaAsyncCopyPtrToMem_real8
    module procedure occaAsyncCopyPtrToMem_char
  end interface occaAsyncCopyPtrToMem

  interface occaAsyncCopyMemToPtr
    module procedure occaAsyncCopyMemToPtr_int4
    module procedure occaAsyncCopyMemToPtr_int8
    module procedure occaAsyncCopyMemToPtr_real4
    module procedure occaAsyncCopyMemToPtr_real8
    module procedure occaAsyncCopyMemToPtr_char
  end interface occaAsyncCopyMemToPtr

  interface occaMemorySwap
    subroutine occaMemorySwap_fc(memoryA, memoryB)
      use occaFTypes_m
      implicit none
      type(occaMemory), intent(inout) :: memoryA
      type(occaMemory), intent(inout) :: memoryB
    end subroutine occaMemorySwap_fc
  end interface occaMemorySwap

  interface occaMemoryFree
    subroutine occaMemoryFree_fc(memory)
      use occaFTypes_m
      implicit none
      type(occaMemory), intent(inout) :: memory
    end subroutine occaMemoryFree_fc
  end interface occaMemoryFree

contains

! ---[ TypesCasting ]------------------
  type(occaType) function occaType_int4_c(v) result(t)
    integer(4), intent(in) :: v

    interface
      subroutine occaInt32_fc(t, v)
        use occaFTypes_m
        implicit none
        type(occaType), intent(out) :: t
        integer(4),     intent(in)  :: v
      end subroutine occaInt32_fc
    end interface

    call occaInt32_fc(t, v)
  end function occaType_int4_c

  ! type(occaType) function occaType_int8_c(v) result(t)
  !   integer(8), intent(in) :: v

  !   interface
  !     subroutine occaInt64_fc(t, v)
  !       use occaFTypes_m
  !       implicit none
  !       type(occaType), intent(out) :: t
  !       integer(8),     intent(in)  :: v
  !     end subroutine occaInt64_fc
  !   end interface

  !   call occaInt64_fc(t, v)
  ! end function occaType_int8_c

  type(occaType) function occaType_real4_c(v) result(t)
    real(4), intent(in) :: v

    interface
      subroutine occaFloat_fc(t, v)
        use occaFTypes_m
        implicit none
        type(occaType), intent(out) :: t
        real(4),        intent(in)  :: v
      end subroutine occaFloat_fc
    end interface

    call occaFloat_fc(t, v)
  end function occaType_real4_c

  type(occaType) function occaType_real8_c(v) result(t)
    real(8), intent(in) :: v

    interface
      subroutine occaDouble_fc(t, v)
        use occaFTypes_m
        implicit none
        type(occaType), intent(out) :: t
        real(8),        intent(in)  :: v
      end subroutine occaDouble_fc
    end interface

    call occaDouble_fc(t, v)
  end function occaType_real8_c

  type(occaType) function occaType_str_c(v) result(t)
    character(len=*), intent(in) :: v

    interface
      subroutine occaString_fc(t, v)
        use occaFTypes_m
        implicit none
        type(occaType),   intent(out) :: t
        character(len=*), intent(in)  :: v
      end subroutine occaString_fc
    end interface

    call occaString_fc(t, v)
  end function occaType_str_c

! ---[ Device ]-----------------------
!  interface occaDeviceMode
!     const char* occaDeviceMode_fc(occaDevice device)
!  end interface occaDeviceMode


  type(occaDevice) function occaGetDevice_func(mode, arg1, arg2) result(device)
    character(len=*), intent(in)  :: mode
    integer(4),       intent(in)  :: arg1
    integer(4),       intent(in)  :: arg2

    interface
      subroutine occaGetDevice_fc(device, mode, arg1, arg2)
        use occaFTypes_m
        implicit none
        type(occaDevice), intent(out) :: device
        character(len=*), intent(in)  :: mode
        integer(4),       intent(in)  :: arg1
        integer(4),       intent(in)  :: arg2
      end subroutine occaGetDevice_fc
    end interface

    call occaGetDevice_fc(device, mode, arg1, arg2)
  end function occaGetDevice_func

  type(occaKernel) function occaBuildKernelFromSource_func(device, filename, functionName, info) result(kernel)
    type(occaDevice),     intent(in)  :: device
    character(len=*),     intent(in)  :: filename
    character(len=*),     intent(in)  :: functionName
    type(occaKernelInfo), intent(in)  :: info

    interface
      subroutine occaBuildKernelFromSource_fc(kernel, device, filename, functionName, info)
        use occaFTypes_m
        implicit none
        type(occaKernel),     intent(out) :: kernel
        type(occaDevice),     intent(in)  :: device
        character(len=*),     intent(in)  :: filename
        character(len=*),     intent(in)  :: functionName
        type(occaKernelInfo), intent(in)  :: info
      end subroutine occaBuildKernelFromSource_fc
    end interface

    call occaBuildKernelFromSource_fc(kernel, device, filename, functionName, info)
  end function occaBuildKernelFromSource_func

  type(occaKernel) function occaBuildKernelFromBinary_func(device, filename, functionName) result(kernel)
    type(occaDevice),     intent(in)  :: device
    character(len=*),     intent(in)  :: filename
    character(len=*),     intent(in)  :: functionName

    interface
      subroutine occaBuildKernelFromBinary_fc(kernel, device, filename, functionName)
        use occaFTypes_m
        implicit none
        type(occaKernel),     intent(out) :: kernel
        type(occaDevice),     intent(in)  :: device
        character(len=*),     intent(in)  :: filename
        character(len=*),     intent(in)  :: functionName
      end subroutine occaBuildKernelFromBinary_fc
    end interface

    call occaBuildKernelFromBinary_fc(kernel, device, filename, functionName)
  end function occaBuildKernelFromBinary_func

  type(occaKernel) function occaBuildKernelFromLoopy_func(device, filename, functionName, pythonCode) result(kernel)
    type(occaDevice),     intent(in)  :: device
    character(len=*),     intent(in)  :: filename
    character(len=*),     intent(in)  :: functionName
    character(len=*),     intent(in)  :: pythonCode

    interface
      subroutine occaBuildKernelFromLoopy_fc(kernel, device, filename, functionName, pythonCode)
        use occaFTypes_m
        implicit none
        type(occaKernel),     intent(out) :: kernel
        type(occaDevice),     intent(in)  :: device
        character(len=*),     intent(in)  :: filename
        character(len=*),     intent(in)  :: functionName
        character(len=*),     intent(in)  :: pythonCode
      end subroutine occaBuildKernelFromLoopy_fc
    end interface

    call occaBuildKernelFromLoopy_fc(kernel, device, filename, functionName, pythonCode)
  end function occaBuildKernelFromLoopy_func


  type(occaMemory) function occaDeviceMalloc_null(device, sz) result(mem)
    type(occaDevice),  intent(inout) :: device
    integer(8),        intent(in)    :: sz

    call occaDeviceMallocNULL_fc(mem, device, sz)
  end function occaDeviceMalloc_null

  type(occaMemory) function occaDeviceMalloc_int4(device, sz, buf) result(mem)
    type(occaDevice),  intent(inout) :: device
    integer(8),        intent(in)    :: sz
    integer(4),        intent(in)    :: buf

    call occaDeviceMalloc_fc(mem, device, sz, buf)
  end function occaDeviceMalloc_int4
  type(occaMemory) function occaDeviceMalloc_int8(device, sz, buf) result(mem)
    type(occaDevice),  intent(inout) :: device
    integer(8),        intent(in)    :: sz
    integer(8),        intent(in)    :: buf

    call occaDeviceMalloc_fc(mem, device, sz, buf)
  end function occaDeviceMalloc_int8
  type(occaMemory) function occaDeviceMalloc_real4(device, sz, buf) result(mem)
    type(occaDevice),  intent(inout) :: device
    integer(8),        intent(in)    :: sz
    real(4),           intent(in)    :: buf

    call occaDeviceMalloc_fc(mem, device, sz, buf)
  end function occaDeviceMalloc_real4
  type(occaMemory) function occaDeviceMalloc_real8(device, sz, buf) result(mem)
    type(occaDevice),  intent(inout) :: device
    integer(8),        intent(in)    :: sz
    real(8),           intent(in)    :: buf

    call occaDeviceMalloc_fc(mem, device, sz, buf)
  end function occaDeviceMalloc_real8
  type(occaMemory) function occaDeviceMalloc_char(device, sz, buf) result(mem)
    type(occaDevice),  intent(inout) :: device
    integer(8),        intent(in)    :: sz
    character,         intent(in)    :: buf

    call occaDeviceMalloc_fc(mem, device, sz, buf)
  end function occaDeviceMalloc_char

  type(occaStream) function occaDeviceGenStream_func(device) result(stream)
    type(occaDevice),     intent(inout)  :: device

    interface
      subroutine occaDeviceGenStream_fc(stream, device)
        use occaFTypes_m
        implicit none
        type(occaStream),  intent(out)   :: stream
        type(occaDevice),  intent(inout) :: device
      end subroutine occaDeviceGenStream_fc
    end interface

    call occaDeviceGenStream_fc(stream, device)
  end function occaDeviceGenStream_func

  type(occaStream) function occaDeviceGetStream_func(device) result(stream)
    type(occaDevice),     intent(inout)  :: device

    interface
      subroutine occaDeviceGetStream_fc(stream, device)
        use occaFTypes_m
        implicit none
        type(occaStream),  intent(out)   :: stream
        type(occaDevice),  intent(inout) :: device
      end subroutine occaDeviceGetStream_fc
    end interface

    call occaDeviceGetStream_fc(stream, device)
  end function occaDeviceGetStream_func


  type(occaTag) function occaDeviceTagStream_func(device) result(tag)
    type(occaDevice),     intent(inout)  :: device

    interface
      subroutine occaDeviceTagStream_fc(tag, device)
        use occaFTypes_m
        implicit none
        type(occaTag),     intent(out)   :: tag
        type(occaDevice),  intent(inout) :: device
      end subroutine occaDeviceTagStream_fc
    end interface

    call occaDeviceTagStream_fc(tag, device)
  end function occaDeviceTagStream_func

  real(8) function occaDeviceTimeBetweenTags_func(device, startTag, endTag) result(time)
    type(occaDevice),     intent(inout) :: device
    type(occaTag),        intent(in)    :: startTag
    type(occaTag),        intent(in)    :: endTag

    interface
      subroutine occaDeviceTimeBetweenTags_fc(time, device, startTag, endTag)
        use occaFTypes_m
        implicit none
        real(8),          intent(out)   :: time
        type(occaDevice), intent(inout) :: device
        type(occaTag),    intent(in)    :: startTag
        type(occaTag),    intent(in)    :: endTag
      end subroutine occaDeviceTimeBetweenTags_fc
    end interface

    call occaDeviceTimeBetweenTags_fc(time, device, startTag, endTag)
  end function occaDeviceTimeBetweenTags_func


! ---[ Kernel ]-----------------------
!  interface occaKernelMode
!     const char* occaKernelMode_fc(occaKernel kernel)
!  end interface occaKernelMode

  integer(4) function occaKernelPreferredDimSize_func(kernel) result(sz)
    type(occaKernel),     intent(in) :: kernel

    interface
      subroutine occaKernelPreferredDimSize_fc(sz, kernel)
        use occaFTypes_m
        implicit none
        integer(4),       intent(out) :: sz
        type(occaKernel), intent(in)  :: kernel
      end subroutine occaKernelPreferredDimSize_fc
    end interface

    call occaKernelPreferredDimSize_fc(sz, kernel)
  end function occaKernelPreferredDimSize_func

  real(8) function occaKernelTimeTaken_func(kernel) result(time)
    type(occaKernel),     intent(in) :: kernel

    interface
      subroutine occaKernelTimeTaken_fc(time, kernel)
        use occaFTypes_m
        implicit none
        real(8),          intent(out) :: time
        type(occaKernel), intent(in)  :: kernel
      end subroutine occaKernelTimeTaken_fc
    end interface

    call occaKernelTimeTaken_fc(time, kernel)
  end function occaKernelTimeTaken_func


  type(occaArgumentList) function occaGenArgumentList_func() result(args)

    interface
      subroutine occaGenArgumentList_fc(args)
        use occaFTypes_m
        implicit none
        type(occaArgumentList), intent(out) :: args
      end subroutine occaGenArgumentList_fc
    end interface

    call occaGenArgumentList_fc(args)
  end function occaGenArgumentList_func

  type(occaKernelInfo) function occaGenKernelInfo_func() result(info)

    interface
      subroutine occaGenKernelInfo_fc(info)
        use occaFTypes_m
        implicit none
        type(occaKernelInfo), intent(out) :: info
      end subroutine occaGenKernelInfo_fc
    end interface

    call occaGenKernelInfo_fc(info)
  end function occaGenKernelInfo_func

! ---[ Memory ]-----------------------
!  interface occaMemoryMode
!     const char* occaMemoryMode_fc(occaMemory memory)
!  end interface occaMemoryMode

  subroutine occaCopyPtrToMem_int4(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    integer(4),       intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyPtrToMem_int4

  subroutine occaCopyPtrToMem_int8(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    integer(8),       intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyPtrToMem_int8

  subroutine occaCopyPtrToMem_real4(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    real(4),          intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyPtrToMem_real4

  subroutine occaCopyPtrToMem_real8(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    real(8),          intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyPtrToMem_real8

  subroutine occaCopyPtrToMem_char(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    character,        intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyPtrToMem_char

  subroutine occaCopyMemToPtr_int4(dest, src, bytes, destOffset, srcOffset)
    integer(4),       intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyMemToPtr_int4

  subroutine occaCopyMemToPtr_int8(dest, src, bytes, destOffset, srcOffset)
    integer(8),       intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyMemToPtr_int8

  subroutine occaCopyMemToPtr_real4(dest, src, bytes, destOffset, srcOffset)
    real(4),          intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyMemToPtr_real4

  subroutine occaCopyMemToPtr_real8(dest, src, bytes, destOffset, srcOffset)
    real(8),          intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyMemToPtr_real8

  subroutine occaCopyMemToPtr_char(dest, src, bytes, destOffset, srcOffset)
    character,        intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaCopyMemToPtr_char

  subroutine occaAsyncCopyPtrToMem_int4(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    integer(4),       intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyPtrToMem_int4

  subroutine occaAsyncCopyPtrToMem_int8(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    integer(8),       intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyPtrToMem_int8

  subroutine occaAsyncCopyPtrToMem_real4(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    real(4),          intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyPtrToMem_real4

  subroutine occaAsyncCopyPtrToMem_real8(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    real(8),          intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyPtrToMem_real8

  subroutine occaAsyncCopyPtrToMem_char(dest, src, bytes, destOffset, srcOffset)
    type(occaMemory), intent(out) :: dest
    character,        intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyPtrToMem_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyPtrToMem_char

  subroutine occaAsyncCopyMemToPtr_int4(dest, src, bytes, destOffset, srcOffset)
    integer(4),       intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyMemToPtr_int4

  subroutine occaAsyncCopyMemToPtr_int8(dest, src, bytes, destOffset, srcOffset)
    integer(8),       intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyMemToPtr_int8

  subroutine occaAsyncCopyMemToPtr_real4(dest, src, bytes, destOffset, srcOffset)
    real(4),          intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyMemToPtr_real4

  subroutine occaAsyncCopyMemToPtr_real8(dest, src, bytes, destOffset, srcOffset)
    real(8),          intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyMemToPtr_real8

  subroutine occaAsyncCopyMemToPtr_char(dest, src, bytes, destOffset, srcOffset)
    character,        intent(out) :: dest
    type(occaMemory), intent(in)  :: src
    integer(8),       intent(in)  :: bytes
    integer(8),       intent(in)  :: destOffset
    integer(8),       intent(in)  :: srcOffset

    call occaAsyncCopyMemToPtr_fc(dest, src, bytes, destOffset, srcOffset)
  end subroutine occaAsyncCopyMemToPtr_char

end module occa