// Copyright (c) 2025 Huawei Device Co., Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/local_frame_mojo_handler.h"
#include "arkweb/chromium_ext/third_party/blink/renderer/core/frame/arkweb_local_frame_mojo_handler_ext.h"

#include "arkweb/build/features/features.h"
#include "base/metrics/histogram_functions.h"
#include "base/numerics/safe_conversions.h"
#include "base/time/time.h"
#include "build/build_config.h"
#include "cc/paint/skia_paint_canvas.h"
#include "services/network/public/cpp/url_loader_completion_status.h"
#include "services/network/public/mojom/url_response_head.mojom.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_provider.h"
#include "third_party/blink/public/common/chrome_debug_urls.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/common/frame/frame_owner_element_type.h"
#include "third_party/blink/public/common/page_state/page_state.h"
#include "third_party/blink/public/mojom/devtools/console_message.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/devtools/inspector_issue.mojom-blink.h"
#include "third_party/blink/public/mojom/frame/frame_owner_properties.mojom-blink.h"
#include "third_party/blink/public/mojom/frame/media_player_action.mojom-blink.h"
#include "third_party/blink/public/mojom/opengraph/metadata.mojom-blink.h"
#include "third_party/blink/public/mojom/timing/resource_timing.mojom-blink-forward.h"
#include "third_party/blink/public/platform/browser_interface_broker_proxy.h"
#include "third_party/blink/public/platform/interface_registry.h"
#include "third_party/blink/public/platform/platform.h"
#include "third_party/blink/public/web/web_local_frame.h"
#include "third_party/blink/public/web/web_local_frame_client.h"
#include "third_party/blink/public/web/web_plugin.h"
#include "third_party/blink/renderer/bindings/core/v8/script_controller.h"
#include "third_party/blink/renderer/bindings/core/v8/script_evaluation_result.h"
#include "third_party/blink/renderer/bindings/core/v8/script_function.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_fullscreen_options.h"
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/element_traversal.h"
#include "third_party/blink/renderer/core/dom/focus_params.h"
#include "third_party/blink/renderer/core/dom/ignore_opens_during_unload_count_incrementer.h"
#include "third_party/blink/renderer/core/editing/editing_utilities.h"
#include "third_party/blink/renderer/core/editing/frame_selection.h"
#include "third_party/blink/renderer/core/editing/surrounding_text.h"
#include "third_party/blink/renderer/core/exported/web_plugin_container_impl.h"
#include "third_party/blink/renderer/core/frame/csp/content_security_policy.h"
#include "third_party/blink/renderer/core/frame/frame_console.h"
#include "third_party/blink/renderer/core/frame/intervention.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_client.h"
#include "third_party/blink/renderer/core/frame/pausable_script_executor.h"
#include "third_party/blink/renderer/core/frame/remote_frame_owner.h"
#include "third_party/blink/renderer/core/frame/reporting_context.h"
#include "third_party/blink/renderer/core/frame/savable_resources.h"
#include "third_party/blink/renderer/core/frame/visual_viewport.h"
#include "third_party/blink/renderer/core/frame/web_local_frame_impl.h"
#include "third_party/blink/renderer/core/fullscreen/fullscreen.h"
#include "third_party/blink/renderer/core/html/html_element.h"
#include "third_party/blink/renderer/core/html/html_embed_element.h"
#include "third_party/blink/renderer/core/html/html_link_element.h"
#include "third_party/blink/renderer/core/html/html_meta_element.h"
#include "third_party/blink/renderer/core/html/html_object_element.h"
#include "third_party/blink/renderer/core/html/media/html_video_element.h"
#include "third_party/blink/renderer/core/input/event_handler.h"
#include "third_party/blink/renderer/core/inspector/console_message.h"
#include "third_party/blink/renderer/core/inspector/main_thread_debugger.h"
#include "third_party/blink/renderer/core/layout/layout_embedded_content.h"
#include "third_party/blink/renderer/core/loader/mixed_content_checker.h"
#include "third_party/blink/renderer/core/messaging/message_port.h"
#include "third_party/blink/renderer/core/navigation_api/navigation_api.h"
#include "third_party/blink/renderer/core/page/chrome_client.h"
#include "third_party/blink/renderer/core/page/focus_controller.h"
#include "third_party/blink/renderer/core/page/page.h"
#include "third_party/blink/renderer/core/paint/cull_rect_updater.h"
#include "third_party/blink/renderer/core/paint/paint_layer_painter.h"
#include "third_party/blink/renderer/core/paint/timing/paint_timing.h"
#include "third_party/blink/renderer/core/script/classic_script.h"
#include "third_party/blink/renderer/core/timing/dom_window_performance.h"
#include "third_party/blink/renderer/core/view_transition/page_swap_event.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_supplement.h"
#include "third_party/blink/renderer/core/xml/document_xpath_evaluator.h"
#include "third_party/blink/renderer/core/xml/xpath_result.h"
#include "third_party/blink/renderer/platform/bindings/exception_state.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_record_builder.h"
#include "third_party/blink/renderer/platform/graphics/unaccelerated_static_bitmap_image.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_timing_utils.h"
#include "third_party/blink/renderer/platform/widget/frame_widget.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkSurface.h"
#if BUILDFLAG(ARKWEB_BLANK_SCREEN_DETECTION)
#include "arkweb/chromium_ext/third_party/blink/renderer/core/paint/timing/blank_screen_detector.h"
#endif
#if BUILDFLAG(ARKWEB_PRECOMPILE)
#include "arkweb/chromium_ext/third_party/blink/renderer/core/v8/v8_code_cache_utils.h"
#endif

#if BUILDFLAG(IS_MAC)
#include "base/apple/foundation_util.h"
#include "third_party/blink/renderer/core/editing/substring_util.h"
#include "third_party/blink/renderer/platform/fonts/mac/attributed_string_type_converter.h"
#include "ui/base/mojom/attributed_string.mojom-blink.h"
#endif

#if BUILDFLAG(IS_ARKWEB)
#include <sys/mman.h>

#include "third_party/ohos_ndk/includes/ohos_adapter/ohos_adapter_helper.h"
#endif

namespace blink {

constexpr int32_t MAX_SIZE = 8192;
constexpr int32_t ZERO_SIZE = 0;

ArkWebLocalFrameMojoHandlerExt::ArkWebLocalFrameMojoHandlerExt(blink::LocalFrame& frame)
    : LocalFrameMojoHandler(frame) {}

#if BUILDFLAG(IS_ARKWEB)
void ArkWebLocalFrameMojoHandlerExt::JavaScriptExecuteRequestExt(
    mojo::ScopedHandle handle_fd,
    const uint64_t scriptLength,
    bool wants_result,
    JavaScriptExecuteRequestCallback callback) {
  MojoPlatformHandle platform_handle;
  platform_handle.struct_size = sizeof(platform_handle);
  MojoUnwrapPlatformHandle(handle_fd.release().value(), nullptr,
                           &platform_handle);
  int fd = static_cast<int>(platform_handle.value);

  auto flowbufferAdapter =
      OHOS::NWeb::OhosAdapterHelper::GetInstance().CreateFlowbufferAdapter();
  if (!flowbufferAdapter) {
    LOG(ERROR) << "create flowbuffer adapter failed";
    close(fd);
    return;
  }
  char* ashmem = static_cast<char*>(flowbufferAdapter->CreateAshmemWithFd(
      fd, static_cast<size_t>(scriptLength + 1), PROT_READ));
  if (!ashmem) {
    close(fd);
    return;
  }
  String javascript = String::FromUTF8(ashmem);
  JavaScriptExecuteRequest(javascript, wants_result, std::move(callback));
  close(fd);
}
#endif

#if BUILDFLAG(ARKWEB_PRECOMPILE)
void ArkWebLocalFrameMojoHandlerExt::GenerateCodeCache(
    const String& url,
    const String& script,
    mojom::blink::CacheOptionsPtr cache_options,
    GenerateCodeCacheCallback callback) {
  ScriptState* script_state = ToScriptStateForMainWorld(frame_);
  V8CodeCacheUtils::CacheOptions options(cache_options->response_headers,
                                    cache_options->is_module,
                                    cache_options->is_top_level);
  V8CodeCacheUtils::CacheError err =
      V8CodeCacheUtils::GenerateCodeCache(script_state, url, script, options);
  std::move(callback).Run(static_cast<int32_t>(err));
}
#endif

#if BUILDFLAG(ARKWEB_BLANK_SCREEN_DETECTION)
void ArkWebLocalFrameMojoHandlerExt::DetectBlankScreen(
    const String& url,
    const Vector<double>& detectionTiming,
    const Vector<int32_t>& detectionMethods,
    int32_t contentfulNodesCountThreshold) {
  if (!frame_) {
    return;
  }

  auto blank_screen_detector = frame_->GetBlankScreenDetector(true);
  if (!blank_screen_detector) {
    return;
  }
  std::vector<double> detectionTimingVector;
  std::vector<int32_t> detectionMethodsVector;
  for (uint32_t i = 0; i < detectionTiming.size(); i++) {
    detectionTimingVector.emplace_back(detectionTiming[i]);
  }
  for (uint32_t i = 0; i < detectionMethods.size(); i++) {
    detectionMethodsVector.emplace_back(detectionMethods[i]);
  }
  blank_screen_detector->DetectBlankScreen(url, detectionTimingVector,
                                           detectionMethodsVector,
                                           contentfulNodesCountThreshold);
}
#endif

#if BUILDFLAG(ARKWEB_MENU) || BUILDFLAG(IS_ARKWEB_EXT)
void ArkWebLocalFrameMojoHandlerExt::GetImageFromCache(
    const String& url,
    LocalFrameMojoHandler::GetImageFromCacheCallback callback) {
  blink::Document* document = frame_->GetDocument();
  if (document == nullptr) {
    LOG(ERROR) << "getImageFromCache: document nullptr";
#if BUILDFLAG(ARKWEB_LOGGER_REPORT)
    LOG_FEEDBACK(ERROR) << "getImageFromCache: document nullptr";
#endif
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  DocumentLoader* loader = document->Loader();
  if (loader == nullptr) {
    LOG(ERROR) << "getImageFromCache: loader nullptr";
#if BUILDFLAG(ARKWEB_LOGGER_REPORT)
    LOG_FEEDBACK(ERROR) << "getImageFromCache: loader nullptr";
#endif
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  scoped_refptr<const SharedBuffer> resource_buffer =
#if BUILDFLAG(ARKWEB_MENU) || BUILDFLAG(IS_ARKWEB_EXT)
      loader->AsArkWebDocumentLoaderExt()->OnGetImageFromCache(url);
#else
      loader->OnGetImageFromCache(url);
#endif
  if (resource_buffer == nullptr) {
    LOG(ERROR) << "getImageFromCache: Get resource buffer null";
#if BUILDFLAG(ARKWEB_LOGGER_REPORT)
    LOG_FEEDBACK(ERROR) << "getImageFromCache: Get resource buffer null";
#endif
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  base::WritableSharedMemoryRegion region =
      base::WritableSharedMemoryRegion::Create(resource_buffer->size());
  if (!region.IsValid()) {
    LOG(ERROR) << "getImageFromCache: WritableSharedMemoryRegion create failed";
#if BUILDFLAG(ARKWEB_LOGGER_REPORT)
    LOG_FEEDBACK(ERROR)
        << "getImageFromCache: WritableSharedMemoryRegion create failed";
#endif
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  base::WritableSharedMemoryMapping mapping = region.Map();
  if (!mapping.IsValid()) {
    LOG(ERROR) << "getImageFromCache: WritableSharedMemoryRegion map failed";
#if BUILDFLAG(ARKWEB_LOGGER_REPORT)
    LOG_FEEDBACK(ERROR)
        << "getImageFromCache: WritableSharedMemoryRegion map failed";
#endif
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  bool finished = resource_buffer->GetBytes(mapping.GetMemoryAsSpan<uint8_t>());
  if (!finished) {
    LOG(ERROR)
        << "getImageFromCache: Get resource bytes unfinished, buffer size "
        << resource_buffer->size();
#if BUILDFLAG(ARKWEB_LOGGER_REPORT)
    LOG_FEEDBACK(ERROR)
        << "getImageFromCache: Get resource bytes unfinished, buffer size "
        << resource_buffer->size();
#endif
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  base::ReadOnlySharedMemoryRegion ro_region =
      base::WritableSharedMemoryRegion::ConvertToReadOnly(std::move(region));
  std::move(callback).Run(static_cast<uint32_t>(resource_buffer->size()),
                          std::move(ro_region));
  return;
}

static Element* GetElementByXPath(blink::Document* document, const String& xpath) {
  DummyExceptionStateForTesting exception_state;
  XPathResult* result = DocumentXPathEvaluator::evaluate(
      *document, xpath, document, nullptr,
      XPathResult::kFirstOrderedNodeType, ScriptValue(), exception_state);
  if (exception_state.HadException() || !result) {
    LOG(ERROR) << "ohmedia: failed to evaluate xpath: " << xpath;
    return nullptr;
  }
 
  Node* result_node = result->singleNodeValue(exception_state);
  if (!result_node) {
    LOG(ERROR) << "ohmedia: failed to get singleNodeValue";
    return nullptr;
  }
 
  Element* result_element = DynamicTo<Element>(result_node);
  if (!result_element) {
    LOG(ERROR) << "ohmedia: failed to convert to element";
    return nullptr;
  }
 
  return result_element;
}

static SkScalar WebCoreDoubleToSkScalar(double d) {
  return SkDoubleToScalar(std::isfinite(d) ? d : 0);
}

static SkM44 AffineTransformToSkM44(const AffineTransform& source) {
  //   INPUT           OUTPUT
  // | a c e |       | a c 0 e |
  // | b d f | ----> | b d 0 f |
  //                 | 0 0 1 0 |
  //                 | 0 0 0 1 |
  SkScalar a = WebCoreDoubleToSkScalar(source.A());
  SkScalar b = WebCoreDoubleToSkScalar(source.B());
  SkScalar c = WebCoreDoubleToSkScalar(source.C());
  SkScalar d = WebCoreDoubleToSkScalar(source.D());
  SkScalar e = WebCoreDoubleToSkScalar(source.E());
  SkScalar f = WebCoreDoubleToSkScalar(source.F());
  return SkM44(a, c, 0, e,   // row 0
               b, d, 0, f,   // row 1
               0, 0, 1, 0,   // row 2
               0, 0, 0, 1);  // row 3
}

static scoped_refptr<StaticBitmapImage> CreateElementSnapshot(const Element* element) {
    if (!element || !element->GetLayoutObject()) return nullptr;
    LocalFrameView* view = element->GetDocument().View();
    if (!view) return nullptr;
 
    view->UpdateAllLifecyclePhasesExceptPaint(
        DocumentUpdateReason::kJavaScript);
 
    LayoutObject* layout_object = element->GetLayoutObject();
    if (!layout_object) return nullptr;
 
    PaintLayer* layer = layout_object->EnclosingLayer();
    if (!layer) [[unlikely]] return nullptr;
 
    if (!layer->GetLayoutObject().IsStackingContext()) {
      layer = layer->AncestorStackingContext();
      if (!layer) return nullptr;
    }
 
    gfx::Rect absolute_bounding_box =
        layout_object->AbsoluteBoundingBoxRectIncludingDescendants();
 
    gfx::RectF bounding_box =
        layer->GetLayoutObject()
            .AbsoluteToLocalQuad(gfx::QuadF(gfx::RectF(absolute_bounding_box)))
            .BoundingBox();
 
    gfx::RectF cull_rect = bounding_box;
    cull_rect.Offset(
        gfx::Vector2dF(layer->GetLayoutObject().FirstFragment().PaintOffset()));
 
    OverriddenCullRectScope cull_rect_scope(
        *layer, CullRect(gfx::ToEnclosingRect(cull_rect)),
        /*disable_expansion*/ true);
    layout_object->GetDocument().Lifecycle().AdvanceTo(
        DocumentLifecycle::kInPaint);
    PaintRecordBuilder builder;
    PaintLayerPainter(*layer).Paint(builder.Context(),
                                    PaintFlag::kOmitCompositingInfo);
    layout_object->GetDocument().Lifecycle().AdvanceTo(
        DocumentLifecycle::kPaintClean);
    // params
    LocalFrame* frame = element->GetDocument().GetFrame();
    gfx::SizeF layout_size = bounding_box.size();
    gfx::Vector2dF paint_offset = bounding_box.OffsetFromOrigin();
    PropertyTreeState border_box_properties = layer->GetLayoutObject()
                                                  .FirstFragment()
                                                  .LocalBorderBoxProperties()
                                                  .Unalias();
    paint_offset +=
        gfx::Vector2dF(layer->GetLayoutObject().FirstFragment().PaintOffset());
 
    float layout_to_device_scale = frame->GetPage()->GetVisualViewport().Scale();
 
    gfx::SizeF device_size = gfx::ScaleSize(layout_size, layout_to_device_scale);
    AffineTransform transform;
    gfx::Vector2dF device_paint_offset =
        gfx::ScaleVector2d(paint_offset, layout_to_device_scale);
    transform.Translate(-device_paint_offset.x(), -device_paint_offset.y());
    transform.Scale(layout_to_device_scale);

    SkSurfaceProps surface_props;
    sk_sp<SkSurface> surface = SkSurfaces::Raster(
        SkImageInfo::MakeN32Premul(device_size.width(), device_size.height()),
        &surface_props);
    if (!surface)
      return nullptr;
 
    cc::SkiaPaintCanvas skia_paint_canvas(surface->getCanvas());
    skia_paint_canvas.concat(AffineTransformToSkM44(transform));
    builder.EndRecording(skia_paint_canvas, border_box_properties);
    scoped_refptr<StaticBitmapImage> static_image =
        UnacceleratedStaticBitmapImage::Create(surface->makeImageSnapshot());

    return static_image;
}

void ArkWebLocalFrameMojoHandlerExt::GetImageByXPath(
    int32_t taskid,
    const String& xpath,
    GetImageByXPathCallback callback) {
  LOG(INFO) << "GetImageByXPath xpath: " << xpath;
  size_t buffer_size;
  int32_t width;
  int32_t height;
  base::ReadOnlySharedMemoryRegion ro_region;
  if (!GetImageByXPathInner(xpath, ro_region, buffer_size, width, height)) {
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion(), 0, 0);
    return;
  }
 
  std::move(callback).Run(static_cast<uint32_t>(buffer_size), 
                          std::move(ro_region), 
                          static_cast<uint32_t>(width), 
                          static_cast<uint32_t>(height)); // xpath
}

bool ArkWebLocalFrameMojoHandlerExt::GetImageByXPathInner(
    const String& xpath,
    base::ReadOnlySharedMemoryRegion& ro_region,
    size_t& buffer_size,
    int32_t& width,
    int32_t& height)  {
  blink::Document* document = frame_->GetDocument();
  if (document == nullptr) {
    LOG(ERROR) << "ohmedia: document is nullptr";
    return false;
  }
 
  Element* element = GetElementByXPath(document, xpath);
  scoped_refptr<StaticBitmapImage> snapshot = CreateElementSnapshot(element);
  if (snapshot == nullptr) {
    LOG(ERROR) << "ohmedia: snapshot is nullptr";
    return false;
  }
 
  PaintImage image = snapshot->PaintImageForCurrentFrame();
  sk_sp<SkImage> sk_image = image.GetSwSkImage();
  if (sk_image == nullptr) {
    LOG(ERROR) << "ohmedia: sk_image is nullptr";
    return false;
  }
 
  SkImageInfo info = sk_image->imageInfo();
  info = info.makeColorType(kN32_SkColorType);
  buffer_size = info.computeMinByteSize();
  width = sk_image->width();
  height = sk_image->height();

  if (width <= ZERO_SIZE || height <= ZERO_SIZE || width > MAX_SIZE || height > MAX_SIZE) {
    LOG(ERROR) << "ohmedia: width or height is invalid";
    return false;
  }

  if (buffer_size == 0) {
    LOG(ERROR) << "ohmedia: buffer_size is zero";
    return false;
  }
 
  base::WritableSharedMemoryRegion region =
    base::WritableSharedMemoryRegion::Create(buffer_size);
  if (!region.IsValid()) {
    LOG(ERROR) << "ohmedia: WritableSharedMemoryRegion create failed";
    return false;
  }
 
  base::WritableSharedMemoryMapping mapping = region.Map();
  if (!mapping.IsValid()) {
    LOG(ERROR) << "ohmedia: WritableSharedMemoryRegion map failed";
    return false;
  }
 
  bool finished = sk_image->readPixels(info, mapping.memory(), info.minRowBytes(), 0, 0);
  if (!finished) {
    LOG(ERROR)
        << "ohmedia: Get resource bytes unfinished, buffer size "
        << buffer_size;
    return false;
  }
 
  ro_region = base::WritableSharedMemoryRegion::ConvertToReadOnly(std::move(region));
  return true;
}

void ArkWebLocalFrameMojoHandlerExt::GetAllImage(
    int32_t taskid,
    const String& url,
    LocalFrameMojoHandler::GetAllImageCallback callback) {
  blink::Document* document = frame_->GetDocument();
  if (document == nullptr) {
    LOG(ERROR) << "ohmedia: document nullptr";
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  DocumentLoader* loader = document->Loader();
  if (loader == nullptr) {
    LOG(ERROR) << "ohmedia: loader nullptr";
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  auto kurl = KURL(document->BaseURL(), url);
  scoped_refptr<const SharedBuffer> resource_buffer =
#if BUILDFLAG(ARKWEB_MENU) || BUILDFLAG(IS_ARKWEB_EXT)
  loader->AsArkWebDocumentLoaderExt()->OnGetImageFromCache(kurl.GetString());
#else
  loader->OnGetImageFromCache(kurl.GetString());
#endif
  if (resource_buffer == nullptr) {
    LOG(ERROR) << "ohmedia: Get resource buffer null";
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  base::WritableSharedMemoryRegion region =
      base::WritableSharedMemoryRegion::Create(resource_buffer->size());
  if (!region.IsValid()) {
    LOG(ERROR) << "ohmedia: WritableSharedMemoryRegion create failed";
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  base::WritableSharedMemoryMapping mapping = region.Map();
  if (!mapping.IsValid()) {
    LOG(ERROR) << "ohmedia: WritableSharedMemoryRegion map failed";
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  bool finished = resource_buffer->GetBytes(mapping.GetMemoryAsSpan<uint8_t>());
  if (!finished) {
    LOG(ERROR)
        << "ohmedia: Get resource bytes unfinished, buffer size "
        << resource_buffer->size();
    std::move(callback).Run(0, base::ReadOnlySharedMemoryRegion());
    return;
  }

  base::ReadOnlySharedMemoryRegion ro_region =
      base::WritableSharedMemoryRegion::ConvertToReadOnly(std::move(region));
  LOG(INFO) << "ohmedia:local frame mojom handler OnGetAllImage";
  std::move(callback).Run(static_cast<uint32_t>(resource_buffer->size()),
                          std::move(ro_region));
  return;
}

#endif  // BUILDFLAG(ARKWEB_MENU) || BUILDFLAG(IS_ARKWEB_EXT)
}  // namespace blink
