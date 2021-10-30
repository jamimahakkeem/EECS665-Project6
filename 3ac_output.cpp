#include "ast.hpp"

namespace cshanty{

IRProgram * ProgramNode::to3AC(TypeAnalysis * ta){
	IRProgram * prog = new IRProgram(ta);
	for (auto global : *myGlobals){
		global->to3AC(prog);
	}
	return prog;
}

void FnDeclNode::to3AC(IRProgram * prog){
	Procedure *proc = new Procedure(prog,this->ID()->getName());
	for (auto formal: *myFormals)
	{
		formal ->to3AC(proc);
	}

	for (auto stmt: *myBody)
	{
		stmt ->to3AC(proc);
	}
}

void FnDeclNode::to3AC(Procedure * proc){
	//This never needs to be implemented,
	// the function only exists because of
	// inheritance needs (A function declaration
	// never occurs within another function)
	throw new InternalError("FnDecl at a local scope");
}

void FormalDeclNode::to3AC(IRProgram * prog){
	//This never needs to be implemented,
	// the function only exists because of
	// inheritance needs (A formal never
	// occurs at global scope)
	throw new InternalError("Formal at a global scope");
}

void FormalDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = ID()->getSymbol();
	assert(sym != nullptr);
	prog->gatherGlobal(sym);
}

void RecordTypeDeclNode::to3AC(IRProgram * prog){
	TODO(Implement me)
}

void RecordTypeDeclNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

Opd * IntLitNode::flatten(Procedure * proc){
	const DataType * type = proc->getProg()->nodeType(this);
	return new LitOpd(std::to_string(myNum), 8);
}

Opd * StrLitNode::flatten(Procedure * proc){
	Opd * res = proc->getProg()->makeString(myStr);
	return res;
}

Opd * TrueNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * FalseNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * AssignExpNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * LValNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * CallExpNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * NegNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * NotNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * PlusNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, ADD64, e1, e2);
	proc->addQuad(quad);
	return temp;
}

Opd * MinusNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, SUB64, e1, e2);
	proc->addQuad(quad);
	return temp;
}

Opd * TimesNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, MULT64, e1, e2);
	proc->addQuad(quad);
	return temp;
}

Opd * DivideNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, DIV64, e1, e2);
	proc->addQuad(quad);
	return temp;
}

Opd * AndNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, DIV64, e1, e2);
	proc->addQuad(quad);
	return temp;
}

Opd * OrNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * EqualsNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * NotEqualsNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * LessNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * GreaterNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * LessEqNode::flatten(Procedure * proc){
	TODO(Implement me)
}

Opd * GreaterEqNode::flatten(Procedure * proc){
	TODO(Implement me)
}

void AssignStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void PostIncStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void PostDecStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void ReceiveStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void ReportStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void IfStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void IfElseStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void WhileStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void CallStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void ReturnStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void VarDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = ID()->getSymbol();
	assert(sym != nullptr);
	proc->gatherLocal(sym);
}

void VarDeclNode::to3AC(IRProgram * prog){
	SemSymbol * sym = ID()->getSymbol();
	assert(sym != nullptr);
	prog->gatherGlobal(sym);
}

Opd * IndexNode::flatten(Procedure * proc){
	TODO(Implement me)
}

//We only get to this node if we are in a stmt
// context (DeclNodes protect descent)
Opd * IDNode::flatten(Procedure * proc){
	TODO(Implement me)
}

}
