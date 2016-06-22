#if OCCA_CUDA_ENABLED
#include "occa/OpenACC.hpp"
#define accDevice acc_device_nvidia


namespace occa {
  //---[ Helper Functions ]-----------
  namespace acc {
    bool isInitialized = false;

    void init(){
      if(isInitialized)
        return;

      acc_init(accDevice);

      isInitialized = true;
    }

    int getDeviceCount(){
      int deviceCount;
      OCCA_ACC_CHECK("Finding Number of Devices");

      return deviceCount = acc_get_num_devices( accDevice );
    }
    
    ACCdevice getDevice(const int id){
       
      CUdevice device;
      OCCA_ACC_CHECK("Getting ACCdevice",
		     acc_get_current_cuda_device(&device));
      return device;
    }
    
    /* uintptr_t getDeviceMemorySize(CUdevice device){
      size_t bytes;
      OCCA_ACC_CHECK("Finding available memory on device",
                      cuDeviceTotalMem(&bytes, device));
      return bytes;
      }*/

    std::string getDeviceListInfo(){
      std::stringstream ss;

      acc::init();
      int deviceCount = acc::getDeviceCount();
      if(deviceCount == 0)
        return "";

      //      char deviceName[1024];
      // OCCA_ACC_CHECK("Getting Device Name",
      //              cuDeviceGetName(deviceName, 1024, 0));

      // uintptr_t bytes      = getDeviceMemorySize(getDevice(0));
      // std::string bytesStr = stringifyBytes(bytes);

      // << "==============o=======================o==========================================\n";
      ss << "     ACC     |  Device ID            | 0 "                                  << '\n'
         << "              |  Device Name          | " << deviceName                      << '\n'
         << "              |  Memory               | " << bytesStr                        << '\n';

      for(int i = 1; i < deviceCount; ++i){
	// bytes    = getDeviceMemorySize(getDevice(i));
	// bytesStr = stringifyBytes(bytes);

	// OCCA_ACC_CHECK("Getting Device Name",
	//              cuDeviceGetName(deviceName, 1024, i));

        ss << "              |-----------------------+------------------------------------------\n"
           << "              |  Device ID            | " << i                                << '\n'
           << "              |  Device Name          | " << deviceName                       << '\n'
           << "              |  Memory               | " << bytesStr                         << '\n';
      }

      return ss.str();
    }
  
     void enablePeerToPeer(CUcontext context){
       // To be implimented

       perror("peer to peer not yet implimented");



       /*#if ACC_VERSION >= 4000
      OCCA_ACC_CHECK("Enabling Peer-to-Peer",
                      cuCtxEnablePeerAccess(context, 0) );
#else
      OCCA_CHECK(false,
                 "ACC version ["
                 << ((int) (ACC_VERSION / 1000))
                 << '.'
                 << ((int) ((ACC_VERSION % 100) / 10))
                 << "] does not support Peer-to-Peer");
#endif
    }

    void checkPeerToPeer(CUdevice destDevice,
                         CUdevice srcDevice){
#if ACC_VERSION >= 4000
        int canAccessPeer;

        OCCA_ACC_CHECK("Checking Peer-to-Peer Connection",
                        cuDeviceCanAccessPeer(&canAccessPeer,
                                              destDevice,
                                              srcDevice));

        OCCA_CHECK((canAccessPeer == 1),
                   "Checking Peer-to-Peer Connection");
#else
      OCCA_CHECK(false,
                 "ACC version ["
                 << ((int) (ACC_VERSION / 1000))
                 << '.'
                 << ((int) ((ACC_VERSION % 100) / 10))
                 << "] does not support Peer-to-Peer");
#endif
    }

    void peerToPeerMemcpy(CUdevice destDevice,
                          CUcontext destContext,
                          CUdeviceptr destMemory,
                          CUdevice srcDevice,
                          CUcontext srcContext,
                          CUdeviceptr srcMemory,
                          const uintptr_t bytes,
                          CUstream usingStream){

      peerToPeerMemcpy(destDevice, destContext, destMemory,
                       srcDevice , srcContext , srcMemory ,
                       bytes,
                       usingStream, false);
    }


    void asyncPeerToPeerMemcpy(CUdevice destDevice,
                               CUcontext destContext,
                               CUdeviceptr destMemory,
                               CUdevice srcDevice,
                               CUcontext srcContext,
                               CUdeviceptr srcMemory,
                               const uintptr_t bytes,
                               CUstream usingStream){

      peerToPeerMemcpy(destDevice, destContext, destMemory,
                       srcDevice , srcContext , srcMemory ,
                       bytes,
                       usingStream, true);
    }

    void peerToPeerMemcpy(CUdevice destDevice,
                          CUcontext destContext,
                          CUdeviceptr destMemory,
                          CUdevice srcDevice,
                          CUcontext srcContext,
                          CUdeviceptr srcMemory,
                          const uintptr_t bytes,
                          CUstream usingStream,
                          const bool isAsync){

#if ACC_VERSION >= 4000
      if(!isAsync){
        OCCA_ACC_CHECK("Peer-to-Peer Memory Copy",
                        cuMemcpyPeer(destMemory, destContext,
                                     srcMemory , srcContext ,
                                     bytes));
      }
      else{
        OCCA_ACC_CHECK("Peer-to-Peer Memory Copy",
                        cuMemcpyPeerAsync(destMemory, destContext,
                                          srcMemory , srcContext ,
                                          bytes,
                                          usingStream));
      }
#else
      OCCA_CHECK(false,
                 "ACC version ["
                 << ((int) (ACC_VERSION / 1000))
                 << '.'
                 << ((int) ((ACC_VERSION % 100) / 10))
                 << "] does not support Peer-to-Peer");
		 #endif */
}

    occa::device wrapDevice(CUdevice device, CUcontext context){
     

      perror("wrap device not yet impimented for OpenACC");

      /* occa::device dev;
      device_t<ACC> &dHandle   = *(new device_t<ACC>());
      ACCDeviceData_t &devData = *(new ACCDeviceData_t);

      dev.dHandle = &dHandle;

      //---[ Setup ]----------
      dHandle.data = &devData;

      devData.device     = device;
      devData.context    = context;
      devData.p2pEnabled = false;
      //======================

      dHandle.modelID_ = library::deviceModelID(dHandle.getIdentifier());
      dHandle.id_      = library::genDeviceID();

      dHandle.currentStream = dHandle.createStream();

      return dev; */
    }
  }

  /* const CUarray_format accFormats[8] = {CU_AD_FORMAT_UNSIGNED_INT8,
                                         CU_AD_FORMAT_UNSIGNED_INT16,
                                         CU_AD_FORMAT_UNSIGNED_INT32,
                                         CU_AD_FORMAT_SIGNED_INT8,
                                         CU_AD_FORMAT_SIGNED_INT16,
                                         CU_AD_FORMAT_SIGNED_INT32,
                                         CU_AD_FORMAT_HALF,
                                         CU_AD_FORMAT_FLOAT};*/

  template <>
  void* formatType::format<occa::ACC>() const {
    return ((void*) &(accFormats[format_]));
    }

  const int ACC_ADDRESS_NONE  = 0; // accBoundaryModeNone
  const int ACC_ADDRESS_CLAMP = 1; // accBoundaryModeClamp
  // accBoundaryModeTrap = 2
  //==================================

  //---[ Kernel ]---------------------
  template <>
  kernel_t<ACC>::kernel_t(){
    strMode = "ACC";

    data    = NULL;
    dHandle = NULL;

    dims  = 1;
    inner = occa::dim(1,1,1);
    outer = occa::dim(1,1,1);

    maximumInnerDimSize_ = 0;
    preferredDimSize_    = 0;
  }

  template <>
  kernel_t<ACC>::kernel_t(const kernel_t<ACC> &k){
    *this = k;
  }

  template <>
  kernel_t<ACC>& kernel_t<ACC>::operator = (const kernel_t<ACC> &k){
    data    = k.data;
    dHandle = k.dHandle;

    metaInfo = k.metaInfo;

    dims  = k.dims;
    inner = k.inner;
    outer = k.outer;

    nestedKernels = k.nestedKernels;

    preferredDimSize_ = k.preferredDimSize_;

    return *this;
  }

  template <>
  kernel_t<ACC>::~kernel_t(){}

  template <>
  void* kernel_t<ACC>::getKernelHandle(){
    OCCA_EXTRACT_DATA(ACC, Kernel);

    return data_.function;
  }

  template <>
  void* kernel_t<ACC>::getProgramHandle(){
    OCCA_EXTRACT_DATA(ACC, Kernel);

    return data_.module;
  }

  template <>
  std::string kernel_t<ACC>::fixBinaryName(const std::string &filename){
    return filename;
  }

  template <>
  kernel_t<ACC>* kernel_t<ACC>::buildFromSource(const std::string &filename,
                                                  const std::string &functionName,
                                                  const kernelInfo &info_){

    name = functionName;

    OCCA_EXTRACT_DATA(ACC, Kernel);
    kernelInfo info = info_;

    dHandle->addOccaHeadersToInfo(info);

    const std::string hash = getFileContentHash(filename,
                                                dHandle->getInfoSalt(info));

    const std::string hashDir       = hashDirFor(filename, hash);
    const std::string sourceFile    = hashDir + kc::sourceFile;
    const std::string binaryFile    = hashDir + fixBinaryName(kc::binaryFile);
    const std::string ptxBinaryFile = hashDir + "ptxBinary.o";
    bool foundBinary = true;

    if (!haveHash(hash, 0))
      waitForHash(hash, 0);
    else if (sys::fileExists(binaryFile))
      releaseHash(hash, 0);
    else
      foundBinary = false;

    if (foundBinary) {
      if(verboseCompilation_f)
        std::cout << "Found cached binary of [" << compressFilename(filename) << "] in [" << compressFilename(binaryFile) << "]\n";

      return buildFromBinary(binaryFile, functionName);
    }

    createSourceFileFrom(filename, hashDir, info);

    std::string archSM = "";

    if((dHandle->compilerFlags.find("-arch=sm_") == std::string::npos) &&
       (            info.flags.find("-arch=sm_") == std::string::npos)){

      std::stringstream archSM_;

      int major, minor;
      OCCA_ACC_CHECK("Kernel (" + functionName + ") : Getting ACC Device Arch",
                      cuDeviceComputeCapability(&major, &minor, data_.device) );

      archSM_ << " -arch=sm_" << major << minor << ' ';

      archSM = archSM_.str();
    }

    std::stringstream command;

    if(verboseCompilation_f)
      std::cout << "Compiling [" << functionName << "]\n";

#if 0
    //---[ PTX Check Command ]----------
    if(dHandle->compilerEnvScript.size())
      command << dHandle->compilerEnvScript << " && ";

    command << dHandle->compiler
            << " -I."
            << " -I"  << env::OCCA_DIR << "include"
            << ' '          << dHandle->compilerFlags
#  if (OCCA_OS == WINDOWS_OS)
            << " -D OCCA_OS=WINDOWS_OS -D _MSC_VER=1800"
#  endif
            << archSM
            << " -Xptxas -v,-dlcm=cg"
            << ' '          << info.flags
            << " -x cu -c " << sourceFile
            << " -o "       << ptxBinaryFile;

    const std::string &ptxCommand = command.str();

    if(verboseCompilation_f)
      std::cout << "Compiling [" << functionName << "]\n" << ptxCommand << "\n";

#  if (OCCA_OS & (LINUX_OS | OSX_OS))
    ignoreResult( system(ptxCommand.c_str()) );
#  else
    ignoreResult( system(("\"" +  ptxCommand + "\"").c_str()) );
#  endif
#endif

    //---[ Compiling Command ]----------
    command.str("");

    command << dHandle->compiler
            << " -o "       << binaryFile
            << " -ptx -I."
            << " -I"  << env::OCCA_DIR << "include"
#  if (OCCA_OS == WINDOWS_OS)
            << " -D OCCA_OS=WINDOWS_OS -D _MSC_VER=1800"
#  endif
            << ' '          << dHandle->compilerFlags
            << archSM
            << ' '          << info.flags
            << " -x cu "    << sourceFile;

    const std::string &sCommand = command.str();

    if(verboseCompilation_f)
      std::cout << sCommand << '\n';

    const int compileError = system(sCommand.c_str());

    if(compileError){
      releaseHash(hash, 0);
      OCCA_CHECK(false, "Compilation error");
    }

    const CUresult moduleLoadError = cuModuleLoad(&data_.module,
                                                  binaryFile.c_str());

    if(moduleLoadError)
      releaseHash(hash, 0);

    OCCA_ACC_CHECK("Kernel (" + functionName + ") : Loading Module",
                    moduleLoadError);

    const CUresult moduleGetFunctionError = cuModuleGetFunction(&data_.function,
                                                                data_.module,
                                                                functionName.c_str());

    if(moduleGetFunctionError)
      releaseHash(hash, 0);

    OCCA_ACC_CHECK("Kernel (" + functionName + ") : Loading Function",
                    moduleGetFunctionError);

    releaseHash(hash, 0);

    return this;
  }

  template <>
  kernel_t<ACC>* kernel_t<ACC>::buildFromBinary(const std::string &filename,
                                                 const std::string &functionName){

    name = functionName;

    OCCA_EXTRACT_DATA(ACC, Kernel);

    OCCA_ACC_CHECK("Kernel (" + functionName + ") : Loading Module",
                    cuModuleLoad(&data_.module, filename.c_str()));

    OCCA_ACC_CHECK("Kernel (" + functionName + ") : Loading Function",
                    cuModuleGetFunction(&data_.function, data_.module, functionName.c_str()));

    return this;
  }

  template <>
  kernel_t<ACC>* kernel_t<ACC>::loadFromLibrary(const char *cache,
                                                  const std::string &functionName){
    OCCA_EXTRACT_DATA(ACC, Kernel);

    OCCA_ACC_CHECK("Kernel (" + functionName + ") : Loading Module",
                    cuModuleLoadData(&data_.module, cache));

    OCCA_ACC_CHECK("Kernel (" + functionName + ") : Loading Function",
                    cuModuleGetFunction(&data_.function, data_.module, functionName.c_str()));

    return this;
  }

  template <>
  uintptr_t kernel_t<ACC>::maximumInnerDimSize(){
    if(maximumInnerDimSize_)
      return maximumInnerDimSize_;

    OCCA_EXTRACT_DATA(ACC, Kernel);

    int maxSize;

    OCCA_ACC_CHECK("Kernel: Getting Maximum Inner-Dim Size",
                    cuFuncGetAttribute(&maxSize, CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK, data_.function));

    maximumInnerDimSize_ = (uintptr_t) maxSize;

    return maximumInnerDimSize_;
  }

  template <>
  int kernel_t<ACC>::preferredDimSize(){
    preferredDimSize_ = 32;
    return 32;
  }

  template <>
  void kernel_t<ACC>::runFromArguments(const int kArgc, const kernelArg *kArgs){
    ACCKernelData_t &data_ = *((ACCKernelData_t*) data);
    CUfunction function_ = data_.function;

    int occaKernelInfoArgs = 0;
    int argc = 0;

    data_.vArgs = new void*[1 + kernelArg::argumentCount(kArgc, kArgs)];
    data_.vArgs[argc++] = &occaKernelInfoArgs;
    for(int i = 0; i < kArgc; ++i) {
      for(int j = 0; j < kArgs[i].argc; ++j){
        data_.vArgs[argc++] = kArgs[i].args[j].ptr();
      }
    }

    OCCA_ACC_CHECK("Launching Kernel",
                    cuLaunchKernel(function_,
                                   outer.x, outer.y, outer.z,
                                   inner.x, inner.y, inner.z,
                                   0, *((CUstream*) dHandle->currentStream),
                                   data_.vArgs, 0));
    delete [] data_.vArgs;
  }

  template <>
  void kernel_t<ACC>::free(){
    OCCA_EXTRACT_DATA(ACC, Kernel);

    OCCA_ACC_CHECK("Kernel (" + name + ") : Unloading Module",
                    cuModuleUnload(data_.module));

    delete (ACCKernelData_t*) this->data;
  }
  //==================================


  //---[ Memory ]---------------------
  template <>
  memory_t<ACC>::memory_t(){
    strMode = "ACC";

    memInfo = memFlag::none;

    handle    = NULL;
    mappedPtr = NULL;
    uvaPtr    = NULL;

    dHandle = NULL;
    size    = 0;

    textureInfo.arg = NULL;

    textureInfo.dim = 1;

    textureInfo.w  = textureInfo.h = textureInfo.d = 0;
  }

  template <>
  memory_t<ACC>::memory_t(const memory_t<ACC> &m){
    *this = m;
  }

  template <>
  memory_t<ACC>& memory_t<ACC>::operator = (const memory_t<ACC> &m){
    memInfo = m.memInfo;

    handle    = m.handle;
    mappedPtr = m.mappedPtr;
    uvaPtr    = m.uvaPtr;

    dHandle = m.dHandle;
    size    = m.size;

    textureInfo.arg = m.textureInfo.arg;

    textureInfo.dim = m.textureInfo.dim;

    textureInfo.w = m.textureInfo.w;
    textureInfo.h = m.textureInfo.h;
    textureInfo.d = m.textureInfo.d;

    return *this;
  }

  template <>
  memory_t<ACC>::~memory_t(){}

  template <>
  void* memory_t<ACC>::getMemoryHandle(){
    return handle;
  }

  template <>
  void* memory_t<ACC>::getTextureHandle(){
    return (void*) ((ACCTextureData_t*) handle)->array;
  }

  template <>
  void memory_t<ACC>::copyFrom(const void *src,
                                const uintptr_t bytes,
                                const uintptr_t offset){
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + offset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << offset << " , " << (offset + bytes_) << " ]");

    if(!isATexture())
      OCCA_ACC_CHECK("Memory: Copy From",
                      cuMemcpyHtoD(*((CUdeviceptr*) handle) + offset, src, bytes_) );
    else{
      if(textureInfo.dim == 1)
        OCCA_ACC_CHECK("Texture Memory: Copy From",
                        cuMemcpyHtoA(((ACCTextureData_t*) handle)->array, offset, src, bytes_) );
      else{
        ACC_MEMCPY2D info;

        info.srcXInBytes   = 0;
        info.srcY          = 0;
        info.srcMemoryType = CU_MEMORYTYPE_HOST;
        info.srcHost       = src;
        info.srcPitch      = 0;

        info.dstXInBytes   = offset;
        info.dstY          = 0;
        info.dstMemoryType = CU_MEMORYTYPE_ARRAY;
        info.dstArray      = ((ACCTextureData_t*) handle)->array;

        info.WidthInBytes = textureInfo.w * textureInfo.bytesInEntry;
        info.Height       = (bytes_ / info.WidthInBytes);

        cuMemcpy2D(&info);

        dHandle->finish();
      }
    }
  }

  template <>
  void memory_t<ACC>::copyFrom(const memory_v *src,
                                const uintptr_t bytes,
                                const uintptr_t destOffset,
                                const uintptr_t srcOffset){
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + destOffset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << destOffset << " , " << (destOffset + bytes_) << " ]");

    OCCA_CHECK((bytes_ + srcOffset) <= src->size,
               "Source has size [" << src->size << "],"
               << "trying to access [ " << srcOffset << " , " << (srcOffset + bytes_) << " ]");

    void *dstPtr, *srcPtr;

    if(!isATexture())
      dstPtr = handle;
    else
      dstPtr = (void*) ((ACCTextureData_t*) handle)->array;

    if( !(src->isATexture()) )
      srcPtr = src->handle;
    else
      srcPtr = (void*) ((ACCTextureData_t*) src->handle)->array;

    if(!isATexture()){
      if(!src->isATexture())
        OCCA_ACC_CHECK("Memory: Copy From [Memory -> Memory]",
                        cuMemcpyDtoD(*((CUdeviceptr*) dstPtr) + destOffset,
                                     *((CUdeviceptr*) srcPtr) + srcOffset,
                                     bytes_) );
      else
        OCCA_ACC_CHECK("Memory: Copy From [Texture -> Memory]",
                        cuMemcpyAtoD(*((CUdeviceptr*) dstPtr) + destOffset,
                                     (CUarray) srcPtr         , srcOffset,
                                     bytes_) );
    }
    else{
      if(!src->isATexture())
        OCCA_ACC_CHECK("Memory: Copy From [Memory -> Texture]",
                        cuMemcpyDtoA((CUarray) dstPtr         , destOffset,
                                     *((CUdeviceptr*) srcPtr) + srcOffset,
                                     bytes_) );
      else
        OCCA_ACC_CHECK("Memory: Copy From [Texture -> Texture]",
                        cuMemcpyAtoA((CUarray) dstPtr, destOffset,
                                     (CUarray) srcPtr, srcOffset,
                                     bytes_) );
    }
  }

  template <>
  void memory_t<ACC>::copyTo(void *dest,
                              const uintptr_t bytes,
                              const uintptr_t offset){
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + offset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << offset << " , " << (offset + bytes_) << " ]");

    if(!isATexture())
      OCCA_ACC_CHECK("Memory: Copy To",
                      cuMemcpyDtoH(dest, *((CUdeviceptr*) handle) + offset, bytes_) );
    else{
      if(textureInfo.dim == 1)
        OCCA_ACC_CHECK("Texture Memory: Copy To",
                        cuMemcpyAtoH(dest, ((ACCTextureData_t*) handle)->array, offset, bytes_) );
      else{
        ACC_MEMCPY2D info;

        info.srcXInBytes   = offset;
        info.srcY          = 0;
        info.srcMemoryType = CU_MEMORYTYPE_ARRAY;
        info.srcArray      = ((ACCTextureData_t*) handle)->array;

        info.dstXInBytes   = 0;
        info.dstY          = 0;
        info.dstMemoryType = CU_MEMORYTYPE_HOST;
        info.dstHost       = dest;
        info.dstPitch      = 0;

        info.WidthInBytes = textureInfo.w * textureInfo.bytesInEntry;
        info.Height       = (bytes_ / info.WidthInBytes);

        cuMemcpy2D(&info);

        dHandle->finish();
      }
    }
  }

  template <>
  void memory_t<ACC>::copyTo(memory_v *dest,
                              const uintptr_t bytes,
                              const uintptr_t destOffset,
                              const uintptr_t srcOffset){
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + srcOffset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << srcOffset << " , " << (srcOffset + bytes_) << " ]");

    OCCA_CHECK((bytes_ + destOffset) <= dest->size,
               "Destination has size [" << dest->size << "],"
               << "trying to access [ " << destOffset << " , " << (destOffset + bytes_) << " ]");

    void *dstPtr, *srcPtr;

    if(!isATexture())
      srcPtr = handle;
    else
      srcPtr = (void*) ((ACCTextureData_t*) handle)->array;

    if( !(dest->isATexture()) )
      dstPtr = dest->handle;
    else
      dstPtr = (void*) ((ACCTextureData_t*) dest->handle)->array;

    if(!isATexture()){
      if(!dest->isATexture())
        OCCA_ACC_CHECK("Memory: Copy To [Memory -> Memory]",
                        cuMemcpyDtoD(*((CUdeviceptr*) dstPtr) + destOffset,
                                     *((CUdeviceptr*) srcPtr) + srcOffset,
                                     bytes_) );
      else
        OCCA_ACC_CHECK("Memory: Copy To [Memory -> Texture]",
                        cuMemcpyDtoA((CUarray) dstPtr         , destOffset,
                                     *((CUdeviceptr*) srcPtr) + srcOffset,
                                     bytes_) );
    }
    else{
      if(dest->isATexture())
        OCCA_ACC_CHECK("Memory: Copy To [Texture -> Memory]",
                        cuMemcpyAtoD(*((CUdeviceptr*) dstPtr) + destOffset,
                                     (CUarray) srcPtr         , srcOffset,
                                     bytes_) );
      else
        OCCA_ACC_CHECK("Memory: Copy To [Texture -> Texture]",
                        cuMemcpyAtoA((CUarray) dstPtr, destOffset,
                                     (CUarray) srcPtr, srcOffset,
                                     bytes_) );
    }
  }

  template <>
  void memory_t<ACC>::asyncCopyFrom(const void *src,
                                     const uintptr_t bytes,
                                     const uintptr_t offset){
    const CUstream &stream = *((CUstream*) dHandle->currentStream);
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + offset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << offset << " , " << (offset + bytes_) << " ]");

    if(!isATexture())
      OCCA_ACC_CHECK("Memory: Asynchronous Copy From",
                      cuMemcpyHtoDAsync(*((CUdeviceptr*) handle) + offset, src, bytes_, stream) );
    else
      OCCA_ACC_CHECK("Texture Memory: Asynchronous Copy From",
                      cuMemcpyHtoAAsync(((ACCTextureData_t*) handle)->array, offset, src, bytes_, stream) );
  }

  template <>
  void memory_t<ACC>::asyncCopyFrom(const memory_v *src,
                                     const uintptr_t bytes,
                                     const uintptr_t destOffset,
                                     const uintptr_t srcOffset){
    const CUstream &stream = *((CUstream*) dHandle->currentStream);
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + destOffset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << destOffset << " , " << (destOffset + bytes_) << " ]");

    OCCA_CHECK((bytes_ + srcOffset) <= src->size,
               "Source has size [" << src->size << "],"
               << "trying to access [ " << srcOffset << " , " << (srcOffset + bytes_) << " ]");

    void *dstPtr, *srcPtr;

    if(!isATexture())
      dstPtr = handle;
    else
      dstPtr = (void*) ((ACCTextureData_t*) handle)->array;

    if( !(src->isATexture()) )
      srcPtr = src->handle;
    else
      srcPtr = (void*) ((ACCTextureData_t*) src->handle)->array;

    if(!isATexture()){
      if(!src->isATexture())
        OCCA_ACC_CHECK("Memory: Asynchronous Copy From [Memory -> Memory]",
                        cuMemcpyDtoDAsync(*((CUdeviceptr*) dstPtr) + destOffset,
                                          *((CUdeviceptr*) srcPtr) + srcOffset,
                                          bytes_, stream) );
      else
        OCCA_ACC_CHECK("Memory: Asynchronous Copy From [Texture -> Memory]",
                        cuMemcpyAtoD(*((CUdeviceptr*) dstPtr) + destOffset,
                                     (CUarray) srcPtr         , srcOffset,
                                     bytes_) );
    }
    else{
      if(src->isATexture())
        OCCA_ACC_CHECK("Memory: Asynchronous Copy From [Memory -> Texture]",
                        cuMemcpyDtoA((CUarray) dstPtr         , destOffset,
                                     *((CUdeviceptr*) srcPtr) + srcOffset,
                                     bytes_) );
      else
        OCCA_ACC_CHECK("Memory: Asynchronous Copy From [Texture -> Texture]",
                        cuMemcpyAtoA((CUarray) dstPtr, destOffset,
                                     (CUarray) srcPtr, srcOffset,
                                     bytes_) );
    }
  }

  template <>
  void memory_t<ACC>::asyncCopyTo(void *dest,
                                   const uintptr_t bytes,
                                   const uintptr_t offset){
    const CUstream &stream = *((CUstream*) dHandle->currentStream);
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + offset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << offset << " , " << (offset + bytes_) << " ]");

    if(!isATexture())
      OCCA_ACC_CHECK("Memory: Asynchronous Copy To",
                      cuMemcpyDtoHAsync(dest, *((CUdeviceptr*) handle) + offset, bytes_, stream) );
    else
      OCCA_ACC_CHECK("Texture Memory: Asynchronous Copy To",
                      cuMemcpyAtoHAsync(dest,((ACCTextureData_t*) handle)->array, offset, bytes_, stream) );
  }

  template <>
  void memory_t<ACC>::asyncCopyTo(memory_v *dest,
                                   const uintptr_t bytes,
                                   const uintptr_t destOffset,
                                   const uintptr_t srcOffset){
    const CUstream &stream = *((CUstream*) dHandle->currentStream);
    const uintptr_t bytes_ = (bytes == 0) ? size : bytes;

    OCCA_CHECK((bytes_ + srcOffset) <= size,
               "Memory has size [" << size << "],"
               << "trying to access [ " << srcOffset << " , " << (srcOffset + bytes_) << " ]");

    OCCA_CHECK((bytes_ + destOffset) <= dest->size,
               "Destination has size [" << dest->size << "],"
               << "trying to access [ " << destOffset << " , " << (destOffset + bytes_) << " ]");

    void *dstPtr, *srcPtr;

    if(!isATexture())
      srcPtr = handle;
    else
      srcPtr = (void*) ((ACCTextureData_t*) handle)->array;

    if( !(dest->isATexture()) )
      dstPtr = dest->handle;
    else
      dstPtr = (void*) ((ACCTextureData_t*) dest->handle)->array;

    if(!isATexture()){
      if(!dest->isATexture())
        OCCA_ACC_CHECK("Memory: Asynchronous Copy To [Memory -> Memory]",
                        cuMemcpyDtoDAsync(*((CUdeviceptr*) dstPtr) + destOffset,
                                          *((CUdeviceptr*) srcPtr) + srcOffset,
                                          bytes_, stream) );
      else
        OCCA_ACC_CHECK("Memory: Asynchronous Copy To [Memory -> Texture]",
                        cuMemcpyDtoA((CUarray) dstPtr         , destOffset,
                                     *((CUdeviceptr*) srcPtr) + srcOffset,
                                     bytes_) );
    }
    else{
      if(dest->isATexture())
        OCCA_ACC_CHECK("Memory: Asynchronous Copy To [Texture -> Memory]",
                        cuMemcpyAtoD(*((CUdeviceptr*) dstPtr) + destOffset,
                                     (CUarray) srcPtr         , srcOffset,
                                     bytes_) );
      else
        OCCA_ACC_CHECK("Memory: Asynchronous Copy To [Texture -> Texture]",
                        cuMemcpyAtoA((CUarray) dstPtr, destOffset,
                                     (CUarray) srcPtr, srcOffset,
                                     bytes_) );
    }
  }

  template <>
  void memory_t<ACC>::mappedFree(){
    if(isMapped()){
      OCCA_ACC_CHECK("Device: mappedFree()",
                      cuMemFreeHost(mappedPtr));

      delete (CUdeviceptr*) handle;

      size = 0;
    }
  }

  template <>
  void memory_t<ACC>::mappedDetach(){
    if(isMapped()){
      delete (CUdeviceptr*) handle;

      size = 0;
    }
  }

  template <>
  void memory_t<ACC>::free(){
    if(!isATexture()){
      cuMemFree(*((CUdeviceptr*) handle));
      delete (CUdeviceptr*) handle;
   }
    else{
      CUarray &array        = ((ACCTextureData_t*) handle)->array;
      CUsurfObject &surface = ((ACCTextureData_t*) handle)->surface;

      cuArrayDestroy(array);
      cuSurfObjectDestroy(surface);

      delete (ACCTextureData_t*) handle;
      delete (CUaddress_mode*)    textureInfo.arg;
      textureInfo.arg = NULL;
    }

    handle = NULL;

    size = 0;
  }

  template <>
  void memory_t<ACC>::detach(){
    if(!isATexture()){
      delete (CUdeviceptr*) handle;
    }
    else{
      delete (ACCTextureData_t*) handle;
      delete (CUaddress_mode*)    textureInfo.arg;
      textureInfo.arg = NULL;
    }

    handle = NULL;

    size = 0;
  }
  //==================================


  //---[ Device ]---------------------
  template <>
  device_t<ACC>::device_t() {
    strMode = "ACC";

    data = NULL;

    uvaEnabled_ = false;

    bytesAllocated = 0;

    getEnvironmentVariables();
  }

  template <>
  device_t<ACC>::device_t(const device_t<ACC> &d){
    *this = d;
  }

  template <>
  device_t<ACC>& device_t<ACC>::operator = (const device_t<ACC> &d){
    modelID_ = d.modelID_;
    id_      = d.id_;

    data = d.data;

    uvaEnabled_    = d.uvaEnabled_;
    uvaMap         = d.uvaMap;
    uvaDirtyMemory = d.uvaDirtyMemory;

    compiler      = d.compiler;
    compilerFlags = d.compilerFlags;

    bytesAllocated = d.bytesAllocated;

    return *this;
  }

  template <>
  void* device_t<ACC>::getContextHandle(){
    OCCA_EXTRACT_DATA(ACC, Device);

    return (void*) data_.context;
  }

  template <>
  void device_t<ACC>::setup(argInfoMap &aim){
    acc::init();
    properties = aim;

    data = new ACCDeviceData_t;

    OCCA_EXTRACT_DATA(ACC, Device);

    data_.p2pEnabled = false;


    OCCA_CHECK(aim.has("deviceID"),
               "[ACC] device not given [deviceID]");

    const int deviceID = aim.iGet("deviceID");

    OCCA_ACC_CHECK("Device: Creating Device",
                    cuDeviceGet(&data_.device, deviceID));

    OCCA_ACC_CHECK("Device: Creating Context",
                    cuCtxCreate(&data_.context, CU_CTX_SCHED_AUTO, data_.device));
  }

  template <>
  void device_t<ACC>::addOccaHeadersToInfo(kernelInfo &info_){
    info_.mode = ACC;
  }

  template <>
  std::string device_t<ACC>::getInfoSalt(const kernelInfo &info_){
    std::stringstream salt;

    salt << "ACC"
         << info_.salt()
         << parserVersion
         << compilerEnvScript
         << compiler
         << compilerFlags;

    return salt.str();
  }

  template <>
  deviceIdentifier device_t<ACC>::getIdentifier() const {
    deviceIdentifier dID;

    dID.mode_ = ACC;

    const size_t archPos = compilerFlags.find("-arch=sm_");

    if(archPos == std::string::npos){
      OCCA_EXTRACT_DATA(ACC, Device);

      std::stringstream archSM_;

      int major, minor;
      OCCA_ACC_CHECK("Getting ACC Device Arch",
                      cuDeviceComputeCapability(&major, &minor, data_.device) );

      archSM_ << major << minor;

      dID.flagMap["sm_arch"] = archSM_.str();
    }
    else{
      const char *c0 = (compilerFlags.c_str() + archPos);
      const char *c1 = c0;

      while((*c1 != '\0') && (*c1 != ' '))
        ++c1;

      dID.flagMap["sm_arch"] = std::string(c0, c1 - c0);
    }

    return dID;
  }

  template <>
  void device_t<ACC>::getEnvironmentVariables(){
    char *c_compiler = getenv("OCCA_ACC_COMPILER");

    if(c_compiler != NULL)
      compiler = std::string(c_compiler);
    else
      compiler = "nvcc";

    char *c_compilerFlags = getenv("OCCA_ACC_COMPILER_FLAGS");

    if(c_compilerFlags != NULL)
      compilerFlags = std::string(c_compilerFlags);
    else{
#if OCCA_DEBUG_ENABLED
      compilerFlags = "-g";
#else
      compilerFlags = "";
#endif
    }
  }

  template <>
  void device_t<ACC>::appendAvailableDevices(std::vector<device> &dList){
    acc::init();

    int deviceCount = acc::getDeviceCount();

    for(int i = 0; i < deviceCount; ++i){
      device d;
      d.setup("ACC", i, 0);

      dList.push_back(d);
    }
  }

  template <>
  void device_t<ACC>::setCompiler(const std::string &compiler_){
    compiler = compiler_;
  }

  template <>
  void device_t<ACC>::setCompilerEnvScript(const std::string &compilerEnvScript_){
    compilerEnvScript = compilerEnvScript_;
  }

  template <>
  void device_t<ACC>::setCompilerFlags(const std::string &compilerFlags_){
    compilerFlags = compilerFlags_;
  }

  template <>
  void device_t<ACC>::flush(){}

  template <>
  void device_t<ACC>::finish(){
    OCCA_ACC_CHECK("Device: Finish",
                    cuStreamSynchronize(*((CUstream*) currentStream)) );
  }

  template <>
  bool device_t<ACC>::fakesUva(){
    return true;
  }

  template <>
  void device_t<ACC>::waitFor(streamTag tag){
    OCCA_ACC_CHECK("Device: Waiting For Tag",
                    cuEventSynchronize(tag.cuEvent()));
  }

  template <>
  stream_t device_t<ACC>::createStream(){
    OCCA_EXTRACT_DATA(ACC, Device);

    CUstream *retStream = new CUstream;

    OCCA_ACC_CHECK("Device: Setting Context",
                    cuCtxSetCurrent(data_.context));

    OCCA_ACC_CHECK("Device: createStream",
                    cuStreamCreate(retStream, CU_STREAM_DEFAULT));

    return retStream;
  }

  template <>
  void device_t<ACC>::freeStream(stream_t s){
    OCCA_ACC_CHECK("Device: freeStream",
                    cuStreamDestroy( *((CUstream*) s) ));

    delete (CUstream*) s;
  }

  template <>
  stream_t device_t<ACC>::wrapStream(void *handle_){
    return handle_;
  }

  template <>
  streamTag device_t<ACC>::tagStream(){
    OCCA_EXTRACT_DATA(ACC, Device);

    streamTag ret;

    OCCA_ACC_CHECK("Device: Setting Context",
                    cuCtxSetCurrent(data_.context));

    OCCA_ACC_CHECK("Device: Tagging Stream (Creating Tag)",
                    cuEventCreate(&(ret.cuEvent()), CU_EVENT_DEFAULT));

    OCCA_ACC_CHECK("Device: Tagging Stream",
                    cuEventRecord(ret.cuEvent(), 0));

    return ret;
  }

  template <>
  double device_t<ACC>::timeBetween(const streamTag &startTag, const streamTag &endTag){
    OCCA_ACC_CHECK("Device: Waiting for endTag",
                    cuEventSynchronize(endTag.cuEvent()));

    float msTimeTaken;
    OCCA_ACC_CHECK("Device: Timing Between Tags",
                    cuEventElapsedTime(&msTimeTaken, startTag.cuEvent(), endTag.cuEvent()));

    return (double) (1.0e-3 * (double) msTimeTaken);
  }

  template <>
  std::string device_t<ACC>::fixBinaryName(const std::string &filename){
    return filename;
  }

  template <>
  kernel_v* device_t<ACC>::buildKernelFromSource(const std::string &filename,
                                                 const std::string &functionName,
                                                 const kernelInfo &info_){
    OCCA_EXTRACT_DATA(ACC, Device);

    OCCA_ACC_CHECK("Device: Setting Context",
                    cuCtxSetCurrent(data_.context));

    kernel_v *k = new kernel_t<ACC>;

    k->dHandle = this;
    k->data    = new ACCKernelData_t;

    ACCKernelData_t &kData_ = *((ACCKernelData_t*) k->data);

    kData_.device  = data_.device;
    kData_.context = data_.context;

    k->buildFromSource(filename, functionName, info_);

    return k;
  }

  template <>
  kernel_v* device_t<ACC>::buildKernelFromBinary(const std::string &filename,
                                                 const std::string &functionName){
    OCCA_EXTRACT_DATA(ACC, Device);

    kernel_v *k = new kernel_t<ACC>;

    k->dHandle = this;
    k->data    = new ACCKernelData_t;

    ACCKernelData_t &kData_ = *((ACCKernelData_t*) k->data);

    kData_.device  = data_.device;
    kData_.context = data_.context;

    k->buildFromBinary(filename, functionName);
    return k;
  }

  template <>
  void device_t<ACC>::cacheKernelInLibrary(const std::string &filename,
                                            const std::string &functionName,
                                            const kernelInfo &info_){
#if 0
    //---[ Creating shared library ]----
    kernel tmpK = occa::device(this).buildKernelFromSource(filename, functionName, info_);
    tmpK.free();

    kernelInfo info = info_;

    addOccaHeadersToInfo(info);

    std::string cachedBinary = getCachedName(filename, getInfoSalt(info));
    std::string contents     = readFile(cachedBinary);
    //==================================

    library::infoID_t infoID;

    infoID.modelID    = modelID_;
    infoID.kernelName = functionName;

    library::infoHeader_t &header = library::headerMap[infoID];

    header.fileID = -1;
    header.mode   = ACC;

    const std::string flatDevID = getIdentifier().flattenFlagMap();

    header.flagsOffset = library::addToScratchPad(flatDevID);
    header.flagsBytes  = flatDevID.size();

    header.contentOffset = library::addToScratchPad(contents);
    header.contentBytes  = contents.size();

    header.kernelNameOffset = library::addToScratchPad(functionName);
    header.kernelNameBytes  = functionName.size();
#endif
  }

  template <>
  kernel_v* device_t<ACC>::loadKernelFromLibrary(const char *cache,
                                                  const std::string &functionName){
#if 0
    OCCA_EXTRACT_DATA(ACC, Device);

    kernel_v *k = new kernel_t<ACC>;

    k->dHandle = this;
    k->data    = new ACCKernelData_t;

    ACCKernelData_t &kData_ = *((ACCKernelData_t*) k->data);

    kData_.device  = data_.device;
    kData_.context = data_.context;

    k->loadFromLibrary(cache, functionName);
    return k;
#endif
    return NULL;
  }

  template <>
  memory_v* device_t<ACC>::wrapMemory(void *handle_,
                                       const uintptr_t bytes){
    memory_v *mem = new memory_t<ACC>;

    mem->dHandle = this;
    mem->size    = bytes;
    mem->handle  = new CUdeviceptr;
    ::memcpy(mem->handle, &handle_, sizeof(CUdeviceptr));

    mem->memInfo |= memFlag::isAWrapper;

    return mem;
  }

  template <>
  memory_v* device_t<ACC>::wrapTexture(void *handle_,
                                        const int dim, const occa::dim &dims,
                                        occa::formatType type, const int permissions){
    memory_v *mem = new memory_t<ACC>;

    mem->dHandle = this;
    mem->size    = ((dim == 1) ? dims.x : (dims.x * dims.y)) * type.bytes();
    mem->handle  = new CUdeviceptr;
    ::memcpy(mem->handle, &handle_, sizeof(CUdeviceptr));

    mem->memInfo |= (memFlag::isATexture |
                     memFlag::isAWrapper);

    mem->textureInfo.dim = dim;

    mem->textureInfo.w = dims.x;
    mem->textureInfo.h = dims.y;
    mem->textureInfo.d = dims.z;

    mem->textureInfo.bytesInEntry = type.bytes();

    return mem;
  }

  template <>
  memory_v* device_t<ACC>::malloc(const uintptr_t bytes,
                                   void *src){
    OCCA_EXTRACT_DATA(ACC, Device);

    memory_v *mem = new memory_t<ACC>;

    mem->dHandle = this;
    mem->handle  = new CUdeviceptr;
    mem->size    = bytes;

    OCCA_ACC_CHECK("Device: Setting Context",
                    cuCtxSetCurrent(data_.context));

    OCCA_ACC_CHECK("Device: malloc",
                    cuMemAlloc((CUdeviceptr*) mem->handle, bytes));

    if(src != NULL)
      mem->copyFrom(src, bytes, 0);

    return mem;
  }

  template <>
  memory_v* device_t<ACC>::textureAlloc(const int dim, const occa::dim &dims,
                                         void *src,
                                         occa::formatType type, const int permissions){
    OCCA_EXTRACT_DATA(ACC, Device);

    memory_v *mem = new memory_t<ACC>;

    mem->dHandle = this;
    mem->handle  = new ACCTextureData_t;
    mem->size    = ((dim == 1) ? dims.x : (dims.x * dims.y)) * type.bytes();

    mem->memInfo |= memFlag::isATexture;

    mem->textureInfo.dim = dim;

    mem->textureInfo.w = dims.x;
    mem->textureInfo.h = dims.y;
    mem->textureInfo.d = dims.z;

    mem->textureInfo.bytesInEntry = type.bytes();

    CUarray &array        = ((ACCTextureData_t*) mem->handle)->array;
    CUsurfObject &surface = ((ACCTextureData_t*) mem->handle)->surface;

    ACC_ARRAY_DESCRIPTOR arrayDesc;
    ACC_RESOURCE_DESC surfDesc;

    memset(&arrayDesc, 0, sizeof(arrayDesc));
    memset(&surfDesc , 0, sizeof(surfDesc));

    arrayDesc.Width       = dims.x;
    arrayDesc.Height      = (dim == 1) ? 0 : dims.y;
    arrayDesc.Format      = *((CUarray_format*) type.format<ACC>());
    arrayDesc.NumChannels = type.count();

    OCCA_ACC_CHECK("Device: Setting Context",
                    cuCtxSetCurrent(data_.context));

    OCCA_ACC_CHECK("Device: Creating Array",
                    cuArrayCreate(&array, (ACC_ARRAY_DESCRIPTOR*) &arrayDesc) );

    surfDesc.res.array.hArray = array;
    surfDesc.resType = CU_RESOURCE_TYPE_ARRAY;

    OCCA_ACC_CHECK("Device: Creating Surface Object",
                    cuSurfObjectCreate(&surface, &surfDesc) );

    mem->textureInfo.arg = new int;
    *((int*) mem->textureInfo.arg) = ACC_ADDRESS_CLAMP;

    mem->copyFrom(src);

    /*
      if(dims == 3){
      ACC_ARRAY3D_DESCRIPTOR arrayDesc;
      memset(&arrayDesc, 0, sizeof(arrayDesc);

      arrayDesc.Width  = size.x;
      arrayDesc.Height = size.y;
      arrayDesc.Depth  = size.z;

      arrayDesc.Format      = type.format<ACC>();
      arrayDesc.NumChannels = type.count();

      cuArray3DCreate(&arr, (ACC_ARRAY3D_DESCRIPTOR*) &arrayDesc);
      }
    */

    return mem;
  }

  template <>
  memory_v* device_t<ACC>::mappedAlloc(const uintptr_t bytes,
                                        void *src){
    OCCA_EXTRACT_DATA(ACC, Device);

    memory_v *mem = new memory_t<ACC>;

    mem->dHandle  = this;
    mem->handle   = new ACCdeviceptr;
    mem->size     = bytes;

    mem->memInfo |= memFlag::isMapped;

    OCCA_ACC_CHECK("Device: Setting Context",
                    cuCtxSetCurrent(data_.context));

    OCCA_ACC_CHECK("Device: malloc host",
                    cuMemAllocHost((void**) &(mem->mappedPtr), bytes));

    OCCA_ACC_CHECK("Device: get device pointer from host",
                    cuMemHostGetDevicePointer((CUdeviceptr*) mem->handle,
                                              mem->mappedPtr,
                                              0));

    if(src != NULL)
      ::memcpy(mem->mappedPtr, src, bytes);

    return mem;
  }

  template <>
  uintptr_t device_t<ACC>::memorySize(){
    OCCA_EXTRACT_DATA(ACC, Device);

    return acc::getDeviceMemorySize(data_.device);
  }

  template <>
  void device_t<ACC>::free(){
    OCCA_EXTRACT_DATA(ACC, Device);

    OCCA_ACC_CHECK("Device: Freeing Context",
                    cuCtxDestroy(data_.context) );

    delete (ACCDeviceData_t*) data;
  }

  template <>
  int device_t<ACC>::simdWidth(){
    if(simdWidth_)
      return simdWidth_;

    OCCA_EXTRACT_DATA(ACC, Device);

    OCCA_ACC_CHECK("Device: Get Warp Size",
                    cuDeviceGetAttribute(&simdWidth_,
                                         ACC_DEVICE_ATTRIBUTE_WARP_SIZE,
                                         data_.device) );

    return simdWidth_;
  }
  //==================================


  //---[ Error Handling ]-------------
  std::string accError(const CUresult errorCode){
    switch(errorCode){
    case ACC_SUCCESS:                              return "ACC_SUCCESS";
    case ACC_ERROR_INVALID_VALUE:                  return "ACC_ERROR_INVALID_VALUE";
    case ACC_ERROR_OUT_OF_MEMORY:                  return "ACC_ERROR_OUT_OF_MEMORY";
    case ACC_ERROR_NOT_INITIALIZED:                return "ACC_ERROR_NOT_INITIALIZED";
    case ACC_ERROR_DEINITIALIZED:                  return "ACC_ERROR_DEINITIALIZED";
    case ACC_ERROR_PROFILER_DISABLED:              return "ACC_ERROR_PROFILER_DISABLED";
    case ACC_ERROR_PROFILER_NOT_INITIALIZED:       return "ACC_ERROR_PROFILER_NOT_INITIALIZED";
    case ACC_ERROR_PROFILER_ALREADY_STARTED:       return "ACC_ERROR_PROFILER_ALREADY_STARTED";
    case ACC_ERROR_PROFILER_ALREADY_STOPPED:       return "ACC_ERROR_PROFILER_ALREADY_STOPPED";
    case ACC_ERROR_NO_DEVICE:                      return "ACC_ERROR_NO_DEVICE";
    case ACC_ERROR_INVALID_DEVICE:                 return "ACC_ERROR_INVALID_DEVICE";
    case ACC_ERROR_INVALID_IMAGE:                  return "ACC_ERROR_INVALID_IMAGE";
    case ACC_ERROR_INVALID_CONTEXT:                return "ACC_ERROR_INVALID_CONTEXT";
    case ACC_ERROR_CONTEXT_ALREADY_CURRENT:        return "ACC_ERROR_CONTEXT_ALREADY_CURRENT";
    case ACC_ERROR_MAP_FAILED:                     return "ACC_ERROR_MAP_FAILED";
    case ACC_ERROR_UNMAP_FAILED:                   return "ACC_ERROR_UNMAP_FAILED";
    case ACC_ERROR_ARRAY_IS_MAPPED:                return "ACC_ERROR_ARRAY_IS_MAPPED";
    case ACC_ERROR_ALREADY_MAPPED:                 return "ACC_ERROR_ALREADY_MAPPED";
    case ACC_ERROR_NO_BINARY_FOR_GPU:              return "ACC_ERROR_NO_BINARY_FOR_GPU";
    case ACC_ERROR_ALREADY_ACQUIRED:               return "ACC_ERROR_ALREADY_ACQUIRED";
    case ACC_ERROR_NOT_MAPPED:                     return "ACC_ERROR_NOT_MAPPED";
    case ACC_ERROR_NOT_MAPPED_AS_ARRAY:            return "ACC_ERROR_NOT_MAPPED_AS_ARRAY";
    case ACC_ERROR_NOT_MAPPED_AS_POINTER:          return "ACC_ERROR_NOT_MAPPED_AS_POINTER";
    case ACC_ERROR_ECC_UNCORRECTABLE:              return "ACC_ERROR_ECC_UNCORRECTABLE";
    case ACC_ERROR_UNSUPPORTED_LIMIT:              return "ACC_ERROR_UNSUPPORTED_LIMIT";
    case ACC_ERROR_CONTEXT_ALREADY_IN_USE:         return "ACC_ERROR_CONTEXT_ALREADY_IN_USE";
    case ACC_ERROR_PEER_ACCESS_UNSUPPORTED:        return "ACC_ERROR_PEER_ACCESS_UNSUPPORTED";
    case ACC_ERROR_INVALID_SOURCE:                 return "ACC_ERROR_INVALID_SOURCE";
    case ACC_ERROR_FILE_NOT_FOUND:                 return "ACC_ERROR_FILE_NOT_FOUND";
    case ACC_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND: return "ACC_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND";
    case ACC_ERROR_SHARED_OBJECT_INIT_FAILED:      return "ACC_ERROR_SHARED_OBJECT_INIT_FAILED";
    case ACC_ERROR_OPERATING_SYSTEM:               return "ACC_ERROR_OPERATING_SYSTEM";
    case ACC_ERROR_INVALID_HANDLE:                 return "ACC_ERROR_INVALID_HANDLE";
    case ACC_ERROR_NOT_FOUND:                      return "ACC_ERROR_NOT_FOUND";
    case ACC_ERROR_NOT_READY:                      return "ACC_ERROR_NOT_READY";
    case ACC_ERROR_LAUNCH_FAILED:                  return "ACC_ERROR_LAUNCH_FAILED";
    case ACC_ERROR_LAUNCH_OUT_OF_RESOURCES:        return "ACC_ERROR_LAUNCH_OUT_OF_RESOURCES";
    case ACC_ERROR_LAUNCH_TIMEOUT:                 return "ACC_ERROR_LAUNCH_TIMEOUT";
    case ACC_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING:  return "ACC_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING";
    case ACC_ERROR_PEER_ACCESS_ALREADY_ENABLED:    return "ACC_ERROR_PEER_ACCESS_ALREADY_ENABLED";
    case ACC_ERROR_PEER_ACCESS_NOT_ENABLED:        return "ACC_ERROR_PEER_ACCESS_NOT_ENABLED";
    case ACC_ERROR_PRIMARY_CONTEXT_ACTIVE:         return "ACC_ERROR_PRIMARY_CONTEXT_ACTIVE";
    case ACC_ERROR_CONTEXT_IS_DESTROYED:           return "ACC_ERROR_CONTEXT_IS_DESTROYED";
    case ACC_ERROR_ASSERT:                         return "ACC_ERROR_ASSERT";
    case ACC_ERROR_TOO_MANY_PEERS:                 return "ACC_ERROR_TOO_MANY_PEERS";
    case ACC_ERROR_HOST_MEMORY_ALREADY_REGISTERED: return "ACC_ERROR_HOST_MEMORY_ALREADY_REGISTERED";
    case ACC_ERROR_HOST_MEMORY_NOT_REGISTERED:     return "ACC_ERROR_HOST_MEMORY_NOT_REGISTERED";
    case ACC_ERROR_NOT_PERMITTED:                  return "ACC_ERROR_NOT_PERMITTED";
    case ACC_ERROR_NOT_SUPPORTED:                  return "ACC_ERROR_NOT_SUPPORTED";
    default:                                        return "UNKNOWN ERROR";
    };
    //==================================
  }
}

#endif
