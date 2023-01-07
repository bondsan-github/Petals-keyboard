#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\text_d2d.h"

#include "..\headers\hid_item.h"
#include "..\headers\hid_collection.h"

namespace hid
{
    class hid_local_item : public hid_collection
    {
        private:

            ushort report_index    { 0 };
            ushort report_amount   { 0 };

            ushort bit_field       { 0 };

            bool   is_absolute     { false }; // or relative

            ushort origin_usage    { 0 };
            ushort origin_page     { 0 };

            bool       is_range         { false };
            hid_range  usages           { hid_range{ 0 , 0 } };
            ushort     data_identifier  { 0 };
            hid_range  data_identifiers { hid_range{ 0 , 0 } };

            bool       has_strings      { false };
            ushort     string           { 0 }; // string_identifier // HidD_GetIndexedString        
            hid_range  strings          { hid_range{ 0 , 0 } }; // string_identifiers

            bool       has_designators  { false };
            ushort     designator       { 0 }; // describes body part recommended control. Index points to a designator in the Physical descriptor
            hid_range  designators      { }; // // designators_identifiers

            text information;

        public:

            hid_local_item();

            hid_local_item( const HIDP_BUTTON_CAPS & button_capabilities ) {}

            hid_local_item( const hid_local_item & in_copy );
            hid_local_item( hid_local_item && in_move ) noexcept;
            
            ~hid_local_item();

            hid_local_item & operator = ( const hid_local_item & assign_copy );
            hid_local_item & operator = ( hid_local_item && assign_move ) noexcept;

            void reset();

            void set_information();

            ushort get_report_index()            const { return report_index;    }
            ushort get_report_amount()           const { return report_amount;   }
            ushort get_bit_field()               const { return bit_field;       }
            bool   get_is_absolute()             const { return is_absolute;     } // or relative
            ushort get_origin_usage()            const { return origin_usage;    }
            ushort get_origin_page()             const { return origin_page;     }
            bool   get_is_range()                const { return is_range;        }
            hid_range  get_usages_range()            const { return usages;          }
            ushort get_data_identifier()         const { return data_identifier; }
            hid_range  get_data_identifiers()        const { return data_identifiers; }
            bool   get_has_strings()             const { return has_strings;     }
            ushort get_string_index()            const { return string;          } // HidD_GetIndexedString        
            hid_range  get_strings_range()           const { return strings;         }
            long   get_strings_index_begin()     const { return strings.begin; }
            long   get_strings_index_end()       const { return strings.end;   }
            bool   get_has_designators()         const { return has_designators; }
            ushort get_designator()              const { return designator;      } // describes body part recommended control. Index points to a designator in the Physical descriptor
            hid_range  get_designators_range()       const { return designators;     }
            long   get_designators_range_begin() const { return designators.begin;   }
            long   get_designators_range_end()   const { return designators.end;     }

            void set_report_index        ( const ushort  &in_report_index       ) { report_index     = in_report_index;     }
            void set_report_amount       ( const ushort & in_report_amount      ) { report_amount    = in_report_amount;    }
            void set_bit_field           ( const ushort & in_bit_field          ) { bit_field        = in_bit_field;        }
            void set_is_absolute         ( const bool & in_is_absolute        ) { is_absolute      = in_is_absolute;      }
            void set_origin_usage        ( const ushort & in_origin_usage       ) { origin_usage     = in_origin_usage;     }
            void set_origin_page         ( const ushort & in_origin_page        ) { origin_page      = in_origin_page;      }
            void set_is_range            ( const bool & in_is_range           ) { is_range         = in_is_range;         }
            void set_usages              ( const hid_range & in_usages             ) { usages           = in_usages;           }
            void set_usages_begin        ( const ushort & in_usages_begin       ) { usages.begin     = in_usages_begin;     }
            void set_usages_end          ( const ushort & in_usages_end         ) { usages.end       = in_usages_end;       }
            void set_data_identifier     ( const ushort & in_data_identifier    ) { data_identifier  = in_data_identifier;  }
            void set_data_identifiers    ( const hid_range & in_data_identifiers   ) { data_identifiers = in_data_identifiers; }
            void set_data_identifiers_begin  ( const ushort & in_data_identifiers_begin  ) { data_identifiers.begin = in_data_identifiers_begin; }
            void set_data_identifiers_end    ( const ushort & in_data_identifiers_end    ) { data_identifiers.end   = in_data_identifiers_end;   }
            void set_has_strings         ( const bool & in_has_strings        ) { has_strings      = in_has_strings;      }
            void set_string_index        ( const ushort & in_string             ) { string           = in_string;           }
            void set_strings_range       ( const hid_range & in_strings            ) { strings          = in_strings;          }
            void set_strings_range_begin ( const long & in_range_begin           ) { strings.begin    = in_range_begin;      }
            void set_strings_range_end   ( const long & in_range_end             ) { strings.end      = in_range_end;        }
            void set_has_designators     ( const bool & in_has_designators    ) { has_designators  = in_has_designators;  }
            void set_designator          ( const ushort & in_designator         ) { designator       = in_designator;       }
            void set_designators_range   ( const hid_range & in_designators        ) { designators      = in_designators;      }
            void set_designators_range_begin ( const long & in_designators_range_begin ) { designators.begin = in_designators_range_begin; }
            void set_designators_range_end   ( const long & in_designators_range_end   ) { designators.end   = in_designators_range_end;   }
            //void set_information_string ( const wstring in_information_string ) { set_information( in_information_string ); }
    };
}