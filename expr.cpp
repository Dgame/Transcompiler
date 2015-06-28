#include <vector>

#include "CVisitor.hpp"
#include "TypeVisitor.hpp"
#include "Expression.hpp"
#include "Type.hpp"
#include "Declaration.hpp"
#include "Statement.hpp"

int main() {
    std::vector<std::unique_ptr<Expr>> exps;
    exps.emplace_back(new IntExpr(42)); // 41
    exps.emplace_back(new AddExpr(new FloatExpr(42), new IntExpr(23))); // 42 + 23
    exps.emplace_back(new AddExpr(new IntExpr(42), new SubExpr(new IntExpr(23), new IntExpr(1337)))); // 42 + 23 - 1337
    exps.emplace_back(new CharExpr('a'));
    exps.emplace_back(new StringExpr("abc"));
    exps.emplace_back(new CompareExpr(new IntExpr(42), new IntExpr(23), Compare::Lower)); // 42 < 23
    exps.emplace_back(new FloatExpr(3.14));

    TypeVisitor tv;
    exps[0].get()->accept(&tv);
    std::cout << "\t" << static_cast<u32_t>(tv.getType()) << std::endl; // Expected 4

    tv.types.clear();
    exps[1].get()->accept(&tv);
    std::cout << "\t" << static_cast<u32_t>(tv.getType()) << std::endl; // Expected 12

    tv.types.clear();
    exps[2].get()->accept(&tv);
    std::cout << "\t" << static_cast<u32_t>(tv.getType()) << std::endl; // Expected 5

    tv.types.clear();
    exps.back().get()->accept(&tv);
    std::cout << "\t" << static_cast<u32_t>(tv.getType()) << std::endl; // Expected 12

    CVisitor cv(std::cout);

    for (auto& exp : exps) {
        exp->accept(&cv);
        cv.getOutput() << ';' << std::endl;
    }

    std::unique_ptr<Decl> decl1(new VarDecl("test1", Type::Uint16, new AssignExpr(new IntExpr(42)))); // u16_t test = 42;
    decl1->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    std::unique_ptr<Decl> decl2(new VarDecl("test2", Type::Uint16, new AssignExpr(new CastExpr(Type::Uint16, new FloatExpr(4.2))))); // u16_t test = (u16_t) 4.2;
    decl2->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    std::unique_ptr<Decl> decl3(new VarDecl("test3", TypePointer::TypeString, new AssignExpr(new StringExpr("ene mene muh")))); // u16_t test = 42;
    decl3->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    std::unique_ptr<Decl> decl21(new VarDecl((VarDecl*) decl2.get(), new AssignExpr(new IntExpr(42))));
    decl21->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    ArrayExpr* arr = new ArrayExpr();
    arr->addExpr(new IntExpr(1));
    arr->addExpr(new IntExpr(2));
    arr->addExpr(new IntExpr(3));
    arr->addExpr(new IntExpr(4));

    std::unique_ptr<Decl> decl_4(new VarDecl("arr1", std::make_shared<TypeStaticArray>(Type::Float32, arr->getExpr()->count()), new AssignExpr(arr))); // u16_t test = 42;
    decl_4->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    const VarDecl* vd = (VarDecl*) decl_4.get();
    std::unique_ptr<Decl> decl22(new VarDecl("count", Type::Size_t, new AssignExpr(new PropertyExpr("length", new VarExpr(vd)))));
    decl22->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    PrintDecl* pd = new PrintDecl(new StringExpr("The answer of everything is %d"));
    pd->addExpr(new IntExpr(42));

    std::unique_ptr<Decl> decl4(pd);
    decl4->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    PrintDecl* pd2 = new PrintDecl();
    pd2->addExpr(new IntExpr(42));
    pd2->addExpr(new IntExpr(23));

    std::unique_ptr<Decl> decl5(pd2);
    decl5->accept(&cv);
    cv.getOutput() << ';' << std::endl;

    Expr* if_expr = new CompareExpr(new IntExpr(42), new IntExpr(23), Compare::Lower);
    Scope* if_scope = new Scope();

    PrintDecl* pd3 = new PrintDecl();
    pd3->addExpr(new IntExpr(42));
    pd3->addExpr(new IntExpr(23));

    if_scope->addInstruction(pd3);
    IfStmt* if_stmt1 = new IfStmt(if_expr, if_scope);

    std::unique_ptr<Stmt> stmt1(if_stmt1);
    stmt1->accept(&cv);

    FuncDecl* fd = new FuncDecl("test", Type::Bool);
    fd->addParameter(new Parameter("a", Type::Int16));
    Scope* sc = new Scope();
    sc->addInstruction(new Return(new BoolExpr(true)));
    fd->setScope(sc);

    std::unique_ptr<Decl> decl6(fd);
    decl6->accept(&cv);

    const VarDecl* vd1 = new VarDecl("item", Type::Uint16, new AssignExpr(new IntExpr(0)));
    const VarDecl* vd2 = new VarDecl(vd1, new AssignExpr(new AddExpr(new VarExpr(vd1), new IntExpr(1))));
    Stmt* for_stmt = new ForLoopStmt(vd1, new CompareExpr(new VarExpr(vd1), new IntExpr(4), Compare::Lower), vd2, new Scope());

    std::unique_ptr<Stmt> stmt2(for_stmt);
    stmt2->accept(&cv);

    const VarDecl* vd3 = new VarDecl("item", Type::Uint16, nullptr);
    Stmt* for_each_stmt = new ForEachLoopStmt(vd3, new VarExpr((VarDecl*) decl_4.get()), new Scope());

    std::unique_ptr<Stmt> stmt3(for_each_stmt);
    stmt3->accept(&cv);
}
