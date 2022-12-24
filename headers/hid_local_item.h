#pragma once

#include "..\headers\direct_2d.h"
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

            bool   is_range        { false };
            range  usages          { range{ 0 , 0 } };
            ushort data_index      { 0 };
            range  datum_index     { range{ 0 , 0 } };

            bool   has_strings     { false };
            ushort string          { 0 }; // HidD_GetIndexedString        
            range  strings         { range{ 0 , 0 } };

            bool   has_designators { false };
            ushort designator      { 0 }; // describes body part recommended control. Index points to a designator in the Physical descriptor
            range  designators     { };

            text information {};

        public:

            //hid_local_item( void );
            //hid_local_item( const hid_local_item & copy );
            //hid_local_item( hid_local_item && move );
            //hid_local_item & operator = ( const hid_local_item & assignment );
            //hid_local_item & operator = ( const hid_local_item && assignment_move );
            //~hid_local_item( void );

            void set_information();

            ushort get_report_index()    { return report_index;    }
            ushort get_report_amount()   { return report_amount;   }
            ushort get_bit_field()       { return bit_field;       }
            bool   get_is_absolute()     { return is_absolute;     } // or relative
            ushort get_origin_usage()    { return origin_usage;    }
            ushort get_origin_page()     { return origin_page;     }
            bool   get_is_range()        { return is_range;        }
            range  get_usages_range()    { return usages;          }
            ushort get_data_index()      { return data_index;      }
            range  get_datum_index()     { return datum_index;     }
            bool   get_has_strings()     { return has_strings;     }
            ushort get_string_index()    { return string;          } // HidD_GetIndexedString        
            range  get_strings_range()   { return strings;         }
            long   get_strings_index_begin()   { return strings.begin; }
            long   get_strings_index_end()     { return strings.end;   }
            bool   get_has_designators()       { return has_designators; }
            ushort get_designator()            { return designator;      } // describes body part recommended control. Index points to a designator in the Physical descriptor
            range  get_designators_range()     { return designators;     }
            long   get_designators_range_begin()  { return designators.begin;     }
            long   get_designators_range_end()     { return designators.end;     }

            void set_report_index       ( ushort  in_report_index       ) { report_index    = in_report_index;    }
            void set_report_amount      ( ushort  in_report_amount      ) { report_amount   = in_report_amount;   }
            void set_bit_field          ( ushort  in_bit_field          ) { bit_field       = in_bit_field;       }
            void set_is_absolute        ( bool    in_is_absolute        ) { is_absolute     = in_is_absolute;     }
            void set_origin_usage       ( ushort  in_origin_usage       ) { origin_usage    = in_origin_usage;    }
            void set_origin_page        ( ushort  in_origin_page        ) { origin_page     = in_origin_page;     }
            void set_is_range           ( bool    in_is_range           ) { is_range        = in_is_range;        }
            void set_usages             ( range   in_usages             ) { usages          = in_usages;          }
            void set_usages_begin       ( ushort  in_usages_begin       ) { usages.begin    = in_usages_begin;    }
            void set_usages_end         ( ushort  in_usages_end         ) { usages.end      = in_usages_end;      }
            void set_data_index         ( ushort  in_data_index         ) { data_index      = in_data_index;      }
            void set_datum_indicies     ( range   in_datum_index        ) { datum_index     = in_datum_index;     }
            void set_datum_index_begin  ( ushort  in_datum_index_begin  ) { datum_index.begin = in_datum_index_begin; }
            void set_datum_index_end    ( ushort  in_datum_index_end    ) { datum_index.end   = in_datum_index_end;   }
            void set_has_strings        ( bool    in_has_strings        ) { has_strings     = in_has_strings;     }
            void set_string_index       ( ushort  in_string             ) { string          = in_string;          }
            void set_strings_range      ( range   in_strings            ) { strings         = in_strings;         }
            void set_strings_range_begin ( long in_range_begin ) { strings.begin = in_range_begin; }
            void set_strings_range_end  ( long in_range_end ) { strings.end = in_range_end; }
            void set_has_designators    ( bool    in_has_designators    ) { has_designators = in_has_designators; }
            void set_designator         ( ushort  in_designator         ) { designator      = in_designator;      }
            void set_designators_range  ( range   in_designators        ) { designators     = in_designators;     }
            void set_designators_range_begin ( long in_designators_range_begin ) { designators.begin = in_designators_range_begin; }
            void set_designators_range_end   ( long in_designators_range_end   ) { designators.end   = in_designators_range_end;   }
            //void set_information_string ( const wstring in_information_string ) { set_information( in_information_string ); }

            //hid_local_item & operator = ( const )
    };
}