#include<vector>
#include"z3++.h" 
using namespace z3;
int main()
 { 
   context c;
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    expr conjecture = ((x >= 1) && (y < x + 3));
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