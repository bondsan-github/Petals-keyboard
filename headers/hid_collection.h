#pragma once

#include "..\headers\direct_2d.h"
#include "..\headers\hid_item.h"
#include "..\headers\text_d2d.h"

//#include "..\headers\hid_usages.h"

namespace hid
{
    class hid_collection : public node
    {
        private:

            using identifier = ushort;
            using amount     = ushort;

            identifier    index    { 0                        };
            hid_item_type type     { hid_item_type::undefined };
            identifier    page     { 0                        };
            identifier    usage    { 0                        };
            bool          is_alias { false                    };
            link          origin   { 0                        }; // parent  
            amount        siblings { 0                        }; // children
            link          first    { 0                        }; // child     
            link          next     { 0                        }; // sibling 

            text          information { };

            //hid_usages *  usages      {  };
                
        public:

             hid_collection( void );
            ~hid_collection( void );

            identifier    get_index()          const { return index;    }
            hid_item_type get_type()           const { return type;     }
            identifier    get_page()           const { return page;     }
            identifier    get_usage()          const { return usage;    }
            bool          get_is_alias()       const { return is_alias; }
            link          get_origin()         const { return origin;   }
            amount        get_sibling_amount() const { return siblings; }
            link          get_first()          const { return first;    }
            link          get_next()           const { return next;     }

            void set_page        ( const identifier in_page    ) { page = in_page;                            }
            void set_information ( const string in_information ) { information.set_content( in_information ); }
            void set_origin      ( const link in_link )          { origin = in_link;                          }
            void set_is_alias    ( const bool in_is_alias )      { is_alias = in_is_alias;                    }
            void set_usage       ( const identifier in_usage )   { usage = in_usage; }

            void set_information();

            void draw() { information.draw(); }
            
            //void gather_information();

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

            /*hid_collection() {};
            hid_collection( hid_collection const & in_collection )
            {
                * this = in_collection;
            }*/
    };
}