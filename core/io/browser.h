#pragma once
#include <iostream>

#include "core/object/ref_counted.h"
#include "servers/rendering/renderer_rd/effects/copy_effects.h"
#include "servers/rendering/renderer_rd/storage_rd/texture_storage.h"
#include "servers/rendering/rendering_server_globals.h"
#include "servers/rendering_server.h"
#include "servers/display_server.h"


class BrowserHelper : public RefCounted {
  GDCLASS(BrowserHelper, RefCounted);

protected:
  static void _bind_methods();

public:
  static uintptr_t getVkInstance();
  BrowserHelper() {}
};
