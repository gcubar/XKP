
#include "stdafx.h"
#include <iostream>
#include <fstream>

#include <schema.h>
#include <serial.h>

#include <xs.h>
#include "xs/ast.h"
#include "xs/compiler.h"
#include "xs/debug_utils.h"
#include "xs/array.h"
#include "xs/xs_error.h"
#include "xs/runtime_error.h"
#include "text/text_renderer.h"
#include "gen/generator.h"
#include "xss/xss_parser.h"
#include "xss/xss_generator.h"
#include "xss/idiom.h"
#include "xss/project.h"
#include "xss/xss_error.h"
#include "xss/jscript.h"
#include "xss/c++.h"
#include "archive/xml_archive.h"

#include "boost/filesystem.hpp"

using namespace xkp;

class dump_visitor : public xss_visitor
{
  public:
    virtual void visit(const str& tag, const str& text, param_list* args)
      {
        std::cout << "-------------TAG: " + tag + "-------------" << '\n' << text << '\n' ;
      }
};

void dump_file(const str fname)
  {
    std::ifstream ifs(fname.c_str());

    str text;
    char buffer[1024];
    while(ifs.good())
      {
        ifs.getline(buffer, 1024);
        text += buffer;
        text += '\n';
      }

    dump_visitor visitor;
    xss_parser parser;
    parser.register_tag("xss:code");
    parser.register_tag("xss:e");

    parser.parse(text, &visitor);
  }

void dump_result(const str& text, code_context& context)
  {
    //td: never really used this, so I'mnot going to bother
    //xss_generator gen(context);
    //xss_parser parser;
    //parser.register_tag("xss:code");
    //parser.register_tag("xss:expression");
    //parser.register_tag("xss:quote");
    //
    //parser.parse(text, &gen);

    //std::cout << "-------------OUTPUT: " << '\n';
    //std::cout << gen.get();
  }

void print_error(param_list data, XSSProject project)
  {
    str id   = variant_cast<str>(data.get("id"), "");
    str desc = variant_cast<str>(data.get("desc"), "");

    std::cout << "Error [" << id << "] " << desc << '\n';

    for(size_t i = 0; i < data.size(); i++)
      {
        str name = data.get_name(i);
        if (name == "id" || name == "desc")
          continue;

        variant value = data.get(i);
        str     value_str;
        try
          {
            value_str = variant_cast<str>(value, str());
          }
        catch(type_mismatch)
          {
            value_str = "[cannot-resolve]";
          }

        std::cout << name << " = " << value_str << '\n';
      }

		std::cout << "\nFile:" << project->top_file() << '\n';
		std::cout << "\nLast Rendererd: \n\n" << project->last_rendered(5);
  }

int main(int argc, char* argv[])
  {
    char* fname = argv[1];
		std::ifstream ifs(fname);

    str text;
    char buffer[1024];
    while(ifs.good())
      {
        ifs.getline(buffer, 1024);
        text += buffer;
        text += '\n';
      }

    //setup types
    type_registry types;
    types.set_default_type(type_schema<xss_serial_object>());
    types.add_type("js-idiom", type_schema<js_idiom>());
    types.add_type("cpp-idiom", type_schema<cpp_idiom>());

    //read the project file,
    xml_read_archive project_file(text, &types, XML_RESOLVE_CLASS|XML_RESOLVE_ID);
    XSSProject project = project_file.get( type_schema<XSSProject>() );

		boost::filesystem::path base(fname);

		str path = base.parent_path().string();
		project->base_path(base.parent_path());

    bool succeeded = true;
    try
      {
        project->build();
      }
    catch(xs_error xse)
      {
        succeeded = false;
        print_error(xse.data, project);
      }
    catch(xss_error xsse)
      {
        succeeded = false;
        print_error(xsse.data, project);
      }
    catch(runtime_error rte)
      {
        succeeded = false;
        print_error(rte.data, project);
      }
		//catch(type_mismatch tm)
		//	{
    //    succeeded = false;
		//		param_list data;
		//		data.add("desc", str("Type mismatch"));
    //    print_error(data, project);
		//	}

    if (succeeded)
      {
        std::cout << "Build Succeeded, your project is at: " << project->output_path();
      }

    std::cin.get();

	return 0;
  }

