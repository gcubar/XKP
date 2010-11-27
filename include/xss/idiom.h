#ifndef XSS_IDIOM_H
#define XSS_IDIOM_H

#include <base.h>
#include <schema.h>

#include <xs/ast.h>
#include <xss/project.h>

namespace xkp{

//this is more like a test idiom at the moment, under construction

//a basic parameter declaration generator
struct base_xss_args
  {
    base_xss_args();
    base_xss_args(const base_xss_args& other);
    base_xss_args(param_list_decl& args);
    
    str generate();

    protected:
      param_list_decl args_;
  };

struct base_xss_expression
  {
    base_xss_expression();
    base_xss_expression(XSSContext ctx, expression& expr);
  
    str generate();    
    private:
      expression expr_;
      XSSContext ctx_;
  };

typedef reference<base_xss_expression> xssExpression;

struct base_xss_code
  {
    base_xss_code();
    base_xss_code(XSSContext ctx, code& code);
  
    str generate();    
    private:
      code       code_;
      XSSContext ctx_;
  };

typedef reference<base_xss_code> xssCode;

//this represents a pice of executable code that will be turned into text
//the way it is implemented you *must* subclass base_xss_function, could make it a 
//proper interface, i guess.
struct base_xss_function
  {
    public:
      base_xss_function();
      base_xss_function(const code& code, const str& name, XSSContext ctx, param_list_decl& args);
    public:
      str generate_code();
    public:
      code            code_;
      str             name_;
      base_xss_args   args_;
      XSSContext      ctx_;
  };

typedef reference<base_xss_function> xssFunction;

//implementing the interface, you can subclass this to do your own processing, 
//the aim is that you dont have to
struct base_idiom : xss_idiom
  {
    base_idiom()                         : id_as_this_(false), force_this_(true)                  {}    
    base_idiom(const base_idiom& other)  : ctx_(other.ctx_),id_as_this_(false), force_this_(true) {}
  
    virtual void    set_context(XSSContext ctx);
    virtual variant process_method(DynamicObject instance, xs_method& mthd);
    virtual variant process_event(DynamicObject instance, const str& event_name, xs_event& ev);
    virtual variant process_code(code& cde, DynamicObject this_);
    virtual variant process_expression(expression expr, DynamicObject this_);
    virtual str     resolve_this(XSSContext ctx);
    
    protected:
      std::vector<xssFunction> functions_;
      XSSContext               ctx_;
    public:  
      bool id_as_this_;
      bool force_this_;
  };


//type info
struct base_xss_args_schema : object_schema<base_xss_args>  
  {
    virtual void declare()
      {
        method_<str, 0>("generate", &base_xss_args::generate);
      }
  };

struct base_xss_function_schema : object_schema<base_xss_function>  
  {
    virtual void declare()
      {
        property_("name",  &base_xss_function::name_);
        static_field("args", &base_xss_function::args_);
        
        method_<str, 0>("generate_code", &base_xss_function::generate_code);
      }
  };

struct base_idiom_schema : object_schema<base_idiom>  
  {
    virtual void declare()
      {
        implements<xss_idiom>();
        property_("id_as_this", &base_idiom::id_as_this_);
        property_("force_this", &base_idiom::force_this_);
      }
  };
  
struct base_xss_code_schema : object_schema<base_xss_code>  
  {
    virtual void declare()
      {
        method_<str, 0>("generate", &base_xss_code::generate);
      }
  };
  
struct base_xss_expression_schema : object_schema<base_xss_expression>  
  {
    virtual void declare()
      {
        method_<str, 0>("generate", &base_xss_expression::generate);
      }
  };
  

register_complete_type(base_xss_expression, base_xss_expression_schema);
register_complete_type(base_xss_args,       base_xss_args_schema);
register_complete_type(base_xss_code,       base_xss_code_schema);
register_complete_type(base_xss_function,   base_xss_function_schema);
register_complete_type(base_idiom,          base_idiom_schema);

} //namespace


#endif