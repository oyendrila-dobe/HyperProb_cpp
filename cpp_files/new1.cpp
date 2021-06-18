#include<vector>
#include"z3++.h" 
using namespace z3;
int main()
 { 
   context c;
    expr x1 = c.int_const("x");
    expr y = c.int_const("y");
    expr conjecture = ((x1 >= 1) && (y < x1 + 3));
   expr_vector v(c); expr x(c);
   float as = 1.0 * 5;
   if (as >= 5.0)
       std::cout << "Yes \n";
   else
       std::cout << "No \n";
   for (unsigned i = 0; i < 10; i++) {
     std::stringstream x_name;
     x_name << "x_" << i;
     x = c.int_const(x_name.str().c_str());
      v.push_back(x);
}
 std::cout << v << std::endl;
    solver s(c);
    s.add(!conjecture);
    std::cout << s.check() << "\n";
    model m = s.get_model();
    for (unsigned i = 0; i < m.size(); i++) {
        func_decl v = m[i];
        assert(v.arity() == 0);
        std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
}