module;

#include < Windows.h >

#include < hidpi.h >
#include < hidsdi.h >

export module hid_device_module;

import std.core;

import globals;
import raw_device_module;

namespace hid
{
   using namespace std;

   export class hid_device : public raw_device
   {
      private: // variables

         using                      item_node         = HIDP_LINK_COLLECTION_NODE;

         HANDLE                     pointer{};
         HIDD_ATTRIBUTES            attributes{};
         HIDP_EXTENDED_ATTRIBUTES   attributes_extra{};
   };
}