#include "occa/defines.hpp"

#if OCCA_OPENACC_ENABLED
#  ifndef OCCA_OPENACC_HEADER
#  define OCCA_OPENACC_HEADER

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#include "occa/base.hpp"
#include "occa/library.hpp"

#if (OCCA_OS & (LINUX_OS | OSX_OS))
#  include <dlfcn.h>
#else
#  include <windows.h>
#endif

namespace occa {
  //---[ Data Structs ]---------------
  struct OpenACCKernelData_t {
    void *dlHandle;
    handleFunction_t handle;

    void *vArgs[2*OCCA_MAX_ARGS];
  };

  struct OpenACCDeviceData_t {
    int vendor;
    bool supportsOpenACC;
    std::string OpenACCFlag;
  };
  //==================================


  //---[ Helper Functions ]-----------
  namespace openacc {
    extern std::string notSupported;

    std::string baseCompilerFlag(const int vendor_);
    std::string compilerFlag(const int vendor_,
                             const std::string &compiler);
  }
  //==================================


  //---[ Kernel ]---------------------
  template <>
  kernel_t<OpenACC>::kernel_t();

  template <>
  kernel_t<OpenACC>::kernel_t(const kernel_t &k);

  template <>
  kernel_t<OpenACC>& kernel_t<OpenACC>::operator = (const kernel_t<OpenACC> &k);

  template <>
  kernel_t<OpenACC>::kernel_t(const kernel_t<OpenACC> &k);

  template <>
  void* kernel_t<OpenACC>::getKernelHandle();

  template <>
  std::string kernel_t<OpenACC>::fixBinaryName(const std::string &filename);

  template <>
  kernel_t<OpenACC>* kernel_t<OpenACC>::buildFromSource(const std::string &filename,
                                                      const std::string &functionName,
                                                      const kernelInfo &info_);

  template <>
  kernel_t<OpenACC>* kernel_t<OpenACC>::buildFromBinary(const std::string &filename,
                                                      const std::string &functionName);

  template <>
  kernel_t<OpenACC>* kernel_t<OpenACC>::loadFromLibrary(const char *cache,
                                                      const std::string &functionName);

  template <>
  uintptr_t kernel_t<OpenACC>::maximumInnerDimSize();

  template <>
  int kernel_t<OpenACC>::preferredDimSize();

  template <>
  void kernel_t<OpenACC>::runFromArguments(const int kArgc, const kernelArg *kArgs);

  template <>
  void kernel_t<OpenACC>::free();
  //==================================


  //---[ Memory ]---------------------
  template <>
  memory_t<OpenACC>::memory_t();

  template <>
  memory_t<OpenACC>::memory_t(const memory_t &m);

  template <>
  memory_t<OpenACC>& memory_t<OpenACC>::operator = (const memory_t &m);

  template <>
  void* memory_t<OpenACC>::getMemoryHandle();

  template <>
  void* memory_t<OpenACC>::getTextureHandle();

  template <>
  void memory_t<OpenACC>::copyFrom(const void *src,
                                  const uintptr_t bytes,
                                  const uintptr_t offset);

  template <>
  void memory_t<OpenACC>::copyFrom(const memory_v *src,
                                  const uintptr_t bytes,
                                  const uintptr_t destOffset,
                                  const uintptr_t srcOffset);

  template <>
  void memory_t<OpenACC>::copyTo(void *dest,
                                const uintptr_t bytes,
                                const uintptr_t destOffset);

  template <>
  void memory_t<OpenACC>::copyTo(memory_v *dest,
                                const uintptr_t bytes,
                                const uintptr_t srcOffset,
                                const uintptr_t offset);

  template <>
  void memory_t<OpenACC>::asyncCopyFrom(const void *src,
                                       const uintptr_t bytes,
                                       const uintptr_t destOffset);

  template <>
  void memory_t<OpenACC>::asyncCopyFrom(const memory_v *src,
                                       const uintptr_t bytes,
                                       const uintptr_t srcOffset,
                                       const uintptr_t offset);

  template <>
  void memory_t<OpenACC>::asyncCopyTo(void *dest,
                                     const uintptr_t bytes,
                                     const uintptr_t offset);

  template <>
  void memory_t<OpenACC>::asyncCopyTo(memory_v *dest,
                                     const uintptr_t bytes,
                                     const uintptr_t destOffset,
                                     const uintptr_t srcOffset);

  template <>
  void memory_t<OpenACC>::mappedFree();

  template <>
  void memory_t<OpenACC>::mappedDetach();

  template <>
  void memory_t<OpenACC>::free();

  template <>
  void memory_t<OpenACC>::detach();
  //==================================


  //---[ Device ]---------------------
  template <>
  device_t<OpenACC>::device_t();

  template <>
  device_t<OpenACC>::device_t(const device_t<OpenACC> &k);

  template <>
  device_t<OpenACC>& device_t<OpenACC>::operator = (const device_t<OpenACC> &k);

  template <>
  void* device_t<OpenACC>::getContextHandle();

  template <>
  void device_t<OpenACC>::setup(argInfoMap &aim);

  template <>
  void device_t<OpenACC>::addOccaHeadersToInfo(kernelInfo &info_);

  template <>
  std::string device_t<OpenACC>::getInfoSalt(const kernelInfo &info_);

  template <>
  deviceIdentifier device_t<OpenACC>::getIdentifier() const;

  template <>
  void device_t<OpenACC>::getEnvironmentVariables();

  template <>
  void device_t<OpenACC>::appendAvailableDevices(std::vector<device> &dList);

  template <>
  void device_t<OpenACC>::setCompiler(const std::string &compiler_);

  template <>
  void device_t<OpenACC>::setCompilerEnvScript(const std::string &compilerEnvScript_);

  template <>
  void device_t<OpenACC>::setCompilerFlags(const std::string &compilerFlags_);

  template <>
  void device_t<OpenACC>::flush();

  template <>
  void device_t<OpenACC>::finish();

  template <>
  void device_t<OpenACC>::waitFor(streamTag tag);

  template <>
  stream_t device_t<OpenACC>::createStream();

  template <>
  void device_t<OpenACC>::freeStream(stream_t s);

  template <>
  stream_t device_t<OpenACC>::wrapStream(void *handle_);

  template <>
  streamTag device_t<OpenACC>::tagStream();

  template <>
  double device_t<OpenACC>::timeBetween(const streamTag &startTag, const streamTag &endTag);

  template <>
  std::string device_t<OpenACC>::fixBinaryName(const std::string &filename);

  template <>
  kernel_v* device_t<OpenACC>::buildKernelFromSource(const std::string &filename,
                                                    const std::string &functionName,
                                                    const kernelInfo &info_);

  template <>
  kernel_v* device_t<OpenACC>::buildKernelFromBinary(const std::string &filename,
                                                    const std::string &functionName);

  template <>
  void device_t<OpenACC>::cacheKernelInLibrary(const std::string &filename,
                                              const std::string &functionName,
                                              const kernelInfo &info_);

  template <>
  kernel_v* device_t<OpenACC>::loadKernelFromLibrary(const char *cache,
                                                    const std::string &functionName);

  template <>
  memory_v* device_t<OpenACC>::wrapMemory(void *handle_,
                                         const uintptr_t bytes);

  template <>
  memory_v* device_t<OpenACC>::wrapTexture(void *handle_,
                                          const int dim, const occa::dim &dims,
                                          occa::formatType type, const int permissions);

  template <>
  memory_v* device_t<OpenACC>::malloc(const uintptr_t bytes,
                                     void *src);

  template <>
  memory_v* device_t<OpenACC>::textureAlloc(const int dim, const occa::dim &dims,
                                           void *src,
                                           occa::formatType type, const int permissions);

  template <>
  memory_v* device_t<OpenACC>::mappedAlloc(const uintptr_t bytes,
                                          void *src);

  template <>
  uintptr_t device_t<OpenACC>::memorySize();

  template <>
  void device_t<OpenACC>::free();

  template <>
  int device_t<OpenACC>::simdWidth();
  //==================================
}

#  endif
#endif
