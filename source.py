import subprocess
import time

if __name__ == '__main__':
    starttime = time.process_time()
    filename = input("Enter new filename without extension:")
    f = open("cpp_files/" + filename + ".cpp", "w")

    # writing cpp file for generic z3 commands
    # initial compulsory includes
    file_str = "#include<vector>\n#include\"z3++.h\" \nusing namespace z3;\n"
    # declaration of main and a context
    file_str += "int main()\n { \n   context c;\n"
    f.write(file_str)
    # declaration of variables
    file_str = "    expr x1 = c.int_const(\"x\");\n    expr y = c.int_const(\"y\");\n"
    # declaration of conjecture
    file_str += "    expr conjecture = ((x1 >= 1) && (y < x1 + 3));\n"
    file_str += "   expr_vector v(c); expr x(c);\n    float as = 1.0 * 5; \n"
    file_str += "   for (unsigned i = 0; i < 10; i++) {\n     std::stringstream x_name;\n     x_name << \"x_\" << i;\n     x = c.int_const(x_name.str().c_str());\n      v.push_back(x);\n}\n std::cout << v << std::endl;\n"
    f.write(file_str)
    # create solver and add conjecture
    file_str = "    solver s(c);\n    s.add(!conjecture);\n"
    # add switch for model
    file_str += "    std::cout << s.check() << \"\\n\";\n"
    # printing model
    file_str += "    model m = s.get_model();\n    for (unsigned i = 0; i < m.size(); i++) {\n        func_decl v = m[i];\n        assert(v.arity() == 0);\n        std::cout << v.name() << \" = \" << m.get_const_interp(v) << \"\\n\";\n    }\n}"
    f.write(file_str)

    f.close()
    print("Time = " + str(time.process_time() - starttime))

    cmd_str = "g++ -D_MP_INTERNAL -DNDEBUG -D_EXTERNAL_RELEASE  -std=c++17 -fvisibility=hidden -c -mfpmath=sse -msse -msse2 -O3 -Wno-unknown-pragmas -Wno-overloaded-virtual -Wno-unused-value -fPIC   -o compiled/" + filename + ".o  -Iz3/src/api -Iz3/src/api/c++ cpp_files/" + filename + ".cpp"
    cmd_split = cmd_str.split()
    process = subprocess.run(cmd_split, universal_newlines=True, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    if process.returncode == 0:
        compile_cmd = "g++ -o output/" + filename + " compiled/" + filename + ".o  z3/build/libz3.dylib -lpthread "
        compile_cmd_split = compile_cmd.split()
        process_com = subprocess.run(compile_cmd_split, universal_newlines=True, stderr=subprocess.PIPE,
                                     stdout=subprocess.PIPE)
        if process_com.returncode == 0:
            run_cmd = "./output/" + filename
            process_run = subprocess.run(run_cmd, universal_newlines=True, stderr=subprocess.PIPE,
                                         stdout=subprocess.PIPE)
            if process_run.returncode == 0:
                print(process_run.stdout)
            else:
                print(process_run.stderr)
        else:
            print(process_com.stderr)
    else:
        print(process.stderr)
