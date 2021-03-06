#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "Env.h"
#include "Var.h"
#include "Parser.h"
#include "Loader.h"
#include <map>
#include <set>

class Interpreter
{
    private:
        int exitCode;
        bool needBreak;
        bool exit;
        Parser parser;
        Env* env;
        Loader *loader;

        std::set<std::string> paths;

        std::map<std::string, int> colors;
        bool IsColor(const std::string& color);
        void ReplaceString(std::string& subject, const std::string& search, const std::string& replace);
        std::string GetFolder(const std::string& path);
        std::string GetName(const std::string& path);
        std::string MakePath(const std::string& fileName);

        Var* CreateClass(Node node, Env *env);

        void MakeError(Var* var, const std::string& text);
        void MakeError(Var* var, const std::string& text, Node& node);
        Var* ApplyOperator(const std::string& op, Var* left, Var* middle, Var* right, Env *env);
        Var* Call(const std::string& func, std::vector<Var*>& args, Env *env, Var* caller = NULL);

        Var* Evaluate(Node node, Env* env, bool isClass = false, Var *caller = NULL);
    public:
        Interpreter();
        ~Interpreter();

        int ExitCode();
        bool NeedBreak();

        std::string OpenFile(const std::string& fileName);
        void AddToPath(const std::string& fileName, bool extract = true);

        bool Evaluate(const std::string& src, bool interactive);
        std::vector<char> Compile(const std::string& src);
};

#endif