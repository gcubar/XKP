#ifndef XSS_IDIOM_H
#define XSS_IDIOM_H

#include <base.h>
#include <schema.h>

#include <xs/ast.h>
#include <xss/project.h>

namespace xkp{

struct ITranslator
	{
		virtual str generate(const param_list pl) = 0;
	};

//detail
struct already_rendered
  {
    already_rendered() : precedence(0)
    {
    }

    str     value;
    variant object;
    int precedence;
  };

enum assign_type
	{
		VANILLA,
		FN_CALL,
		XSS_RESOLVE
	};

struct assign_info
	{
		assign_info() : type(VANILLA), this_(false) {}

		assign_type type;
		str					data;
		bool				this_;
	};

struct capture_property
	{
		XSSProperty prop;
		str					xss;
	};

struct expression_renderer : expression_visitor
  {
    expression_renderer(XSSContext ctx, bool id_as_this = false);

    XSSProperty get_property(variant v);
    XSSProperty get_property(variant v, const str& name);
    XSSObject get_instance(variant v);
    XSSObject get_instance(variant v, const str& name);

    //expression_visitor
    virtual void push(variant operand, bool top);
    virtual void exec_operator(operator_type op, int pop_count, int push_count, bool top);

    virtual str resolve_assigner(variant operand, XSSObject instance, assign_info* ai);
    virtual str operand_to_string(variant operand, XSSObject parent = XSSObject(), int* prec = null);
    virtual str array_operation(str lopnd, str ropnd, operator_type op);
    virtual str get();

    assign_info* assigner;

    protected:
      typedef std::stack<variant> expr_stack;

      expr_stack        stack_;
      std::stringstream result_;
      XSSContext        ctx_;
			bool							capturing_property_;
			capture_property	capture_property_;

      void push_rendered(str value, int prec, variant object);
			str	 render_captured_property();
  };

//engine, this are the items that get translated
struct base_xss_args : ITranslator
  {
    base_xss_args();
    base_xss_args(const base_xss_args& other);
    base_xss_args(param_list_decl& args);

		//ITranslator
		virtual str generate(const param_list pl);

		//interface
		virtual str resolve_param(const param_decl& param) = 0;
    protected:
      param_list_decl args_;
  };

struct base_xss_expression : ITranslator
  {
    base_xss_expression();
    base_xss_expression(XSSContext ctx, expression& expr);

		//ITranslator
		virtual str generate(const param_list pl);

		private:
      expression expr_;
      XSSContext ctx_;
  };

struct base_xss_code : ITranslator, code_visitor
  {
    base_xss_code();
    base_xss_code(XSSContext ctx, code& code);

		//ITranslator
		virtual str generate(const param_list pl);

		//code_visitor
    virtual void if_(stmt_if& info);
    virtual void variable_(stmt_variable& info);
    virtual void for_(stmt_for& info);
    virtual void iterfor_(stmt_iter_for& info);
    virtual void while_(stmt_while& info);
    virtual void break_();
    virtual void continue_();
    virtual void return_(stmt_return& info);
    virtual void expression_(stmt_expression& info);
    virtual void dsl_(dsl& info);
    virtual void dispatch(stmt_dispatch& info);

    protected:
    	std::map<str, xs_type_info> vars_;
      code       code_;
      XSSContext ctx_;
			str				 result_;
			int				 indent_;

			void add_line(const str& line, bool dress_line = false);
			str	 get_indent_str();
      void render_code(code& cde, int indent);
	    void register_var(const str& name, const str& type);

      virtual str render_expression(expression& expr, XSSContext ctx);
  };

struct base_idiom : xss_idiom
  {
		base_idiom();
		base_idiom(const base_idiom& other);

		//xss_idiom
    virtual void set_context(XSSContext ctx);
    virtual str  resolve_separator(XSSObject lh = XSSObject());
    virtual str  translate_type(const str& type);
    virtual str  translate_type(schema *type);
    virtual bool allow_cast(schema *fts_type, schema *sec_type);
		public:
			XSSContext ctx_;
			void setTypes(DynamicArray da);
		protected:
			std::map<str, str> types_;
  };

//utils
struct idiom_utils
	{
    static str get_operator_str(operator_type op);
    static int get_operator_prec(operator_type op);

    template <typename T>
    static str render_expression(expression& expr, XSSContext ctx)
      {
        //deal with assigns
        operator_type op;
        if (expr.top_operator(op))
	        {
		        bool simple_assign = false;
		        switch(op)
			        {
				        case op_assign:
					        simple_assign = true;
                case op_plus_equal:
                case op_minus_equal:
                case op_mult_equal:
                case op_div_equal:
                case op_shift_right_equal:
                case op_shift_left_equal:
					        {
						        expression_splitter es(op);
						        expr.visit(&es);

                    T value_renderer(ctx);
						        es.right.visit(&value_renderer);

						        str value = value_renderer.get();

						        //get the assigner
                    T assign_renderer(ctx);
						        assign_info ai;
                    ai.data = value;
						        assign_renderer.assigner = &ai;

						        es.left.visit(&assign_renderer);

						        str assign = assign_renderer.get();

						        str result;
						        switch(ai.type)
							        {
								        case FN_CALL:
									        {
										        if (simple_assign)
											        result = assign + "(" + value + ")";
										        else
											        {
												        //we need to resolve the getter as well for *= operators
                                T getter(ctx);
												        es.left.visit(&getter);

												        //this is lame
                                str op_str = get_operator_str(op);

												        assert(op_str.size() > 1);
												        op_str.erase(op_str.end() - 1);

												        result = assign + "(" + getter.get() + " " + op_str + " " + value + ")";
											        }
										        break;
									        }

								        case VANILLA:
									        {
                            xs_type_info xstype = ctx->get_xss_type(assign);

                            if ((op == op_plus_equal || op == op_minus_equal) && xstype.is_array)
                              result = assign_renderer.array_operation(assign, value, op);
                            else if (simple_assign && xstype.is_array && !ai.data.empty())
                              result = ai.data;
                            else
                              result = assign + " " + get_operator_str(op) + " " + value;
										        break;
									        }
								        case XSS_RESOLVE:
									        {
                            T getter_(ctx);
										        es.left.visit(&getter_);
										        str getter = getter_.get();

										        if (!simple_assign)
											        {
                                str op_str = get_operator_str(op);
												        assert(op_str.size() > 1);
												        op_str.erase(op_str.end() - 1);

												        value = getter + " " + op_str + " " + value;
											        }

												    //lets find out if the getter is a single word (like "width") or a composite (like "object.width")
												    //if composite we'll get rid of the last accesor (width) to get the actual accesor

												    xss_idiom* idiom = ctx->idiom_;
												    str separator = idiom->resolve_separator();
												    size_t last_dot = getter.find_last_of(separator);
										        if (last_dot != str::npos)
											        {
												        size_t count = getter.size() - last_dot + 1;
												        getter.erase(getter.end() - count, getter.end());
											        }
										        else
													    getter = idiom->resolve_this(ctx);

										        //replace quotes, life is hard
										        for(size_t i = 0; i < assign.size(); i++)
											        {
												        if (assign[i] == 39)
													        assign[i] = '"';
											        }

										        //td: is all this really neccesary?
										        XSSProject project_ = ctx->project_;
										        xss_idiom* idiom_		= ctx->idiom_;
												    XSSContext context(new xss_code_context(project_, idiom_, fs::path()));
										        xss_code_context& ctx = *context.get();

										        XSSGenerator gen(new xss_generator(context));
										        project_->push_generator(gen);

										        project_->prepare_context(ctx, gen);

										        ctx.scope_->register_symbol("value",	value);
										        ctx.scope_->register_symbol("caller", getter);

										        result = project_->generate_xss(assign, gen);

										        project_->pop_generator();
										        break;
									        }
								        default:
									        assert(false); //trap use cases
							        }

						        return result;
					        }
                default: break;
			        }
	        }

        T er(ctx);
        expr.visit(&er);

        return er.get();
      }

		static str expr2str(expression& expr, XSSContext ctx);
	};

//utils, this is soon to be changed completely
struct code_type_resolver : code_visitor
	{
		code_type_resolver(XSSContext ctx)
      : vars_(ctx->vars_), ctx_(ctx), is_variant_(false) {}

		xs_type_info get();

		//code_visitor
    virtual void variable_(stmt_variable& info);
    virtual void return_(stmt_return& info);
    virtual void expression_(stmt_expression& info);
		virtual void if_(stmt_if& info);
    virtual void for_(stmt_for& info);
    virtual void iterfor_(stmt_iter_for& info);
    virtual void while_(stmt_while& info);

    virtual void break_()                           {}
    virtual void continue_()                        {}
    virtual void dsl_(dsl& info)                    {}
    virtual void dispatch(stmt_dispatch& info)      {}

		public:
			void register_var(const str& name, xs_type_info type, const str& str_type = str());
      void update_type(const str& name, xs_type_info type);
    public:
  		typedef std::map<str, xs_type_info> local_variables;
			local_variables&       vars_;
		private:
			XSSContext						 ctx_;
			bool									 is_variant_;

      void expression_type_resolver(expression& expr, XSSContext ctx);
	};

//expr_type_resolver
struct expr_type_resolver : expression_visitor
	{
    expr_type_resolver(XSSContext ctx);
		xs_type_info get();
		str type_name();
    variant top_stack();

		//expression_visitor
    virtual void push(variant operand, bool top);
		virtual void exec_operator(operator_type op, int pop_count, int push_count, bool top);

    private:
  		typedef std::map<str, xs_type_info> local_variables;
		  typedef std::stack<variant>		      expr_stack;

		  expr_stack				stack_;
		  bool							is_variant_;
		  operator_registry operators_;
		  local_variables&	local_;
		  XSSContext				ctx_;

			xs_type_info		result_xs_type_info;
			XSSObject       result_xss;

			xs_type_info resolve_type(variant var);
			XSSObject resolve_xss_type(variant var);

			bool resolve_variable(const str& id, xs_type_info &xstype);
			XSSObject	resolve_object(const variant v);
  };


//type info
template<typename T>
struct translator_schema : object_schema<T>
	{
    virtual void declare_base()
      {
        this->template implements<ITranslator>();
				this->template dynamic_function_<str>("generate", &T::generate);
      }

		virtual void declare()
			{
			}
	};

template <typename T>
struct base_idiom_schema : object_schema<T>
  {
    virtual void declare_base()
      {
        this->template implements<xss_idiom>();
        this->template writeonly_property<DynamicArray>("types", &T::setTypes);
      }
  };
} //namespace


#endif
