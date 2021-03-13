#pragma once

#include "dml_common.h"

// Helper for adding tracing events useful in ETW-based perf analysis
// (GPUView/WPA). No telemetry.
class DmlTracing {
 private:
  DmlTracing();
  ~DmlTracing();

  enum TraceLevel
  {
    None = 0,
    LowFrequency = 1,
    All = 10
  };

  TraceLevel trace_level_ = LowFrequency;

 public:
  static DmlTracing& Instance();

  void LogSessionRunStart();
  void LogSessionRunEnd();
  void LogExecutionContextCopyBufferRegion();
  void LogExecutionContextFillBufferWithPattern();
  void LogExecutionContextFlush();
  void LogKernelCompute(const std::string& op_type, const std::string& op_name);

  // GPU timeline
  void LogKernelExecuteBegin(ID3D12GraphicsCommandList* command_list, UINT64 color, const std::string& name);
  void LogKernelExecuteEnd(ID3D12GraphicsCommandList* command_list);
};