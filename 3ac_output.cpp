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
	Opd* e = exp->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new UnaryOpQuad(temp, NEG64, e);
	proc->addQuad(quad);
	return temp;
}

Opd * NotNode::flatten(Procedure * proc){
	Opd* e = exp->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new UnaryOpQuad(temp, NOT8, e);
	proc->addQuad(quad);
	return temp;
}

Opd * PlusNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, ADD64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * MinusNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, SUB64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * TimesNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, MULT64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * DivideNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, DIV64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * AndNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, AND64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * OrNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, OR64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * EqualsNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, EQ64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * NotEqualsNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, NEQ64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * LessNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, LT64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * GreaterNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, GT64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * LessEqNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, LTE64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
}

Opd * GreaterEqNode::flatten(Procedure * proc){
	Opd* lhs = e1->flatten(proc);
	Opd* rhs = e2->flatten(proc);
	Opd* temp = proc->makeTmp(this->getWidth());
	Quad * quad = new BinOpQuad(temp, GTE64, lhs, rhs);
	proc->addQuad(quad);
	return temp;
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
	Opd* condition = myCond->flatten(proc);
	Label * after = proc->makeLabel();
	Quad condQuad = new IfzQuad(condition, after);
	Quad nop = new NopQuad();
	nop->addLabel(after);
	proc -> addQuad(condQuad);
	proc -> addQuad(nop);
	myBody -> to3AC(proc);


}

void IfElseStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void WhileStmtNode::to3AC(Procedure * proc){
	Quad nop1 = new NopQuad();
	Label * head = proc->makeLabel();
	nop1->addLabel(head);
	proc -> addQuad(nop1);

	Quad nop2 = new NopQuad();
	Label * after = proc->makeLabel();
	nop2->addLabel(after);
	proc -> addQuad(nop2);

	Opd* condition = myCond->flatten(proc);
	Quad condQuad = new IfzQuad(condition, after);
	proc -> addQuad(condQuad);
	myBody -> to3AC(proc);
}

void CallStmtNode::to3AC(Procedure * proc){
	TODO(Implement me)
}

void ReturnStmtNode::to3AC(Procedure * proc){


	Opd* stmt = myExp->flatten(proc);
	Quad return = new SetRetQuad(stmt);
	proc -> addQuad(return);

	Label * function_end = proc->makeLabel();
	Quad end = new GotoQuad(function_end);
	proc -> addQuad(end);

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
