#include "browser.h"

#ifdef LINUXBSD_ENABLED
#include "platform/linuxbsd/wayland/display_server_wayland.h"
#include "platform/linuxbsd/x11/display_server_x11.h"
#endif

#ifdef _WIN32
#include "platform/windows/display_server_windows.h"
#include "platform/windows/rendering_context_driver_vulkan_windows.h"
#endif

void BrowserHelper::_bind_methods() {
  ClassDB::bind_static_method("BrowserHelper", D_METHOD("getVkInstance"), &BrowserHelper::getVkInstance);
}

uintptr_t BrowserHelper::getVkInstance() {
  auto ds = DisplayServer::get_singleton();
  auto rs = RenderingDevice::get_singleton();
  auto ds_name = ds->get_name();

#ifdef LINUXBSD_ENABLED
  if(ds_name == "X11") {
    auto *rc = static_cast<RenderingContextDriverVulkanX11*>(rs->get_context_driver());
    return reinterpret_cast<uintptr_t>(rc->instance);
  } 
#ifdef WAYLAND_ENABLED
  if(ds_name == "Wayland") {
    auto *rc = static_cast<RenderingContextDriverVulkanWayland*>(rs->get_context_driver());
    return reinterpret_cast<uintptr_t>(rc->instance);
  } 
#endif
#endif

#ifdef _WIN32
  if(ds_name == "Windows") {
    auto *rc = static_cast<RenderingContextDriverVulkanWindows*>(rs->get_context_driver());
    return reinterpret_cast<uintptr_t>(rc->instance);
  } 
#endif
  else {
    printf("BrowserHelper: unknown display server '%s'\n", ds_name.utf8().get_data());
  }
  return 0;
}

