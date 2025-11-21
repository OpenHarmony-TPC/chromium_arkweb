// Copyright (c) 2025 Huawei Device Co., Ltd.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CRASHPAD_HANDLER_LINUX_CRASH_REPORT_EXCEPTION_HANDLER_UTILS_H
#define CRASHPAD_HANDLER_LINUX_CRASH_REPORT_EXCEPTION_HANDLER_UTILS_H

#include "third_party/crashpad/crashpad/handler/linux/crash_report_exception_handler.h"
#include <map>
#include <string>

#include "client/crash_report_database.h"
#include "handler/crash_report_upload_thread.h"
#include "handler/linux/exception_handler_server.h"
#include "handler/user_stream_data_source.h"
#include "util/linux/exception_handler_protocol.h"
#include "util/linux/ptrace_connection.h"
#include "util/misc/address_types.h"
#include "util/misc/uuid.h"
#include "third_party/crashpad/crashpad/minidump/minidump_user_extension_stream_data_source.h"

namespace crashpad {

class ProcessSnapshotLinux;
class ProcessSnapshotSanitized;

//! \brief An exception handler that writes crash reports for exceptions
//!     to a CrashReportDatabase.
class CrashReportExceptionHandlerUtils {
public:

CrashReportExceptionHandlerUtils() = default;

~CrashReportExceptionHandlerUtils();

CrashReportExceptionHandlerUtils(const CrashReportExceptionHandlerUtils&) =
      delete;
CrashReportExceptionHandlerUtils& operator=(
      const CrashReportExceptionHandlerUtils&) = delete;

static void InitExtendedUserStream(
  PtraceConnection* connection,
  UserStreamDataSources* extendedUserStream);
};
}
#endif  // CRASHPAD_HANDLER_LINUX_CRASH_REPORT_EXCEPTION_HANDLER_H_