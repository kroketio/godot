#include "browser.h"

#ifdef LINUXBSD_ENABLED
#include "platform/linuxbsd/wayland/display_server_wayland.h"
#include "platform/linuxbsd/x11/display_server_x11.h"
#endif

#ifdef MACOS_ENABLED
// #include "platform/macos/display_server_macos.h"
#include "platform/macos/rendering_context_driver_vulkan_macos.h"
#endif

#ifdef _WIN32
#include "platform/windows/display_server_windows.h"
#include "platform/windows/rendering_context_driver_vulkan_windows.h"
#endif

uint64_t WEBVIEW_VK_DEVICE = 0;
uint64_t WEBVIEW_VK_INSTANCE = 0;
uint64_t WEBVIEW_VK_PHYSICAL_DEVICE = 0;

void BrowserHelper::_bind_methods() {
  ClassDB::bind_static_method("BrowserHelper", D_METHOD("getVkInstance"), &BrowserHelper::getVkInstance);
  ClassDB::bind_static_method("BrowserHelper", D_METHOD("getVkDevice"), &BrowserHelper::getVkDevice);
  ClassDB::bind_static_method("BrowserHelper", D_METHOD("getVkPhysicalDevice"), &BrowserHelper::getVkPhysicalDevice);
}

uint64_t BrowserHelper::getVkDevice() {
  printf("BrowserHelper::getVkDevice() called\n");
  return WEBVIEW_VK_DEVICE;
}

uint64_t BrowserHelper::getVkPhysicalDevice() {
  printf("BrowserHelper::getVkPhysicalDevice() called\n");
  return WEBVIEW_VK_PHYSICAL_DEVICE;
}

uint64_t BrowserHelper::getVkInstance() {
  auto ds = DisplayServer::get_singleton();
  auto rs = RenderingDevice::get_singleton();
  auto ds_name = ds->get_name();

#ifdef LINUXBSD_ENABLED
  if(ds_name == "X11") {
    printf("BrowserHelper::getVkInstance() called: x11 driver\n");

    auto *rc = static_cast<RenderingContextDriverVulkanX11*>(rs->get_context_driver());
    return reinterpret_cast<uint64_t>(rc->instance);
  }
#endif

#ifdef WAYLAND_ENABLED  // @TODO: test wayland
  if(ds_name == "Wayland") {
    auto *rc = static_cast<RenderingContextDriverVulkanWayland*>(rs->get_context_driver());
    return reinterpret_cast<uint64_t>(rc->instance);
  } 
#endif

#ifdef MACOS_ENABLED
if(ds_name == "macOS") {
    printf("BrowserHelper::getVkInstance() called: MacOS vulkan driver\n");
    auto *rc = static_cast<RenderingContextDriverVulkanMacOS*>(rs->get_context_driver());
    return reinterpret_cast<uint64_t>(rc->instance);
}
#endif

#ifdef _WIN32
  if(ds_name == "Windows") {
    auto *rc = static_cast<RenderingContextDriverVulkanWindows*>(rs->get_context_driver());
    return reinterpret_cast<uint64_t>(rc->instance);
  } 
#endif

  printf("BrowserHelper: unknown display server '%s'\n", ds_name.utf8().get_data());
  return 0;
}

