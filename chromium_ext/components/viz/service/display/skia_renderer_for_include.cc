/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkweb/chromium_ext/gpu/config/gpu_finch_features_ext.h"
#include "arkweb/ohos_adapter_ndk/interfaces/ohos_adapter_helper.h"

namespace viz {
#if BUILDFLAG(ARKWEB_PARTIAL_DRAW)
enum CtlPolicy {
  NONE = 0,
  SINGLE = 1,
  MULTI = 2,
};

namespace {
int32_t IsPartialDrawEnable() {
  static std::atomic<int32_t> flag = -1;
  if (flag < 0) {
    bool cloud_ctl = base::FeatureList::IsEnabled(features::kDefaultPartialDraw);
    if (!cloud_ctl) {
      flag = CtlPolicy::NONE;
      return flag;
    }

    auto& system_properties = OHOS::NWeb::OhosAdapterHelper::GetInstance()
                                .GetSystemPropertiesInstance();
    std::string policy = system_properties.GetStringParameter("web.gpu.partial.draw", "none");
    if (policy == "single") {
        flag = CtlPolicy::SINGLE;
    } else if (policy == "multi") {
        flag = CtlPolicy::MULTI;
    } else {
        flag = CtlPolicy::NONE;
    }
  }

  return flag;
}
}

void SkiaRenderer::ClosePostSubBuffer() {
  if (skia_output_surface_ == nullptr) {
    return;
  }
  skia_output_surface_->ClosePostSubBuffer();
}

bool SkiaRenderer::IsPresentBuffersFullDamage(gfx::Rect damage_rect) {
  auto policy = IsPartialDrawEnable();
  if (skia_output_surface_ == nullptr || (policy == CtlPolicy::NONE)) {
    is_partial_damage_ = false;
    return true;
  }

  int buffer_age = skia_output_surface_->GetLastBufferAge();
  if (!buffer_age) {
    skia_output_surface_->SetPresentBufferDamageRect(gfx::Rect(), damage_rect);
    is_partial_damage_ = false;
    return true;
  }

  if (skia_last_damage_rect_ != damage_rect) {
    skia_last_damage_rect_ = damage_rect;
    skia_output_surface_->SetPresentBufferDamageRect(gfx::Rect(), damage_rect);
    is_partial_damage_ = false;
    return true;
  }

  skia_last_damage_rect_ = damage_rect;

  int same_cnt = skia_output_surface_->GetLastBufferSameCnt();
  if (same_cnt <= buffer_age) {
    skia_output_surface_->SetPresentBufferDamageRect(gfx::Rect(), damage_rect);
    is_partial_damage_ = false;
    return true;
  }

  if (!skia_output_surface_->SetPresentBufferDamageRect(damage_rect, damage_rect)) {
    is_partial_damage_ = false;
    return true;
  }

  LOG(DEBUG) << "partial draw damage rect = " << damage_rect.ToString()
             << " buffer_age " << buffer_age << " same_cnt " << same_cnt;
  is_partial_damage_ = true;
  return false;
}
#endif
}
