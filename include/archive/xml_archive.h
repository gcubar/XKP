
#ifndef XML_ARCHIVE_H
#define XML_ARCHIVE_H

#include <serial.h>
#include <tinyxml.h>

namespace xkp
{
  struct xml_writer : writer
    {
      xml_writer(TiXmlElement* node, type_registry* types) : node_(node), types_(types) {}
      
      //writer
      virtual void          attribute(const str& name, const variant& value);
      virtual Writer        create_node(const str& name); 
      virtual WriteIterator create_iterator(const str& name, schema* type = null); 

      TiXmlElement*  node_;
      type_registry* types_;
    };

  struct xml_write_archive : base_write_archive
    {
      xml_write_archive(type_registry* types = null);

      str result() {return result_;}
      
      //write archive
      virtual Writer create_root(); 
      virtual void   save(const variant& what);
      
      private:
        str           result_;      
        TiXmlDocument doc_;
    };

const size_t XML_RESOLVE_ID    = 0x01;
const size_t XML_RESOLVE_CLASS = 0x02;

struct xml_reader : reader
    {
      xml_reader(TiXmlElement* node, type_registry* types, size_t options) : 
        node_(node), 
        types_(types),
        options_(options)
        {
        }
      
      virtual bool         attribute(const str& name, schema* type, variant& result);
      virtual Reader       create_node(const str& name);
      virtual ReadIterator create_iterator(const str& name, schema* type); 
      virtual void         visit(reader_visitor* visitor); 

      private:
        TiXmlElement*  node_;
        type_registry* types_;
        int            options_;
	      variant attribute_value(const TiXmlAttribute* attr);
    };

  struct xml_read_archive : base_read_archive
    {
      xml_read_archive(const str& xml, type_registry* types = null, size_t options = 0);
      
      protected:
        virtual Reader create_root(); 
      private:
        TiXmlDocument doc_;
        size_t        options_;
    };

}

#endif