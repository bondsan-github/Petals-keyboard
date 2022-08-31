#pragma once

#include "..\headers\direct_2d.h"
#include "..\headers\hid_item.h"
#include "..\headers\text_d2d.h"

namespace hid
{
    struct hid_collection : public HIDP_LINK_COLLECTION_NODE
    {
            using identifier = ushort;
            using amount     = ushort;

            ushort        index    {};
            hid_item_type type     { hid_item_type::undefined };
            identifier    page     { 0     };
            identifier    usage    { 0     };
            bool          is_alias { false };
            link          origin   { 0     }; // parent  
            amount        siblings { 0     }; // children
            link          first    { 0     }; // child     
            link          next     { 0     }; // sibling 

            text          information {};

                
            void draw() { information.draw(); }
            void gather_information();

            bool operator == ( const hid_collection & in_collection ) const
            {
                bool result { false };

                if ( type     == hid_item_type { in_collection.CollectionType } &&
                     usage    == in_collection.LinkUsage                        &&
                     page     == in_collection.LinkUsagePage                    &&
                     origin   == in_collection.Parent                           &&
                     siblings == in_collection.NumberOfChildren                 &&
                     next     == in_collection.NextSibling                      &&
                     first    == in_collection.FirstChild                       &&
                     is_alias == in_collection.IsAlias 
                   ) result = true;

                return result;
            }

            hid_collection & operator = ( const node & in_collection )
            {
                //new_item.index    = index;
                type     = hid_item_type { in_collection.CollectionType };
                page     = in_collection.LinkUsagePage;
                usage    = in_collection.LinkUsage;
                is_alias = in_collection.IsAlias;
                siblings = in_collection.NumberOfChildren;

                origin   = in_collection.Parent;
                next     = in_collection.NextSibling;
                first    = in_collection.FirstChild;

                return * this;
            }

            hid_collection() {};
            hid_collection( hid_collection const & in_collection )
            {
                * this = in_collection;
            }
    };
}