#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\text_d2d.h"

#include <string>
#include <hidpi.h>

namespace hid
{
    class hid_collection : public HIDP_LINK_COLLECTION_NODE
    {
        private:

            //using identifier = ushort;
            //using amount     = ushort;

            ushort        index    { 0                        };
            hid_item_type type     { hid_item_type::undefined };
            ushort        page     { 0                        };
            ushort        usage    { 0                        };
            bool          is_alias { false                    };
            ushort        origin   { 0                        }; // parent  
            ushort        siblings { 0                        }; // children
            ushort        first    { 0                        }; // child     
            ushort        next     { 0                        }; // sibling 

            text          information;

            //hid_usages *  usages      {  };
                
        public:

            hid_collection();
            ~hid_collection();

            hid_collection( const hid_collection & in_copy );
            hid_collection( hid_collection && in_move ) noexcept;

            hid_collection & operator = ( const hid_collection & assign_copy );
            hid_collection & operator = ( hid_collection && assign_move ) noexcept;

            bool operator == ( const hid_collection & in_collection ) const;
            hid_collection & operator = ( const HIDP_LINK_COLLECTION_NODE & in_collection );

            void reset();
            
            ushort        get_index()          const { return index;    }
            hid_item_type get_type()           const { return type;     }
            ushort        get_page()           const { return page;     }
            ushort        get_usage()          const { return usage;    }
            bool          get_is_alias()       const { return is_alias; }
            ushort        get_origin()         const { return origin;   }
            ushort        get_sibling_amount() const { return siblings; }
            ushort        get_first()          const { return first;    }
            ushort        get_next()           const { return next;     }

            void set_page        ( const ushort in_page )              { page = in_page;                            }
            void set_information ( const std::wstring in_information ) { information.set_content( in_information ); }
            void set_origin      ( const ushort in_link )              { origin = in_link;                          }
            void set_is_alias    ( const bool in_is_alias )            { is_alias = in_is_alias;                    }
            void set_usage       ( const ushort in_usage )             { usage = in_usage; }

            void set_information();

            void draw() { information.draw(); }
            
            //void gather_information();
    };
}